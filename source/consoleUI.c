/*
 * This file is part of the Iñatrix Overflow Project.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *  Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file consoleUI.c
 * @brief Fichero en el que se definen las funciones encargadas
 * de mostrar en la pantalla de arriba el texto oportuno.
 * Emulando una "User Interface" con simplemente texto y
 * símbolos. De ahora en adelante se les llamará Menús
 * o UI.
 *
 * Ésta manera no es que esté muy bien, pero durante el desarrollo
 * he encontrado varios bugs con la gestión de libnds y su consola,
 * así que he decidido el hacerlo de manera simple y, bastante troglodita.
 *
 */

#include "consoleUI.h"
#include "game.h"
#include "matrix.h"
#include "time.h"

/**
 * @brief UI del menú principal, dando la posibilidad de que el
 * usuario presione una tecla para ejecutar una acción.
 */
void consoleUI_showMenu(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |***************************|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           |");
    iprintf("\x1b[8;00H |                           |");
    iprintf("\x1b[9;00H |  <PRESS START TO BEGIN>   |");
    iprintf("\x1b[10;00H |                           |");
    iprintf("\x1b[11;00H |                           |");
    iprintf("\x1b[12;00H |___________________________|");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[14;00H |                           |");
    iprintf("\x1b[15;00H |                           |");
    iprintf("\x1b[16;00H |          <Lore>           |");
    iprintf("\x1b[17;00H |                           |");
    iprintf("\x1b[18;00H | <Gameplay>    <Controls>  |");
    iprintf("\x1b[19;00H |                           |");
    iprintf("\x1b[20;00H |___________________________|");
}

/**
 * @brief Menú que se mostrará en el proceso de comienzo de juego.
 * Con objeto de dar un poco más de dinamicidad.
 */
void consoleUI_showIntro1(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H                            ");
    iprintf("\x1b[8;00H                            ");
    iprintf("\x1b[9;00H                            ");
    iprintf("\x1b[10;00H     _                       ");
    iprintf("\x1b[11;00H    Inatrix, Lord of        ");
    iprintf("\x1b[12;00H                            ");
    iprintf("\x1b[13;00H     the Overflow enters   ");
    iprintf("\x1b[14;00H                            ");
    iprintf("\x1b[15;00H     the system!            ");
    iprintf("\x1b[16;00H                            ");
    iprintf("\x1b[17;00H                            ");
    iprintf("\x1b[18;00H ___________________________");
}

/**
 * @brief Menú cada vez que haya Overflow.
 */
void consoleUI_showIntro2(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           |");
    iprintf("\x1b[8;00H |                           |");
    iprintf("\x1b[9;00H |                           |");
    iprintf("\x1b[10;00H |                           |");
    iprintf("\x1b[11;00H |                           |");
    iprintf("\x1b[12;00H |    START OVERFLOWING!!    |");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[14;00H |                           |");
    iprintf("\x1b[15;00H |                           |");
    iprintf("\x1b[16;00H |                           |");
    iprintf("\x1b[17;00H |                           |");
    iprintf("\x1b[18;00H |___________________________|");
}

/**
 * @brief Menú UI que aparece durante el juego mostrando datos y estádisticas
 * a tiempo real.
 */
void consoleUI_showUI(){
    char nm[] = "Normal";
    char hm[] = "Hard";

    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H                            ");
    iprintf("\x1b[8;00H           ---------         ");
    iprintf("\x1b[9;00H          |OVERFLOWS|        ");
    iprintf("\x1b[10;00H           ---------         ");
    iprintf("\x1b[11;00H                            ");
    iprintf("\x1b[12;00H  Total: %i  ||  Current: %i  ", playerData.overflowScore, playerData.runOverflows);
    iprintf("\x1b[13;00H                            ");
    iprintf("\x1b[14;00H                            ");
    iprintf("\x1b[15;00H  Mode: %s (Ovf@ %i)       ", gameData.mode == DIFFICULTY_NORMAL_MODE ? nm : hm, gameData.mode == DIFFICULTY_HARD_MODE ? OVERFLOW_HM : OVERFLOW_NM);
    iprintf("\x1b[16;00H                            ");
    iprintf("\x1b[17;00H                            ");
    iprintf("\x1b[18;00H  Matrix regenerations:  %i  ", gameData.matrixRegens);
    iprintf("\x1b[19;00H                            ");
    iprintf("\x1b[20;00H  Destroy time:    %i       ", gameData.destroyMatrixTime);
    iprintf("\x1b[21;00H ___________________________");
}

/**
 * @brief Menú para el Game Over
 */

void consoleUI_showGameOver(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******** GAME OVER ********|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           |");
    iprintf("\x1b[8;00H |                           |");
    iprintf("\x1b[9;00H |                           |");
    iprintf("\x1b[10;00H |                           |");
    iprintf("\x1b[11;00H |      _                    |");
    iprintf("\x1b[12;00H | May Inatrix be with you.  |");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[14;00H |                           |");
    iprintf("\x1b[15;00H |                           |");
    iprintf("\x1b[16;00H |                           |");
    iprintf("\x1b[17;00H |                           |");
    iprintf("\x1b[18;00H |___________________________|");
}

/**
 * Menú para el Overflow.
 */
void consoleUI_showOverflow(){
    // ASCII Text, que se active una secuencia y vaya recorriendo la consola
    // que vaya llamando a funciones con el texto desplazado rollo, 1, 2.
    iprintf("\x1b[2J"); // Forzamos un clear console
    iprintf("\x1b[12;00H .----.-..-.---..---- ");
    iprintf("\x1b[13;00H | || |\\ /| |-- | |-< ");
    iprintf("\x1b[14;00H `----' `' `---'`-'`-");

    iprintf("\x1b[15;00H .---- .-.   .----..-.-.-.");
    iprintf("\x1b[16;00H | |-| | |__ | || || | | |");
    iprintf("\x1b[17;00H `-'   `----'`----'`-----'");

}

/**
 * @brief Menú UI para la fase de regeneración de la matriz.
 */
void consoleUI_showRegeneratingMatrix(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           |");
    iprintf("\x1b[8;00H |                           |");
    iprintf("\x1b[9;00H |  THE MATRIX IS            |");
    iprintf("\x1b[10;00H |                           |");
    iprintf("\x1b[11;00H |   REGENERATING ITSELF!    |");
    iprintf("\x1b[12;00H |                           |");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[14;00H |                           |");
    iprintf("\x1b[15;00H |___________________________|");
}

/**
 * @brief Menú que mostrará una frase de Iñaki aleatoria cada vez
 * que se falle.
 */
void consoleUI_showFail(){
    char f1[] = "\x1b[10;00H 'Me he columpiao!'";
    char f2[] = "\x1b[10;00H 'Socorroooo!'";

    srand(time(0));
    iprintf("\x1b[2J");
    iprintf(rand() % 2 == 0 ? f1 : f2);
    iprintf("\x1b[13;00H -Inatrix, Lord of the");
    iprintf("\x1b[15;00H  Overflow ");
}

/**
 * @brief Menú UI para la muestra de estadísticas al final de la partida.
 */
void consoleUI_showStats(){
    char nm[] = "Normal";
    char hm[] = "Hard";

    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |***** GENERAL STATS *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H                            ");
    iprintf("\x1b[8;00H  Overflows:        %i  ", playerData.totalOverflows);
    iprintf("\x1b[9;00H                            ");
    iprintf("\x1b[10;00H  Mode:  %s    ", gameData.mode == DIFFICULTY_NORMAL_MODE ? nm : hm);
    iprintf("\x1b[11;00H                            ");
    iprintf("\x1b[12;00H  Matrix regenerations: %i", gameData.matrixRegens);
    iprintf("\x1b[13;00H                            ");
    iprintf("\x1b[14;00H  Fails: %i  ", playerData.failScore);
    iprintf("\x1b[15;00H                            ");
    iprintf("\x1b[16;00H   <PRESS ANY KEY TO QUIT>  ");
    iprintf("\x1b[17;00H ___________________________");
}

/**
 * @brief Menú UI para el pause.
 */
void consoleUI_showPauseUI(){
        iprintf("\x1b[2J");
        iprintf("\x1b[4;00H |***************************|");
        iprintf("\x1b[5;00H |******* The Matrix  *******|");
        iprintf("\x1b[6;00H |***************************|");
        iprintf("\x1b[7;00H |                           |");
        iprintf("\x1b[8;00H |                           |");
        iprintf("\x1b[9;00H |                           |");
        iprintf("\x1b[10;00H |          <PAUSE>          |");
        iprintf("\x1b[11;00H |                           |");
        iprintf("\x1b[12;00H |                           |");
        iprintf("\x1b[13;00H |                           |");
        iprintf("\x1b[14;00H |                           |");
        iprintf("\x1b[15;00H |___________________________|");
}

/**
 * @brief Menú de interrupción/interferencia.
 */
void consoleUI_showSurrenderUI(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******* The Matrix  *******|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           |");
    iprintf("\x1b[8;00H |                           |");
    iprintf("\x1b[9;00H | Something is interfering  |");
    iprintf("\x1b[10;00H |                           |");
    iprintf("\x1b[11;00H |   with the Matrix,        |");
    iprintf("\x1b[12;00H |                           |");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[14;00H |        YOU DIED.          |");
    iprintf("\x1b[15;00H |                           |");
    iprintf("\x1b[16;00H |___________________________|");
}

/**
 * @brief Menú de controles
 */
void consoleUI_showControls(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******** CONTROLS *********|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H |                           |");
    iprintf("\x1b[8;00H |           <UP>            |");
    iprintf("\x1b[9;00H |                           |");
    iprintf("\x1b[10;00H |     <LEFT>    <RIGHT>     |");
    iprintf("\x1b[11;00H |                           |");
    iprintf("\x1b[12;00H |          <DOWN>           |");
    iprintf("\x1b[13;00H |                           |");
    iprintf("\x1b[14;00H |                           |");
    iprintf("\x1b[15;00H |  <A> - Select BitBlock    |");
    iprintf("\x1b[16;00H |                           |");
    iprintf("\x1b[17;00H |  <START> Pause            |");
    iprintf("\x1b[18;00H |                           |");
    iprintf("\x1b[19;00H |  <SELECT><B> Surrender    |");
    iprintf("\x1b[20;00H |                           |");
    iprintf("\x1b[21;00H |***************************|");
    iprintf("\x1b[22;00H                             ");
}

/**
 * @brief Menú de Gameplay
 */
void consoleUI_showGameplay(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |******** GAMEPLAY *********|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H                            ");
    iprintf("\x1b[8;00H 1) Move both characters.  ");
    iprintf("\x1b[9;00H                            ");
    iprintf("\x1b[10;00H 2) Select a bit from the Matrix.");
    iprintf("\x1b[11;00H                            ");
    iprintf("\x1b[12;00H 3) The three horizontal ");
    iprintf("\x1b[13;00H  lines will be considered ");
    iprintf("\x1b[14;00H  as 3 separated binary  ");
    iprintf("\x1b[15;00H  numbers (bitBlock)");
    iprintf("\x1b[16;00H                            ");
    iprintf("\x1b[17;00H 4) If the addition of the");
    iprintf("\x1b[18;00H  3 numbers generates an ");
    iprintf("\x1b[19;00H  overflow: +1 point.");
    iprintf("\x1b[20;00H                             ");
    iprintf("\x1b[21;00H 5) 1 Overflow per Matrix ");
    iprintf("\x1b[22;00H  regeneration is needed. ");
}

/**
 * @brief Menú de Lore
 *
 * Inatrix is the one and he  structure of our reality.
 * Due to his unprecedented powers of identifying overflows within the Matrix structure,
 * he is able to stabilize our world. This Universe is in constant decay and the only way to keep
 * it out of a fatal system failure is by eliminating the erroneous bits that infect the structure from its root.
 */
void consoleUI_showLore(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |********** LORE ***********|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H                              ");
    iprintf("\x1b[8;00H Inatrix is the one and he    ");
    iprintf("\x1b[9;00H thoroughly analyzes the      ");
    iprintf("\x1b[10;00H structure of our reality.   ");
    iprintf("\x1b[11;00H Due to his unprecedent powers");
    iprintf("\x1b[12;00H of identifying overflows     ");
    iprintf("\x1b[13;00H within the Matrix structure");
    iprintf("\x1b[14;00H he is able to stabilize our");
    iprintf("\x1b[15;00H world. This Universe is in ");
    iprintf("\x1b[16;00H constant decay and the only");
    iprintf("\x1b[17;00H way to keep it out of a fatal");
    iprintf("\x1b[18;00H system failure is by ");
    iprintf("\x1b[19;00H eliminating the erroneous bits");
    iprintf("\x1b[20;00H that infect the Matrix from ");
    iprintf("\x1b[21;00H its root.");
}

/**
 * @brief Menú de Lore 2
 */
void consoleUI_showLore2(){
    iprintf("\x1b[2J");
    iprintf("\x1b[4;00H |***************************|");
    iprintf("\x1b[5;00H |********** LORE ***********|");
    iprintf("\x1b[6;00H |***************************|");
    iprintf("\x1b[7;00H                            ");
    iprintf("\x1b[8;00H  The lord of the Overflows ");
    iprintf("\x1b[9;00H   is our only choice.");
    iprintf("\x1b[10;00H                            ");
    iprintf("\x1b[11;00H       _                     ");
    iprintf("\x1b[12;00H  May Inatrix be with you.  ");
    iprintf("\x1b[13;00H                            ");
    iprintf("\x1b[14;00H                            ");
    iprintf("\x1b[15;00H                            ");
    iprintf("\x1b[16;00H                            ");
    iprintf("\x1b[17;00H     -Archive XXIV,12,052 GE");
    iprintf("\x1b[18;00H                            ");
    iprintf("\x1b[19;00H      Encyclopedia Galactica,");
    iprintf("\x1b[20;00H      Galactic Library.");
    iprintf("\x1b[21;00H                             ");
    iprintf("\x1b[22;00H                             ");
}