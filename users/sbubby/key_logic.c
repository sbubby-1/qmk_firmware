#include "keys.h"
#include "deferred_exec.h"
#include <stdint.h>
#include "timer.h"

// MARK: Properties

// The delay (in ms) for the repeatable custom key to be held before it's first sent.
static const uint16_t REPEATABLE_CUSTOM_KEY_INITIAL_DELAY = 140;

// The delay (in ms) between sends of the repeatable custom key.
static const uint16_t REPEATABLE_CUSTOM_KEY_REPEAT_DELAY = 50;

// The keycode for the currently held repeatable custom key.
static uint16_t current_repeatable_custom_keycode = 0;

// A Boolean indicating whether the repeatable custom key has been sent yet.
static bool has_sent_repeatable_custom_key = false;

// A token for the deferred task to send the repeatable custom key. This is used to cancel the task.
deferred_token repeat_custom_key_token = 0;

// The keycode for the last used opening pair.
static uint16_t opening_pair_keycode = KC_NO;

// MARK: Function declarations

// The deferred task to send the repeatable custom key. The return value is used by QMK core as the
// delay before repeating this task.
static uint32_t repeat_custom_key_task(uint32_t trigger_time, void *cb_arg);

// Sends `current_repeatable_custom_keycode`.
static void send_held_repeatable_custom_key(void);

// Cancels the deferred execution of `repeat_custom_key_task` and clears repeatable custom key
// state.
static void cancel_repeat_custom_key(void);

// Returns a Boolean indicating whether this custom key is repeatable.
static bool is_repeatable_key(uint16_t keycode);

// Handles the behavior for non-repeatable custom keys and returns a Boolean indicating whether
// further processing of this keycode is needed.
static bool handle_nonrepeatable_custom_key(uint16_t keycode);

// Returns a Boolean indicating whether this keycode is an opening pair.
static bool is_opening_pair(uint16_t keycode);

// Sends the corresponding closing pair for the last opening pair and moves inside the pair.
static bool handle_closing_pair(void);

// MARK: QMK overrides

__attribute__((weak)) bool process_record_user_weak(uint16_t keycode, keyrecord_t *record) {
    if (is_repeatable_key(keycode)) {
        if (keycode != current_repeatable_custom_keycode) {
            cancel_repeat_custom_key();
        }

        if (record->event.pressed) {
            current_repeatable_custom_keycode = keycode;
            repeat_custom_key_token           = defer_exec(REPEATABLE_CUSTOM_KEY_INITIAL_DELAY, repeat_custom_key_task, NULL);
        } else {
            if (!has_sent_repeatable_custom_key) {
                send_held_repeatable_custom_key();
            }
            cancel_repeat_custom_key();
        }
        return false;
    }

    if (is_opening_pair(keycode)) {
        opening_pair_keycode = keycode;
    }

    if (record->event.pressed) {
        return handle_nonrepeatable_custom_key(keycode);
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_user_weak(keycode, record);
}

__attribute__((weak)) bool get_chordal_hold_weak(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    switch (tap_hold_keycode) {
        case LCTL_N:
            if (other_keycode == KC_D) {
                return true;
            }
            break;

        case RALT_H:
            switch (other_keycode) {
                case KC_J:
                case KC_Y:
                case KC_O:
                case KC_U:
                case KC_COMM:
                    return true;
            }
            break;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}

bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    return get_chordal_hold_weak(tap_hold_keycode, tap_hold_record, other_keycode, other_record);
}

// MARK: Helper functions

static uint32_t repeat_custom_key_task(uint32_t trigger_time, void *cb_arg) {
    send_held_repeatable_custom_key();
    return REPEATABLE_CUSTOM_KEY_REPEAT_DELAY;
}

static void send_held_repeatable_custom_key(void) {
    has_sent_repeatable_custom_key = true;
    switch (current_repeatable_custom_keycode) {
        case SLW:
            register_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            tap_code(KC_LEFT);
            unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            break;

        case SRW:
            register_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            tap_code(KC_RGHT);
            unregister_mods(MOD_BIT(KC_LSFT) | MOD_BIT(KC_LALT));
            break;

        case DEL_LINE:
            SEND_STRING(SS_LGUI(SS_TAP(X_RGHT)));
            SEND_STRING(SS_LGUI(SS_TAP(X_BSPC)));
            break;
    }
}

static void cancel_repeat_custom_key(void) {
    cancel_deferred_exec(repeat_custom_key_token);
    has_sent_repeatable_custom_key    = false;
    current_repeatable_custom_keycode = 0;
    repeat_custom_key_token           = 0;
}

static bool handle_nonrepeatable_custom_key(uint16_t keycode) {
    switch (keycode) {
        case KC_ESC:
            if (get_oneshot_mods()) {
                clear_oneshot_mods();
                return false;
            }
            return true;

        case DBL_QUOT:
            SEND_STRING("\"\"");
            tap_code(KC_LEFT);
            return false;

        case VIWPYIW:
            SEND_STRING("viwpyiw");
            return false;

        case CLOSE_PAIR:
            return handle_closing_pair();

        case COPY_ALL:
            tap_code16(LGUI(KC_A));
            tap_code16(LGUI(KC_C));
            return false;

        case SLACK:
            tap_code16(LALT(KC_S));
            tap_code16_delay(LGUI(KC_K), 100);
            return false;

        case FINDER:
            tap_code16(HYPR(KC_G));
            tap_code16_delay(LSG(KC_E), 400);
            return false;
    }
    return true;
}

static bool handle_closing_pair(void) {
    switch (opening_pair_keycode) {
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
    opening_pair_keycode = KC_NO;
    return true;
}

static bool is_opening_pair(uint16_t keycode) {
    switch (keycode) {
        case KC_LPRN:
        case KC_LBRC:
        case KC_LCBR:
        case KC_LABK:
        case KC_QUOT:
        case KC_DQUO:
        case KC_GRV:
            return true;
        default:
            return false;
    }
}

static bool is_repeatable_key(uint16_t keycode) {
    switch (keycode) {
        case DEL_LINE:
        case SLW:
        case SRW:
            return true;
        default:
            return false;
    }
}
