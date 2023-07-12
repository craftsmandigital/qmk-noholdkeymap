/* Copyright 2023 Jon Arne Viksås (@craftsmandigital)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once


#define U_NP KC_NO // key is not present
#define U_NA KC_NO // present but not available for use
#define U_NU KC_NO // available but not used

#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

#define UU_CUT SS_LCTL("x")
#define UU_PST SS_LCTL("v")
#define UU_CPY SS_LCTL("c")

#define UU_WORDL SS_LCTL(SS_TAP(X_LEFT))
#define UU_WORDR SS_LCTL(SS_TAP(X_RIGHT))

#define UU_GRAPH_UP SS_LCTL(SS_TAP(X_UP))
#define UU_GRAPH_DN SS_LCTL(SS_TAP(X_DOWN))

#define UU_SEL_ALL SS_LCTL("a")
#define UU_SEL_LINE SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_DOWN))
#define UU_SEL_WORDR SS_LSFT(UU_WORDR)
#define UU_SEL_WORDL SS_LSFT(UU_WORDL)
#define UU_SEL_GRAPH_UP SS_LSFT(UU_GRAPH_UP)
#define UU_SEL_GRAPH_DN SS_LSFT(UU_GRAPH_DN)