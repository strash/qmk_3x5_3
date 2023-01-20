# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
RGB_MATRIX_ENABLE = no
RGB_MATRIX_DRIVER = WS2812
# if firmware size over limit, try this option
LTO_ENABLE = no

DEFAULT_FOLDER = crkbd/rev1

RGBLIGHT_SUPPORTED = no
RGB_MATRIX_SUPPORTED = no

LAYOUTS = split_3x5_3

SPLIT_KEYBOARD = yes
OLED_DRIVER_ENABLE = no
OLED_ENABLE = no
CAPS_WORD_ENABLE = yes
TAP_DANCE_ENABLE = yes
DYNAMIC_TAPPING_TERM_ENABLE = yes
