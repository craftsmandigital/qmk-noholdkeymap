/* Copyright 2023 Jon Arne Viksås (@craftsmandigital)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once
//#include QMK_KEYBOARD_H // Does not need this, its included before this file in joppa.c
// Macro stuff
enum custom_keycodes {
	PAREN = SAFE_RANGE,
    BRACKET,
    CURLEY,
	QUOT,
	DQUOT,
	MY_END,
	MY_HOME,
	MY_PASTE,
	MY_COPY,
 	MY_PGUP,
	MY_PGDN,
	MY_GUI_NUM,
	MY_UNDRDO,
	MY_ONESHOT,
	MY_PREV,
	_AA, // Åå
	_AE, // æÆ
	_OE, // øØ
};

enum layers { BASE, NUM, NAV, SYM, FUN };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_miryoku(
//┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
    KC_Q , KC_W , KC_E , KC_R , KC_T ,                      KC_Y , KC_U , KC_I , KC_O , KC_P ,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
    KC_A , KC_S , KC_D , KC_F , KC_G ,                      KC_H , KC_J , KC_K , KC_L ,US_OSTR,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
    KC_Z , KC_X , KC_C , KC_V , KC_B ,                      KC_N , KC_M , UNDO,US_ARNG, US_AE,
//└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┴──────┘
                        OSL(4),KC_SPC,LEADER,      OSL(1),KC_BSPC,OSL(3)),
//                     └──────┴──────┴──────┘      └──────┴──────┴──────┘ 
  ),
  [NUM] = LAYOUT_miryoku(
//┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
  KC_PLUS, KC_P7, KC_P8, KC_P9,KC_ASTR,                   KC_PCMM,KC_ENT,KC_PDOT,KC_NO, KC_NO,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
  KC_PMNS, KC_P4, KC_P5, KC_P6,KC_PSLS,                   KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,KC_NO,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
  KC_PERC, KC_P1, KC_P2, KC_P3,KC_PEQL,                    KC_NO , KC_NO,KC_TRNS,KC_NO, KC_NO,
//└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┴──────┘
                        KC_P0,KC_TRNS, KC_LT,       KC_GT ,KC_TRNS,KC_NO
//                     └──────┴──────┴──────┘      └──────┴──────┴──────┘ 
  ),
  [NAV] = LAYOUT_miryoku(
//┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                 KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,KC_TRNS,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
 KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
//└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┴──────┘
                       KC_TRNS,KC_TRNS,KC_TRNS,   KC_TRNS,KC_TRNS,KC_TRNS,
//                     └──────┴──────┴──────┘      └──────┴──────┴──────┘ 
  ),
  [SYM] = LAYOUT_miryoku(
//┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
KC_PLUS,KC_EXLM,KC_SCLN,KC_QUOT,KC_ASTR,                  KC_PCMM,KC_ENT,KC_PDOT,CW_TOGG,KC_CAPS,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
KC_PMNS,KC_QUES,KC_COLN,KC_DQUO,KC_PSLS,                 KC_LCBR,KC_LPRN,KC_LBRC,KC_DLR,KC_UNDS,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
  KC_PERC, KC_NO, KC_NO,KC_GRV,KC_PEQL,                   KC_CIRC,KC_TILD,REDO,KC_AMPR,KC_HASH,
//└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┴──────┘
                       KC_PIPE,KC_BSLS,KC_LT,       KC_GT, KC_DEL, KC_AT
//                     └──────┴──────┴──────┘      └──────┴──────┴──────┘ 
  ),
  [FUN] = LAYOUT_miryoku(
//┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
   KC_NO , KC_F7, KC_F8, KC_F9,QK_BOOT,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
   KC_NO , KC_F4, KC_F5, KC_F6,DB_TOGG,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
//├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
    KC_NO, KC_F1, KC_F2, KC_F3,EE_CLR,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
//└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┼──────┴──────┘
                        KC_F10,KC_F11,KC_F12,        KC_NO, KC_NO, KC_NO
//                     └──────┴──────┴──────┘      └──────┴──────┴──────┘ 
  )
};

