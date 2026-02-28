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
 * @file psram.h
 * @brief Octal PSRAM verification and heap reporting.
 *
 * The ESP32-S3R8 integrates 8 MB of OPI (Octal SPI) PSRAM directly
 * on the package.  After ESP-IDF initialises the SPIRAM heap region
 * during startup, this module verifies availability and reports stats.
 *
 * Prerequisites (sdkconfig.defaults):
 *   CONFIG_SPIRAM=y
 *   CONFIG_SPIRAM_MODE_OCT=y
 *   CONFIG_SPIRAM_BOOT_INIT=y
 */

#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Verify Octal PSRAM is accessible and perform a heap smoke-test.
     *
     * Logs total / free SPIRAM heap sizes, then round-trip allocates a
     * 1 MB probe block to confirm the physical memory is read/write capable.
     *
     * Must be called from app_main() after the IDF startup sequence has
     * initialised the SPIRAM heap (@c CONFIG_SPIRAM_BOOT_INIT=y).
     *
     * @return
     *   - ESP_OK   — PSRAM detected, smoke-test passed.
     *   - ESP_FAIL — PSRAM not detected or allocation failed.
     */
    esp_err_t psram_verify(void);

#ifdef __cplusplus
} /* extern "C" */
#endif
