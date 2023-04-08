/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2023 @dizave

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "dizave.h"
#include <stdio.h>

// Layers
enum layer_number {
  _COLEMAK = 0,
  _NAV,
  _NUMBERS,
  _ADJUST,
  _LAW
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    DZ_R,    DZ_S,    DZ_T,    KC_D,                         KC_H,    DZ_N,    DZ_E,    DZ_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI,   MO(1),  DZ_SPC,  KC_SFTENT, DZ_BSPC, KC_LALT
                                      //`--------------------------'  `--------------------------'

  ),

  [_NAV] = LAYOUT_split_3x6_3(  // nav layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, _______,                      KC_CAPS, KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, S(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                       KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,   MO(3), _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUMBERS] = LAYOUT_split_3x6_3(  // number layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      KC_GRV , KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,                      _______, _______, KC_LPRN, KC_RPRN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    OSL(_LAW), KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL,                      _______, KC_RSFT, KC_RCTL, KC_LALT, KC_RGUI, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_PPLS,    KC_1,    KC_2,    KC_3, KC_MINS,                      _______, _______, KC_LCBR, KC_RCBR, _______, _______, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_DOT,    DZ_0, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  DZ_WIN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_LAW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX, XXXXXXX,  DZ_CFR,  DZ_USC,  DZ_F3D,                      DZ_NMSC, DZ_NMSA, DZ_NMRA, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  DZ_ABQ, XXXXXXX,  DZ_SEC, DZ_PARA,  DZ_F2D,                      DZ_NMCA,   DZ_RP,  DZ_BIC,   DZ_AB, XXXXXXX, DZ_RQOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                        DZ_NM, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, DZ_EMDS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, DZ_NBSP,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};




#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
 return OLED_ROTATION_270;
  return rotation;
}

#define L_BASE 0
#define L_NAV 2
#define L_NUMBERS 4
#define L_ADJUST 8

void oled_render_layer_state(void) {
    oled_write_ln("Layer", false);
    switch (layer_state) {
        case L_BASE:
            oled_write_ln("Dflt ", false);
            break;
        case L_NAV:
            oled_write_ln(" nav ", false);
            break;
        case L_NUMBERS:
            oled_write_ln(" num ", false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_NAV:
        case L_ADJUST|L_NUMBERS:
        case L_ADJUST|L_NAV|L_NUMBERS:
            oled_write_ln_P(PSTR("Adjst"), false);
            break;
        default:
            oled_write_ln("-law-",false);
            break;
    }
}




bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();

        dizave_render_master();

      // display apple / windows logo
      dizave_render_bootmagic_status(!is_mac());
      oled_write_ln("    ", false);

      dizave_render_numbers(layer_state==4);
      oled_write_ln("     ", false);

      // CAPS LOCK
      if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) { 
          oled_write_ln("CAPS",true);
      } else {
        oled_write_ln("    ", false);
      } 

    } else {
        dizave_render_logo();
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  switch(keycode) {

    default:
      return dizave_process_record_user(keycode, record);
      break;

  }  // switch

  return true;
}
#endif // OLED_ENABLE
