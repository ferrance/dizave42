# only one of these should be enabled
RGBLIGHT_ENABLE = no    # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = ws2812

OLED_ENABLE     = yes
OLED_DRIVER     = ssd1306

# be small
LTO_ENABLE      = yes
CONSOLE_ENABLE  = no
COMMAND_ENABLE  = no
EXTRAKEY_ENABLE = no
MOUSEKEY_ENABLE = no
GRAVE_ESC_ENABLE= no
SPACE_CADET_ENABLE = no

# features this keymap uses
#UNICODE_ENABLE = yes
UNICODEMAP_ENABLE = yes
TAP_DANCE_ENABLE = no      # for double tapping brackets
KEY_OVERRIDE_ENABLE = yes    # for shift backspace = delete
CAPS_WORD_ENABLE = yes

# i've given up on promicro, it's just too small
# all my crkbds run on adafruit kb2040s
CONVERT_TO=kb2040

# for testing
#LTO_ENABLE=no

# to build for the 1.3 inch 128x64  oled add 
#   -e BIG_OLED=yes 
# to the qmk compile command
ifneq ($(strip $(BIG_OLED)),)
    OPT_DEFS += -DBIG_OLED
endif

SRC += ./dizave.c
SRC += features/achordion.c
#SRC += features/select_word.c