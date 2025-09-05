#include QMK_KEYBOARD_H
#include "../custom_keys.h"
#include "custom_key_functions.h"
#include "timer.h"

static bool     is_custom_key_held    = false;
static bool     did_custom_key_repeat = false;
static uint16_t held_custom_key       = 0;
static uint16_t custom_key_held_timer = 0;
static uint16_t last_keycode          = KC_NO;

void handle_opening_pair(uint16_t keycode) {
    last_keycode = keycode;
    tap_code16(keycode);
}

bool handle_closing_pair(void) {
    switch (last_keycode) {
        case KC_LPRN:
            tap_code16(KC_RPRN);
            break; // (
        case KC_LBRC:
            tap_code16(KC_RBRC);
            break; // [
        case KC_LCBR:
            tap_code16(KC_RCBR);
            break; // {
        case KC_LABK:
            tap_code16(KC_RABK);
            break; // <
        case KC_QUOT:
            tap_code16(KC_QUOT);
            break; // '
        case KC_DQUO:
            tap_code16(KC_DQUO);
            break; // "
        case KC_GRV:
            tap_code16(KC_GRV);
            break; // `
        default:
            return false;
    }
    tap_code(KC_LEFT);
    last_keycode = KC_NO;
    return true;
}

void tap_custom_key(void) {
    switch (held_custom_key) {
        case LEFT_WORD:
            register_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            tap_code(KC_LEFT);
            unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            break;

        case RIGHT_WORD:
            register_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            tap_code(KC_RGHT);
            unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            break;

        case DELETE_LINE:
            SEND_STRING(SS_LGUI(SS_TAP(X_RGHT)));
            SEND_STRING(SS_LGUI(SS_TAP(X_BSPC)));
            break;
    }
}

void set_repeat_custom_key(uint16_t keycode, keyrecord_t *record) {
    held_custom_key = keycode;

    if (record->event.pressed) {
        is_custom_key_held    = true;
        custom_key_held_timer = timer_read();
    } else {
        is_custom_key_held = false;

        if (!did_custom_key_repeat) tap_custom_key();

        did_custom_key_repeat = false;
    }
}

void try_repeat_custom_key(void) {
    static uint16_t last_repeat = 0;

    if (is_custom_key_held) {
        uint16_t elapsed = timer_elapsed(custom_key_held_timer);

        if (elapsed > CUSTOM_KEY_DELAY && timer_elapsed(last_repeat) > CUSTOM_KEY_INTERVAL) {
            tap_custom_key();
            did_custom_key_repeat = true;
            last_repeat           = timer_read();
        }
    }
}

bool handle_nonrepeatable_key(uint16_t keycode) {
    switch (keycode) {
        case KC_ESC:
            if (get_oneshot_mods()) {
                clear_oneshot_mods();
                return false;
            }
            return true;

        case XC_LFT_SPLT:
            tap_code16(LGUI(KC_J));
            wait_ms(4);
            tap_code(KC_LEFT);
            wait_ms(4);
            tap_code(KC_ENT);
            return false;

        case XC_RGT_SPLT:
            tap_code16(LGUI(KC_J));
            wait_ms(4);
            tap_code(KC_RGHT);
            wait_ms(4);
            tap_code(KC_ENT);
            return false;

        case DBL_QUOT:
            SEND_STRING("\"\"");
            tap_code(KC_LEFT);
            return false;

        case VIWPYIW:
            SEND_STRING("viwpyiw");
            return false;

        case KC_LPRN:
        case KC_LBRC:
        case KC_LCBR:
        case KC_LABK:
        case KC_QUOT:
        case KC_DQUO:
        case KC_GRV:
            handle_opening_pair(keycode);
            return false;

        case CLOSE_PAIR:
            return handle_closing_pair();
    }
    return true;
}
