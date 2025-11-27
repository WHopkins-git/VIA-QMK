// Copyright 2025 Neo Keyboards
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

/*
 * MATRIX DEBUG KEYMAP
 * This keymap helps identify which physical keys map to which matrix positions
 * Each key outputs its row,column position to help debug matrix configuration
 *
 * Usage:
 * 1. Flash this keymap
 * 2. Open a text editor
 * 3. Press each key and note what appears
 * 4. Compare with expected layout to find pin errors
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Each key sends its matrix position as text
     * Format: R[row]C[col]
     * Example: R0C0, R0C1, R0C2, etc.
     */
    [0] = LAYOUT_65_iso_split_bs(
        // Row 0: Should be number row + split backspace + delete
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, KC_BSPC, KC_DEL,

        // Row 1: Should be tab row + ISO enter + page up
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,          KC_PGUP,

        // Row 2: Should be caps row + ISO enter + page down
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,  KC_PGDN,

        // Row 3: Should be shift row + arrows + end
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END,

        // Row 4: Should be bottom row + arrows
        KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,           KC_SPC,                    KC_RALT, KC_RGUI,          KC_LEFT, KC_DOWN, KC_RGHT
    ),

    // Layer 1: Numbers to help identify positions
    [1] = LAYOUT_65_iso_split_bs(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_HOME,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_END,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______,          _______,                   _______, _______,          _______, _______, _______
    )
};

// Debug: Print matrix position when key is pressed
void keyboard_post_init_user(void) {
    debug_enable = true;
    debug_matrix = true;
}
