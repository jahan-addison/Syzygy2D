/*****************************************************************************
 * Copyright (c) Jahan Addison
 *
 * This software is dual-licensed under the Apache License, Version 2.0 or
 * the GNU General Public License, Version 3.0 or later.
 *
 * You may use this work, in part or in whole, under the terms of either
 * license.
 *
 * See the LICENSE.Apache-v2 and LICENSE.GPL-v3 files in the project root
 * for the full text of these licenses.
 ****************************************************************************/

/**
 * @file pins.h
 * @brief ESP32-S3-EYE v2.2 — complete GPIO / peripheral pin mapping.
 *
 * Sources:
 *   - ESP32-S3-EYE schematic SCH_ESP32-S3-EYE-MB_20211201_V2.2
 *   - ESP32-S3-EYE BSP (espressif/esp-bsp)
 *   - ESP32-S3-WROOM-1 datasheet
 */

#pragma once

#include "driver/gpio.h"
#include "driver/spi_master.h"

#ifdef __cplusplus
extern "C"
{
#endif

/* ============================================================
 *  LCD — ST7789 1.3" 240×240 RGB565 (SPI3_HOST / VSPI)
 * ============================================================ */
#define PIN_LCD_MOSI GPIO_NUM_47 ///< SPI MOSI (data)
#define PIN_LCD_CLK GPIO_NUM_21  ///< SPI SCLK
#define PIN_LCD_CS GPIO_NUM_44   ///< SPI chip-select (active low)
#define PIN_LCD_DC GPIO_NUM_43   ///< Data / Command select
#define PIN_LCD_RST GPIO_NUM_NC  ///< Reset — pulled high on sub-board; no GPIO
#define PIN_LCD_BL GPIO_NUM_48   ///< Backlight PWM (active high)

#define LCD_SPI_HOST SPI3_HOST
#define LCD_PIXEL_CLK_HZ (80 * 1000 * 1000) ///< 80 MHz SPI clock
#define LCD_H_RES 240
#define LCD_V_RES 240
#define LCD_COLOR_BITS 16 ///< RGB565

/* ============================================================
 *  Input — 6 physical buttons
 *
 *  Physical layout (top to bottom on board edge):
 *    MENU  PLAY  DOWN  UP   [RST]  BOOT
 *
 *  RST is wired directly to the chip RESET pin — not GPIO-accessible.
 *  BOOT is pulled high; ground to enter Download Mode.
 *  MENU / PLAY / DOWN / UP share a single ADC line through a resistor
 *  voltage-divider ladder (ADC1, channel 0, GPIO1).
 * ============================================================ */
#define PIN_BTN_ADC GPIO_NUM_1  ///< ADC1 ch0 — MENU/PLAY/DOWN/UP ladder
#define PIN_BTN_BOOT GPIO_NUM_0 ///< BOOT button (active low, ext pull-up)

/** Approximate ADC output (mV) when each button is pressed.
 *  Calibrate against your specific board; values may vary ±50 mV. */
#define BTN_MENU_MV 2700
#define BTN_PLAY_MV 2060
#define BTN_DOWN_MV 1520
#define BTN_UP_MV 1070

/* ============================================================
 *  Status LED (open-drain, active LOW — do not push-pull high)
 * ============================================================ */
#define PIN_LED_GREEN GPIO_NUM_3

/* ============================================================
 *  I2C — shared by Accelerometer (QMA7981) and Camera SCCB (OV2640)
 * ============================================================ */
#define PIN_I2C_SCL GPIO_NUM_5
#define PIN_I2C_SDA GPIO_NUM_4
#define I2C_FREQ_HZ 400000 ///< Fast-mode 400 kHz

/* ============================================================
 *  I2S — Digital Microphone MSM261S4030H0 (mono, 48 kHz, 24-bit)
 * ============================================================ */
#define PIN_MIC_SCLK GPIO_NUM_41 ///< Bit clock
#define PIN_MIC_WS GPIO_NUM_42   ///< Word select (L/R clock)
#define PIN_MIC_DIN GPIO_NUM_2   ///< Serial data in

/* ============================================================
 *  Camera — OV2640 2MP (parallel DVP interface)
 * ============================================================ */
#define PIN_CAM_XCLK GPIO_NUM_15 ///< Master clock out
#define PIN_CAM_PCLK GPIO_NUM_13 ///< Pixel clock in
#define PIN_CAM_VSYNC GPIO_NUM_6 ///< Vertical sync
#define PIN_CAM_HSYNC GPIO_NUM_7 ///< Horizontal sync
#define PIN_CAM_D0 GPIO_NUM_11
#define PIN_CAM_D1 GPIO_NUM_9
#define PIN_CAM_D2 GPIO_NUM_8
#define PIN_CAM_D3 GPIO_NUM_10
#define PIN_CAM_D4 GPIO_NUM_12
#define PIN_CAM_D5 GPIO_NUM_18
#define PIN_CAM_D6 GPIO_NUM_17
#define PIN_CAM_D7 GPIO_NUM_16

/* ============================================================
 *  SD Card — 1-bit MMC (SDMMC peripheral, slot 1)
 * ============================================================ */
#define PIN_SD_D0 GPIO_NUM_40  ///< DAT0
#define PIN_SD_CMD GPIO_NUM_38 ///< CMD
#define PIN_SD_CLK GPIO_NUM_39 ///< CLK

    /* ============================================================
     *  PSRAM — 8 MB Octal SPI PSRAM (OPI)
     *
     *  The ESP32-S3R8 variant has OPI PSRAM bonded internally.
     *  The physical signals are not broken out to user GPIO; enable
     *  via Kconfig (see sdkconfig.defaults):
     *    CONFIG_SPIRAM=y
     *    CONFIG_SPIRAM_MODE_OCT=y
     *    CONFIG_SPIRAM_SPEED_80M=y
     * ============================================================ */
    /* No user-accessible GPIO — configuration is done via sdkconfig */

#ifdef __cplusplus
} /* extern "C" */
#endif
