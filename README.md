# Syzygy2D: ESP32-S3-EYE 2D Graphics Engine

## Overview

#### A 2D Graphics Engine for the ESP32-S3-EYE

<p align="center">
  <img src="/docs/ESP32-S3-EYE.png" width="400px" />
</p>


## Project

### Roadmap

- [ ] **Step 1: Foundation (The Root)**
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

```bash
cmake -Bbuild -DCMAKE_BUILD_TYPE=Debug -DUSE_SANITIZER="Address;Undefined" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DIWYU=ON
cmake --build build
```

Run the test suite:

```bash
./build/test_suite
```


## License

This project is dual-licensed under the **Apache License, Version 2.0** and the **GNU General Public License, Version 3.0 (or later)**.


You are free to choose the license that best fits your specific use case. For the full text of each license, please see [LICENSE.Apache-v2](LICENSE.Apache-v2) and [LICENSE-GPL-v3](LICENSE.GPL-v3).