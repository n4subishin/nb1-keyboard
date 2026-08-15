// Copyright 2026
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers { _BASE = 0, _FN };

// ---------------------------------------------------------------------------
// Position numbering (matches the user manual)
//
//        col1   col2   col3   col4
//  row1 [  1 ] [  2 ] [  3 ] [  4 ]      SW13  SW16  SW19  SW22
//  row2 [  5 ] [  6 ] [  7 ] [  8 ]      SW14  SW17  SW20  SW23
//  row3 [  9 ] [ 10 ] [ 11 ] [ 12 ]      SW15  SW18  SW21  SW24
//
// Every position takes EITHER a Cherry MX switch (via a Kailh hotswap socket)
// OR a rotary encoder -- the two share one footprint and cannot coexist.
// This single firmware covers any mix: unpopulated encoders idle high on their
// internal pull-ups, and unpopulated matrix positions simply never trigger.
//
// NUM LOCK INDEPENDENCE
// KC_P0..KC_P9 and KC_PDOT change meaning when Num Lock is off (Home, arrows,
// Insert, Delete...). This board has no Num Lock key, so the user would have no
// way to fix that state. The digits below are the main-row keycodes KC_0..KC_9,
// which always send digits. Keypad OPERATORS (KC_PSLS, KC_PAST, KC_PMNS,
// KC_PPLS, KC_PENT) are not affected by Num Lock and are safe to use.
// ---------------------------------------------------------------------------

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // 7 8 9 Backspace / 4 5 6 Enter / 1 2 3 (tap 0, hold FN)
    [_BASE] = LAYOUT_3x4(
        KC_7,    KC_8,    KC_9,    KC_BSPC,
        KC_4,    KC_5,    KC_6,    KC_PENT,
        KC_1,    KC_2,    KC_3,    LT(_FN, KC_0)
    ),

    [_FN] = LAYOUT_3x4(
        KC_PSLS, KC_PAST, KC_PMNS, KC_DEL,
        KC_PPLS, KC_EQL,  KC_DOT,  KC_TAB,
        KC_COMM, KC_LPRN, KC_RPRN, _______
    ),
};

#ifdef ENCODER_MAP_ENABLE
// Same order as the "rotary" array in keyboard.json: { CCW, CW }
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [_BASE] = {
        { KC_VOLD, KC_VOLU  },  //  0  position 1
        { KC_MPRV, KC_MNXT  },  //  1  position 2
        { KC_PGDN, KC_PGUP  },  //  2  position 3
        { KC_LEFT, KC_RGHT  },  //  3  position 4

        { MS_WHLD, MS_WHLU  },  //  4  position 5
        { KC_UP,   KC_DOWN  },  //  5  position 6
        { MS_LEFT, MS_RGHT  },  //  6  position 7
        { S(KC_TAB), KC_TAB },  //  7  position 8

        { KC_MINS, KC_EQL   },  //  8  position 9
        { KC_LBRC, KC_RBRC  },  //  9  position 10
        { KC_COMM, KC_DOT   },  // 10  position 11
        { KC_BRID, KC_BRIU  },  // 11  position 12
    },
    [_FN] = {
        { KC_VOLD, KC_VOLU },
        { KC_MPRV, KC_MNXT },
        { KC_HOME, KC_END  },
        { KC_LEFT, KC_RGHT },

        { MS_WHLD, MS_WHLU },
        { KC_UP,   KC_DOWN },
        { MS_LEFT, MS_RGHT },
        { S(KC_TAB), KC_TAB },

        { KC_MINS, KC_EQL  },
        { KC_LBRC, KC_RBRC },
        { KC_COMM, KC_DOT  },
        { KC_BRID, KC_BRIU },
    },
};
#endif

// ---------------------------------------------------------------------------
// Indicator LED on PA15
//
// Red 0603, anode to PA15, cathode through R6 (1k) to GND -> active HIGH.
// PA15 is JTDI at reset on STM32F4, so it has to be claimed as a plain GPIO
// output before use. Only SWD (PA13/PA14) is used for debug, so this is safe.
//
// Num Lock is meaningless on this board now, so the LED tracks the active
// layer instead: lit whenever the user is holding the FN layer.
// ---------------------------------------------------------------------------

#define INDICATOR_LED A15

void keyboard_post_init_user(void) {
    gpio_set_pin_output(INDICATOR_LED);
    gpio_write_pin_low(INDICATOR_LED);
}

layer_state_t layer_state_set_user(layer_state_t state) {
    gpio_write_pin(INDICATOR_LED, get_highest_layer(state) != _BASE);
    return state;
}
