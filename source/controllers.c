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
// TODO: Geru: Quitar event_manager.h y game.h de aqui una vez implementado correctamente.

int seg3;

void controllers_EnableIntMaster(){
    IME = 1;
}

void controllers_DisableIntMaster(){
    IME = 0;
}

void controllers_RutAtencionTeclado ()
{
    if (data.state == CLOSED)
    {
        if (input_KeyPressed()==A)
        {
            data.state = OPEN;
            visualizarPuertaAbierta();
            seg3=0;
            MostrarRombo(1, 5, 5);
            MostrarRomboGrande(2, 100, 100);
        }
    }
}

void controllers_RutAtencionTempo() {
    static int tick = 0;
    static int seg = 0;

    if (data.state != WAIT) {
        tick++;
        if (tick == 5) {
            seg++;
            iprintf("\x1b[13;5HSegundos que han pasado=%d", seg);
            tick = 0;
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

void controllers_ConfigureControlRegisters(){
    /*
     * Registro de Control del Teclado
     * Teclas a detectar por Interrupción
     **/
    TECLAS_CNT = 0x43FD;
}

void controllers_SetInterruptionVector()
{
    irqSet(IRQ_KEYS, input_KeyPadHandler);
}

void controllers_ConfigureInterrupts(){

    /* Controllers */
    controllers_EnableIntMaster();
    controllers_ConfigureControlRegisters();
    controllers_SetInterruptionVector();

    /* Input */
    input_EnableKeyPadInt();
}

