// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "features/achordion.h"
#include "custom_keys.h"
#include "features/custom_key_functions.h"

enum layers { BASE, SYM, NAV, NUM, MOUSE };

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        LT(MOUSE, KC_ESC), KC_B,  KC_L,   KC_D,  KC_C,    KC_V,                    KC_J,    KC_Y,    KC_O,   KC_U,    KC_COMM, KC_TAB,
        OSM(MOD_LGUI), HOME_N, HOME_R, KC_T, HOME_S, KC_G,                         KC_P,    HOME_H,  KC_A,   HOME_E,  HOME_I, KC_ENT,
        OSM(MOD_LSFT), KC_X,   KC_Q, KC_M, KC_W, KC_Z,                             KC_K,    KC_F,    KC_QUOT,KC_SCLN, KC_DOT, KC_SLSH,
                                            TT(NAV), HYPR_SPC,                     KC_BSPC, MO(SYM)
    ),
    [SYM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        VIWPYIW, KC_TILD, KC_LT,   KC_GT, KC_LCBR,  KC_RCBR,                       KC_DEL,  KC_PSCR, KC_EXLM, KC_HASH, KC_BSLS, _______,
        _______, KC_AT, KC_LPRN, KC_LBRC, KC_RPRN, KC_RBRC,                        KC_CIRC, KC_EQL,  KC_PLUS, KC_MINS, KC_PIPE, _______,
        _______, _______, KC_GRV, KC_AMPR, KC_UNDS, DBL_QUOT,                      KC_ASTR, CLOSE_PAIR, KC_DLR,  KC_PERC, SCRNSHOT, LCA(KC_G),
                                                     _______, _______,    _______, _______
    ),
    [NAV] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        BACK,    FORWARD, XC_LFT_SPLT, KC_UP, XC_RGT_SPLT, KC_HOME,                OSM(MOD_LALT), LEFT_WORD, DELETE_LINE, RIGHT_WORD,  XCODE_SPLIT, _______,
        _______, CLOSE_WIN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,                     _______, HMRW_SCROLL, HMRW_CLICK, _______, XC_CONSOLE, XC_PREVIEW,
        _______, ZOOM_OUT,WS_1,    WS_2, TAB_L, TAB_R,                             _______, XC_SIDEBAR, XC_SEARCH, XC_SHOW, ZOOM_IN, _______,
                                                     _______, _______,    _______, _______
    ),
    [NUM] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, KC_F11,                       KC_F12,  _______, _______, _______, _______, _______,
        _______, KC_9,    KC_5,    KC_0,    KC_3,    KC_7,                         KC_6,    KC_2,    KC_1,    KC_4,    KC_8,    _______,
        _______, KC_F9,   KC_F5,   KC_F10,  KC_F3,   KC_F7,                        KC_F6,   KC_F2,   KC_F1,   KC_F4,   KC_F8,    _______,
                                                     _______, _______,    _______, _______
    ),
    [MOUSE] = LAYOUT(
        _______, _______, MS_WHLD, MS_WHLU, _______, _______,                      _______, _______, _______, _______, _______, _______,
        _______, MS_ACL1, KC_MS_BTN1, KC_MS_BTN1, _______, _______,                _______, _______, KC_MS_UP, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                      _______, KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, _______,
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
                                                     _______, _______,    _______, _______
    ),
};

void housekeeping_task_user(void) {
    achordion_task();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_achordion(keycode, record)) {
        return false;
    }

    if (is_repeatable_key(keycode)) {
        set_repeat_custom_key(keycode, record);
        return false;
    }

    if (record->event.pressed) {
        if(!handle_nonrepeatable_key(keycode)) return false;
    }
    return true;
}

uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
  // If you quickly hold a tap-hold key after tapping it, the tap action is
  // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
  // lead to missed triggers in fast typing. Here, returning 0 means we
  // instead want to "force hold" and disable key repeating.
  switch (keycode) {
    case HOME_N:
    case HOME_E:
    case HYPR_SPC:
      return QUICK_TAP_TERM;
    default:
      return 0;
  }
}

void matrix_scan_user(void) {
    try_repeat_custom_key();
}
