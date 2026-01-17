# Arduino Software

This folder contains the Arduino sketch used in the Bluetooth audio player project.

The software is responsible only for **basic system control**.
All audio processing is handled by dedicated hardware modules.

---

## Responsibilities

- Bluetooth module initialization  
- Physical button input handling  
- Basic playback control logic  

---

## Design Notes

The firmware is intentionally kept **simple** to ensure reliability and ease of debugging.
No audio decoding or complex processing is performed in software.

---

## Files

- `bluetooth_player.ino`  
  Main Arduino sketch for system control
