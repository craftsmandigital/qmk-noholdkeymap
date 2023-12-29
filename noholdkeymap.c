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

#include <stdint.h>
#include QMK_KEYBOARD_H

#include "noholdkeymap.h"

#include "keymap_us_international.h"
#include "sendstring_us_international.h"

#include "keyboard-layout.h" // Layout has its own file
#include "features/magic-keys.h"
typedef enum {
    TOGGLE_ON,
    TOGGLE_OF_IF_ON,
} togle_actions_t;

bool caps_word(togle_actions_t action, uint8_t key) {
    bool capsOn, noESCtap = true;
    capsOn = (host_keyboard_leds() & (1 << USB_LED_CAPS_LOCK));
    if (action == TOGGLE_ON && !capsOn) {
        // Caps Lock is off
        tap_code(KC_CAPS);
    } else if (action == TOGGLE_OF_IF_ON && capsOn) {
        switch (key) {
            case KC_SPC:
            case KC_ESC:
            case KC_ENTER:
                tap_code(KC_CAPS);
                noESCtap = (key != KC_ESC);
        }
    }
    return noESCtap;
}

bool num_word(togle_actions_t action, uint8_t key) {
    bool noESCtap = true;
    bool layerOn  = (IS_LAYER_ON(NUM));
    if (action == TOGGLE_OF_IF_ON && layerOn) {
        // The NUM layer is active
        switch (key) {
            case KC_SPC:
            case KC_ESC:
                layer_off(NUM);
                noESCtap = (key != KC_ESC);
        }
    }
    return noESCtap;
}

void turn_off_nav_layer(uint8_t key) {
    if (IS_LAYER_ON(NAV)) {
        // The NAV layer is active
        // could not find a way to test on KC_TRANS. Then I had to test all the keys on the lyer.
        switch (key) {
            case KC_LEFT:
            case KC_RIGHT:
            case KC_UP:
            case KC_DOWN:
            case KC_PGUP:
            case KC_PGDN:
                return; // do nothing and return from function.
        }
        layer_off(NAV);
    }
}

// static bool holding_oneshot_layer = false;
// uint16_t my_key_pressed_timer = 0;

// --------------------------------------------------------------------------------
// combos stuff
enum combo_events {
    /*
      NAV_TOGLE,
      SYM_TOGLE,
      eUM_TOGLE,
      MOUSE_TOGLE,
      GUI_NUM,
    */
    FR_CTRL,
    KI_ALT,
    JU_SHIFT,
    DE_GUI,
    DOWNUP_ESC,
    JK_ESC,
    FD_TAB,
    DS_NEXT_KEY_FRIEND,
    /* JK_NEXT_KEY, */
    /* FD_NEXT_KEY_FRIEND, */
    VC_QUOTATION_END_KEY,
    KL_FUN,
};

// combos stuff
/*
const uint16_t PROGMEM nav_combo[] = {LT(NAV, KC_SPC),	LSFT_T(KC_J),	COMBO_END};
const uint16_t PROGMEM sym_combo[] = {LSFT_T(KC_F),		OSL(SYM),		COMBO_END};
const uint16_t PROGMEM num_combo[] = {LSFT_T(KC_F),		LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM mouse_combo[] = {LT(MOUSE, KC_DOT),LSFT_T(KC_J), COMBO_END};
const uint16_t PROGMEM gui_num_combo[] = {LCTL_T(KC_K), LALT_T(KC_L), COMBO_END};
*/
const uint16_t PROGMEM ctrl_combo[]  = {KC_F, KC_R, COMBO_END};
const uint16_t PROGMEM shift_combo[] = {KC_J, KC_U, COMBO_END};
const uint16_t PROGMEM alt_combo[]   = {KC_K, KC_I, COMBO_END};
const uint16_t PROGMEM gui_combo[]   = {KC_D, KC_E, COMBO_END};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM fd_combo[] = {KC_F, KC_D, COMBO_END};
const uint16_t PROGMEM kl_combo[] = {KC_K, KC_L, COMBO_END};
const uint16_t PROGMEM ds_combo[] = {KC_D, KC_S, COMBO_END};

/* const uint16_t PROGMEM jk_combo[]     = {KC_J, KC_K, COMBO_END}; */
const uint16_t PROGMEM downup_combo[] = {KC_DOWN, KC_UP, COMBO_END};
/* const uint16_t PROGMEM fd_combo[]     = {KC_F, KC_D, COMBO_END}; */
const uint16_t PROGMEM vc_combo[] = {KC_V, KC_C, COMBO_END};

