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
#include "features/achordion.h"    // https://getreuer.info/posts/keyboards/achordion/index.html
#include <stdio.h>

// Layers
enum layer_number {
  _COLEMAK = 0,
  _NAV,
  _NUMBERS,
  _ADJUST,
  _LAW,
  _FUNC,
  _OLDNAV
};

#define DZ_LCTL OSM(MOD_LCTL)
#define DZ_LSFT OSM(MOD_LSFT)
#define DZ_LALT OSM(MOD_LALT)
#define DZ_LGUI OSM(MOD_LGUI)
#define DZ_RCTL OSM(MOD_RCTL)
#define DZ_RSFT OSM(MOD_RSFT)
#define DZ_RGUI OSM(MOD_RGUI)

#define DZ_SFTENT LSFT_T(KC_ENT)

// tap dance declarations
enum {
  TD_LBKT_LBRC = 0,
  TD_RBKT_RBRC,
};

// tap dance definitions
tap_dance_action_t tap_dance_actions[] = {
  // tap once for left bracket, twice for left brace
  [TD_LBKT_LBRC] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),
  [TD_RBKT_RBRC] = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),
};

// hit bracket twice for curly brace
// pondering making a double semicolon be a colona--
#define DZTDLBC TD(TD_LBKT_LBRC)
#define DZTDRBC TD(TD_RBKT_RBRC)

// temp while I try this out
#define DZ_SPC1 LT(_NAV, KC_SPC)
#define DZ_ENT1 LT(_NUMBERS,KC_ENT)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    DZ_A,    DZ_R,    DZ_S,    DZ_T,    KC_D,                         KC_H,    DZ_N,    DZ_E,    DZ_I,    DZ_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                          KC_LGUI,   MO(1),  DZ_SPC,  DZ_SFTENT, DZ_BSPC,  KC_DEL
                                          KC_LGUI,   DZ_OSS,  DZ_SPC1,  DZ_ENT1, KC_BSPC,  KC_DEL
                                      //`--------------------------'  `--------------------------'

  ),

  [_NAV] = LAYOUT_split_3x6_3(  // nav layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, DZ_CLSE, XXXXXXX, DZ_VDLT, DZ_VDRT, XXXXXXX,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DZ_LGUI, DZ_LALT, DZ_LCTL, DZ_LSFT, _______,                      KC_PGDN, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX, S(KC_QUOT),
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,   MO(3), _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUMBERS] = LAYOUT_split_3x6_3(  // number layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, DZTDLBC,    KC_7,    KC_8,    KC_9, DZTDRBC,                      _______, _______, KC_LPRN, KC_RPRN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    OSL(_LAW), KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL,                      _______, DZ_RSFT, DZ_RCTL, DZ_LALT, DZ_RGUI, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   OSL(_FUNC),  KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      _______, _______, _______, _______, _______, _______, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_DOT,    DZ_0, KC_SPC,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
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
  ),

  [_FUNC] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       DZ_WIN,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, DZ_NBSP,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
 
  )
};



// variable tapping term per key. I needed the tappinng term
// to be a bit faster on the thumb keys because I was not getting
// the shift to pick up often enough.
//
/*
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DZ_SPC:
        case DZ_SFTENT:
            return 150;
        default:
            return TAPPING_TERM;
    }
}
*/

//
// achordian functions
//

void matrix_scan_user(void) {
  achordion_task();
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) 
{
  return achordion_opposite_hands(tap_hold_record, other_record);
}

// don't apply bilateral combos to the thumb keys
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  switch (tap_hold_keycode) {
    case DZ_ENT1:
    case DZ_SPC1:
      return 0;  // Bypass Achordion for these keys.
  }

  return 800;  // Otherwise use a timeout of 800 ms.
}


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
            oled_write_ln("-Dflt ", false);
            break;
        case L_NAV:
            oled_write_ln("-nav-", false);
            break;
        case L_NUMBERS:
            oled_write_ln("-num-", false);
            break;
        case L_ADJUST:
        case L_ADJUST|L_NAV:
        case L_ADJUST|L_NUMBERS:
        case L_ADJUST|L_NAV|L_NUMBERS:
            oled_write_ln_P(PSTR("Adjst"), false);
            break;
        case 32:
            oled_write_ln("-fnc-", false);
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
        if (host_keyboard_led_state().caps_lock) { 
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

  if (!process_achordion(keycode, record)) { return false; }

  switch(keycode) {

    default:
      return dizave_process_record_user(keycode, record);
      break;

  }  // switch

  return true;
}
#endif // OLED_ENABLE
