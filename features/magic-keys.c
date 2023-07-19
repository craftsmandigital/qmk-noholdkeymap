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

#ifdef MAGIC_KEYS_DEFAULT_CONFIG
    #include "magic-keys-default.c"
#endif // Default config

typedef struct {
    void (*function_pointer)(uint16_t keycodes_to_process[]);
    uint16_t *keycodes;
} magic_key_struct_t;

magic_key_struct_t magic_keys[MAGIC_KEYS_COUNT];



void magic_tap_key(magic_key_t keytype) {
    /* magic_execute_key(magic_keys[keytype].function_pointer, magic_keys[keytype].keycodes, NO_KEY); */


    // Determine what to do based on the inncomming parameters
    //
    if (magic_keys[keytype].function_pointer != NULL) { // run function
        // Execute provided function that takes care of the further processing
        magic_keys[keytype].function_pointer(magic_keys[keytype].keycodes);
    } else if (magic_keys[keytype].keycodes != NULL) {  // Tap keycodes
        // Access and print the array elements until the sentinel(0) is encountere
        for (int i = 0; magic_keys[keytype].keycodes[i] != 0; i++) {
            tap_code16(magic_keys[keytype].keycodes[i]);
        }
    }
}




void magic_set(magic_key_t keytype,
               void (*function_pointer)(uint16_t *keycodes_to_process),
               uint16_t *keycodes) {


    // Copying the function to the internal holder, for later use
    magic_keys[keytype].function_pointer = function_pointer;



    // Copying keycodes to the internal keycodes aray, for later use

    // Find the size of the keycodes array
    int size = 0;
    while (keycodes[size] != 0) size++;
    // free memory if it exists
    if (magic_keys[keytype].keycodes != NULL) {
        free(magic_keys[keytype].keycodes);

    }
    // Allocate memory
    magic_keys[keytype].keycodes = calloc(size + 1, sizeof(uint16_t));
    // Do the copying
    for (int i = 0; i < size; i++) {
        magic_keys[keytype].keycodes[i] = keycodes[i];
    }
    magic_keys[keytype].keycodes[size] = 0;

}

