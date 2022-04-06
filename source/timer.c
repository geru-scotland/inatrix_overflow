//
// Created by Geru on 31/3/22.
//

#include "../include/timer.h"
#include "../include/defines.h"

TimerData timer;

void timer_UpdateTimer(){
}

void timer_ConfigureTimer(int Latch, int Conf_Tempo)
{
    //Configuración del temporizador. El latch es el valor del registro de datos del temporizador
    //Activar los bits del registro de control necesarios en base a los bits activados en el parámetro Conf_Tempo
}

void timer_HabilitarIntTempo()
{
    //Habilitar las interrupciones del temporizador (timer0)
    //Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación,
    //y después volver a habilitar las interrupciones de forma general
    IME=0;
    //ESCRIBIR AQUÍ VUESTRO CÓDIGO

    IME=1;
}

void timer_InhibirIntTempo()
{

    //Deshabilitar las interrupciones del temporizado (timer0)
    //Para realizar esa operación, primero deshabilitar todas las interrupciones de forma general, realizar la operación,
    //y después volver a habilitar las interrupciones de forma general
    IME=0;
    //ESCRIBIR AQUÍ VUESTRO CÓDIGO

    IME=1;
}

void timer_PonerEnMarchaTempo()
{
    //ESCRIBIR AQUÍ VUESTRO CÓDIGO

}

void timer_PararTempo()
{
    //ESCRIBIR AQUÍ VUESTRO CÓDIGO

}
