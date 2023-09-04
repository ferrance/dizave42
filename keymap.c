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
#include "dizave.h"                 // the dizave library
#include "features/achordion.h"     // https://getreuer.info/posts/keyboards/achordion/index.html
#include "features/sentence_case.h" // https://getreuer.info/posts/keyboards/sentence-case/index.html
#include <stdio.h>

// Layers
enum layer_number {
  _COLEMAK = 0,
  _QWERTY,
  _NAV,
  _NUM,
  _LAW,
  _FUNC,
  _UNKNOWN
};

const char* layer_names[][2] = {
  { "clmak", "Colemak"   },
  { "qwrty", "Qwerty"},
  { "-nav-", "Navgation"},
  { "-num-", "Numbers"  },
  { "-law-", "Legal"    },
  { "-fun-", "Function" },
  { "unkwn", "Unknown"  }
};

// tap dance declarations
// eventually move to dizave.c and .h?
//
enum {
  TD_PARENS = 0, 
  TD_BRACES,
};

// tap dance definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_PARENS] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  [TD_BRACES] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
};

// pondering making a double semicolon be a colon
#define DZTDPRN TD(TD_PARENS)  // double tap ( to get )
#define DZTDBRC TD(TD_BRACES)  // double tap [ to get ]

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
       DZ_OSS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_K,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_ESC,MO(_NAV),  KC_SPC,     KC_ENT,MO(_NUM), OSL(_LAW)
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,   DZQ_A,   DZQ_S,   DZQ_D,   DZQ_F,    KC_G,                         KC_H,   DZQ_J,   DZQ_K,   DZQ_L,  DZQ_SC, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_ESC,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LCTL,MO(_NAV),  KC_SPC,     KC_ENT,MO(_NUM),  DZ_OSS
                                      //`--------------------------'  `--------------------------'

  ),
  [_NAV] = LAYOUT_split_3x6_3(  // nav layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, DZ_CLSE, XXXXXXX, DZ_VDLT, DZ_VDRT, XXXXXXX,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DZ_LGUI, DZ_LALT, DZ_LCTL, DZ_LSFT, _______,                      KC_PGDN, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,                      DZ_SCAP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______,OSL(_LAW),OSL(_FUNC)
                                      //`--------------------------'  `--------------------------'
  ),

  [_NUM] = LAYOUT_split_3x6_3(  // number layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC, XXXXXXX,    KC_7,    KC_8,    KC_9, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC, KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL,                      XXXXXXX, DZ_RSFT, DZ_RCTL, DZ_LALT, DZ_RGUI, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS,  KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      _______, _______, _______, _______, _______, _______, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          DZTDBRC,    KC_0, DZTDPRN,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_LAW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,  DZ_CFR,   DZ_F4,  DZ_SID,   DZ_US,                        DZ_RP, DZ_NMSC, DZ_NMRA,   DZ_CO,  DZ_ROG, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  DZ_ABQ,  DZ_USC,  DZ_F3D,  DZ_SEE,  DZ_P3D,                       DZ_BIC, DZ_NMCA, DZ_NMSA,   DZ_EA, XXXXXXX, DZ_RQOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  DZ_NM2, XXXXXXX,  DZ_F2D,DZ_SALSO,  DZ_P2D,                        DZ_AB,   DZ_NM, XXXXXXX, XXXXXXX, XXXXXXX, DZ_EMDS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          DZ_NBSP,  DZ_SEC, DZ_PARA,      DZ_ID,  DZ_ID2, OSL(_FUNC)
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      DZ_QWTY,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,                      RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,DZ_SCASE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      DZ_CLMK,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,                      RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI,DZ_SCASE,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,                     RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,  DZ_WIN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    QK_BOOT, _______, XXXXXXX
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

// I'm playing with a shorter tapping term for the shift keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case DZ_T:  // make it a little faster for the shift home row mods
        case DZ_N:
        case DZQ_F:
        case DZQ_J:
          return 160;

        case DZTDPRN: // 180 was a little too fast for the parens
        case DZTDBRC:
          return 220;
        default:
            return TAPPING_TERM;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_achordion(keycode, record)) { return false; }
  if (!process_sentence_case(keycode, record)) { return false; }
  // select word will go here

  switch(keycode) {

    case DZ_QWTY:
    {
      uint8_t cdl = eeconfig_read_default_layer();
      if (cdl==_QWERTY) {
        set_single_persistent_default_layer(_COLEMAK);
      } else {
        set_single_persistent_default_layer(_QWERTY);
      }
      break;
      
    // toggle between colemak and qwerty  
    case DZ_CLMK:


      set_single_persistent_default_layer(_COLEMAK);
    }
      break;

    case DZ_SCASE:
        sentence_case_toggle();
      break;

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

  void oled_render_layer_state(void) {

    int l = get_highest_layer(layer_state);

/* debug stuff 
    char layer_state_str[24];
    snprintf(layer_state_str, sizeof(layer_state_str), "st-%d", layer_state);    
    oled_write_ln(layer_state_str, false);
    snprintf(layer_state_str, sizeof(layer_state_str), "dflt-%d", default_layer_state);    
    oled_write_ln(layer_state_str, false);
    snprintf(layer_state_str, sizeof(layer_state_str), "l-%d", l);    
    oled_write_ln(layer_state_str, false);

//      oled_write_ln("Test1",false);
//      return ;

*/

    // if highest layer state is 0, it means it could be either 
    // colemak or qwerty. need to set it to the default 
    // layer state. if default is 0 then no change.
    // otherwise subtract one.
    if (l==0 && default_layer_state>0) {
      l = default_layer_state-1;
    }

    #ifdef OLED_DISPLAY_128X64
      oled_write("Layer: ", false);
      oled_write_ln(layer_names[l][1],false);
    #else
      oled_write_ln("Layer", false);
      oled_write_ln(layer_names[l][0],false);
    #endif
  }

  // for drawing in a 128x64 oled
  #ifdef OLED_DISPLAY_128X64
    bool big_oled(void) {

        int layer = get_highest_layer(layer_state);

        // if we are going to need to display layout info, clear 
        // the screen (basically to get rid of logo)
        if (layer==_NUM || layer==_NAV){
            oled_clear();
        }

        oled_render_layer_state();

        oled_write(" Mods: ", false);
        dizave_render_mods();

        if (layer == _NUM) {       
            dizave_render_numbers(0,4);
        } else if (layer == _NAV) {
            dizave_render_nav(12,5);
        } else {
            // if nothing else to do, display the logo at bottom
            oled_write_ln("",false);	
            oled_write_ln("",false);	
            oled_write_ln("",false);	
            dizave_render_logo();
        }

        // display the apple/windows logo in the upper right
        dizave_render_bootmagic_status_at(!is_mac(),18,0);

        // caps lock indicator
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

//      int layer = get_highest_layer(layer_state);

      if (is_keyboard_master()) {

          oled_render_layer_state();
          dizave_render_mods();
          oled_write_ln("    ", false);

//        if (layer == _NUM) {       
//            dizave_render_numbers();
//        } else if (layer == _NAV) {
//            dizave_render_nav(12,5);
//        } else {
            // if nothing else to do, display the logo at bottom
            oled_write_ln("",false);	
            oled_write_ln("",false);	
//            oled_write_ln("",false);	
//            oled_write_ln("",false);	
//        }

          oled_write_ln("     ", false);
          if (is_sentence_case_on()) {
            oled_write_ln("SCASE", true);
          } else {
            oled_write_ln("",false);	
          }

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