combo_t key_combos[] = {
    /*

      [NAV_TOGLE] = COMBO(nav_combo, TG(NAV)),
      [SYM_TOGLE] = COMBO(sym_combo, TG(SYM)),
      [NUM_TOGLE] = COMBO(num_combo, TG(NUM)),
      [GUI_NUM] = COMBO(gui_num_combo, MY_GUI_NUM),
      [MOUSE_TOGLE] = COMBO(mouse_combo, TG(MOUSE)),
      // [QW_SFT] = COMBO(qw_combo, KC_LSFT)
      // [SD_LAYER] = COMBO(layer_combo, MO(_LAYER)),
    */
    [JU_SHIFT] = COMBO(shift_combo, OSM(MOD_LSFT)),
    [FR_CTRL]  = COMBO(ctrl_combo, OSM(MOD_LCTL)),
    [KI_ALT]   = COMBO(alt_combo, OSM(MOD_LALT)),
    [DE_GUI]   = COMBO(gui_combo, OSM(MOD_LGUI)),

    [JK_ESC]     = COMBO(jk_combo, KC_ESC),
    [DOWNUP_ESC] = COMBO(downup_combo, KC_ESC),
    [FD_TAB]     = COMBO(fd_combo, KC_TAB),
    [KL_FUN]     = COMBO(kl_combo, OSL(FUN)),

    /* [JK_NEXT_KEY]          = COMBO_ACTION(jk_combo), */
    /* [FD_NEXT_KEY_FRIEND]   = COMBO_ACTION(fd_combo), */
    [DS_NEXT_KEY_FRIEND]   = COMBO_ACTION(ds_combo),
    [VC_QUOTATION_END_KEY] = COMBO_ACTION(vc_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        /* case JK_NEXT_KEY: */
        /*     if (pressed) { */
        /*         magic_tap_key(NEXT_KEY); */
        /*     } */
        /*     break; */
        case DS_NEXT_KEY_FRIEND:
            if (pressed) {
                if (IS_LAYER_ON(NAV)) {
                    tap_code(KC_PGDN);
                } else {
                    magic_tap_key(NEXT_KEY_FRIEND);
                }
            }
            break;
        case VC_QUOTATION_END_KEY:
            if (pressed) {
                magic_tap_key(QUOTATION_END_KEY);
            }
            break;
    }
}

// --------------------------------------------------------------------------------

// remember key stuff
/* enum remember_key_events {
  SET,
  GET,
  PREVIOUS_KEY,
  NEXT_KEY,
  NEXT_QUOTATION_KEY,
}; */

// --------------------------------------------------------------------------------
// Leadr key stuff

/* void magic_execute_key(uint16_t *keycodes) { */
/**/
/*     // Access and print the array elements until the sentinel(0) is encountered */
/*     for (int i = 0; keycodes[i] != 0; i++) { */
/*        tap_code16(keycodes[i]); */
/*     } */
/* } */

/* void test_function(uint16_t keycodes_to_process[]) { */
/*     SEND_STRING("test"); */
/* } */

