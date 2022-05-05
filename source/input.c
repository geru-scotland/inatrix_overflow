/*-------------------------------------
        Keyboard and Screen
-------------------------------------*/

#include "nds.h"
#include <stdio.h>
#include "input.h"
#include "defines.h"

KeyData keyData;
touchPosition screen;

void input_ConfigureInput(int mask)
{
    TECLAS_CNT |= mask;
}

void input_UpdateKeyData()
{
    keyData.isPressed = input_KeyDetected();

    if(keyData.isPressed)
        keyData.key = input_KeyPressed();
    else
        keyData.key = -1;
}

int input_KeyDetected()
{
	//Devuelve TRUE si detecta que se ha pulsado alguna tecla.
    return (~TECLAS_DAT & 0x03ff)!=0 ? 1 : 0;
}

int input_KeyPressed()
{
     /*
     * Geru:
     * Cadena de 10 bits (0 a 9) Se apaga el indicador
     * Simplemente he calculado en binario los números
     * y pasado a hexadecimal.
     *
     * E.g. Otra opción de implementación sería:
     * if(~TECLAS_DAT & 0x0001) { return A; }
     *
     * De "defines.h":
     * A=0;B=1;SELECT=2;START=3;IZQUIERDA=4;DERECHA=5;
     * ARRIBA=6;ABAJO=7;R=8;L=9;
     */

    /*
     * Los registros de las teclas X e Y, al igual que los de la pantalla táctil, sólo son accesibles
     * desde el procesador ARM7, por esa razón y puesto que en este caso tenemos disponibles
     * el resto de las teclas, estas no las vamos a utilizar.
     */
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

bool input_touchScreenUsed() {
    touchRead(&screen);
    return (screen.px != 0 && screen.py != 0);
}

int input_getTouchScreenX() {
    touchRead(&screen);
    return screen.px;
}

int input_getTouchScreenY() {
    touchRead(&screen);
    return screen.py;
}