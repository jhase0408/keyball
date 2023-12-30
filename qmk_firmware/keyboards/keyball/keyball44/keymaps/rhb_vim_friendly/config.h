/*
This is the c configuration file for the keymap

Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#define TAP_CODE_DELAY 5

// enable/disable RGB Light animations
#undef RGBLIGHT_EFFECT_ALTERNATING
// #undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_TWINKLE

// RGB Light configs
#define RGBLIGHT_SLEEP
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
#define RGBLIGHT_DEFALUT_HUE 106
#define RGBLIGHT_DEFALUT_SAT 128
#define RGBLIGHT_DEFALUT_VAL 50

// RGB Matrix configs
// #define DRIVER_LED_TOTAL 60
// #define RGB_MATRIX_LED_COUNT 60
// #define RGB_MATRIX_MAXIMUM_BRIGTNESS 126
// #define RGB_MATRIX_DEFAULT_HUE 125
// #define RGB_MATRIX_DEFAULT_SAT 255
// #define RGB_MATRIX_DEFAULT_VAL 125
//
// #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
// #define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #define RGB_MATRIX_TYPING_HEATMAP_SPREAD 32
// #define RGB_MATRIX_TYPING_HEATMAP_AREA_LIMIT 16
// #define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25
//
// #define RGB_MATRIX_KEYPRESSES
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
// #define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_TYPING_HEATMAP

// split transaction
#define SPLIT_LAYER_STATE_ENABLE

// Automatic Mouse Layer
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE
#define AUTO_MOUSE_DEFAULT_LAYER 3