void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    // Fire nav layer after done firststep navigation
    // with tha arrow keys
    if (leader_sequence_one_key(KC_H)) {
        tap_code(KC_LEFT);
        layer_on(NAV);
    } else if (leader_sequence_one_key(KC_J)) {
        tap_code(KC_DOWN);
        layer_on(NAV);
    } else if (leader_sequence_one_key(KC_K)) {
        tap_code(KC_UP);
        layer_on(NAV);
    } else if (leader_sequence_one_key(KC_L)) {
        tap_code(KC_RIGHT);
        layer_on(NAV);

    //} else if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        // SEND_STRING("QMK is awesome.");
        // layer_on(FUN);
        //set_oneshot_layer(FUN, ONESHOT_START);
    } else if (leader_sequence_one_key(KC_D)) {
        MAGIC_SET(NEXT_KEY, NULL, U_PST);
        tap_code16(U_CUT);
    } else if (leader_sequence_one_key(KC_Y)) {
        MAGIC_SET(NEXT_KEY, NULL, U_PST);
        tap_code16(U_CPY);

        /* Word stuff */
        /* Moving */
    } else if (leader_sequence_one_key(KC_B)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_WORDR);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_WORDL);
        magic_tap_key(NEXT_KEY_FRIEND);
    } else if (leader_sequence_one_key(KC_W)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_WORDR);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_WORDL);
        magic_tap_key(NEXT_KEY);

        /* Selecting */
    } else if (leader_sequence_two_keys(KC_V, KC_B)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_WORDR);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_WORDL);
        magic_tap_key(NEXT_KEY_FRIEND);
    } else if (leader_sequence_two_keys(KC_V, KC_W)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_WORDR);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_WORDL);
        magic_tap_key(NEXT_KEY);

        /* Deleting */
    } else if (leader_sequence_two_keys(KC_D, KC_B)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_WORDR, U_CUT);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_WORDL, U_CUT);
        magic_tap_key(NEXT_KEY_FRIEND);
    } else if (leader_sequence_two_keys(KC_D, KC_W)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_WORDR, U_CUT);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_WORDL, U_CUT);
        magic_tap_key(NEXT_KEY);

        /* Copying */
    } else if (leader_sequence_two_keys(KC_Y, KC_B)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_WORDR, U_CPY);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_WORDL, U_CPY);
        magic_tap_key(NEXT_KEY_FRIEND);
    } else if (leader_sequence_two_keys(KC_Y, KC_W)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_WORDR, U_CPY);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_WORDL, U_CPY);
        magic_tap_key(NEXT_KEY);

        /* Line stuff */
        /* Selecting */
    } else if (leader_sequence_two_keys(KC_V, KC_V)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_LINE); // Dummy key to tap. Because first key pressed is unlike NEXT_KEY/NEXT_KEY_FRIEND
        magic_tap_key(NEXT_KEY);
        MAGIC_SET(NEXT_KEY, NULL, S(KC_UP));
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, S(KC_DOWN));

        /* Deleting */
    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_LINE, U_CUT); // Dummy key to tap. Because first key pressed is unlike NEXT_KEY/NEXT_KEY_FRIEND
        magic_tap_key(NEXT_KEY);
        MAGIC_SET(NEXT_KEY, NULL, KC_UP, UU_SEL_LINE, KC_DEL);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_LINE, KC_DEL);

        /* Copying */
    } else if (leader_sequence_two_keys(KC_Y, KC_Y)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_LINE, U_CPY); // Dummy key to tap. Because first key pressed is unlike NEXT_KEY/NEXT_KEY_FRIEND
        magic_tap_key(NEXT_KEY);
        MAGIC_SET(NEXT_KEY, NULL, KC_HOME, KC_HOME, U_PST); // Unselect and go home then paste copied text.
        // Copy line does not have a friend :-(

        /* Paragraph/sentence stuff */
        /* Moving */
    } else if (leader_sequence_two_keys(KC_G, KC_D)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_GRAPH_UP);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_GRAPH_UP);
        magic_tap_key(NEXT_KEY);
    } else if (leader_sequence_two_keys(KC_G, KC_U)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_GRAPH_UP);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_GRAPH_UP);
        magic_tap_key(NEXT_KEY_FRIEND);
        /* Selecting */
    } else if (leader_sequence_two_keys(KC_V, KC_P)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_GRAPH_UP);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_GRAPH_DN);
        magic_tap_key(NEXT_KEY);

        /* All stuff */
        /* Selecting */
    } else if (leader_sequence_two_keys(KC_V, KC_A)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_ALL); // Dummy key to tap. Because first key pressed is unlike NEXT_KEY/NEXT_KEY_FRIEND
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, U_CUT);
        magic_tap_key(NEXT_KEY);
        MAGIC_SET(NEXT_KEY, NULL, U_CPY);
        /* Deleting */
    } else if (leader_sequence_two_keys(KC_D, KC_A)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_ALL, U_CUT); // Dummy key to tap. Because first key pressed is unlike NEXT_KEY/NEXT_KEY_FRIEND
        magic_tap_key(NEXT_KEY);
        MAGIC_SET(NEXT_KEY, NULL, U_PST);
        /* Copying */
    } else if (leader_sequence_two_keys(KC_Y, KC_A)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_ALL, U_CPY); // Dummy key to tap. Because first key pressed is unlike NEXT_KEY/NEXT_KEY_FRIEND
        magic_tap_key(NEXT_KEY);
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_ALL, U_PST);

        /* Other stuff */
        /* Paste  with formating*/
    } else if (leader_sequence_two_keys(KC_P, KC_P)) {
        tap_code16(U_PST);
        /* Paste  without formating*/
    } else if (leader_sequence_one_key(KC_P)) {
        tap_code16(LSFT(U_PST));
        /* goto start of line */
    } else if (leader_sequence_one_key(KC_A)) {
        tap_code(KC_HOME);
        /* goto end of line */
    } else if (leader_sequence_one_key(US_OSTR)) {
        tap_code(KC_END);
        /* Delete one character */
    } else if (leader_sequence_one_key(KC_BSPC)) {
        MAGIC_SET(NEXT_KEY, NULL, KC_DEL);
        magic_tap_key(NEXT_KEY);
        /* pgdn*/
    } else if (leader_sequence_two_keys(KC_G, KC_D)) {
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, KC_PGDN);
        MAGIC_SET(NEXT_KEY, NULL, KC_PGUP);
        magic_tap_key(NEXT_KEY_FRIEND);
        /*  pgup */
    } else if (leader_sequence_two_keys(KC_G, KC_U)) {
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, KC_PGDN);
        MAGIC_SET(NEXT_KEY, NULL, KC_PGUP);
        magic_tap_key(NEXT_KEY);
        /* go to start of dockument*/
    } else if (leader_sequence_two_keys(KC_G, KC_G)) {
        tap_code16(LCTL(KC_HOME));
        /*  go to end of dockument */
    } else if (leader_sequence_three_keys(KC_G, KC_G, KC_G)) {
        tap_code16(LCTL(KC_END));
    } else if (leader_sequence_one_key(KC_R)) {
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, U_RDO);
        MAGIC_SET(NEXT_KEY, NULL, U_UND);
        magic_tap_key(NEXT_KEY_FRIEND);
    } else if (leader_sequence_one_key(KC_U)) {
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, U_RDO);
        MAGIC_SET(NEXT_KEY, NULL, U_UND);
        magic_tap_key(NEXT_KEY);
    } else if (leader_sequence_one_key(QK_LEAD)) {
        tap_code(KC_B);
    } else if (leader_sequence_one_key(KC_X)) {
        tap_code16(LCTL(KC_F4));
    } else if (leader_sequence_one_key(KC_Q)) {
        tap_code16(LALT(KC_F4));
    } else if (leader_sequence_one_key(KC_M)) {
        tap_code16(LSFT(KC_F10));
    }
    //---------------------------------------------------------------

    //---------------------------------------------------------------
}


