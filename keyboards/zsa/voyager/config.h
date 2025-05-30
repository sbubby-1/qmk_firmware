// Copyright 2023 ZSA Technology Labs, Inc <@zsa>
// Copyright 2023 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define MATRIX_COLS 7
#define MATRIX_ROWS 12

#define IS31FL3731_I2C_ADDRESS_1 IS31FL3731_I2C_ADDRESS_GND
#define IS31FL3731_I2C_ADDRESS_2 IS31FL3731_I2C_ADDRESS_VCC

#define IS31FL3731_I2C_TIMEOUT 5

#define MOUSEKEY_WHEEL_INTERVAL MOUSEKEY_INTERVAL
#define MOUSEKEY_WHEEL_MAX_SPEED MOUSEKEY_MAX_SPEED
#define MOUSEKEY_WHEEL_TIME_TO_MAX MOUSEKEY_TIME_TO_MAX

#define MK_COMBINED
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 6
#define MOUSEKEY_INITIAL_SPEED 12
#define MOUSEKEY_MAX_SPEED 5
#define MOUSEKEY_MOVE_DELTA 4

#define ORYX_CONFIGURATOR

#define TAPPING_TOGGLE 3

#define TAPPING_TERM 170
#define PERMISSIVE_HOLD
#define MAX_DEFERRED_EXECUTORS 10
#define QUICK_TAP_TERM_PER_KEY

#undef RGBLIGHT_DEFAULT_ON
#define RGBLIGHT_DEFAULT_ON false

#define ACHORDION_STREAK
