/*
 * This file is part of the Iñatrix Overflow Project.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file input.h
 */
#ifndef INPUT_H
#define INPUT_H
#include "nds.h"
#include <stdbool.h>
//registros del teclado
#define TECLAS_DAT	(*(vu16*)0x4000130) //registro de datos
#define TECLAS_CNT	(*(vu16*)0x4000132) //registro de control

enum KEYS {
    INPUT_KEY_A       = 0,
    INPUT_KEY_B		  = 1,
    INPUT_KEY_SELECT  = 2,
    INPUT_KEY_START	  = 3,
    INPUT_KEY_RIGHT   = 4,
    INPUT_KEY_LEFT    = 5,
    INPUT_KEY_UP      = 6,
    INPUT_KEY_DOWN    = 7,
    INPUT_KEY_R       = 8,
    INPUT_KEY_L       = 9
};

typedef struct {
    bool isPressed;
    int key;
} KeyData;

extern KeyData keyData;

// TODO: Poner extern solo las que realmente vayan a ser linkadas
// En otros archivos, no en el c

extern void input_ConfigureInput(int mask);
extern void input_UpdateKeyData();
extern int input_KeyDetected();
extern int input_KeyPressed();

extern bool input_touchScreenUsed();
extern int input_getTouchScreenX();
extern int input_getTouchScreenY();

extern touchPosition screen;
#endif // INPUT_H
