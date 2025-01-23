#include QMK_KEYBOARD_H

// screenshot to buffer
#define SCR_TO_B SCMD(LCTL(KC_4))
// screenshot to file
#define SCR_TO_F SCMD(KC_4)
// screen recording to file
#define VIDEO SCMD(KC_5)
// change language
#define LANG HYPR(KC_SPC)

enum layout {
	XYOU = 0,
	QWE,
	NAV,
	SYM,
	MEDIA
};

// nav hold
#define NAV_HOLD LT(NAV, KC_ESC)
// sym hold
#define SYM_HOLD LT(SYM, KC_BSPC)

enum key {
    BASE = SAFE_RANGE, // change base layer and lang
    HIS_BACK,          // go back in the history (browser)
    HIS_FORW,          // go forward in the history (browser)
    PREV_TAB,          // go to the previous tab
    NEXT_TAB,          // go to the next tab
    PREW_SPC,          // go to the previous space
    NEXT_SPC,          // go to the next space
    WEB_INSPECTOR,     // open/close web inspector
};

// tap dance

enum tap_dance {
	TILD_GRV,
	CIRC_BSLS,
	QWE_P_QUOT,
	QWE_M_LBRC,
	QWE_COMM_RBRC,
	QWE_SLSH_BSLS,
};

