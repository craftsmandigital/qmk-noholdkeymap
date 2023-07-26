#include "magic-keys-default.h"



void default_shift_one_shot(uint16_t keycodes_to_process[])
{
    magic_tap_machine(keycodes_to_process);
	set_oneshot_mods(MOD_BIT(KC_RSFT));
}


void magic_key_set_all(uint16_t key)
{
    uint16_t nextQuotationMark = 0;

    switch (key) {

        // Common processing for all parentheses and quotation mark characters

        // Processing for quotation mark characters
        case KC_QUOT:   // Proc5essing for single quotation mark (')
        case KC_DQUO:   // Processing for double quotation mark (")
        case KC_GRV:    // Processing for backtick (`)
            nextQuotationMark = key;
            break;

        // Processing for parentheses
        case KC_LPRN: // Processing for '(' character
        // case KC_RPAREN: // Processing for ')' character
            nextQuotationMark = KC_RPRN;
            break;
        case KC_LBRC:   // Processing for '[' character
        // case KC_RBRC:   // Processing for ']' character
            nextQuotationMark = KC_RBRC;
            break;
        case KC_LCBR:   // Processing for '{' character
        // case KC_RCBR:   // Processing for '}' character
            nextQuotationMark = KC_RCBR;
            break;
        // Processing for quotation marks
        case KC_LABK:   // Processing for right-pointing double angle quotation mark (»)
        // case KC_RABK:   // Processing for right-pointing double angle quotation mark (»)
            nextQuotationMark = KC_RABK;
            break;




        // Processing for all other characters

        case KC_DOT:

            MAGIC_SET(NEXT_KEY , default_shift_one_shot, KC_SPACE);
            MAGIC_SET(NEXT_KEY_FRIEND , default_shift_one_shot, KC_ENT);
            break;



    }


    if (nextQuotationMark != 0) {
        uint16_t keycodes[3];

        // NEXT_KEY
        keycodes[0] = nextQuotationMark;
        keycodes[1] = KC_LEFT;
        keycodes[2] = 0;
        magic_set(NEXT_KEY, NULL, keycodes);

        // NEXT_KEY_FRIEND
        keycodes[0] = KC_RIGHT;
        keycodes[1] = 0;
        keycodes[2] = 0;
        magic_set(NEXT_KEY_FRIEND, NULL, keycodes);

        // QUOTATION_END_KEY
        keycodes[0] = nextQuotationMark;
        keycodes[1] = 0;
        keycodes[2] = 0;
        magic_set(QUOTATION_END_KEY, NULL, keycodes);

    }
}
