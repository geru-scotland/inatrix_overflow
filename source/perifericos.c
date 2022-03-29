/*-------------------------------------
perifericos.c
-------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include "definiciones.h"


int tecla; //variable para guardar la tecla pulsada



int TeclaDetectada() 
{
	//Devuelve TRUE si detecta que se ha pulsado alguna tecla.
	if ((~TECLAS_DAT & 0x03ff)!=0) return 1;
	else return 0;

}

int TeclaPulsada() 
{

     /*
     * Geru:
     * Cadena de 10 bits (0 a 9) Se apaga el indicador
     * Simplemente he calculado en binario los números
     * y pasado a hexadecimal.
     *
     * De "definiciones.h":
     * A=0;B=1;SELECT=2;START=3;IZQUIERDA=4;DERECHA=5;
     * //ARRIBA=6;ABAJO=7;R=8;L=9;
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
            break;
    }
}

void ConfigurarTeclado(int Conf_Tec)
{
	//Configuración del teclado. Modificar su registro de control en base a los bits
        //activados en el parametro Conf_Tec
	
}

void ConfigurarTemporizador(int Latch, int Conf_Tempo)
{
	//Configuración del temporizador. El latch es el valor del registro de datos del temporizador
        //Activar los bits del registro de control necesarios en base a los bits activados en el parámetro Conf_Tempo

	
}

void HabilitarIntTeclado()
{
	//Habilitar las interrupciones del teclado
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
        //ESCRIBIR AQUÍ VUESTRO CÓDIGO
	
	IME=1;
}

void InhibirIntTeclado()
{

	//Deshabilitar las interrupciones del teclado
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 

	IME=0;
	//ESCRIBIR AQUÍ VUESTRO CÓDIGO

	IME=1;
}  

void HabilitarIntTempo()
{


	//Habilitar las interrupciones del temporizador (timer0)
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
	//ESCRIBIR AQUÍ VUESTRO CÓDIGO
	
	IME=1;
}

void InhibirIntTempo()
{

	//Deshabilitar las interrupciones del temporizado (timer0)
	//Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación, 
	//y después volver a habilitar las interrupciones de forma general 
	IME=0;
	//ESCRIBIR AQUÍ VUESTRO CÓDIGO
	
	IME=1;

}

void PonerEnMarchaTempo()
{
	//ESCRIBIR AQUÍ VUESTRO CÓDIGO
	
}

void PararTempo()
{
	//ESCRIBIR AQUÍ VUESTRO CÓDIGO
	
}
