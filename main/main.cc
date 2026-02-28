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

#include <board_hal/pins.h>
#include <board_hal/psram.h>
#include <esp_log.h>

static const char* TAG = "syzygy2d";

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "=========================================");
    ESP_LOGI(TAG, "  Syzygy2D — ESP32-S3-EYE 2D Engine");
    ESP_LOGI(TAG, "  Step 1: Foundation");
    ESP_LOGI(TAG, "=========================================");

    /* Verify Octal PSRAM is accessible and report heap stats */
    ESP_ERROR_CHECK(psram_verify());

    ESP_LOGI(TAG,
        "LCD  : ST7789 240×240 RGB565 on SPI%" PRIu32 " (MOSI=%" PRIu32
        " CLK=%" PRIu32 " CS=%" PRIu32 " DC=%" PRIu32 " BL=%" PRIu32 ")",
        (uint32_t)LCD_SPI_HOST,
        (uint32_t)PIN_LCD_MOSI,
        (uint32_t)PIN_LCD_CLK,
        (uint32_t)PIN_LCD_CS,
        (uint32_t)PIN_LCD_DC,
        (uint32_t)PIN_LCD_BL);

    ESP_LOGI(TAG,
        "BTN  : ADC ladder on GPIO%" PRIu32 "  BOOT on GPIO%" PRIu32,
        (uint32_t)PIN_BTN_ADC,
        (uint32_t)PIN_BTN_BOOT);

    ESP_LOGI(TAG, "Hardware init complete — ready for Step 2.");
}
