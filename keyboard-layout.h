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

	CWM_TOGG,
    MY_NEXT_KEY_FRIEND,
    MY_NEXT_KEY,
    MY_SPC,
};

enum layers { BASE, NUM, NAV, SYM, FUN };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] =  {
  [BASE] = LAYOUT_miryoku(
    //┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
        KC_Q , KC_W , KC_E , KC_R , KC_T ,                      KC_Y , KC_U , KC_I , KC_O , KC_P ,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
        KC_A , KC_S , KC_D , KC_F , KC_G ,                      KC_H , KC_J , KC_K , KC_L ,US_OSTR,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
        KC_Z , KC_X , KC_C , KC_V , KC_B,  /* OSL(SYM), */    KC_N ,KC_M,MY_NEXT_KEY,US_ARNG,US_AE,
    //└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┴──────┴──────┘
      U_NP,U_NP,         QK_LEAD,KC_SPC,OSL(SYM),LT(FUN,KC_ENT),KC_BSPC,OSL(NUM),         U_NP,U_NP
    //                     └──────┴──────┴──────┘      └──────┴──────┴──────┘
    ),
  [NUM] = LAYOUT_miryoku(
    //┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
      KC_PLUS, KC_7 , KC_8 , KC_9 ,KC_ASTR,                   KC_COMM,KC_DOT,KC_NO, KC_NO, KC_NO,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
      KC_MINS, KC_4 , KC_5 , KC_6 ,KC_SLSH,                   KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,KC_NO,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
      KC_PERC, KC_1 , KC_2 , KC_3 ,KC_EQL,                    KC_NO , KC_NO, MY_SPC, KC_NO, KC_NO,
    //└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┴──────┴──────┘
      U_NP,U_NP,            KC_0, KC_TRNS,KC_TRNS,     KC_TRNS,KC_TRNS,KC_NO,         U_NP,U_NP
    //                     └──────┴──────┴──────┘      └──────┴──────┴──────┘
    ),
  [NAV] = LAYOUT_miryoku(
    //┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
     KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                 KC_LEFT,KC_DOWN,KC_UP,KC_RGHT,KC_TRNS,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
    KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,KC_TRNS,KC_PGUP,KC_TRNS,KC_TRNS,
    //└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┴──────┴──────┘
      U_NP,U_NP,          KC_TRNS,KC_TRNS,KC_TRNS,     KC_TRNS,KC_TRNS,KC_TRNS,         U_NP,U_NP
    //                     └──────┴──────┴──────┘      └──────┴──────┴──────┘
  ),
  [SYM] = LAYOUT_miryoku(
    //┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
    KC_PLUS,KC_EXLM,KC_SCLN,KC_QUOT,KC_ASTR,                 KC_COMM,KC_DOT,CWM_TOGG,KC_CAPS,KC_NO,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
    KC_MINS,KC_QUES,KC_COLN,KC_DQUO,KC_SLSH,                 KC_LCBR,KC_LPRN,KC_LBRC,KC_DLR,KC_UNDS,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
     KC_PERC,KC_TILD,KC_CIRC,KC_GRV,KC_EQL,                 KC_RCBR,KC_RPRN,KC_RBRC,KC_AMPR,KC_HASH,
    //└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┴──────┴──────┘
      U_NP,U_NP,          KC_PIPE,KC_BSLS,KC_LT,        KC_GT, KC_AT, KC_NO,         U_NP,U_NP
    //                     └──────┴──────┴──────┘      └──────┴──────┴──────┘
  ),
  [FUN] = LAYOUT_miryoku(
    //┌──────┬──────┬──────┬──────┬──────┐                    ┌──────┬──────┬──────┬──────┬──────┐
       KC_NO , KC_F7, KC_F8, KC_F9,QK_BOOT,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
       KC_NO , KC_F4, KC_F5, KC_F6,DB_TOGG,                     KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //├──────┼──────┼──────┼──────┼──────┤                    ├──────┼──────┼──────┼──────┼──────┤
       KC_NO, KC_F1, KC_F2, KC_F3,EE_CLR,                      KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
    //└──────┴──────┴──────┼──────┼──────┼──────┐      ┌──────┼──────┼──────┼──────┴──────┴──────┘
      U_NP,U_NP,            KC_F10,KC_F11,KC_F12,        KC_NO, KC_NO, KC_NO,         U_NP,U_NP
    //                     └──────┴──────┴──────┘      └──────┴──────┴──────┘
  )
};

