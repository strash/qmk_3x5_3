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
	GFU = 0,
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
    PREV_APP,          // go to the previous app
    NEXT_APP,          // go to the next app
    PREW_SPC,          // go to the previous space
    NEXT_SPC,          // go to the next space
    WEB_INSPECTOR,     // open/close web inspector
    C_MEDIA,           // close media
};

// tap dance

enum tap_dance {
	TILD_GRV,
	MINS_PLUS,
	CIRC_BSLS,
	QWE_P_QUOT,
	QWE_M_LBRC,
	QWE_COMM_RBRC,
	QWE_SLSH_BSLS,
};

tap_dance_action_t tap_dance_actions[] = {
	[TILD_GRV]      = ACTION_TAP_DANCE_DOUBLE(KC_TILD, KC_GRV),
	[MINS_PLUS]     = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_PLUS),
	[CIRC_BSLS]     = ACTION_TAP_DANCE_DOUBLE(KC_CIRC, KC_BSLS),
	[QWE_P_QUOT]    = ACTION_TAP_DANCE_DOUBLE(KC_P,    KC_QUOT),
	[QWE_M_LBRC]    = ACTION_TAP_DANCE_DOUBLE(KC_M,    KC_LBRC),
	[QWE_COMM_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_RBRC),
	[QWE_SLSH_BSLS] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
};

// combo

enum combos {
	DVO_CAPS_WORD,
	QWE_CAPS_WORD,
};

const uint16_t PROGMEM dvo_caps_word_combo[] = {LSFT_T(KC_E), RSFT_T(KC_T), COMBO_END};
const uint16_t PROGMEM qwe_caps_word_combo[] = {LSFT_T(KC_D), RSFT_T(KC_K), COMBO_END};

combo_t key_combos[] = {
	[DVO_CAPS_WORD] = COMBO(dvo_caps_word_combo, CW_TOGG),
	[QWE_CAPS_WORD] = COMBO(qwe_caps_word_combo, CW_TOGG),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[GFU] = LAYOUT( \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
       XXXXXXX,         KC_G,         KC_F,         KC_U,         KC_P,      KC_COMM,            KC_B,         KC_C,         KC_M,         KC_H,         KC_L,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
       XXXXXXX,         KC_O, LOPT_T(KC_A), LSFT_T(KC_E), LCMD_T(KC_I),         KC_Y,            KC_D, RCMD_T(KC_S), RSFT_T(KC_T), ROPT_T(KC_N),         KC_R,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
       XXXXXXX,         KC_Q,         KC_X,         KC_Z,       KC_DOT,      KC_QUOT,         KC_SCLN,         KC_W,         KC_V,         KC_K,         KC_J,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
											     XXXXXXX,     NAV_HOLD,LCTL_T(KC_SPC), RCTL_T(KC_ENT),     SYM_HOLD,      XXXXXXX \
										//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),

	// йцуке нгшщз(э)
	// фывап ролдж
	// ячсми тьбю/

	[QWE] = LAYOUT( \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,         KC_Q,         KC_W,         KC_E,         KC_R,         KC_T,            KC_Y,         KC_U,         KC_I,        KC_O,TD(QWE_P_QUOT),XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
	   XXXXXXX,         KC_A,         KC_S, LSFT_T(KC_D),         KC_F,         KC_G,            KC_H,         KC_J, RSFT_T(KC_K),         KC_L,      KC_SCLN,XXXXXXX, \
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
	   XXXXXXX,     PREV_APP,     NEXT_APP,     PREW_SPC,     NEXT_SPC, LOPT(KC_DEL),    RSA(KC_LEFT),ROPT(KC_LEFT),ROPT(KC_DOWN),  ROPT(KC_UP),ROPT(KC_RGHT),XXXXXXX, \
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
	   XXXXXXX,      KC_LCBR,      KC_RCBR,TD(MINS_PLUS),       KC_EQL, TD(TILD_GRV),         KC_SLSH,      KC_LBRC,      KC_RBRC,      KC_LPRN,      KC_RPRN,XXXXXXX, \
	//|-------+-------------+-------------+-------------+-------------+-------------|  |-------------+-------------+-------------+-------------+-------------+-------|
												 XXXXXXX,      KC_UNDS,    TO(MEDIA),         XXXXXXX,      XXXXXXX,      XXXXXXX \
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
											     XXXXXXX,      C_MEDIA,       KC_SPC,          KC_ENT,      C_MEDIA,      XXXXXXX \
										//|-------------+-------------+-------------|  |-------------+-------------+-------------|
	),
};

bool is_select_prev_app_active = false;
bool is_select_next_app_active = false;

void unselect_app_selection(void) {
	// unselect PREV_APP
	if (is_select_prev_app_active == true) {
		is_select_prev_app_active = false;
		unregister_mods(MOD_MASK_SG);
	}
	// unselect NEXT_APP
	if (is_select_next_app_active == true) {
		is_select_next_app_active = false;
		unregister_mods(MOD_MASK_GUI);
	}
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	static bool is_nav_interrupted = false;
	static bool is_sym_interrupted = false;

	if (record->event.pressed) {
		is_nav_interrupted = true;
		is_sym_interrupted = true;
	}

    switch (keycode) {
		case BASE:
			if (record->event.pressed) {
				default_layer_xor((GFU + 1) | (QWE + 1));
				register_mods(MOD_MASK_CSAG);
				register_code(KC_SPC);
				clear_keyboard();
			}
			return false;
		case NAV_HOLD:
			if (record->event.pressed) {
				is_nav_interrupted = false;
			} else {
				unselect_app_selection();
				if (is_nav_interrupted && IS_LAYER_ON(NAV)) {
					layer_off(NAV);
					return false;
				}
			}
			return true;
		case SYM_HOLD:
			if (record->event.pressed) {
				is_sym_interrupted = false;
			} else {
				unselect_app_selection();
				if (is_sym_interrupted && IS_LAYER_ON(SYM)) {
					layer_off(SYM);
					return false;
				}
			}
			return true;
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
		case C_MEDIA:
			if (IS_LAYER_ON(MEDIA)) layer_off(MEDIA);
			return false;
	}
	return true;
};

