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
void dizave_render_mods(void);
void dizave_render_nav(uint8_t, uint8_t);
void dizave_render_logo(void);
void dizave_render_bootmagic_status(bool);
void dizave_render_bootmagic_status_at(bool, uint8_t, uint8_t);
bool dizave_process_record_user(uint16_t keycode, keyrecord_t *record);

void plot_line (int, int, int, int, bool);

#ifdef OLED_DISPLAY_128X64
void dizave_render_numbers(uint8_t, uint8_t);
#else
void dizave_render_numbers(void);
#endif

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
  DZ_USC,    // U.S.C. §
  DZ_CFR,    // C.F.R. §
  DZ_NMSA,   // NMSA 1978, 
  DZ_NMRA,   // Rule NMRA 
  DZ_RP,     // [RP ]
  DZ_BIC,    // [BIC ]
  DZ_AB,     // [AB ]
  DZ_NMSC,   // -NMSC-
  DZ_NMCA,   // -NMCA-
  DZ_NM,     // N.M.
  DZ_NM2,    // New Mexico
  DZ_F4,     // F.4th
  DZ_F3D,    // F.3d
  DZ_F2D,    // F.2d
  DZ_US,     // U.S. 
  DZ_P3D,    // P.3d
  DZ_P2D,    // P.2d
  DZ_SEE,    // See
  DZ_SID,    // See id. 
  DZ_SEEG,   // See, e.g.
  DZ_SALSO,  // See also
  DZ_ID,     // Id.
  DZ_ID2,    // id.
  DZ_ABQ,    // Albuquerque
  DZ_EA,     // emphasis added
  DZ_CO,     // citations omitted
  DZ_ROG,    // Interrogatory
  DZ_RGB, 
  DZ_SCAP,   // cross platform screen cap
  DZ_SCASE   // toggle sentence case
};

//#define DZ_SPC  LSFT_T(KC_SPC)
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
