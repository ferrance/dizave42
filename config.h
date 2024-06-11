/*

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2023 D. Ferrance (@ferrance)

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

#pragma once

/* Select hand configuration */
#define MASTER_LEFT

#undef PRODUCT
#define PRODUCT "dizave42"

// sexy dizave42 logo
#undef OLED_FONT_H
#define OLED_FONT_H "dizave42.c"

#ifdef BIG_OLED
    #define OLED_IC OLED_IC_SH1106
    #define OLED_COLUMN_OFFSET 2
    #define OLED_DISPLAY_128X64
#endif 

// leader key
#define LEADER_PER_KEY_TIMING
#define LEADER_TIMEOUT 300
#define LEADER_NO_TIMEOUT

// home row mods
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 180
#define TAPPING_TERM_PER_KEY
//#define HOLD_ON_OTHER_KEY_PRESS
//#define PERMISSIVE_HOLD
//#define IGNORE_MOD_TAP_INTERRUPT // remove for qmk 21.0

// dizave supports mac and windows
#define UNICODE_SELECTED_MODES UNICODE_MODE_MACOS, UNICODE_MODE_WINCOMPOSE

// caps_word enabled by double tapping left shift
#define BOTH_SHIFTS_TURNS_ON_CAPS_WORD   

// for rgb matrix support
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE

#define ONE_SHOT_TIMEOUT 1000

// trying to be small
#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT

/* much of this comes from the bermeo layout */

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_KEYPRESSES // reacts to keypresses 
#    define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#    define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
#    undef RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #    define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#    define RGB_MATRIX_LED_FLUSH_LIMIT 16                           // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150                       // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
#    define RGB_MATRIX_HUE_STEP 8
#    define RGB_MATRIX_SAT_STEP 8
#    define RGB_MATRIX_VAL_STEP 8
#    define RGB_MATRIX_SPD_STEP 10

/* Disable the animations you don't want/need.  You will need to disable a good number of these    *
 * because they take up a lot of space.  Disable until you can successfully compile your firmware. */
#    define ENABLE_RGB_MATRIX_ALPHAS_MODS
#    define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN			// solid bit w different colors
#    undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON		// this one is great
#    define ENABLE_RGB_MATRIX_BAND_VAL				// interesting one 

#    undef ENABLE_RGB_MATRIX_BREATHING
#    undef ENABLE_RGB_MATRIX_BAND_SAT				//not bad
#    undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT			// not bad but there are better ones
#    undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT              // kinda dumb
#    undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#    undef ENABLE_RGB_MATRIX_CYCLE_ALL				// a little too freaky for me
#    define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT			// not bad
#    undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN			// not bad
#    undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN			// not bad
#    undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL			// not bad a little fast tho
#    undef ENABLE_RGB_MATRIX_DUAL_BEACON
#    undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#    undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#    undef ENABLE_RGB_MATRIX_RAINBOW_BEACON			// meh
#    undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#    undef ENABLE_RGB_MATRIX_RAINDROPS				// boring
#    undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#    undef ENABLE_MATRIX_PIXEL_FLOW
#    undef ENABLE_MATRIX_PIXEL_RAIN
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE			// better than jest plain solid
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS		// makes a cross at the key you hit
#    undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    undef ENABLE_RGB_MATRIX_SPLASH				// meh
#    undef ENABLE_RGB_MATRIX_MULTISPLASH			// meh
#    undef ENABLE_RGB_MATRIX_SOLID_SPLASH
#    undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

#endif

