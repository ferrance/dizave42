/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2024 @ferrance

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

#include <stdio.h>

#include QMK_KEYBOARD_H
#include "dizave.h"                 // the dizave library
#include "features/achordion.h"     // https://getreuer.info/posts/keyboards/achordion/index.html
//#include "features/select_word.h"   // https://getreuer.info/posts/keyboards/select-word/index.html
#include "os_detection.h"

// graphics for the small oled layer names
// todo put in dizave42.h
extern const unsigned char dz_oled_colemak[];
extern const unsigned char dz_oled_legal[];
extern const unsigned char dz_oled_nav[];
extern const unsigned char dz_oled_num[];
extern const unsigned char dz_oled_func[];
extern const unsigned char dz_oled_qwerty[];

#define DZNAV MO(_NAV)
//#define DZNAV LT(_NAV, KC_TAB)
#define DZNUM MO(_NUM)
//#define DZNUM LT(_NUM, KC_BSPC)
//#define DZLAW LT(_LAW, KC_DEL)
#define DZLAW OSL(_LAW)


//
// Layers
//

enum layer_number {
  _COLEMAK = 0,
  _QWERTY,
  _NAV,
  _NUM,
  _LAW,
  _FUNC,
  _UNKNOWN
};

// not sure these are used anymore, replaced with graphics
// still used for big oled, not small one
const char* layer_names[][2] = {
  { "clmak", "Colemak"   },
  { "qwrty", "Qwerty"},
  { "-nav-", "Navgation"},
  { "-num-", "Numbers"  },
  { "-law-", "Legal"    },
  { "-fun-", "Function" },
  { "unkwn", "Unknown"  }
};

// key override
//   - make shift backspace send a delete
//   - make shift space send a tab
//   - make shift para a section sumbol
//
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t shift_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_TAB);
const key_override_t para_key_override = ko_make_basic(MOD_MASK_SHIFT, DZ_PARA, DZ_SEC);

// This globally defines all key overrides to be used
const key_override_t *key_overrides[] = {
    &delete_key_override,
//    &shift_key_override,
    &para_key_override
};

//
// key combos
//

const uint16_t PROGMEM esc_combo[] = { KC_TAB, KC_Q, COMBO_END};  // tab+q = esc
const uint16_t PROGMEM caps_combo[] = { KC_V, KC_M, COMBO_END};   // v+m = caps word
const uint16_t PROGMEM lead_combo[] = { KC_D, KC_H, COMBO_END};   // d+h = leader key

combo_t key_combos[] = {
  COMBO(esc_combo, KC_ESC),
//  COMBO(caps_combo, CW_TOGG),
  COMBO(lead_combo, QK_LEAD)
};

//
// unicode characters
//

enum unicode_names {
  U_PARA_LOWER,
  U_PARA_UPPER,
  U_RQOT,
  U_MDASH,
  U_NBSP
};

const uint32_t unicode_map[] PROGMEM = {
  [U_PARA_LOWER]   = 0x00B6, // ¶
  [U_PARA_UPPER]   = 0x00a7, // §
  [U_RQOT] = 0x2019, 
  [U_MDASH] = 0x2014, 
  [U_NBSP] = 0x202F
};

#define PARASEC UP(U_PARA_LOWER, U_PARA_UPPER)
#define DZ_SEC  UM(U_PARA_UPPER)
#define DZ_PARA UM(U_PARA_LOWER)
#define DZ_RQOT UM(U_RQOT) 
#define DZ_EMDS UM(U_MDASH)  

