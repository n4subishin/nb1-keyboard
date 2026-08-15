// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// ---------------------------------------------------------------------------
// VIA / Remap keymap
//
// What is compiled here is only the FACTORY DEFAULT. Once the customer opens
// Remap and saves a change, their keymap lives in EEPROM and this file stops
// mattering. So the job here is a sensible out-of-the-box state, not a final
// design.
//
// Layer count must match DYNAMIC_KEYMAP_LAYER_COUNT (4) in config.h. Layers 2
// and 3 are left transparent for the customer to fill in.
//
//        col1   col2   col3   col4
//  row1 [  1 ] [  2 ] [  3 ] [  4 ]
//  row2 [  5 ] [  6 ] [  7 ] [  8 ]
//  row3 [  9 ] [ 10 ] [ 11 ] [ 12 ]
//
// Digits are the main-row KC_0..KC_9, never KC_P0..KC_P9: this board has no
// Num Lock key, so keypad digits would be stuck as Home/arrows/Insert whenever
// the host had Num Lock off, with no way for the customer to recover.
// ---------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_3x4(
        KC_7,    KC_8,    KC_9,    KC_BSPC,
        KC_4,    KC_5,    KC_6,    KC_PENT,
        KC_1,    KC_2,    KC_3,    LT(1, KC_0)
    ),

    [1] = LAYOUT_3x4(
        KC_PSLS, KC_PAST, KC_PMNS, KC_DEL,
        KC_PPLS, KC_EQL,  KC_DOT,  KC_TAB,
        KC_COMM, KC_LPRN, KC_RPRN, _______
    ),

    [2] = LAYOUT_3x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),

    [3] = LAYOUT_3x4(
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______
    ),
};

#ifdef ENCODER_MAP_ENABLE
// Encoder index = row * 4 + col, matching the "rotary" array in keyboard.json.
// Each row is { counter-clockwise, clockwise }.
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] = {
        { KC_VOLD, KC_VOLU  }, { KC_MPRV, KC_MNXT  },
        { KC_PGDN, KC_PGUP  }, { KC_LEFT, KC_RGHT  },
        { MS_WHLD, MS_WHLU  }, { KC_UP,   KC_DOWN  },
        { MS_LEFT, MS_RGHT  }, { S(KC_TAB), KC_TAB },
        { KC_MINS, KC_EQL   }, { KC_LBRC, KC_RBRC  },
        { KC_COMM, KC_DOT   }, { KC_BRID, KC_BRIU  },
    },
    [1] = {
        { KC_VOLD, KC_VOLU  }, { KC_MPRV, KC_MNXT  },
        { KC_HOME, KC_END   }, { KC_LEFT, KC_RGHT  },
        { MS_WHLD, MS_WHLU  }, { KC_UP,   KC_DOWN  },
        { MS_LEFT, MS_RGHT  }, { S(KC_TAB), KC_TAB },
        { KC_MINS, KC_EQL   }, { KC_LBRC, KC_RBRC  },
        { KC_COMM, KC_DOT   }, { KC_BRID, KC_BRIU  },
    },
    [2] = {
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
    },
    [3] = {
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
        { _______, _______ }, { _______, _______ },
    },
};
#endif

// ---------------------------------------------------------------------------
// Indicator LED on PA15 -- active HIGH (anode to PA15, cathode via R6 to GND).
// PA15 is JTDI at reset on STM32F4 and must be claimed as a plain GPIO first;
// SWD-only debug makes that safe.
//
// Lit whenever any layer above the base one is active, so the customer can see
// which layer they are on regardless of how they remap the layer keys.
// ---------------------------------------------------------------------------

#define INDICATOR_LED A15

void keyboard_post_init_user(void) {
    gpio_set_pin_output(INDICATOR_LED);
    gpio_write_pin_low(INDICATOR_LED);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(INDICATOR_LED, get_highest_layer(state) != 0);
    return state;
}
