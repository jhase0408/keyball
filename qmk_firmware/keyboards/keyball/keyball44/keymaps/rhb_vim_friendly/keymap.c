/*
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

#include "keycodes.h"
#include "rgblight.h"
#include QMK_KEYBOARD_H

#include "quantum.h"
#include "lib/keyball/keyball.h"
// for debug
#include "print.h"


enum userKey {
    KC_SLOW = KEYBALL_SAFE_RANGE,
    KC_FAST,
    KC_VSCL,
    KC_HSCL,
};

enum layer {
  BASE = 0,
  NUM,
  CUR,
  SYM,
  MOUSE,
  LAYER_MAX,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  // keymap for default
  [BASE] = LAYOUT_right_ball(
    QK_GESC       , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                        KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_LBRC  ,
    LCTL_T(KC_TAB), KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                        KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , KC_QUOT  ,
    SC_LSPO       , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     ,                                        KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , SC_RSPC  ,
                    KC_LALT  , KC_LGUI             ,MO(SYM)   ,LT(NUM,KC_SPC), QK_LEAD,        LT(MOUSE,KC_BSPC), LT(CUR,KC_ENT),                             KC_PSCR
  ),

  [NUM] = LAYOUT_right_ball(
    _______       ,  KC_1    , KC_2     , KC_3    , KC_4     , KC_5     ,                                         KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_MINS  ,
    _______       ,  _______ , _______  , _______ , _______  , _______  ,                                         _______  , _______  , _______  , _______  , _______  , _______  ,
    _______       ,  _______ , _______  , _______ , _______  , _______  ,                                         _______  , _______  , _______  , _______  , _______  , _______  ,
                     _______ , _______            , _______  , _______  , _______  ,                   _______  , _______  ,                                  _______
  ),

  [CUR] = LAYOUT_right_ball(
    _______       ,  _______ , _______  , _______ , _______  , _______  ,                                         _______  , KC_PGUP  , _______  , _______  , _______  , _______  ,
    _______       ,  _______ , _______  , KC_PGDN , _______  , _______  ,                                         KC_LEFT  , KC_DOWN  , KC_UP    , KC_RIGHT , _______  , _______  ,
    _______       ,  _______ , _______  , _______ , _______  , _______  ,                                         _______  , _______  , _______  , _______  , _______  , _______  ,
                     _______ , _______            , _______  , _______  , _______  ,                   _______  , _______  ,                                  _______
  ),
  
  [SYM] = LAYOUT_right_ball(
    _______       , KC_F1    , KC_F2    , KC_F3   , KC_F4    , KC_F5    ,                                         KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_RBRC  ,
    _______       , _______  , _______  , _______ , _______  , _______  ,                                         _______  , _______  , _______  , KC_MINS  , KC_EQL   , KC_BSLS  ,
    _______       , _______  , _______  , _______ , _______  , _______  ,                                         _______  , _______  , _______  , _______  , _______  , _______  ,
                    _______  , _______            , _______  , _______  , _______  ,            LT(MOUSE,KC_DEL), _______  ,                                  _______
  ),

  [MOUSE] = LAYOUT_right_ball(
    _______       , _______  , _______  , _______  , _______  , KC_BTN5  ,                                        _______  , _______  , _______  , _______  , KC_BTN4  , _______  ,
    _______       , _______  , KC_BTN2  , KC_BTN3  , KC_BTN1  , _______  ,                                        _______  , KC_BTN1  , KC_BTN3  , KC_BTN2  , _______  , SCRL_MO  ,
    _______       , _______  , _______  , _______  , _______  , KC_BTN4  ,                                        KC_BTN5  , _______  , _______  , _______  , _______  , _______  ,
                    _______  , _______             , _______  , _______  , _______  ,                   _______ , _______  ,                                  _______
  ),
  /* template
  [4] = LAYOUT_right_ball(
    _______       , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______       , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
    _______       , _______  , _______  , _______  , _______  , _______  ,                                        _______  , _______  , _______  , _______  , _______  , _______  ,
                    _______  , _______             , _______  , _______  , _______  ,                  _______  , _______  ,                                  _______  
  ),
  */
};
// clang-format on

