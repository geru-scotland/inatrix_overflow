/*-------------------------------------
        Keyboard and Screen
-------------------------------------*/

#include "../include/libnds/nds.h"
#include <stdio.h>
#include "../include/input.h"
#include "../include/defines.h"

KeyData keyData;

void input_UpdateKeyData(){
    keyData.isPressed = input_KeyDetected();

    if(keyData.isPressed)
        keyData.key = input_KeyPressed();
    else
        keyData.key = NULL;
}

int input_KeyDetected()
{
	//Devuelve TRUE si detecta que se ha pulsado alguna tecla.
	if ((~TECLAS_DAT & 0x03ff)!=0) return 1;
	else return 0;
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
            return A;
        case 0x03FD:
            return B;
        case 0x03FB:
            return SELECT;
        case 0x03F7:
            return START;
        case 0X03EF:
            return IZQUIERDA;
        case 0x03DF:
            return DERECHA;
        case 0X03BF:
            return ARRIBA;
        case 0x037F:
            return ABAJO;
        case 0x02FF:
            return R;
        case 0x01FF:
            return L;
        default:
            return -1;
    }
}

void input_ConfigureKeyPad(int Conf_Tec)
{
        /*
         * Geru: el bit número 14 de este registro (TECLAS_CNT), pero aquí parece
         * ser Conf_tec (registro control del teclado), determina si es por
         * interrupción o no. Así que le hago un and con el bitmask 0xB111 (B = 1011)
         * Con lo que apago el bit 14 (tercer bit de B) con esta operación.
        */
        //Conf_Tec &= 0xB111;
}

void input_EnableKeyPadInt()
{
	IME=0;
    IE = IE | 0x1008;
	IME=1;
}

void input_DisableKeyPadInt()
{
	IME=0;
	//ESCRIBIR AQUÍ VUESTRO CÓDIGO
	IME=1;
}  

void input_KeyPadHandler(){
    // Teclas por interrupción, triguean esto.
}