#include QMK_KEYBOARD_H
#include "quantum.h"
#include <stdio.h>
#include <stdint.h>
#include "strash_keymap.h"

// screenshot to buffer
#define SCR_TO_B SCMD(LCTL(KC_4))
// screenshot to file
#define SCR_TO_F SCMD(KC_4)
// screen recording to file
#define VIDEO SCMD(KC_5)
// change language
#define LANG HYPR(KC_SPC)

enum layout {
	DVO = 0,
	QWE,
	MEDIA,
	FN,
	NAV,
	SYM
};

enum key {
    BASE = SAFE_RANGE, // move to active base layer
    HIS_BACK,          // go back in the history (browser)
    HIS_FORW,          // go forward in the history (browser)
    PREV_TAB,          // go to the previous tab
    NEXT_TAB,          // go to the next tab
    PREV_APP,          // go to the previous app
    NEXT_APP,          // go to the next app
    PREW_SPC,          // go to the previous space
    NEXT_SPC,          // go to the next space
    WEB_INSPECTOR,     // open/close web inspector
    T_BASE_H_NAV,      // change base layer and lang on tap and open nav layer on hold
    T_MEDIA_H_SYM      // open media layer on tap and open sym layer on hold
};

int active_base   = DVO;
int opposite_base = QWE;

bool is_select_prev_app_active = false;
bool is_select_next_app_active = false;

uint16_t timer_base_nav;
uint16_t timer_media_sym;

