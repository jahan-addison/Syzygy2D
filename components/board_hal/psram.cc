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

#include <board_hal/psram.h>

#include <esp_heap_caps.h>
#include <esp_log.h>

#include <cstddef>
#include <cstdint>
#include <cstring>

static const char* TAG = "psram";

esp_err_t psram_verify(void)
{
    /* ------------------------------------------------------------------ *
     *  1. Check that SPIRAM heap region exists                            *
     * ------------------------------------------------------------------ */
    const size_t total = heap_caps_get_total_size(MALLOC_CAP_SPIRAM);
    const size_t free_ = heap_caps_get_free_size(MALLOC_CAP_SPIRAM);

    if (total == 0) {
        ESP_LOGE(TAG,
            "Octal PSRAM NOT detected.\n"
            "  Check sdkconfig: CONFIG_SPIRAM=y, "
            "CONFIG_SPIRAM_MODE_OCT=y, CONFIG_SPIRAM_BOOT_INIT=y");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG,
        "Octal PSRAM detected — total: %u KB  free: %u KB",
        static_cast<unsigned>(total / 1024u),
        static_cast<unsigned>(free_ / 1024u));

    /* ------------------------------------------------------------------ *
     *  2. Allocation smoke-test: alloc 1 MB, write, verify, free          *
     * ------------------------------------------------------------------ */
    constexpr size_t PROBE_BYTES = 1u * 1024u * 1024u; /* 1 MB */
    constexpr uint8_t PATTERN = 0xA5u;

    uint8_t* probe =
        static_cast<uint8_t*>(heap_caps_malloc(PROBE_BYTES, MALLOC_CAP_SPIRAM));

    if (probe == nullptr) {
        ESP_LOGE(TAG,
            "PSRAM allocation smoke-test FAILED: "
            "could not allocate %u KB from SPIRAM heap",
            static_cast<unsigned>(PROBE_BYTES / 1024u));
        return ESP_FAIL;
    }

    std::memset(probe, PATTERN, PROBE_BYTES);

    /* Verify first, middle, and last byte */
    bool ok = (probe[0] == PATTERN) && (probe[PROBE_BYTES / 2] == PATTERN) &&
              (probe[PROBE_BYTES - 1] == PATTERN);

    heap_caps_free(probe);

    if (!ok) {
        ESP_LOGE(
            TAG, "PSRAM read-back verification FAILED — memory may be faulty");
        return ESP_FAIL;
    }

    ESP_LOGI(TAG,
        "PSRAM smoke-test passed (%u KB alloc/write/verify/free)",
        static_cast<unsigned>(PROBE_BYTES / 1024u));

    /* ------------------------------------------------------------------ *
     *  3. Report internal SRAM for comparison                             *
     * ------------------------------------------------------------------ */
    ESP_LOGI(TAG,
        "Internal SRAM — free: %u KB  (DMA-capable: %u KB)",
        static_cast<unsigned>(
            heap_caps_get_free_size(MALLOC_CAP_INTERNAL) / 1024u),
        static_cast<unsigned>(heap_caps_get_free_size(MALLOC_CAP_DMA) / 1024u));

    return ESP_OK;
}
