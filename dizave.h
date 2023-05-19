/*
Copyright 2022 David Ferrance (@ferrance) 

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

// Functions in dizave.c

bool is_mac(void);
void dizave_set_win_mode(void);
void dizave_set_mac_mode(void);
void dizave_render_master(void);
void dizave_render_numbers(bool);
void dizave_render_logo(void);
void dizave_render_bootmagic_status(bool);
bool dizave_process_record_user(uint16_t keycode, keyrecord_t *record);

// Colemak home row mods
#define DZ_A LGUI_T(KC_A)
#define DZ_R LALT_T(KC_R)
#define DZ_S LCTL_T(KC_S)
#define DZ_T LSFT_T(KC_T)
#define DZ_N RSFT_T(KC_N)
#define DZ_E RCTL_T(KC_E)
#define DZ_I LALT_T(KC_I)
#define DZ_O RGUI_T(KC_O)

// QWERTY home row mods - GACS
#define DZQ_A LGUI_T(KC_A)
#define DZQ_S LALT_T(KC_S)
#define DZQ_D LCTL_T(KC_D)
#define DZQ_F LSFT_T(KC_F)
#define DZQ_J RSFT_T(KC_J)
#define DZQ_K RCTL_T(KC_K)
#define DZQ_L LALT_T(KC_L)
#define DZQ_SC RGUI_T(KC_SCLN)

// one shot home row mods 
// use on the nav and number layers
#define DZ_LCTL OSM(MOD_LCTL)
#define DZ_LSFT OSM(MOD_LSFT)
#define DZ_LALT OSM(MOD_LALT)
#define DZ_LGUI OSM(MOD_LGUI)
#define DZ_RCTL OSM(MOD_RCTL)
#define DZ_RSFT OSM(MOD_RSFT)
#define DZ_RGUI OSM(MOD_RGUI)

//#define DZ_VDRT G(C(KC_RIGHT))
#define DZ_VDLT G(C(KC_LEFT))

// Dizave Keycodes
enum my_keycodes {
  DZ_WIN = SAFE_RANGE,
//  DZ_MAC,    // switch to mac mode  (not used?)
  DZ_VDRT,
  DZ_QWTY,   // switch base layer to qwerty
  DZ_CLMK,   // switch base layer to colemak
  DZ_CLSE,   // close window
  DZ_USC,
  DZ_CFR,
  DZ_NMSA,
  DZ_NMRA,
  DZ_RP,
  DZ_BIC,
  DZ_AB,
  DZ_NMSC,
  DZ_NMCA,
  DZ_NM,
  DZ_F3D,
  DZ_F2D,
  DZ_ABQ,
  DZ_RGB
};

//#define DZ_SPC  LSFT_T(KC_SPC)
//#define DZ_0    LT(3,KC_0)
#define DZ_OSS  OSM(MOD_LSFT)

// Legal macros that are not keycodes
#define DZ_LAW  OSL(_LEGAL)
#define DZ_SEC  UC(0x00A7)
#define DZ_PARA UC(0x00B6)
#define DZ_RQOT UC(0x2019) 
#define DZ_EMDS UC(0x2014)  

// A0 does not work on mac? and although alt space works in US layout mac, it
// does not work on US unicode input mac????? But the narrow one 202F appears to work.
//#define DZ_NBSP UC(0x00A0) 
#define DZ_NBSP UC(0x202F)
