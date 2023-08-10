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

void caps_word(togle_actions_t action, uint8_t key) {
    bool capsOn;
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
        }
    }
}

void num_word(togle_actions_t action, uint8_t key) {
    bool layerOn = (IS_LAYER_ON(NUM));
    if (action == TOGGLE_OF_IF_ON && layerOn) {
        // The NUM layer is active
        switch (key) {
            case KC_SPC:
            case KC_ESC:
                layer_off(NUM);
        }
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

    UI_ESC,
    RE_TAB,

    JK_NEXT_KEY,
    FD_NEXT_KEY_FRIEND,
    VC_QUOTATION_END_KEY
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

const uint16_t PROGMEM ui_combo[] = {KC_U, KC_I, COMBO_END};
const uint16_t PROGMEM re_combo[] = {KC_R, KC_E, COMBO_END};

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM fd_combo[] = {KC_F, KC_D, COMBO_END};
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

    [UI_ESC] = COMBO(ui_combo, KC_ESC),
    [RE_TAB] = COMBO(re_combo, KC_TAB),

    [JK_NEXT_KEY]          = COMBO_ACTION(jk_combo),
    [FD_NEXT_KEY_FRIEND]   = COMBO_ACTION(fd_combo),
    [VC_QUOTATION_END_KEY] = COMBO_ACTION(vc_combo),
};

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch (combo_index) {
        case JK_NEXT_KEY:
            if (pressed) {
                magic_tap_key(NEXT_KEY);
            }
            break;
        case FD_NEXT_KEY_FRIEND:
            if (pressed) {
                magic_tap_key(NEXT_KEY_FRIEND);
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
    if (leader_sequence_one_key(KC_F)) {
        // Leader, f => Types the below string
        // SEND_STRING("QMK is awesome.");
        // layer_on(FUN);
        set_oneshot_layer(FUN, ONESHOT_START);
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
        MAGIC_SET(NEXT_KEY, NULL, S(KC_DOWN));
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, S(KC_UP));

        /* Deleting */
    } else if (leader_sequence_two_keys(KC_D, KC_D)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_LINE, U_CUT); // Dummy key to tap. Because first key pressed is unlike NEXT_KEY/NEXT_KEY_FRIEND
        magic_tap_key(NEXT_KEY);
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_LINE, KC_DEL);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, KC_UP, UU_SEL_LINE, KC_DEL);

        /* Copying */
    } else if (leader_sequence_two_keys(KC_Y, KC_Y)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_LINE, U_CPY); // Dummy key to tap. Because first key pressed is unlike NEXT_KEY/NEXT_KEY_FRIEND
        magic_tap_key(NEXT_KEY);
        MAGIC_SET(NEXT_KEY, NULL, KC_HOME, KC_HOME, U_PST); // Unselect and go home then paste copied text.
        // Copy line does not have a friend :-(

        /* Paragraph/sentence stuff */
        /* Moving */
    } else if (leader_sequence_two_keys(KC_G, KC_J)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_GRAPH_DN);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_GRAPH_UP);
        magic_tap_key(NEXT_KEY);
    } else if (leader_sequence_two_keys(KC_G, KC_K)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_GRAPH_DN);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_GRAPH_UP);
        magic_tap_key(NEXT_KEY_FRIEND);
        /* Selecting */
    } else if (leader_sequence_two_keys(KC_V, KC_P)) {
        MAGIC_SET(NEXT_KEY, NULL, UU_SEL_GRAPH_DN);
        MAGIC_SET(NEXT_KEY_FRIEND, NULL, UU_SEL_GRAPH_UP);
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
    }

    //---------------------------------------------------------------

    //---------------------------------------------------------------
}

/*
uint16_t remember_key(	uint8_t  type, 		// type of remembering --> PREVIOUS_KEY, NEXT_KEY, NEXT_QUOTATION_KEY"
                        uint8_t  action,	// what to do --> GET/SET keyvalue
                        uint16_t keycode) {	// keycode to SET. NULL when GET is registerd
// Function returns a rememberd keycode if GET action is set.
// If SET action is present then it stores the keycode and returns NULL.
    static uint16_t previousKey = KC_NO, nextKey = KC_NO, nextQuotKey = KC_NO, returnKey = KC_NO;

    if (action == GET){
        if (type == PREVIOUS_KEY){
            returnKey = previousKey;
        } else if (type == NEXT_KEY){
            returnKey = nextKey;
        } else if (type == NEXT_QUOTATION_KEY){
            returnKey = nextQuotKey;
        }
    } else if (action == SET){
        if (type == PREVIOUS_KEY){
            previousKey = keycode;
        } else if (type == NEXT_KEY){
            nextKey = keycode;
        } else if (type == NEXT_QUOTATION_KEY){
            nextQuotKey = keycode;
        }
    }

    return returnKey;
}
 */