enum tap_dance {
	QWE_P_QUOT,
	ESC_LANG
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[QWE_P_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_QUOT),
	[ESC_LANG] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, LANG)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [DVO] = LAYOUT( \
    //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------|
             KC_QUOT,      KC_COMM,      KC_DOT,          KC_P,         KC_Y,            KC_F,         KC_G,         KC_C,         KC_R,         KC_L, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------|
        LCTL_T(KC_A), LOPT_T(KC_O), LSFT_T(KC_E), LCMD_T(KC_U),         KC_I,            KC_D, RCMD_T(KC_H), RSFT_T(KC_T), ROPT_T(KC_N), RCTL_T(KC_S), \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------|
             KC_SCLN,         KC_Q,         KC_J,         KC_K,         KC_X,            KC_B,         KC_M,         KC_W,         KC_V,         KC_Z, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------|
									TD(ESC_LANG), T_BASE_H_NAV,       KC_ENT,          KC_SPC,T_MEDIA_H_SYM,      KC_BSPC \
								//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

    // йцуке нгшщз(э)
    // фывап ролдж
    // ячсми тьбю/

    [QWE] = LAYOUT( \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	            KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,            KC_Y,         KC_U,         KC_I,         KC_O, TD(QWE_P_QUOT), \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	            KC_A,         KC_S,         KC_D,         KC_F,         KC_G,            KC_H,         KC_J,         KC_K,         KC_L,        KC_SCLN, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	            KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,            KC_N,         KC_M,      KC_COMM,       KC_DOT,        KC_SLSH, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
								  LSFT_T(KC_ESC), T_BASE_H_NAV,       KC_ENT,          KC_SPC,T_MEDIA_H_SYM,      KC_BSPC \
								//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

    [MEDIA] = LAYOUT( \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	           KC_NO,        KC_NO,        VIDEO,     SCR_TO_F,     SCR_TO_B,           KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_MPLY, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	           KC_NO,        KC_NO,      KC_BRMD,      KC_BRMU,   LCMD(KC_V),         KC_MUTE,      KC_MRWD,      KC_VOLD,      KC_VOLU,        KC_MFFD, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	         KC_LEFT,      KC_DOWN,        KC_UP,      KC_RGHT,   LCMD(KC_C),           KC_NO,      KC_LEFT,      KC_DOWN,        KC_UP,        KC_RGHT, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
								    TD(ESC_LANG),         BASE,       KC_ENT,          KC_SPC,       TO(FN),      KC_BSPC \
								//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

    [FN] = LAYOUT( \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	           KC_F1,        KC_F2,        KC_F3,        KC_F4,        KC_F5,           KC_F6,        KC_F7,        KC_F8,        KC_F9,         KC_F10, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	          KC_F11,       KC_F12,       KC_F13,       KC_F14,       KC_F15,          KC_F16,       KC_F17,       KC_F18,       KC_F19,          KC_NO, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
	           KC_NO,        KC_NO,        KC_NO,        KC_NO,        KC_NO,           KC_NO,        KC_NO,        KC_NO,        KC_NO,          KC_NO, \
	//|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
									TD(ESC_LANG),         BASE,       KC_ENT,          KC_SPC,       TG(FN),      KC_BSPC \
								//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

    [NAV] = LAYOUT( \
        //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
		        HIS_BACK,     HIS_FORW,     PREV_TAB,     NEXT_TAB,LCMD(KC_BSPC),    RSG(KC_LEFT),RSFT(KC_LEFT),RSFT(KC_DOWN),  RSFT(KC_UP),  RSFT(KC_RGHT), \
        //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
		  LCTL_T(KC_TAB),      KC_LOPT,      KC_LSFT,      KC_LCMD,LOPT(KC_BSPC),   RCMD(KC_LEFT),      KC_LEFT,      KC_DOWN,        KC_UP,        KC_RGHT, \
        //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
		        PREV_APP,     NEXT_APP,     PREW_SPC,     NEXT_SPC,WEB_INSPECTOR,    RSA(KC_LEFT),ROPT(KC_LEFT),ROPT(KC_DOWN),  ROPT(KC_UP),  ROPT(KC_RGHT), \
        //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
										TD(ESC_LANG),        KC_NO,       KC_ENT,          KC_SPC,        KC_NO,      KC_BSPC \
									//|-------------+-------------+-------------|  |-------------+-------------+-------------|
        ),

    [SYM] = LAYOUT( \
        //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
		         KC_EXLM,        KC_AT,      KC_HASH,       KC_DLR,      KC_PERC,         KC_CIRC,      KC_AMPR,      KC_ASTR,      KC_LPRN,        KC_RPRN, \
        //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
		   LCTL_T(KC_P1),LOPT_T(KC_P2),LSFT_T(KC_P3),LCMD_T(KC_P4),        KC_P5,           KC_P6,RCMD_T(KC_P7),RSFT_T(KC_P8),ROPT_T(KC_P9),  RCTL_T(KC_P0), \
        //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
		         KC_LCBR,      KC_RCBR,      KC_MINS,       KC_EQL,       KC_GRV,         KC_SLSH,      KC_LBRC,      KC_RBRC,      KC_PIPE,        KC_BSLS, \
        //|-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+---------------|
										TD(ESC_LANG),        KC_NO,       KC_ENT,          KC_SPC,        KC_NO,      KC_BSPC \
									//|-------------+-------------+-------------|  |-------------+-------------+-------------|
        ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case DVO:
            active_base   = DVO;
            opposite_base = QWE;
            break;
        case QWE:
            active_base   = QWE;
            opposite_base = DVO;
            break;
    }
    return state;
};

void unselect_app_selection(void) {
    if (is_select_prev_app_active == true) {
        is_select_prev_app_active = false;
        clear_mods();
    }
    if (is_select_next_app_active == true) {
        is_select_next_app_active = false;
        clear_mods();
    }
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case T_BASE_H_NAV:
            if (record->event.pressed) {
                timer_base_nav = timer_read();
                if (IS_LAYER_OFF(NAV)) layer_on(NAV);
            } else {
                if (IS_LAYER_ON(NAV)) layer_off(NAV);
                if (timer_elapsed(timer_base_nav) < TAPPING_TERM) {
                    default_layer_xor((DVO + 1) | (QWE + 1));
					register_mods(MOD_MASK_CSAG);
					register_code(KC_SPC);
                    clear_keyboard();
                }
            }
            return false;
        case T_MEDIA_H_SYM:
            if (record->event.pressed) {
                timer_media_sym = timer_read();
                if (IS_LAYER_OFF(SYM)) layer_on(SYM);
            } else {
                if (IS_LAYER_ON(SYM)) layer_off(SYM);
                if (timer_elapsed(timer_media_sym) < TAPPING_TERM) {
                    layer_on(MEDIA);
                }
            }
            return false;
        case BASE:
            if (record->event.pressed) {
                layer_clear();
            }
            return false;
        case HIS_BACK:
            if (record->event.pressed) {
				register_mods(MOD_MASK_GUI);
				register_code(KC_LBRC);
            } else {
                clear_keyboard();
            }
            return false;
        case HIS_FORW:
            if (record->event.pressed) {
				register_mods(MOD_MASK_GUI);
				register_code(KC_RBRC);
            } else {
                clear_keyboard();
            }
            return false;
        case PREV_TAB:
            if (record->event.pressed) {
				register_mods(MOD_MASK_CS);
				register_code(KC_TAB);
            } else {
                clear_keyboard();
            }
            return false;
        case NEXT_TAB:
            if (record->event.pressed) {
				register_mods(MOD_MASK_CTRL);
				register_code(KC_TAB);
            } else {
                clear_keyboard();
            }
            return false;
        case PREV_APP:
            if (record->event.pressed) {
                if (is_select_prev_app_active == false) {
                    if (is_select_next_app_active == true) {
                        is_select_next_app_active = false;
                        clear_mods();
                    }
                    register_mods(MOD_MASK_SG);
                    tap_code(KC_TAB);
                    is_select_prev_app_active = true;
                } else {
                    tap_code(KC_TAB);
                }
            }
            return false;
        case NEXT_APP:
            if (record->event.pressed) {
                if (is_select_next_app_active == false) {
                    if (is_select_prev_app_active == true) {
                        is_select_prev_app_active = false;
                        clear_mods();
                    }
                    register_mods(MOD_MASK_GUI);
                    tap_code(KC_TAB);
                    is_select_next_app_active = true;
                } else {
                    tap_code(KC_TAB);
                }
            }
            return false;
        case PREW_SPC:
            if (record->event.pressed) {
				register_mods(MOD_MASK_CTRL);
				register_code(KC_LEFT);
            } else {
                clear_keyboard();
            }
            return false;
        case NEXT_SPC:
            if (record->event.pressed) {
				register_mods(MOD_MASK_CTRL);
				register_code(KC_RGHT);
            } else {
                clear_keyboard();
            }
            return false;
        case WEB_INSPECTOR:
            if (record->event.pressed) {
				register_mods(MOD_MASK_AG);
				register_code(KC_I);
            } else {
                clear_keyboard();
            }
            return false;
        case KC_ENT:
            if (record->event.pressed) {
                unselect_app_selection();
            }
            return true;
        case KC_ESC:
            if (record->event.pressed) {
                unselect_app_selection();
            }
            return true;
        default:
            return true;
    }
};
