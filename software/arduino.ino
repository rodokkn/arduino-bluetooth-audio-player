#include <LovyanGFX.hpp>
#include "BluetoothA2DPSink.h"

// ================= DISPLAY CONFIG =================
class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789 _panel_instance;
  lgfx::Bus_SPI      _bus_instance;

public:
  LGFX(void) {
    {
      auto cfg = _bus_instance.config();
      cfg.spi_host = VSPI_HOST;
      cfg.spi_mode = 3;
      cfg.freq_write = 40000000;
      cfg.freq_read  = 16000000;
      cfg.spi_3wire  = false;
      cfg.use_lock   = true;
      cfg.dma_channel = 1;
      cfg.pin_sclk = 18;
      cfg.pin_mosi = 23;
      cfg.pin_miso = -1;
      cfg.pin_dc   = 2;
      _bus_instance.config(cfg);
      _panel_instance.setBus(&_bus_instance);
    }

    {
      auto cfg = _panel_instance.config();
      cfg.pin_cs   = -1;
      cfg.pin_rst  = 4;
      cfg.pin_busy = -1;
      cfg.memory_width  = 240;
      cfg.memory_height = 240;
      cfg.panel_width   = 240;
      cfg.panel_height  = 240;
      cfg.offset_x = 0;
      cfg.offset_y = 0;
      cfg.readable = false;
      cfg.invert   = false;
      cfg.rgb_order = false;
      cfg.bus_shared = false;
      _panel_instance.config(cfg);
    }

    setPanel(&_panel_instance);
  }
};

// ================= GLOBAL OBJECTS =================
LGFX tft;
BluetoothA2DPSink a2dp_sink;

// ================= PIN DEFINITIONS =================
const int buttonPin = 13;
const int potentiometerPin = 34;

// ================= STATE VARIABLES =================
unsigned long lastPressTime = 0;
const unsigned long pressTimeout = 300;
int pressCount = 0;
bool playing = false;

int currentVolume = 50;
const int maxVolume = 130;
bool buttonPressed = false;

// ================= METADATA =================
String currentSong   = "Unknown";
String currentArtist = "Unknown";
String currentAlbum  = "Unknown";

// ================= ANIMATION =================
int heartX = 0;
int heartY = 200;
int heartSpeed = 5;

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_WHITE);
  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);

  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(potentiometerPin, INPUT);

  i2s_pin_config_t i2s_config = {
    .mck_io_num = I2S_PIN_NO_CHANGE,
    .bck_io_num = 26,
    .ws_io_num  = 25,
    .data_out_num = 22,
    .data_in_num  = I2S_PIN_NO_CHANGE
  };

  a2dp_sink.set_pin_config(i2s_config);
  a2dp_sink.set_avrc_metadata_callback(avrc_metadata_callback);
  a2dp_sink.start("Bluetooth_Audio_Device");

  drawTitle();
  updateSongInfo();
  updateVolumeDisplay();
}

// ================= CALLBACK =================
void avrc_metadata_callback(uint8_t id, const uint8_t* text) {
  String data = String((const char*)text);

  if (id == ESP_AVRC_MD_ATTR_TITLE)  currentSong = data;
  if (id == ESP_AVRC_MD_ATTR_ARTIST) currentArtist = data;
  if (id == ESP_AVRC_MD_ATTR_ALBUM)  currentAlbum = data;

  updateSongInfo();
}

// ================= UI FUNCTIONS =================
void drawTitle() {
  tft.fillRect(0, 0, 240, 40, TFT_WHITE);
  tft.setCursor(10, 10);
  tft.setTextColor(TFT_GREEN, TFT_WHITE);
  tft.print("Bluetooth Audio");
}

void updateSongInfo() {
  tft.fillRect(10, 50, 220, 60, TFT_WHITE);
  tft.setCursor(10, 50);
  tft.setTextColor(TFT_BLACK, TFT_WHITE);
  tft.printf("Song: %s\n", currentSong.c_str());
  tft.setCursor(10, 90);
  tft.printf("Artist: %s", currentArtist.c_str());
}

void updateVolumeDisplay() {
  tft.fillRect(10, 120, 220, 40, TFT_WHITE);
  tft.setCursor(10, 130);
  tft.printf("Volume: %d/13", currentVolume / 10);
}

// ================= INPUT HANDLING =================
void handleButtonPress() {
  if (pressCount == 1) {
    playing ? a2dp_sink.pause() : a2dp_sink.play();
    playing = !playing;
  }
  else if (pressCount == 2) a2dp_sink.next();
  else if (pressCount == 3) a2dp_sink.previous();
}

// ================= VOLUME CONTROL =================
void adjustVolume() {
  int pot = analogRead(potentiometerPin);
  int scaled = map(pot, 0, 4095, 0, 10);
  int newVolume = scaled * (maxVolume / 10);

  if (newVolume != currentVolume) {
    currentVolume = newVolume;
    a2dp_sink.set_volume(currentVolume);
    updateVolumeDisplay();
  }
}

// ================= ANIMATION =================
void drawHeart(int x, int y, uint16_t color) {
  tft.fillCircle(x, y, 10, color);
  tft.fillCircle(x + 20, y, 10, color);
  tft.fillTriangle(x - 10, y, x + 30, y, x + 10, y + 30, color);
}

void animateHeart() {
  drawHeart(heartX, heartY, TFT_WHITE);
  heartX += heartSpeed;

  if (heartX < 0 || heartX > tft.width() - 30)
    heartSpeed = -heartSpeed;

  drawHeart(heartX, heartY, TFT_RED);
}

// ================= LOOP =================
void loop() {
  bool btn = digitalRead(buttonPin) == LOW;
  unsigned long now = millis();

  if (btn && !buttonPressed) {
    buttonPressed = true;
    lastPressTime = now;
    pressCount++;
  }

  if (!btn && buttonPressed)
    buttonPressed = false;

  if (now - lastPressTime > pressTimeout && pressCount > 0) {
    handleButtonPress();
    pressCount = 0;
  }

  adjustVolume();
  animateHeart();
  delay(50);
}
