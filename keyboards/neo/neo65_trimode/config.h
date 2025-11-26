// Copyright 2025 Neo Keyboards
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameters */
#define VENDOR_ID       0x342D
#define PRODUCT_ID      0xDFA0
#define DEVICE_VER      0x0001
#define MANUFACTURER    Neo
#define PRODUCT         Neo65 Tri-Mode

/* Matrix Configuration */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* Matrix pin configuration for WB32F3G71 */
#define MATRIX_ROW_PINS { B12, B13, B14, B15, A8 }
#define MATRIX_COL_PINS { B11, B10, B1, B0, A7, A6, A5, A4, A3, A2, A1, A0, C15, C14, C13 }

/* Diode direction - COL2ROW means columns to rows */
#define DIODE_DIRECTION COL2ROW

/* Debounce reduces chatter */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* RGB/LED Configuration (optional - enable if hardware supports) */
// #define RGB_MATRIX_LED_COUNT 68
// #define WS2812_DI_PIN A9

/* VIA Configuration */
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* Force NKRO */
#define FORCE_NKRO

/* USB polling rate */
#define USB_POLLING_INTERVAL_MS 1

/* Firmware size optimization */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
