#include QMK_KEYBOARD_H
#include "custom_keys.h"

const uint16_t repeatable_keys[]   = {LEFT_WORD, DELETE_LINE, RIGHT_WORD};
const size_t   repeatable_keys_len = sizeof(repeatable_keys) / sizeof(repeatable_keys[0]);

bool is_repeatable_key(uint16_t keycode) {
    for (size_t i = 0; i < repeatable_keys_len; i++) {
        if (keycode == repeatable_keys[i]) {
            return true;
        }
    }
    return false;
}
