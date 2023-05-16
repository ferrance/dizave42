# only one of these should be enabled
#RGBLIGHT_ENABLE = yes    # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes

RGB_MATRIX_DRIVER = WS2812
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes
UNICODE_ENABLE = yes
MOUSEKEY_ENABLE = no
TAP_DANCE_ENABLE = yes


# to build for kb2040: qmk compile -e CONVERT_TO=kb2040
ifeq ($(strip $(CONVERT_TO)), rp2040)
  MCU = kb2040
  BOOTLOADER = RP2040
endif

SRC += ./dizave.c
