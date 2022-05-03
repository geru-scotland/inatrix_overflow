//
// Created by Geru on 3/5/22.
//

#include "../include/consoleUI.h"
#include "../include/game.h"

void consoleUI_showUI(){
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           |");
    iprintf("\x1b[8;00H | Overflows        %i        |", playerData.overflowScore);
    iprintf("\x1b[9;00H |                           |");
    iprintf("\x1b[10;00H | Mode             Hard     |");
    iprintf("\x1b[11;00H |                           |");
    iprintf("\x1b[12;00H | Matrix regens    5        |");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[13;00H | Destroy time:    %i         |", gameData.destroyMatrixTime);
    iprintf("\x1b[14;00H |___________________________|");
}

void consoleUI_showOverflow(){
    // ASCII Text, que se active una secuencia y vaya recorriendo la consola
    // que vaya llamando a funciones con el texto desplazado rollo, 1, 2.
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[12;00H .----.-..-.---..---. ");
    iprintf("\x1b[13;00H | || |\\ /| |- | |-< ");
    iprintf("\x1b[14;00H `----' `' `---'`-'`-'");

    iprintf("\x1b[15;00H .---.-.   .----..-.-.-.");
    iprintf("\x1b[16;00H | |-| |__ | || || | | |");
    iprintf("\x1b[17;00H `-' `----'`----'`-----'");

}

void consoleUI_showFail(){
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[10;00H FAIL! You shall be lost within the Matrix...");
}