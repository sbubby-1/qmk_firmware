#include "quantum.h"

// Base layer

// Left-hand home row mods
#define LCTL_N LCTL_T(KC_N)
#define LGUI_R LGUI_T(KC_R)
#define LALT_S LALT_T(KC_S)

// Right-hand home row mods
#define RALT_H RALT_T(KC_H)
#define RGUI_E RGUI_T(KC_E)
#define RCTL_I RCTL_T(KC_I)

#define MOUSE_ESC LT(MOUSE, KC_ESC)

#define HYPR_SPC MT(MOD_LCTL | MOD_LSFT | MOD_LALT | MOD_LGUI, KC_SPC)

// Nav layer

// Left-hand only
#define BACK G(KC_LEFT)
#define FORWARD G(KC_RIGHT)
#define CLOSE_WIN G(KC_W)
#define COPY G(KC_C)
#define PASTE G(KC_V)
#define TAB_L LSG(KC_LBRC)
#define TAB_R LSG(KC_RBRC)
#define WS_1 C(KC_1)
#define WS_2 C(KC_2)

#define HMRW_CLICK HYPR(KC_A)
#define HMRW_SCROLL HYPR(KC_H)
#define SCRNSHOT LCSG(KC_4)

// Sym layer

#define XC_CONSOLE LSG(KC_Y)
#define XC_FORMAT LAG(KC_S)
#define XC_LINE_NUM LCAG(KC_C)
#define XC_PREVIEW LAG(KC_ENT)
#define XC_SEARCH LSG(KC_O)
#define XC_SHOW LSG(KC_J)
#define XC_SIDEBAR G(KC_0)

enum custom_keycodes {
    DBL_QUOT = SAFE_RANGE,
    VIWPYIW,
    CLOSE_PAIR,
    DEL_LINE,
    SLW,
    SRW
};
