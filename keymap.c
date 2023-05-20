/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2023 @ferrance

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
#include "dizave.h"                // the dizave library
#include "features/achordion.h"    // https://getreuer.info/posts/keyboards/achordion/index.html
#include <stdio.h>

// Layers
enum layer_number {
  _COLEMAK = 0,
  _NAV,
  _NUM,
  _LAW,
  _FUNC,
};

// tap dance declarations
// eventually move to dizave.c and .h?
//
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


// key override - make shift backspace send a delete
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &delete_key_override,
    NULL // Null terminate the array of overrides!
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    DZ_A,    DZ_R,    DZ_S,    DZ_T,    KC_D,                         KC_H,    DZ_N,    DZ_E,    DZ_I,    DZ_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           DZ_OSS,MO(_NAV),  KC_SPC,     KC_ENT,MO(_NUM),  DZ_OSS
                                      //`--------------------------'  `--------------------------'

  ),

  [_NAV] = LAYOUT_split_3x6_3(  // nav layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, DZ_CLSE, XXXXXXX, DZ_VDLT, DZ_VDRT, XXXXXXX,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DZ_LGUI, DZ_LALT, DZ_LCTL, DZ_LSFT, _______,                      KC_PGDN, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      KC_CAPS, XXXXXXX, XXXXXXX, XXXXXXX,  KC_INS,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,  MO(_LAW),MO(_FUNC), _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT_split_3x6_3(  // number layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, DZTDLBC,    KC_7,    KC_8,    KC_9, DZTDRBC,                      _______, _______, KC_LPRN, KC_RPRN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
    OSL(_LAW), KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL,                      _______, DZ_RSFT, DZ_RCTL, DZ_LALT, DZ_RGUI, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
   OSL(_FUNC),  KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      _______, _______, _______, _______, _______, _______, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LPRN,    KC_0, KC_RPRN,    _______, _______, _______
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
      XXXXXXX,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,                      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,                      RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,  DZ_RGB,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,                     RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,  DZ_WIN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, DZ_NBSP,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
 
  )



};



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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_achordion(keycode, record)) { return false; }

  switch(keycode) {

    default:
      return dizave_process_record_user(keycode, record);
      break;

  }  // switch

  return true;
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
#define L_NUMBERS (1 << _NUM)
#define L_LAW 8
#define L_FUNC 16

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
        case L_LAW:
        case L_LAW | L_NAV:
            oled_write_ln("-law-", false);
            break;
        case L_FUNC:
        case L_FUNC | L_NAV:  // because you can also get here from nav layer thumb key
            oled_write_ln("-func", false);
            break;
        default:
            oled_write_ln("-unk-",false);
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


#endif // OLED_ENABLE

// Nav        - right side lights up yellow
// Numbers    - left side lights up yellow
// Law        - entire board lights up red
// Functions  - entire board lights up blue
//
// When shift is active, thumb cluster turns pink
//
bool rgb_matrix_indicators_user(void) {

        switch(get_highest_layer(layer_state|default_layer_state)) {
            case _NUM:
		// make the number pad a different color
                for (uint8_t i=10; i<=20; i++) {
                    if (i!=14) { rgb_matrix_set_color(i, RGB_GOLD); }
                }
                break;
            case _NAV:
                // arrow keys different color
                rgb_matrix_set_color(43, RGB_GOLD);
                rgb_matrix_set_color(44, RGB_GOLD);
                rgb_matrix_set_color(38, RGB_GOLD);
                rgb_matrix_set_color(46, RGB_GOLD);
                break;
            case _LAW:
                rgb_matrix_set_color(9, RGB_RED);
                rgb_matrix_set_color(8, RGB_RED);
                rgb_matrix_set_color(7, RGB_RED);

                rgb_matrix_set_color(25, RGB_RED);
                rgb_matrix_set_color(22, RGB_RED);
                rgb_matrix_set_color(19, RGB_RED);
                rgb_matrix_set_color(16, RGB_RED);
                rgb_matrix_set_color(11, RGB_RED);

                rgb_matrix_set_color(34, RGB_RED);
                rgb_matrix_set_color(35, RGB_RED);
                rgb_matrix_set_color(36, RGB_RED);

                rgb_matrix_set_color(52, RGB_RED);
                rgb_matrix_set_color(49, RGB_RED);
                rgb_matrix_set_color(46, RGB_RED);
                rgb_matrix_set_color(43, RGB_RED);
                rgb_matrix_set_color(38, RGB_RED);

                 break;
            case _FUNC:
                rgb_matrix_set_color(9, RGB_BLUE);
                rgb_matrix_set_color(8, RGB_BLUE);
                rgb_matrix_set_color(7, RGB_BLUE);

                rgb_matrix_set_color(25, RGB_BLUE);
                rgb_matrix_set_color(22, RGB_BLUE);
                rgb_matrix_set_color(19, RGB_BLUE);
                rgb_matrix_set_color(16, RGB_BLUE);
                rgb_matrix_set_color(11, RGB_BLUE);

                rgb_matrix_set_color(34, RGB_BLUE);
                rgb_matrix_set_color(35, RGB_BLUE);
                rgb_matrix_set_color(36, RGB_BLUE);

                rgb_matrix_set_color(52, RGB_BLUE);
                rgb_matrix_set_color(49, RGB_BLUE);
                rgb_matrix_set_color(46, RGB_BLUE);
                rgb_matrix_set_color(43, RGB_BLUE);
                rgb_matrix_set_color(38, RGB_BLUEg);
                 break;

            default:
                break;
        }

    // this picks up shift and one shot shift but not caps lock 
    if(get_mods() & MOD_MASK_SHIFT || get_oneshot_mods() & MOD_MASK_SHIFT){
        rgb_matrix_set_color(6, RGB_PINK );
        rgb_matrix_set_color(13, RGB_PINK );
        rgb_matrix_set_color(14, RGB_PINK );
        rgb_matrix_set_color(33, RGB_PINK );
        rgb_matrix_set_color(40, RGB_PINK );
        rgb_matrix_set_color(41, RGB_PINK );
    }

    return false;
}

