LTO_ENABLE = yes
SPLIT_KEYBOARD = yes
EXTRAKEY_ENABLE = yes
OLED_DRIVER_ENABLE = yes
RGBLIGHT_ENABLE = yes
# Load the necessary support files
ifeq ($(strip $(OLED_DRIVER_ENABLE)), yes)
	SRC += oled.c
endif
