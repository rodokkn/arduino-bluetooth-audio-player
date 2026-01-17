# Arduino Bluetooth Audio Player

This project is a **portable Bluetooth audio player** built using Arduino-based hardware modules.

The purpose of this project is **not advanced software development**, but **system-level integration**.  
The device was created by configuring and combining multiple electronic components, embedded firmware, and a custom mechanical enclosure into a single functional system.

No complex or proprietary audio processing software was developed as part of this project.

---

## Project Overview

The Bluetooth audio player enables **wireless audio playback** to an external speaker in a standalone, battery-powered form factor.  
The project focuses on **hardware integration, embedded firmware configuration, power management, and enclosure design**.

The system was developed and tested as a complete working device rather than a software-only application.

---

## What Was Done in This Project

- Selected and integrated an Arduino-compatible microcontroller  
- Integrated a Bluetooth audio module for wireless audio streaming  
- Connected an external audio amplifier and speaker  
- Implemented physical control buttons for user interaction  
- Designed and tested a rechargeable power system  
- Developed basic Arduino firmware for system control  
- Designed a custom enclosure in CAD  
- Manufactured the enclosure using PLA 3D printing  
- Assembled and tested the complete device  

---

## Hardware Components

- **Microcontroller**
  - Arduino Nano (5V logic level)

- **Bluetooth Audio Module**
  - Serial Bluetooth audio module for wireless audio streaming

- **Audio Amplifier**
  - PAM8302 Class-D amplifier  
  - Operating voltage: 2.5–5.5V  
  - Mono audio output

- **Speaker**
  - Single 5V-compatible speaker

- **Power System**
  - Single-cell rechargeable Li-ion battery  
  - TP4056 charging and protection module  
  - DC-DC voltage regulator providing stable 5V output

- **User Interface**
  - Physical control buttons

- **Enclosure**
  - Custom CAD-designed enclosure  
  - PLA 3D printed

---

## Software Structure

The software consists of:
- Arduino sketches for Bluetooth initialization  
- Button input handling  
- Basic system control logic  

The software is intentionally kept simple to ensure reliability and ease of debugging.  
All software files are located under the `software` directory.

---

## Hardware Design

The hardware design includes:
- Microcontroller and Bluetooth module integration  
- Audio amplifier and speaker wiring  
- Battery, charging, and power management circuitry  
- Custom-designed enclosure  

CAD and STL files for the enclosure are provided in the `hardware` directory.

---

## Features

- Bluetooth audio playback  
- External speaker output  
- Physical control buttons  
- Rechargeable battery operation  
- Portable standalone design  
- Custom 3D printed enclosure  

---

## Media

<img src="hardware/photos/m1.jpeg" width="45%">
<img src="hardware/photos/m2.jpeg" width="45%">

---

## Notes

This repository documents the **system setup, hardware integration, and enclosure design** of the project rather than focusing on application-level software development.
