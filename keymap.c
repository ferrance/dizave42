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
// pondering making a double semicolon be a colon
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
      _______, DZ_LGUI, DZ_LALT, DZ_LCTL, DZ_LSFT, _______,                      KC_PGDN, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_CAPS,
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

  // bigoled is always at 0
  // pair of small ones has left at 180, right at 270 
  oled_rotation_t oled_init_user(oled_rotation_t rotation) 
  {
    #ifdef OLED_DISPLAY_128X64
      return OLED_ROTATION_0;  // testing for larger display
    #else
      if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
      }
      return OLED_ROTATION_270;
    #endif 
  }

  #define L_BASE 0
  #define L_NAV (1 << _NAV)
  #define L_NUMBERS (1 << _NUM)
  #define L_LAW (1 << _LAW)
  #define L_FUNC (1 << _FUNC)

  void oled_render_layer_state(void) {

  #ifdef OLED_DISPLAY_128X64
      oled_write("Layer: ", false);
      if (layer_state==L_BASE) {
        oled_write_ln("Colemak", false);
      } else if (layer_state==L_NAV) {
        oled_write_ln("Navigation", false);
      } else if (layer_state== L_NUMBERS) {
        oled_write_ln("Numbers", false);
      } else if (layer_state==L_LAW || layer_state==(L_LAW|L_NAV) ) {
        oled_write_ln("Legal", false);
      } else if (layer_state==L_FUNC) {
        oled_write_ln("Function", false);
      } else {
        oled_write_ln("Unknown", false);
      }
  #else
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
              oled_write_ln("unkwn",false);
              break;
      }
  #endif
  }

  // for drawing in a 128x64 oled
  #ifdef OLED_DISPLAY_128X64
    bool big_oled(void) {

        // if we are going to need to display layout info, clear 
        // the screen (basically to get rid of logo)
        if (layer_state==L_NUMBERS || layer_state==L_NAV){
            oled_clear();
        }

        oled_render_layer_state();
        oled_write(" Mods: ", false);
        dizave_render_mods();

        if (layer_state == L_NUMBERS) {       
            dizave_render_numbers(0,4);
        } else if (layer_state == L_NAV) {
            dizave_render_nav(12,5);
        } else {
            // if nothing else to do, display the logo at bottom
            oled_write_ln("",false);	
            oled_write_ln("",false);	
            oled_write_ln("",false);	
    //        oled_set_cursor(0,5);
            dizave_render_logo();
        }

        // display the apple/windows logo in the upper right
        dizave_render_bootmagic_status_at(!is_mac(),18,0);

        if (host_keyboard_led_state().caps_lock) {
          oled_set_cursor(16,2);
          oled_write_char(213,false);
          oled_write_char(214,false);
          oled_write_char(215,false);
          oled_write_char(216,false);
        }

      return false;
    }

  #else 
    bool small_oled(void) {

      if (is_keyboard_master()) {

          oled_render_layer_state();
          dizave_render_mods();
          oled_write_ln("    ", false);

        if (layer_state == L_NUMBERS) {       
            dizave_render_numbers();
        } else if (layer_state == L_NAV) {
            dizave_render_nav(12,5);
        } else {
            // if nothing else to do, display the logo at bottom
            oled_write_ln("",false);	
            oled_write_ln("",false);	
            oled_write_ln("",false);	
            oled_write_ln("",false);	
        }

//          dizave_render_numbers(layer_state==4);
          oled_write_ln("     ", false);

          // CAPS LOCK
          if (host_keyboard_led_state().caps_lock) { 
              oled_write_ln("CAPS",true);
          } else {
              oled_write_ln("    ", false);
          } 

          // display apple / windows logo
          dizave_render_bootmagic_status_at(!is_mac(), 0, 13);

      } else {
          dizave_render_logo();
      }
      return false;
    }
  #endif

  bool oled_task_user(void) {
    #ifdef OLED_DISPLAY_128X64
      return big_oled();
    #else
      return small_oled();
    #endif
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

    const int arrows[] = { 43, 44, 38, 46 };
    const int chevron[] = { 7,8,9, 11,16,19,22,25, 34,35,36, 38,43,46,49,52 } ;
    const int shifts[] = { 6,13,14,33,40,41 };
    const int numpad[] = { 10,11,12,13,15,16,17,18,19,20 };

        switch(get_highest_layer(layer_state|default_layer_state)) {

            // make the number pad a different color
            case _NUM:
		for (int i=0;i<sizeof(numpad)/sizeof(*numpad);i++) { rgb_matrix_set_color(numpad[i], RGB_GOLD); }
                break;

            // arrow keys different color
            case _NAV:
		for (int i=0;i<sizeof(arrows)/sizeof(*arrows)	;i++) { rgb_matrix_set_color(arrows[i], RGB_GOLD); }
                break;

            case _LAW:
		for (int i=0;i<sizeof(chevron)/sizeof(*chevron);i++) { rgb_matrix_set_color(chevron[i], RGB_RED); }
                 break;

            case _FUNC:
		for (int i=0;i<sizeof(chevron)/sizeof(*chevron);i++) { rgb_matrix_set_color(chevron[i], RGB_BLUE); }
                 break;

            default:
                break;
        }

    // this picks up shift, one shot shift, and caps_word but not caps lock 
    // caps_word state does not sync across kb halves, so only the master side will
    // light up when caps word is active
    // same is true for caps lock
    //
    if(get_mods() & MOD_MASK_SHIFT || 
       get_oneshot_mods() & MOD_MASK_SHIFT || 
       is_caps_word_on() || 
       host_keyboard_led_state().caps_lock )
    {

        for (int i=0;i<sizeof(shifts)/sizeof(*shifts);i++) { rgb_matrix_set_color(shifts[i], RGB_PINK); }

    }

    return false;
}