// --------------------------------------------------------------------------------

// Macro stuff
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t hold_timer;
	bool quotChar = false;
    if (record->event.pressed) {
        quotChar = magic_key_set_all(keycode);
        if (!caps_word(TOGGLE_OF_IF_ON, keycode)) return false;
        if (!num_word(TOGGLE_OF_IF_ON, keycode)) return false;
    } else {
        turn_off_nav_layer(keycode);
    }
	
	if ((quotChar) && (record->event.pressed)){
		tap_code16(keycode);
		magic_tap_key(QUOTATION_END_KEY);
		tap_code(KC_LEFT);
		return false;
    }
	
    // if (IS_LAYER_ON(FUN) && !record->event.pressed){
    // clear_oneshot_layer_state(ONESHOT_PRESSED);
    // }
    // if ((holding_oneshot_layer) && (keycode != MY_ONESHOT) &&labs (!record->event.pressed))
    // {
    // clear_oneshot_layer_state(ONESHOT_PRESSED);
    // holding_oneshot_layer = false;
    // }
    switch (keycode) {
        case CWM_TOGG:
            if (record->event.pressed) {
                caps_word(TOGGLE_ON, 0);
                // This is a trick to keep CAPS-WORD on, when pressing an alternative space.
                MAGIC_SET(NEXT_KEY, NULL, KC_SPACE);
            }
            break;

        case OSL(NUM):
            if (record->event.pressed) {
                hold_timer = timer_read();
            } else {
                if (timer_elapsed(hold_timer) < TAPPING_TERM) {
                    // Key was tapped
                    if ((get_oneshot_mods() == 0) && (get_mods() == 0)) {
                        // Either one-shot mods or ordinary mods is active
                        layer_on(NUM);
                        return false;
                    } else {
                        // Key was held
                        // Do nothing. This alows holding of key
                    }
                }
            }
            break;

        case MY_NEXT_KEY:
            if (record->event.pressed) {
                magic_tap_key(NEXT_KEY);
            }
            break;

        case MY_NEXT_KEY_FRIEND:
            if (record->event.pressed) {
                magic_tap_key(NEXT_KEY_FRIEND);
            }
            break;

        case MY_SPC:
            if (record->event.pressed) {
                // Alternative space to not leave NUM layer.
                tap_code(KC_SPC);
            }
            break;
	    case KC_CIRC: // ^
        case KC_TILD: // ~
		    if (!record->event.pressed) {
                // Some codes neds an extra space afterwords to show up in "keymap_us_international.h"
                tap_code(KC_SPC);
            }
            break;
    }

    return true;
};
