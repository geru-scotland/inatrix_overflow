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
    timer_ConfigureTimer(0, 0x00C0);
    // Quitado para poder hacer muestra 2Actividad.
    //timer_StartTimer();
}

void controllers_ConfigureInput(){
    /*
     * Geru: el bit número 14 de este registro (TECLAS_CNT), pero aquí parece
     * ser Conf_tec (registro control del teclado), determina si es por
     * interrupción o no. Así que le hago un and con el bitmask 0xB111 (B = 1011)
     * Con lo que apago el bit 14 (tercer bit de B) con esta operación.
    */

    //TODO: Pasar esto a input.
    TECLAS_CNT |= 0x4000 | 0x0001;
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
    iprintf("\x1b[10;00H TECLA POR INTERRUPCION ");
    if (data.state != WAIT) {
        if (timer.ticks == 5) {
            seg++;
            iprintf("\x1b[13;5HSegundos que han pasado=%d", seg);
            timer.ticks = 0;
            if (data.state == OPEN) {
                seg3++;
                if (seg3 == 3) {
                    visualizarPuerta();
                    seg3 = 0;
                    data.state = CLOSED;
                    BorrarRombo(1, 5, 5);
                    BorrarRomboGrande(2, 100, 100);
                }
            }
        }
    }
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

