// Copyright 2025 Neo Keyboards
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* USB Device descriptor parameters */
#define VENDOR_ID       0xFFFE
#define PRODUCT_ID      0x0015
#define DEVICE_VER      0x0001
#define MANUFACTURER    Neo
#define PRODUCT         Neo65 Tri-Mode

/* Matrix Configuration */
#define MATRIX_ROWS 5
#define MATRIX_COLS 16

/* Debounce reduces chatter */
#define DEBOUNCE 5

/* Bootmagic Lite key configuration */
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

/* VIA Configuration */
#define DYNAMIC_KEYMAP_LAYER_COUNT 4

/* Force NKRO */
#define FORCE_NKRO

/* Firmware size optimization */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
