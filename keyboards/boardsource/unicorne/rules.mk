POINTING_DEVICE_DRIVER = analog_joystick
SRC += lib/oled.c

RGBLIGHT_ENABLE = no
DEFERRED_EXEC_ENABLE = yes
SRC += features/achordion.c
SRC += features/custom_key_functions.c
SRC += custom_keys.c
MOUSEKEY_ENABLE = yes
COMBOS_ENABLE = yes
REPEAT_KEY_ENABLE = yes
