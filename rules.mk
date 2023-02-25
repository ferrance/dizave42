#MOUSEKEY_ENABLE = yes    # Mouse keys


# only one of these should be enabled
#RGBLIGHT_ENABLE = yes    # Enable WS2812 RGB underlight.
RGB_MATRIX_ENABLE = yes

RGB_MATRIX_DRIVER = WS2812
OLED_ENABLE     = yes
OLED_DRIVER     = SSD1306
LTO_ENABLE      = yes
UNICODE_ENABLE = yes

# uncomment below when using the kb2040 board
MCU = kb2040
BOOTLOADER = RP2040

SRC += ./dizave.c