// --------------------------------------------------------------------------------

/*
void organize_layer(uint8_t	layerToSet		// BASE, SYM, NAV, NUM, ...
                    ,bool	oneShot) {// TRUE if oneShot behaviour else FALSE when PERSISTENT layer
    static uint8_t currentLayer = BASE;
    currentLayer = layerToSet;
}

void organize_layer_connect(uint8_t	layerToSet		// BASE, SYM, NAV, NUM, ...
                    ,bool	oneShot) {// TRUE if oneShot behaviour else FALSE when PERSISTENT layer

}

void organize_layer_check(uint8_t	layerToSet		// BASE, SYM, NAV, NUM, ...
                    ,bool	oneShot) {// TRUE if oneShot behaviour else FALSE when PERSISTENT layer

}

void organize_layer_disconnect(uint8_t	layerToSet		// BASE, SYM, NAV, NUM, ...
                    ,bool	oneShot) {// TRUE if oneShot behaviour else FALSE when PERSISTENT layer

}
*/

// --------------------------------------------------------------------------------

// Macro stuff
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        magic_key_set_all(keycode);
        caps_word(TOGGLE_OF_IF_ON, keycode);
        num_word(TOGGLE_OF_IF_ON, keycode);
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
            }
            break;

        case OSL(NUM):
            if (record->event.pressed) {
                if ((get_oneshot_mods() == 0) && (get_mods() == 0)) {
                    // Either one-shot mods or ordinary mods is active
                    layer_on(NUM);
                    return false;
                }
            }
            break;
    }
    /*

        case KC_SPC:
            if (record->event.pressed) {
                // when layer is on go back to caling layer and pres space
                if (IS_LAYER_ON(NUM)){
                    layer_invert(NUM);
                    tap_code(KC_SPC);
                    return false;
                }
            }
            break;
        case OSL(NUM):
            if (record->event.pressed) {
                // when modifier keys is held then prosess key as usual.
                // When no mods then togle SYM layer permanent
                const uint8_t mods = get_mods() | get_oneshot_mods();
                if (!mods){
                  layer_invert(NUM);
                  return false;
                }
            }
            break;
        // case MY_ONESHOT:
            // if (record->event.pressed) {
               // set_oneshot_layer(SYM, ONESHOT_START);
               // holding_oneshot_layer = true;
            // } return false;
            // break;
        case PAREN:
            if (record->event.pressed) {
                // when key ( is pressed
                SEND_STRING("()"SS_TAP(X_LEFT));
            }
            break;
        case BRACKET:
            if (record->event.pressed) {
                // when key [ is pressed
                SEND_STRING("[]"SS_TAP(X_LEFT));
            }
            break;
        case CURLEY:
            if (record->event.pressed) {
                // when key { is pressed
                SEND_STRING("{}"SS_TAP(X_LEFT));
            }
            break;
        case QUOT:
            if (record->event.pressed) {
                // when key ' is pressed
                SEND_STRING("''"SS_TAP(X_LEFT));
            }
            break;
        case DQUOT:
            if (record->event.pressed) {
                // when key " is pressed
                SEND_STRING("\"\""SS_TAP(X_LEFT));
            }
            break;
        // The four next keys goes to their extremes on long tapp
        // and do shorter travel on short press
        case MY_END:
            if (record->event.pressed) {
                my_key_pressed_timer = timer_read();
            } else {
                // goes by word to the right when short pressed.
                if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
                    register_code(KC_LCTL);
                    tap_code(KC_RGHT);
                    unregister_code(KC_LCTL);
                } else {
                    // goes to end of line on long press
                    tap_code(KC_END);
                }
            }
            break;
            case MY_HOME:
            if (record->event.pressed) {
                my_key_pressed_timer = timer_read();
            } else {
                if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
                    register_code(KC_LCTL);
                    tap_code(KC_LEFT);
                    unregister_code(KC_LCTL);
                } else {
                    tap_code(KC_HOME);
                }
            }
            break;
            case MY_COPY:
            if (record->event.pressed) {
                my_key_pressed_timer = timer_read();
            } else {
                if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
                    register_code(KC_LCTL);
                    tap_code(KC_C);
                    unregister_code(KC_LCTL);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_A);
                    unregister_code(KC_LCTL);
                }
            }
            break;
            case MY_UNDRDO:
            if (record->event.pressed) {
                my_key_pressed_timer = timer_read();
            } else {
                if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
                    register_code(KC_LCTL);
                    tap_code(KC_Z);
                    unregister_code(KC_LCTL);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_Y);
                    unregister_code(KC_LCTL);
                }
            }
            break;
            case MY_PASTE:
            if (record->event.pressed) {
                my_key_pressed_timer = timer_read();
            } else {
                register_code(KC_LCTL);
                if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
                    register_code(KC_LSFT);
                    tap_code(KC_V);
                    unregister_code(KC_LSFT);
                } else {
                    tap_code(KC_V);
                }
                unregister_code(KC_LCTL);
            }
            break;
            case MY_PGDN:
            if (record->event.pressed) {
                my_key_pressed_timer = timer_read();
            } else {
                if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
                    tap_code(KC_PGDN);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_END);
                    unregister_code(KC_LCTL);

                }
            }
            break;
            case MY_PGUP:
            if (record->event.pressed) {
                my_key_pressed_timer = timer_read();
            } else {
                if (timer_elapsed(my_key_pressed_timer) < LEADER_TIMEOUT) {
                    tap_code(KC_PGUP);
                } else {
                    register_code(KC_LCTL);
                    tap_code(KC_HOME);
                    unregister_code(KC_LCTL);

                }
            }
            break;
            // Nordic caracter stuff is dependent of autohotkey
            // https://www.thenickmay.com/how-to-expand-text-for-free-with-autohotkey/
            // When keypress is shifted then keypress is different the char "-" becoms a "_"
            // auto hotkey schipt handles this and expand the right nordic character
            case _AA	:	// å Å
            if (record->event.pressed) {
                    SEND_STRING("-&a");  // Becomes _&a when shifted
            }
            break;
            case _AE	:	// æ Æ
            if (record->event.pressed) {
                    SEND_STRING("-&e");  // Becomes _&e when shifted
            }
            break;
            // case _OE	:	// ø Ø
            // if (record->event.pressed) {
                    // SEND_STRING("-&o");  // Becomes _&o when shifted
            // }
            // break;
            case RGUI_T(_OE)	:	// ø Ø
            // This was extremely difficult to program, because of the nature of GUI modifier
            // It is also triggered on tap. luckyly the solution was quite easy. The solution was found on website under:
            // https://github.com/qmk/qmk_firmware/blob/master/docs/mod_tap.md#changing-tap-function.
            // The moust obious solution was something like the website under.
            // But doestnt work because of the nature of the GUI modifier
            // https://thomasbaart.nl/2018/12/09/qmk-basics-tap-and-hold-actions/#a-workaround-for-mod-tap

            if (record->tap.count && record->event.pressed) {
                SEND_STRING("-&o"); // Send KC_DQUO on tap
                return false;        // Return false to ignore further processing of key
            }
            break;

        }
        */
    return true;
};

/*
 void post_process_record_user(uint16_t keycode, keyrecord_t *record) {


    switch (keycode) {

    case MY_GUI_NUM:
    // This is a oneshotlayer and oneshot modifier at the same time
    // SYM layer and GUI modifier at once.
    // This makes it easy to switch apps in the taskbar in windows 10.
    // The state before next key pressed is num layer and gui modifier.
    // When user press a nuber key, then it triggers to open or switching to that app in taskbar
        if (record->event.pressed) {
            // layer_on(NUM);
            set_oneshot_layer(NUM, ONESHOT_START);
            clear_oneshot_layer_state(ONESHOT_PRESSED);

            set_oneshot_mods(MOD_RGUI);
        } else {
            // clear_oneshot_layer_state(ONESHOT_PRESSED);
        }
        break;

    }

};
*/
