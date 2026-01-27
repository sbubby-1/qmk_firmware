#define MK_KINETIC_SPEED
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_INTERVAL 6
#define MOUSEKEY_INITIAL_SPEED 240
#define MOUSEKEY_BASE_SPEED 3200
#define MOUSEKEY_MOVE_DELTA 24

#define TAPPING_TERM 230
// Default: Tapping term must pass for the mod-tap to become a mod.
// Permissive hold: If another key is pressed and released during the tapping term, the mod is used.
// Hold on other key press: If another key is pressed during the tapping term, the mod is used.
#define PERMISSIVE_HOLD

// https://docs.qmk.fm/tap_hold#chordal-hold
// If another key is pressed within the tapping term while a mod-tap key is held, if the two keys
// are on the same hand, the mod-tap is settled as a tap. For opposing hands, no logic is inserted.
#define CHORDAL_HOLD

// Modifiers are applied greedily, and if tapped, dismissed shortly before the tap fires.
#define SPECULATIVE_HOLD

#define RGBLIGHT_DEFAULT_ON false
