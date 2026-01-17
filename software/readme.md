# Arduino Bluetooth Audio Player

This folder contains the Arduino firmware used in the Bluetooth Audio Player project.

## Main Sketch
- **arduino.ino**
  - Handles Bluetooth A2DP audio streaming
  - Controls audio playback (play / pause / next / previous)
  - Reads volume level via potentiometer
  - Displays song metadata and system status on ST7789 TFT display
  - Drives a simple on-screen animation

## Libraries Used
- **BluetoothA2DPSink** – Bluetooth A2DP audio sink and AVRCP control
- **LovyanGFX** – High-performance graphics library for TFT display

## Features
- Bluetooth audio streaming (A2DP)
- AVRCP media control via single button
- Analog volume control
- Real-time song and artist display
- SPI-based 240×240 TFT screen support

## Notes
- The sketch is written for ESP32-based boards
- I2S audio output is configured for external DAC / amplifier modules
- All device names and identifiers are kept generic for portability
