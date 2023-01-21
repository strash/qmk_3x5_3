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
	NAV,
	SYM,
	MEDIA
};

enum key {
    BASE = SAFE_RANGE, // change base layer and lang
    NAV_HOLD,          // go to NAV on hold
    SYM_HOLD,          // go to SYM on hold
    HIS_BACK,          // go back in the history (browser)
    HIS_FORW,          // go forward in the history (browser)
    PREV_TAB,          // go to the previous tab
    NEXT_TAB,          // go to the next tab
    PREV_APP,          // go to the previous app
    NEXT_APP,          // go to the next app
    PREW_SPC,          // go to the previous space
    NEXT_SPC,          // go to the next space
    WEB_INSPECTOR,     // open/close web inspector
};

bool is_select_prev_app_active = false;
bool is_select_next_app_active = false;

enum tap_dance {
	QWE_P_QUOT,
};

qk_tap_dance_action_t tap_dance_actions[] = {
	[QWE_P_QUOT] = ACTION_TAP_DANCE_DOUBLE(KC_P, KC_QUOT),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[DVO] = LAYOUT( \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
             XXXXXXX,      KC_QUOT,      KC_COMM,      KC_DOT,          KC_P,         KC_Y,            KC_F,         KC_G,         KC_C,         KC_R,         KC_L,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
             XXXXXXX, LCTL_T(KC_A), LOPT_T(KC_O), LSFT_T(KC_E), LCMD_T(KC_U),         KC_I,            KC_D, RCMD_T(KC_H), RSFT_T(KC_T), ROPT_T(KC_N), RCTL_T(KC_S),      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
             XXXXXXX,      KC_SCLN,         KC_Q,         KC_J,         KC_K,         KC_X,            KC_B,         KC_M,         KC_W,         KC_V,         KC_Z,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
														KC_ESC,     NAV_HOLD,       KC_SPC,          KC_ENT,     SYM_HOLD,      KC_BSPC \
											  //|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	// йцуке нгшщз(э)
	// фывап ролдж
	// ячсми тьбю/

	[QWE] = LAYOUT( \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,            KC_Y,         KC_U,         KC_I,         KC_O,TD(QWE_P_QUOT),     XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,         KC_A,         KC_S,         KC_D,         KC_F,         KC_G,            KC_H,         KC_J,         KC_K,         KC_L,      KC_SCLN,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,         KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,            KC_N,         KC_M,      KC_COMM,       KC_DOT,      KC_SLSH,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
														KC_ESC,     NAV_HOLD,       KC_SPC,          KC_ENT,     SYM_HOLD,LSFT_T(KC_BSPC) \
											  //|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	[NAV] = LAYOUT( \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,     HIS_BACK,     HIS_FORW,     PREV_TAB,     NEXT_TAB,LCMD(KC_BSPC),    RSG(KC_LEFT),RSFT(KC_LEFT),RSFT(KC_DOWN),  RSFT(KC_UP),RSFT(KC_RGHT),      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,LCTL_T(KC_TAB),     KC_LOPT,      KC_LSFT,      KC_LCMD,LOPT(KC_BSPC),   RCMD(KC_LEFT),      KC_LEFT,      KC_DOWN,        KC_UP,      KC_RGHT,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,     PREV_APP,     NEXT_APP,     PREW_SPC,     NEXT_SPC, LOPT(KC_DEL),    RSA(KC_LEFT),ROPT(KC_LEFT),ROPT(KC_DOWN),  ROPT(KC_UP),ROPT(KC_RGHT),      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
													   XXXXXXX,      XXXXXXX,      XXXXXXX,            LANG,         BASE,      KC_BSPC \
											  //|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	[SYM] = LAYOUT( \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,      KC_EXLM,        KC_AT,      KC_HASH,       KC_DLR,      KC_PERC,         KC_CIRC,      KC_AMPR,      KC_ASTR,      KC_LPRN,      KC_RPRN,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,LCTL_T(KC_P1),LOPT_T(KC_P2),LSFT_T(KC_P3),LCMD_T(KC_P4),        KC_P5,           KC_P6,RCMD_T(KC_P7),RSFT_T(KC_P8),ROPT_T(KC_P9),RCTL_T(KC_P0),      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,      KC_LCBR,      KC_RCBR,      KC_MINS,      KC_PLUS,       KC_GRV,         KC_SLSH,      KC_LBRC,      KC_RBRC,      KC_PIPE,      KC_BSLS,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
													   KC_UNDS,       KC_EQL,    TO(MEDIA),         XXXXXXX,      XXXXXXX,      XXXXXXX \
											  //|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	[MEDIA] = LAYOUT( \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,WEB_INSPECTOR,      XXXXXXX,        VIDEO,     SCR_TO_F,     SCR_TO_B,         XXXXXXX,      XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_MPLY,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_BRMD,      KC_BRMU,   LCMD(KC_V),         KC_MUTE,      KC_MRWD,      KC_VOLD,      KC_VOLU,      KC_MFFD,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
			 XXXXXXX,      KC_LEFT,      KC_DOWN,        KC_UP,      KC_RGHT,   LCMD(KC_C),         XXXXXXX,      KC_LEFT,      KC_DOWN,        KC_UP,      KC_RGHT,      XXXXXXX, \
	//|-------------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------------|
														KC_ESC,     NAV_HOLD,       KC_SPC,          KC_ENT,     SYM_HOLD,      KC_BSPC \
											  //|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),
};

void unselect_app_selection(void) {
	if (is_select_prev_app_active == true) {
		is_select_prev_app_active = false;
		unregister_mods(MOD_MASK_SG);
	}
	if (is_select_next_app_active == true) {
		is_select_next_app_active = false;
		unregister_mods(MOD_MASK_GUI);
	}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		case BASE:
			if (record->event.pressed) {
				default_layer_xor((DVO + 1) | (QWE + 1));
				register_mods(MOD_MASK_CSAG);
				register_code(KC_SPC);
				clear_keyboard();
			}
			return false;
		case NAV_HOLD:
			if (record->event.pressed) {
				if (IS_LAYER_ON(MEDIA)) layer_off(MEDIA);
				if (IS_LAYER_OFF(NAV)) layer_on(NAV);
			} else {
				unselect_app_selection();
				if (IS_LAYER_ON(NAV)) layer_off(NAV);
			}
			return false;
		case SYM_HOLD:
			if (record->event.pressed) {
				if (IS_LAYER_ON(MEDIA)) layer_off(MEDIA);
				if (IS_LAYER_OFF(SYM)) layer_on(SYM);
			} else {
				unselect_app_selection();
				if (IS_LAYER_ON(SYM)) layer_off(SYM);
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
		default:
			return true;
	}
};