// experimenting with different shift options
#define SF_Z LSFT_T(KC_Z)
#define SF_V LSFT_T(KC_V)
#define SF_SLSH RSFT_T(KC_SLSH)
#define SF_M RSFT_T(KC_M)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,                         KC_J,    KC_L,    KC_U,    KC_Y, KC_SCLN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,    KC_A,    KC_R,    KC_S,    KC_T,    KC_D,                         KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       DZ_OSS,    DZ_Z,    DZ_X,    DZ_C,    DZ_V,    KC_B,                         KC_K,    DZ_M, DZ_COMM,  DZ_DOT, DZ_SLSH, DZ_OSSR,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          DZ_SEC,   DZNAV,  KC_SPC,     KC_ENT,   DZNUM, PARASEC
                                      //`--------------------------'  `--------------------------'

  ),

  [_QWERTY] = LAYOUT_split_3x6_3(-
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_BSPC,   DZQ_A,   DZQ_S,   DZQ_D,   DZQ_F,    KC_G,                         KC_H,   DZQ_J,   DZQ_K,   DZQ_L,  DZQ_SC, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       DZ_OSS,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_MINS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           _______,MO(_NAV), KC_SPC,     KC_ENT,MO(_NUM), _______
                                      //`--------------------------'  `--------------------------'

  ),
  [_NAV] = LAYOUT_split_3x6_3(  // nav layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, DZ_CLSE, XXXXXXX, DZ_VDLT, DZ_VDRT, XXXXXXX,                      KC_PGUP, KC_HOME,   KC_UP,  KC_END, XXXXXXX,   WBSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DZ_LGUI, DZ_LALT, DZ_LCTL, DZ_LSFT, _______,                      KC_PGDN, KC_LEFT, KC_DOWN,KC_RIGHT, XXXXXXX,  KC_INS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, DZ_LGUI, DZ_LALT, DZ_LCTL, DZ_LSFT, _______,                      XXXXXXX,   WLEFT, _______,  WRIGHT, XXXXXXX, DZ_SCAP,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    KC_BSPC,OSL(_LAW),OSL(_FUNC)
                                      //`--------------------------'  `--------------------------'
  ),
  
  [_NUM] = LAYOUT_split_3x6_3(  // number layer
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,                      XXXXXXX, S(KC_9), S(KC_0), _______, XXXXXXX,    WDEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,S(KC_SCLN),  KC_4,    KC_5,    KC_6,  KC_EQL,                      XXXXXXX, DZ_RSFT, DZ_RCTL, DZ_LALT, DZ_RGUI, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_CAPS,  KC_GRV,    KC_1,    KC_2,    KC_3, KC_BSLS,                      _______, DZ_RSFT, DZ_RCTL, DZ_LALT, DZ_RGUI, _______, 
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______,    KC_0, KC_MINS,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

  [_LAW] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      XXXXXXX, XXXXXXX,  DZ_CFR,   DZ_F4,  DZ_US,   DZ_SEE,                        DZ_RP, DZ_NMSC, DZ_NMRA, XXXXXXX,  DZ_ROG, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  DZ_ABQ,  DZ_USC,  DZ_F3D,  DZ_P3D,  DZ_ID2,                       DZ_BIC, DZ_NMCA, DZ_NMSA, XXXXXXX, XXXXXXX, DZ_RQOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  DZ_NM2, XXXXXXX,  DZ_F2D,  DZ_P2D, DZ_BERN,                       DZ_AB,   DZ_NM, XXXXXXX, XXXXXXX, XXXXXXX, DZ_EMDS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           DZ_SEC, DZ_PARA, _______,    _______, _______,_______
                                      //`--------------------------'  `--------------------------'
  ),

  [_FUNC] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,                      RGB_TOG, RGB_TOG, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,                      RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, RGB_SPI, DZ_CLMK,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      DZ_TEST,  KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS,                     RGB_RMOD, RGB_HUD, RGB_SAD, RGB_VAD, RGB_SPD,  DZ_WIN,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, XXXXXXX
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
  if (tap_hold_keycode==DZNAV)
  {
    return true; // consider it held, not tapped
  }

  return achordion_opposite_hands(tap_hold_record, other_record);
}

uint16_t achordion_timeout(uint16_t tap_hold_keycode) {
  switch (tap_hold_keycode) {
    case DZNAV:
    case DZLAW:
      return 200;  // Bypass Achordion for these keys.
  }

  return 800;  // Otherwise use a timeout of 800 ms.
}


// I'm playing with a shorter tapping term for the shift keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {

        case DZ_T:  // make it a little faster for the shift home row mods
        case DZ_N:
        case DZQ_F:
        case DZQ_J:
          return 160;

        default:
            return TAPPING_TERM;
    }
}


bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  if (!process_achordion(keycode, record)) { return false; }
//  if (!process_sentence_case(keycode, record)) { return false; }
//  if (!process_select_word(keycode, record, SELWORD, is_mac())) { return false; }
//  if (!process_record_num_word(keycode, record)) { return false; }

  switch(keycode) {

    // toggle between colemak and qwerty  
    case DZ_CLMK:
      if (!record->event.pressed) 
      {
        if (default_layer_state==2) {
          set_single_persistent_default_layer(_COLEMAK);
        } else {
          set_single_persistent_default_layer(_QWERTY);
        }
      }
      return false;

      case DZ_TEST:
#ifdef RGB_MATRIX_ENABLE

//        rgb_matrix_toggle();
//          rgb_matrix_enable(); return false;
        if (record->event.pressed) {
          if (rgb_matrix_is_enabled()) {
            rgb_matrix_disable();
          } else {
            rgb_matrix_enable();
          }
        }
#endif
        return false;

    default:
      return dizave_process_record_user(keycode, record);

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
      return OLED_ROTATION_180;
    #endif 
  }

  void oled_render_layer_state(void) {

    int l = get_highest_layer(layer_state);

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
        oled_write_ln("",false);

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

    bool small_oled2(void) {

      int layer = get_highest_layer(layer_state);
      if (layer==0 && default_layer_state>0) {
        layer = default_layer_state-1;
      }

      if (is_keyboard_master()) {

          // select the bitmap for this layer
          const unsigned char *data = dz_oled_colemak;
          if (layer==_LAW)
            data = dz_oled_legal;
          else if (layer==_NAV)
            data = dz_oled_nav;
          else if (layer==_NUM)
            data = dz_oled_num;
          else if (layer==_FUNC)
            data = dz_oled_func;
          else if (layer==_QWERTY)
            data = dz_oled_qwerty;

          // display the bitmap
          for (int i=0;i<128*4;i++)
          {
            uint8_t c = pgm_read_byte(data++);
            oled_write_raw_byte(c, i);            
          }

          // delete caps if necessary - from (56,24 to 93,32)
          if (!host_keyboard_led_state().caps_lock) { 
            rect(56,21,39,11,false);
          }

          // delete either win or apple
          if (is_mac())
            rect(97,21,15,11,false); // delete the windows logo
          else
            rect(113,21,16,11,false); // delete the mac logo


        oled_set_cursor(1,3);
        dizave_render_mods();           // show which home row mods are active
        //oled_write("C", get_mods() & MOD_MASK_CTRL);

      } else {
          dizave_render_logo();
      }
      return false;
    }

/* for promicro 
    bool small_oled2(void)
    {
      //int layer = get_highest_layer(layer_state);

        oled_render_layer_state();
        oled_write(" Mods: ", false);
        dizave_render_mods();
        oled_write_ln("",false);

      return false;
    }
*/

  #endif

  bool oled_task_user(void) {
    #ifdef OLED_DISPLAY_128X64
      return big_oled();
    #else
      return small_oled2();
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
#ifdef RGB_MATRIX_ENABLE

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
#endif


#ifdef LEADER_ENABLE

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_A)) {
        SEND_STRING("Albuquerque");
    } else if (leader_sequence_two_keys(KC_C, KC_A)) {
        SEND_STRING("Court of Appeals");
    } else if (leader_sequence_two_keys(KC_C, KC_O)) {
        SEND_STRING("(citation omitted)");
    } else if (leader_sequence_two_keys(KC_D, KC_C)) {
        SEND_STRING("district court");
    } else if (leader_sequence_two_keys(KC_E, KC_A)) {
        SEND_STRING("(emphasis added)");        
    } else if (leader_sequence_two_keys(KC_N, KC_M)) {
        SEND_STRING("New Mexico");
    } else if (leader_sequence_two_keys(KC_P, KC_R)) {
        SEND_STRING("Personal Representative");
    } else if (leader_sequence_two_keys(KC_S, KC_A)) {
        SEND_STRING("Special Administrator");
    } else if (leader_sequence_two_keys(KC_S, KC_C)) {
        SEND_STRING("Supreme Court");
    } else if (leader_sequence_three_keys(KC_R, KC_O, KC_G)) {
        SEND_STRING("Interrogatory");
    } else if (leader_sequence_four_keys(KC_B, KC_E, KC_R, KC_N)) {
        SEND_STRING("Bernalillo");
    } else if (leader_sequence_four_keys(KC_N, KC_M, KC_S, KC_C)) {
        SEND_STRING("New Mexico Supreme Court");
    } else if (leader_sequence_four_keys(KC_N, KC_M, KC_C, KC_A)) {
        SEND_STRING("New Mexico Court of Appeals");
    } else if (leader_sequence_five_keys(KC_N, KC_M, KC_P, KC_E, KC_L)) {
        SEND_STRING("New Mexico Probate & Estate Lawyers");
    }
  }

#endif

bool process_detected_host_os_user(os_variant_t os) {
  if (os==OS_MACOS || os==OS_IOS) {
    dizave_set_mac_mode();
  } else {
    dizave_set_win_mode();
  }
  return true;
}