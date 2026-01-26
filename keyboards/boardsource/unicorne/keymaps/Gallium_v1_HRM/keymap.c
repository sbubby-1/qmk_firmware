#include QMK_KEYBOARD_H
#include "Custom/keys.h"

enum layers { BASE, SYM, NAV, NUM, MOUSE };

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE]  = LAYOUT(
        MOUSE_ESC, KC_B,     KC_L,     KC_D,     KC_C,     KC_V,              KC_J,     KC_Y,     KC_O,     KC_U,     KC_COMM,  KC_TAB,
        OS_LCTL,   LCTL_N,   LGUI_R,   KC_T,     LALT_S,   KC_G,              KC_P,     RALT_H,   KC_A,     RGUI_E,   RCTL_I,   KC_ENT,
        OS_LSFT,   KC_X,     KC_Q,     KC_M,     KC_W,     KC_Z,              KC_K,     KC_F,     KC_QUOT,  KC_SCLN,  KC_DOT,   KC_SLSH,
                                       OS_LGUI,  MO(NAV),  HYPR_SPC,          KC_BSPC,  MO(SYM),  OS_LALT
    ),
    [SYM]   = LAYOUT(
        VIWPYIW,   KC_TILD,  KC_LT,    KC_GT,    KC_LCBR,  KC_RCBR,           KC_DEL,   KC_PSCR,  KC_EXLM,  KC_HASH,  KC_BSLS,  _______,
        _______,   KC_AT,    KC_LPRN,  KC_LBRC,  KC_RPRN,  KC_RBRC,           KC_CIRC,  KC_EQL,   KC_PLUS,  KC_MINS,  KC_PIPE,  _______,
        _______,   _______,  KC_GRV,   KC_AMPR,  KC_UNDS,  DBL_QUOT,          KC_ASTR,  CLOSE_PAIR,KC_DLR,   KC_PERC,  SCRNSHOT, LCA(KC_G),
                                      _______,  _______,  _______,            _______,  _______,  _______
    ),
    [NAV]   = LAYOUT(
        BACK,      FORWARD,  COPY,     KC_UP,    PASTE,    KC_HOME,           _______,  SLW,      DEL_LINE, SRW,      _______,  _______,
        _______,   CLOSE_WIN,KC_LEFT,  KC_DOWN,  KC_RGHT,  KC_END,            XC_FORMAT,HMRW_SCROLL,HMRW_CLICK,XC_LINE_NUM,XC_CONSOLE,XC_PREVIEW,
        _______,   _______,  WS_1,     WS_2,     TAB_L,    TAB_R,             _______,  XC_SIDEBAR,XC_SEARCH,XC_SHOW,  _______,  _______,
                                      _______,  _______,  _______,            _______,  _______,  _______
    ),
    [NUM]   = LAYOUT(
        _______,   _______,  _______,  _______,  _______,  KC_F11,            KC_F12,   _______,  _______,  _______,  _______,  _______,
        _______,   KC_9,     KC_5,     KC_0,     KC_3,     KC_7,              KC_6,     KC_2,     KC_1,     KC_4,     KC_8,     _______,
        _______,   KC_F9,    KC_F5,    KC_F10,   KC_F3,    KC_F7,             KC_F6,    KC_F2,    KC_F1,    KC_F4,    KC_F8,    _______,
                                       _______,  _______,  _______,           _______,  _______,  _______
    ),
    [MOUSE] = LAYOUT(
        _______,   MS_ACL1,  MS_BTN1,  MS_BTN1,  _______,  _______,           _______,  _______,  MS_UP,    _______,  _______,  _______,
        _______,   _______,  _______,  _______,  _______,  _______,           _______,  MS_LEFT,  MS_DOWN,  MS_RGHT,  _______,  _______,
        _______,   _______,  _______,  _______,  _______,  _______,           _______,  _______,  _______,  _______,  _______,  _______,
                                       _______,  _______,  _______,           _______,  _______,  _______
    ),
};
// clang-format on
