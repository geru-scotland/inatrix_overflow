//
// Created by Geru on 3/5/22.
//

#include "../include/consoleUI.h"
#include "../include/game.h"

void consoleUI_showUI(){
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[10;00H Overflows: %i", playerData.overflowScore);
}

void consoleUI_showOverflow(){
    // ASCII Text, que se active una secuencia y vaya recorriendo la consola
    // que vaya llamando a funciones con el texto desplazado rollo, 1, 2.
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[10;00H OOOOVERFLOOWWW!!!");
}

void consoleUI_showFail(){
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[10;00H FAIL! You shall be lost within the Matrix...");
}