#include QMK_KEYBOARD_H
#include "keymap.h"

// Create a simple logo for the chocolad
static void render_logo(void) {
    static const char PROGMEM my_logo[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xf0, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0xf0,
        0xf0, 0x00, 0x00, 0x00, 0x10, 0x10, 0x30, 0xf0, 0x20, 0x20, 0x60, 0x40, 0xc0, 0xc0, 0x80, 0x80,
        0x00, 0x00, 0x00, 0x00, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30, 0x00,
        0x00, 0x00, 0x00, 0xc0, 0xe0, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0xe0, 0xc0, 0x00,
        0x00, 0x00, 0x00, 0xc0, 0x60, 0x30, 0x30, 0x10, 0x10, 0x10, 0x30, 0x30, 0x60, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0xc0, 0xe0, 0x30, 0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0xe0, 0xc0, 0x00, 0x00,
        0x00, 0x00, 0x30, 0x30, 0x30, 0x30, 0x30, 0xf0, 0xf0, 0x30, 0x30, 0x30, 0x30, 0x00, 0x00, 0x00,
        0x00, 0xc0, 0xe0, 0x30, 0x30, 0x10, 0x10, 0x10, 0x10, 0x30, 0x30, 0xe0, 0x80, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x06, 0x04, 0x04, 0x04, 0x04, 0x06, 0x07, 0x03,
        0x00, 0x00, 0x00, 0x00, 0x04, 0x04, 0x06, 0x07, 0x02, 0x02, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x01, 0x03, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x06, 0x03, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x07, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x06, 0x07, 0x00, 0x00,
        0x00, 0x00, 0x01, 0x03, 0x06, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x06, 0x03, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x06, 0x06, 0x06, 0x06, 0x00, 0x00, 0x00,
        0x00, 0x03, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x07, 0x01, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(my_logo, sizeof(my_logo));
}

// Flip the right display 180 degrees
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_left() && is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

// Spectify the OLED displays
void oled_task_user(void) {

    // On the host display show the top layer, and active modifiers and locks
    if (is_keyboard_master()) {

        // Host keyboard layer status
        oled_write_P(PSTR("Lyr: "), false);
        switch (get_highest_layer(layer_state)) {
        default:
            oled_write_ln_P(PSTR("QWERTY"), false);
        }

        // Host keyboard modifier status
        oled_write_P(PSTR("Mod: "), false);
        static uint8_t active_mods;
        static uint8_t active_oneshot_mods;
        active_mods = get_mods();
        active_oneshot_mods = get_oneshot_mods();
        if ((active_mods | active_oneshot_mods) & MOD_MASK_SHIFT) {
            if ((active_mods | active_oneshot_mods) & MOD_MASK_CTRL) {
                if ((active_mods | active_oneshot_mods) & MOD_MASK_ALT) {
                    if ((active_mods | active_oneshot_mods) & MOD_MASK_GUI) {
                        oled_write_P(PSTR("sft ctl alt gui\n"), false);
                    } else {
                        oled_write_P(PSTR("sft ctl alt\n"), false);
                    }
                } else if ((active_mods | active_oneshot_mods) & MOD_MASK_GUI) {
                    oled_write_P(PSTR("sft ctl     gui\n"), false);
                } else {
                    oled_write_P(PSTR("sft ctl\n"), false);
                }
            } else if ((active_mods | active_oneshot_mods) & MOD_MASK_ALT) {
                if ((active_mods | active_oneshot_mods) & MOD_MASK_GUI) {
                    oled_write_P(PSTR("sft     alt gui\n"), false);
                } else {
                    oled_write_P(PSTR("sft     alt\n"), false);
                }
            } else if ((active_mods | active_oneshot_mods) & MOD_MASK_GUI) {
                oled_write_P(PSTR("sft         gui\n"), false);
            } else {
                oled_write_P(PSTR("sft\n"), false);
            }
        } else if ((active_mods | active_oneshot_mods) & MOD_MASK_CTRL) {
            if ((active_mods | active_oneshot_mods) & MOD_MASK_ALT) {
                if ((active_mods | active_oneshot_mods) & MOD_MASK_GUI) {
                    oled_write_P(PSTR("    ctl alt gui\n"), false);
                } else {
                    oled_write_P(PSTR("    ctl alt\n"), false);
                }
            } else if ((active_mods | active_oneshot_mods) & MOD_MASK_GUI) {
                oled_write_P(PSTR("    ctl     gui\n"), false);
            } else {
                oled_write_P(PSTR("    ctl\n"), false);
            }
        } else if ((active_mods | active_oneshot_mods) & MOD_MASK_ALT) {
             if ((active_mods | active_oneshot_mods) & MOD_MASK_GUI) {
                 oled_write_P(PSTR("        alt gui\n"), false);
             } else {
                 oled_write_P(PSTR("        alt\n"), false);
             }
        } else if ((active_mods | active_oneshot_mods) & MOD_MASK_GUI) {
             oled_write_P(PSTR("            gui\n"), false);
        } else {
            oled_write_P(PSTR("none         \n"), false);
        }

        // Host keyboard locks status (only works one at a time)
        oled_write_P(PSTR("Lck: "), false);
        led_t led_state = host_keyboard_led_state();
        if (led_state.num_lock) {
            oled_write_P(PSTR("num\n"), false);
        } else if (led_state.caps_lock) {
            oled_write_P(PSTR("caps\n"), false);
        } else if (led_state.scroll_lock) {
            oled_write_P(PSTR("scrl\n"), false);
        } else {
            oled_write_P(PSTR("none\n"), false);
        }

    // On the secondary display show the logo
    } else {
        render_logo();
    }

}
