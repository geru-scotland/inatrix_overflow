//
// Created by Geru on 3/5/22.
//

#include "../include/consoleUI.h"
#include "../include/game.h"

void consoleUI_showIntro1(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H     _                       ");
    iprintf("\x1b[8;00H    Inatrix, Lord of        ");
    iprintf("\x1b[9;00H                            ");
    iprintf("\x1b[10;00H     the Overflow enters   ");
    iprintf("\x1b[11;00H                            ");
    iprintf("\x1b[12;00H     the system!            ");
    iprintf("\x1b[13;00H                            ");
    iprintf("\x1b[13;00H                            ");
    iprintf("\x1b[14;00H ___________________________");
}

void consoleUI_showIntro2(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           ");
    iprintf("\x1b[8;00H |                           ");
    iprintf("\x1b[9;00H |     START OVERFLOWING!!   ");
    iprintf("\x1b[10;00H |                          ");
    iprintf("\x1b[11;00H |                           ");
    iprintf("\x1b[12;00H |                           ");
    iprintf("\x1b[13;00H |                           ");
    iprintf("\x1b[13;00H |                           ");
    iprintf("\x1b[14;00H |___________________________");
}

void consoleUI_showUI(){
    char nm[] = "Normal";
    char hm[] = "Hard";

    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           ");
    iprintf("\x1b[8;00H | Overflows        %i       ", playerData.overflowScore);
    iprintf("\x1b[9;00H |                           ");
    iprintf("\x1b[10;00H | Mode             %s       ", gameData.mode == DIFFICULTY_NORMAL_MODE ? nm : hm);
    iprintf("\x1b[11;00H |                           ");
    iprintf("\x1b[12;00H | Matrix regens    %i       ", gameData.matrixRegens);
    iprintf("\x1b[13;00H |                           ");
    iprintf("\x1b[14;00H | Destroy time:    %i       ", gameData.destroyMatrixTime);
    iprintf("\x1b[15;00H |___________________________");
}

void consoleUI_showGameOver(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           |");
    iprintf("\x1b[8;00H |      _                    |");
    iprintf("\x1b[9;00H | May Inatrix be with you.  |");
    iprintf("\x1b[10;00H |                          |");
    iprintf("\x1b[11;00H |                           |");
    iprintf("\x1b[12;00H |                           |");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[14;00H |___________________________|");
}

void consoleUI_showOverflow(){
    // ASCII Text, que se active una secuencia y vaya recorriendo la consola
    // que vaya llamando a funciones con el texto desplazado rollo, 1, 2.
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[12;00H .----.-..-.---..---. ");
    iprintf("\x1b[13;00H | || |\\ /| |- | |-< ");
    iprintf("\x1b[14;00H `----' `' `---'`-'`-'");

    iprintf("\x1b[15;00H .---- .-.   .----..-.-.-.");
    iprintf("\x1b[16;00H | |-- | |__ | || || | | |");
    iprintf("\x1b[17;00H `-'   `----'`----'`-----'");

}

void consoleUI_showFail(){
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[10;00H 'Me he columpiao!'");
    iprintf("\x1b[13;00H -Inatrix, Lord of the");
    iprintf("\x1b[15;00H  Overlflow ");

}