# Syzygy2D: ESP32-S3-EYE 2D Graphics Engine

## Overview

#### A 2D Graphics Engine for the ESP32-S3-EYE

<p align="center">
  <img src="/docs/ESP32-S3-EYE.png" width="400px" />
</p>


## Project

### Roadmap

- [x] **Step 1: Foundation (The Root)**
    - Hardware pin mappings for ST7789 LCD and 6-button matrix
    - Configure Octal PSRAM and verify heap allocation

- [ ] **Step 2: Hardware Drivers (I/O)**
    - DMA-backed SPI Master for non-blocking display updates
    - ISR-driven Input Manager with atomic bitmasks for button states
    - Low-level ST7789 HAL (Software Reset, Gamma, Color Mode)

- [ ] **Step 3: Graphics & Memory**
    - Allocate Framebuffers in PSRAM for smooth 60 FPS output
    - Pool Allocators for sprite and entity management
    - SIMD-accelerated Blitter using Xtensa LX7 Vector instructions

- [ ] **Step 4: 2D Engine Loop**
    - Double-Buffering Sync via FreeRTOS Task Notifications
    - Pin Render Task to Core 1 and Logic/Physics Task to Core 0
    - Decouple frame rate from physics using a Fixed-Timestep Update Loop

- [ ] **Step 5: Asset Pipeline**
    - Mount LittleFS/VFS partition for data storage
    - Binary Asset Loader to stream raw RGB565 sprites


## Build

### Prerequisites

#### MacOS

```bash
# macOS — install toolchain dependencies
brew install cmake ninja dfu-util

# Clone and install ESP-IDF v5.4.1
mkdir -p ~/esp && cd ~/esp
git clone --depth 1 --branch v5.4.1 --recursive \
    https://github.com/espressif/esp-idf.git esp-idf
~/esp/esp-idf/install.sh esp32s3

# Add to ~/.zshrc (or source manually each session):
# . ~/esp/esp-idf/export.sh
```

### Configure & Build

```bash
# Source the IDF environment (once per shell session)

# Set target (only needed once; writes into sdkconfig)
idf.py set-target esp32s3

# Build
idf.py build
```

### Flash & Monitor

```bash
idf.py -p /dev/tty.usbmodem* flash monitor
```

Press `Ctrl-]` to exit the monitor.

### VS Code

Open the project in VS Code with the **ESP-IDF** extension installed.
Use **ESP-IDF: Build your project** (`Ctrl+E B`) to build, and
**ESP-IDF: Flash your project** (`Ctrl+E F`) to flash.


## License

This project is dual-licensed under the **Apache License, Version 2.0** and the **GNU General Public License, Version 3.0 (or later)**.


You are free to choose the license that best fits your specific use case. For the full text of each license, please see [LICENSE.Apache-v2](LICENSE.Apache-v2) and [LICENSE-GPL-v3](LICENSE.GPL-v3).