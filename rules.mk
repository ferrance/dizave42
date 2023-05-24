# only one of these should be enabled
#RGBLIGHT_ENABLE = yes    # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes

RGB_MATRIX_DRIVER = WS2812
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306

# be small
LTO_ENABLE      = yes
CONSOLE_ENABLE  = no
COMMAND_ENABLE  = no
EXTRAKEY_ENABLE = no
MOUSEKEY_ENABLE = no
GRAVE_ESC_ENABLE= no
SPACE_CADET_ENABLE = no

# features this keymap uses
UNICODE_ENABLE = yes
TAP_DANCE_ENABLE = yes       # for double tapping brackets
KEY_OVERRIDE_ENABLE = yes    # for shift backspace = delete
CAPS_WORD_ENABLE = yes

# to build for kb2040: qmk compile -e CONVERT_TO=kb2040
ifeq ($(strip $(CONVERT_TO)), rp2040)
  MCU = kb2040
  BOOTLOADER = RP2040
endif

SRC += ./dizave.c
SRC += features/achordion.c