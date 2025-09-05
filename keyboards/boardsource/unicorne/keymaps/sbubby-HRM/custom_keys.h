#include "quantum.h"

// Left-hand home row mods
#define HOME_N LCTL_T(KC_N)
#define HOME_R LGUI_T(KC_R)
#define HOME_T LSFT_T(KC_T)
#define HOME_S LALT_T(KC_S)

// Right-hand home row mods
#define HOME_H RALT_T(KC_H)
#define HOME_A RSFT_T(KC_A)
#define HOME_E LGUI_T(KC_E)
#define HOME_I RCTL_T(KC_I)

#define SCRNSHOT LGUI(LCTL(LSFT(KC_4)))
#define BACK G(KC_LEFT)
#define FORWARD G(KC_RIGHT)
#define CLOSE_WIN G(KC_W)
#define XCODE_SPLIT HYPR(KC_U)
#define HMRW_SCROLL HYPR(KC_J)
#define HMRW_CLICK HYPR(KC_K)
#define XC_CONSOLE LSG(KC_Y)
#define XC_PREVIEW LAG(KC_ENT)
#define WS_1 C(KC_1)
#define WS_2 C(KC_2)
#define TAB_L LSG(KC_LBRC)
#define TAB_R LSG(KC_RBRC)
#define XC_SEARCH LSG(KC_O)
#define XC_SHOW LSG(KC_J)
#define XC_SIDEBAR G(KC_0)
#define ZOOM_IN G(KC_PLUS)
#define ZOOM_OUT G(KC_MINS)

#define HYPR_SPC MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI, KC_SPC)

extern const uint16_t repeatable_keys[];
extern const size_t   repeatable_keys_len;
enum custom_keycodes { XC_LFT_SPLT = SAFE_RANGE, XC_RGT_SPLT, DBL_QUOT, VIWPYIW, DELETE_LINE, LEFT_WORD, RIGHT_WORD, CLOSE_PAIR };

bool is_repeatable_key(uint16_t keycode);