tap_dance_action_t tap_dance_actions[] = {
	[TILD_GRV]      = ACTION_TAP_DANCE_DOUBLE(KC_TILD, KC_GRV),
	[CIRC_BSLS]     = ACTION_TAP_DANCE_DOUBLE(KC_CIRC, KC_BSLS),
	[QWE_P_QUOT]    = ACTION_TAP_DANCE_DOUBLE(KC_P,    KC_QUOT),
	[QWE_M_LBRC]    = ACTION_TAP_DANCE_DOUBLE(KC_M,    KC_LBRC),
	[QWE_COMM_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_RBRC),
	[QWE_SLSH_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
};

// combo

enum combos {
	XYOU_CAPS_WORD,
	QWE_CAPS_WORD,
	MEDIA_TOG_WITH_MOD,
	MEDIA_TOG,
};

const uint16_t PROGMEM xyou_caps_word_combo[] = {LSFT_T(KC_E), RSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM qwe_caps_word_combo[] = {LSFT_T(KC_D), RSFT_T(KC_K), COMBO_END};
const uint16_t PROGMEM media_w_mod_combo[] = {LCTL_T(KC_SPC), RCTL_T(KC_ENT), COMBO_END};
const uint16_t PROGMEM media_combo[] = {KC_SPC, KC_ENT, COMBO_END};

combo_t key_combos[] = {
	[XYOU_CAPS_WORD] = COMBO(xyou_caps_word_combo, CW_TOGG),
	[QWE_CAPS_WORD] = COMBO(qwe_caps_word_combo, CW_TOGG),
	[MEDIA_TOG_WITH_MOD] = COMBO(media_w_mod_combo, TG(MEDIA)),
	[MEDIA_TOG] = COMBO(media_combo, TG(MEDIA)),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[XYOU] = LAYOUT( \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
       XXXXXXX,         KC_X,         KC_Y,         KC_O,         KC_U,      KC_QUOT,            KC_G,         KC_C,         KC_L,         KC_P,         KC_M,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
       XXXXXXX,         KC_H, LOPT_T(KC_I), LSFT_T(KC_E), LCMD_T(KC_A),       KC_DOT,            KC_D, RCMD_T(KC_S), RSFT_T(KC_T), ROPT_T(KC_N),         KC_R,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
       XXXXXXX,      KC_SCLN,         KC_Z,         KC_J,         KC_K,      KC_COMM,            KC_B,         KC_W,         KC_F,         KC_V,         KC_Q,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
											     XXXXXXX,     NAV_HOLD,LCTL_T(KC_SPC), RCTL_T(KC_ENT),     SYM_HOLD,      XXXXXXX \
										//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	//           э
	// йцуке нгшщз
	// фывап ролдж
	// ячсми тьбю/
	//        хъ ё

	[QWE] = LAYOUT( \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,            KC_Y,         KC_U,         KC_I,        KC_O,TD(QWE_P_QUOT),XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,         KC_A, LOPT_T(KC_S), LSFT_T(KC_D), LCMD_T(KC_F),         KC_G,            KC_H, RCMD_T(KC_J), RSFT_T(KC_K), ROPT_T(KC_L),      KC_SCLN,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,         KC_Z,         KC_X,         KC_C,         KC_V,         KC_B,            KC_N,TD(QWE_M_LBRC),TD(QWE_COMM_RBRC),KC_DOT,TD(QWE_SLSH_BSLS),XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
											     XXXXXXX,     NAV_HOLD,       KC_SPC,          KC_ENT,     SYM_HOLD,      XXXXXXX \
										//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	[NAV] = LAYOUT( \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,     HIS_BACK,     HIS_FORW,     PREV_TAB,     NEXT_TAB,LCMD(KC_BSPC),    RSG(KC_LEFT),RSFT(KC_LEFT),RSFT(KC_DOWN),  RSFT(KC_UP),RSFT(KC_RGHT),XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX, LSFT(KC_TAB),       KC_TAB,      KC_LSFT,      KC_LCMD,LOPT(KC_BSPC),   RCMD(KC_LEFT),      KC_LEFT,      KC_DOWN,        KC_UP,      KC_RGHT,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,         KC_Q,      XXXXXXX,     PREW_SPC,     NEXT_SPC, LOPT(KC_DEL),    RSA(KC_LEFT),ROPT(KC_LEFT),ROPT(KC_DOWN),  ROPT(KC_UP),ROPT(KC_RGHT),XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
												 XXXXXXX,      XXXXXXX,      XXXXXXX,            LANG,         BASE,      XXXXXXX \
										//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	[SYM] = LAYOUT( \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,      KC_EXLM,        KC_AT,      KC_HASH,       KC_DLR,      KC_PERC,   TD(CIRC_BSLS),      KC_AMPR,      KC_PIPE,      KC_ASTR,      KC_QUES,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,        KC_P1,        KC_P2,        KC_P3,        KC_P4,        KC_P5,           KC_P6,        KC_P7,        KC_P8,        KC_P9,        KC_P0,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,      KC_LCBR,      KC_RCBR,      KC_MINS,      KC_PLUS, TD(TILD_GRV),         KC_SLSH,      KC_LBRC,      KC_RBRC,      KC_LPRN,      KC_RPRN,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
												 XXXXXXX,      KC_UNDS,       KC_EQL,         XXXXXXX,      XXXXXXX,      XXXXXXX \
										//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	[MEDIA] = LAYOUT( \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,WEB_INSPECTOR,      XXXXXXX,        VIDEO,     SCR_TO_F,     SCR_TO_B,          KC_ESC,      KC_MPLY,      KC_MUTE,      XXXXXXX,      XXXXXXX,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,      XXXXXXX,      XXXXXXX,      KC_BRMD,      KC_BRMU,   LCMD(KC_C),         KC_BSPC,      KC_MRWD,      KC_VOLD,      KC_VOLU,      KC_MFFD,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,      KC_LEFT,      KC_DOWN,        KC_UP,      KC_RGHT,   LCMD(KC_V),         XXXXXXX,      KC_LEFT,      KC_DOWN,        KC_UP,      KC_RGHT,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
											     XXXXXXX,    TG(MEDIA),       KC_SPC,          KC_ENT,    TG(MEDIA),      XXXXXXX \
										//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
		case BASE:
			if (record->event.pressed) {
				default_layer_xor((XYOU + 1) | (QWE + 1));
				register_mods(MOD_MASK_CSAG);
				register_code(KC_SPC);
				clear_keyboard();
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
	}
	return true;
};

