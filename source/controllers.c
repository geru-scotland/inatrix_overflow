/*-------------------------------------
controllers.cc
-------------------------------------*/

#include "../include/libnds/nds.h"
#include <stdio.h>
#include "../include/defines.h"
#include "../include/input.h"
#include "../include/backgrounds.h"
#include "../include/sprites.h"
#include "../include/eventMgr.h"
#include "../include/game.h"
#include "../include/timer.h"
// TODO: Geru: Quitar event_manager.h y game.h de aqui una vez implementado correctamente.

int seg3;
int seg;
/**
 * INTERRUPTION MASTER
 */
void controllers_EnableIntMaster(){
    IME = 1;
}

void controllers_DisableIntMaster(){
    IME = 0;
}

void controllers_ConfigureTimer(){
    timer_ConfigureTimer(0, 0x0000);
    // Deshabilitado para poder hacer muestra 2Actividad:
    //timer_StartTimer();
}

void controllers_ConfigureInput(){
    /*
     * Geru: el bit número 14 de este registro (TECLAS_CNT), pero aquí parece
     * ser Conf_tec (registro control del teclado), determina si es por
     * interrupción o no. Así que le hago un and con el bitmask 0xB111 (B = 1011)
     * Con lo que apago el bit 14 (tercer bit de B) con esta operación.
    */
    input_ConfigureInput(0x4000 | 0x0001);
}

void controllers_EnableKeyPadInt(){
    IME=0;
    IE |= IRQ_KEYS;
    IME=1;
}

void controllers_DisableKeyInt(){
    IME=0;
    IE &= ~IRQ_KEYS;
    IME=1;
}

/**
 * HANDLERS
 */


void controllers_TimerHandler(){
    // El handler será llamado por interrupción constantemente
    timer_UpdateTimer();
}

void controllers_KeyPadHandler(){
    // TODO: Geru: Hacer esto bien con el nuevo gestor de eventos.
    /**
     *
     * Esto se llama cada vez que una tecla sea pulsada POR INTERRUPCIÓN.
     * Con lo que, el pulsar una tecla lo activaría.
     *
     * Tendría que llamar a la función de la actividad 2, de abrir la puerta
     * tras varios segundos etc.
     *
     * Como estamos implementando un gestor de eventos, aquí habría que programar
     * o schedulear dicho evento, lo cual agregará a una cola y ejecutará
     * cuando corresponda (tiempo actual + tiempo del evento).
     */

    // Mostrar por pantalla la tecla que ha sido pulsada
    // Tanto por interrupción como por encuesta.
}

void controllers_SetInterruptionVector()
{
    irqSet(IRQ_KEYS, controllers_KeyPadHandler);
    irqSet(IRQ_TIMER0, controllers_TimerHandler);
}


void controllers_InitSetup(){
    controllers_EnableIntMaster();
    controllers_EnableKeyPadInt();
    controllers_ConfigureTimer();
    controllers_ConfigureInput();
    controllers_SetInterruptionVector();
}

