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
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */


/**
 * @author Geru-Scotland.
 * @file input.c
 * @brief Gestión y configuración de los registros correspondientes al
 * sistema de entrada y salida de la NDS.
 */

#include "nds.h"
#include <stdio.h>
#include "input.h"
#include "defines.h"

KeyData keyData;
touchPosition screen;

/**
 * @brief Agrega la máscara al registro de control TECLAS_CNT.
 * @param mask Bitmask utilizado para configurar TECLAS_DAT.
 */
void input_ConfigureInput(int mask)
{
    TECLAS_CNT |= mask;
}

/**
 * @brief Función encargada de actualizar el @struct KeyData con la información
 * extraída de los registros apropidos.
 * @return Devuelve 1 si detecta que se ha pulsado alguna tecla, -1 en caso contrario.
 */
void input_UpdateKeyData()
{
    keyData.isPressed = input_KeyDetected();

    if(keyData.isPressed)
        keyData.key = input_KeyPressed();
    else
        keyData.key = -1;
}

/**
 * @brief Control de pulsación de teclas.
 * @return Devuelve TRUE si detecta que se ha pulsado alguna tecla.
 */
int input_KeyDetected()
{
    return (~TECLAS_DAT & 0x03FF) != 0 ? 1 : 0;
}

/**
 * @brief Función para detectar qué tecla ha sido pulsada.
 * @note Los registros de las teclas X e Y, al igual que los de la pantalla táctil, sólo son accesibles
 * desde el procesador ARM7, por esa razón y puesto que en este caso tenemos disponibles
 * el resto de las teclas, estas no las vamos a utilizar.
 * @return Identificador de la tecla asociada correspondiente.
 */
int input_KeyPressed()
{

    switch(TECLAS_DAT){
        case 0x03FE:
            return INPUT_KEY_A;
        case 0x03FD:
            return INPUT_KEY_B;
        case 0x03FB:
            return INPUT_KEY_SELECT;
        case 0x03F7:
            return INPUT_KEY_START;
        case 0X03EF:
            return INPUT_KEY_RIGHT;
        case 0x03DF:
            return INPUT_KEY_LEFT;
        case 0X03BF:
            return INPUT_KEY_UP;
        case 0x037F:
            return INPUT_KEY_DOWN;
        case 0x02FF:
            return INPUT_KEY_R;
        case 0x01FF:
            return INPUT_KEY_L;
        default:
            return -1;
    }
}

/**
 * @brief Detecta si se ha utilizado la pantalla táctil (click izquierdo del ratón
 * en el emulador).
 * @return true si ha sido pulsada, false en caso contrario.
 */
bool input_touchScreenUsed() {
    touchRead(&screen);
    return (screen.px != 0 && screen.py != 0);
}

/**
 * @brief Consulta la posición x del punto donde ha sido presionada la pantalla táctil.
 * @return Entero que indica la posición en el eje X.
 */
int input_getTouchScreenX() {
    touchRead(&screen);
    return screen.px;
}

/**
 * @brief Consulta la posición y del punto donde ha sido presionada la pantalla táctil.
 * @return Entero que indica la posición en el eje y.
 */
int input_getTouchScreenY() {
    touchRead(&screen);
    return screen.py;
}