/* LED Layout reference:
// backlight: 0-19, 40-58 
    17, 14, 10,  6,  3,  0,                   56, 53, 50, 47, 43, 40,
    18, 15, 11,  7,  4,  1,                   57, 54, 51, 48, 44, 41,
    19, 16, 12,  8,  5,  2,                   58, 55, 52, 49, 45, 42,
            13,  9,     __, __, __,       __, __,             46

// underglow: 20-29, 30-39
      22,     21,     20,                           39, 38,     37,
    23,                                                           36,
    24,                                           32,             35,
            25, 26,     27, 28, 29,       30, 31,     33,     34 

*/

// RGB Lighting Layer
const rgblight_segment_t PROGMEM keyball_rgblight_layer_base[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 20, HSV_BLACK},
    {40, 19, HSV_BLACK}
);

const rgblight_segment_t PROGMEM keyball_rgblight_layer_num[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_CYAN},  {3, 1, HSV_CYAN},  {6, 1, HSV_CYAN},  {10, 1, HSV_CYAN}, {14, 1, HSV_CYAN}, {17, 1, HSV_CYAN},
    {40, 1, HSV_CYAN}, {43, 1, HSV_CYAN}, {47, 1, HSV_CYAN}, {50, 1, HSV_CYAN}, {53, 1, HSV_CYAN}, {56, 1, HSV_CYAN}
);

const rgblight_segment_t PROGMEM keyball_rgblight_layer_cur[] = RGBLIGHT_LAYER_SEGMENTS(
    {48, 1, HSV_GREEN}, {51, 1, HSV_GREEN}, {54, 1, HSV_GREEN}, {57, 1, HSV_GREEN}, 
    { 7, 1, HSV_AZURE}, {53, 1, HSV_AZURE} 
);

const rgblight_segment_t PROGMEM keyball_rgblight_layer_sym[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GOLD},  {3, 1, HSV_GOLD},  {6, 1, HSV_GOLD},  {10, 1, HSV_GOLD}, {14, 1, HSV_GOLD}, {17, 1, HSV_GOLD},
    {40, 2, HSV_GOLD}, {43, 2, HSV_GOLD}, {47, 2, HSV_GOLD}, {50, 1, HSV_GOLD}, {53, 1, HSV_GOLD}, {56, 1, HSV_GOLD},
    {30, 1, HSV_GOLD}
);

const rgblight_segment_t PROGMEM keyball_rgblight_layer_mouse[] = RGBLIGHT_LAYER_SEGMENTS(
    {33,  2, HSV_RED},
    { 0,  1, HSV_RED}, { 2,  1, HSV_RED}, { 4,  1, HSV_RED}, { 7,  1, HSV_RED}, {11,  1, HSV_RED}, 
    {43,  1, HSV_RED}, {48,  1, HSV_RED}, {51,  1, HSV_RED}, {54,  1, HSV_RED}, {58,  1, HSV_RED}
);

const rgblight_segment_t* const PROGMEM keyball_rgblight_layers[] = RGBLIGHT_LAYERS_LIST(
  keyball_rgblight_layer_base,
  keyball_rgblight_layer_num,
  keyball_rgblight_layer_cur,
  keyball_rgblight_layer_sym,
  keyball_rgblight_layer_mouse
);

void keyboard_post_init_user(void) {
    // for debug
    // debug_enable=true;
  
    rgblight_layers = keyball_rgblight_layers;
    rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_sethsv(106, 128, 50);
    rgblight_set_layer_state(BASE, true);
}

void pointing_device_init_user(void) {
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    if (is_keyboard_master()) {
       set_auto_mouse_layer(MOUSE);
       set_auto_mouse_enable(true);
    }
#endif //POINTING_DEVICE_AUTO_MOUSE_ENABLE
}

// Leader key

void leader_start_user(void) {
    
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_J)) {
        tap_code(KC_LNG1); // LANG: JA
    } else if (leader_sequence_one_key(KC_E)) {
        tap_code(KC_LNG2); // LANG: EN
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {

    if (is_keyboard_master()) {
        rgblight_set_layer_state(BASE, true);
        for (int i = 1; i < LAYER_MAX; ++i){
            rgblight_set_layer_state(i, layer_state_cmp(state, i));
        }
    }
    return state;
}


// OLED
#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif
