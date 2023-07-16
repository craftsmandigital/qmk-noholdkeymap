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


#include QMK_KEYBOARD_H

/* #define MAGIC_KEYS_COUNT 3 */

typedef enum {
    NEXT_KEY,
    NEXT_KEY_FRIEND,
    QUOTATION_END_KEY,
    MAGIC_KEYS_COUNT,   // Has to be located after all the magic key types
    NO_KEY,             // Must be after MAGIC_KEYS_COUNT. Parameter to execute_key_sequence() if no register of key is preferred
} magic_key_t;



void execute_key_sequence(uint16_t *keycodes);
void magic_tap_key(magic_key_t *keytype);

void magic_set(magic_key_t *keytype,
               void (*function_pointer)(uint16_t keycodes_to_process[]),
               uint16_t keycodes[]);

