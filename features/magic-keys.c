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



#include "magic-keys.h"


typedef struct {
    void (*function_pointer)(uint16_t keycodes_to_process[]);
    uint16_t keycodes[];
} magic_key_struct_t;

magic_key_struct_t magic_keys[MAGIC_KEYS_COUNT];



void magic_execute_key(
        void (*function_pointer)(uint16_t keycodes_to_process[]),
        uint16_t *keycodes,
        magic_key_t store_as_keytype) {

    // Access and print the array elements until the sentinel(0) is encountere
    for (int i = 0; keycodes[i] != 0; i++) {
       tap_code16(keycodes[i]);
    }
}


void magic_tap_key(magic_key_t *keytype) {

}



void magic_set(magic_key_t *keytype,
               void (*function_pointer)(uint16_t keycodes_to_process[]),
               uint16_t keycodes[]) {

}




