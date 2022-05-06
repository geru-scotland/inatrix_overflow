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
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file matrix.c
 * @brief Gestión completa de los sistemas core matriciales del proyecto.
 */

#include "matrix.h"
#include "gfxInfo.h"
#include "eventMgr.h"
#include "game.h"
#include <math.h>
#include <time.h>

/**
 * @var matrix[MATRIX_SIZE][MATRIX_SIZE]: Matriz principal, array bidimensional 10x10
 * que contiene punteros a structs del tipo @struct MatrixElement.
 * @var bitBlockBuffer[BITBLOCK_SIZE][BITBLOCK_SIZE] Matriz que hace de buffer para servir de ayuda
 * cuando el jugador elimina un bloque de bits.
 * @var pivot: elemento que hará de centro del bloque de bits.
 */
MatrixElement* matrix[MATRIX_SIZE][MATRIX_SIZE];
MatrixElement* bitBlockBuffer[BITBLOCK_SIZE][BITBLOCK_SIZE];
MatrixPivot* pivot; // Quizá hacer un pivotLocked para entre eventos, evitar updates.
bool isMatrixHidden = true;
bool isBufferHidden = true;

/**
 * @var baseMatrix[MATRIX_SIZE][MATRIX_SIZE]: Hace matriz base. Realmente la matriz que se gestionará
 * en el juego es una matriz que contiene direcciones de memoria de structs @struct MatrixElement.
 * Ésta únicamente hace de plantilla para que el sistema de creación y reserva de sprites en
 * memoria, sepa qué GFX generar y asociar a cada posición, de manera inicial.
 */
Binary baseMatrix[MATRIX_SIZE][MATRIX_SIZE] = {

        { 0, 0, 1, 0, 0, 1, 0, 0, 1, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 0, 0 },
        { 0, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 0, 0 },
        { 0, 1, 1, 0, 0, 1, 1, 0, 0, 0 },
        { 1, 0, 1, 1, 1, 0, 1, 1, 0, 1 },
        { 1, 1, 1, 1, 1, 0, 0, 0, 1, 0 },
        { 0, 0, 1, 0, 0, 1, 1, 1, 0, 1 },
        { 1, 0, 1, 1, 1, 0, 1, 0, 1, 0 }

};

/**
 * @var baseBitBlockBuffer: Mismo caso que la baseMatrix, pero únicamente en lo relativo
 * a los bloques de bits.
 */
Binary baseBitBlockBuffer[BITBLOCK_SIZE][BITBLOCK_SIZE] = {

        { 1, 0, 1 },
        { 0, 1, 0 },
        { 0, 1, 0 }

};

/**
 * @brief Función inicializadora del sistema de matrices. Reserva memoria, escribe bitmaps en el banco
 * de memoria de la NDS (main) en función de las matrices base.
 */
void matrix_initSystem(){
    gfxInfo_initMatrix(baseMatrix[0], MATRIX_SIZE);
    gfxInfo_initMatrix(baseBitBlockBuffer[0], BITBLOCK_SIZE);
    pivot = malloc(sizeof(MatrixPivot));
}

/**
 * Función auxiliar para mostrar/ocultar los sprites de la matriz
 * @param display
 */
void matrix_displayMatrix(bool display){
    matrix_hideMatrix(!display);
}

/**
 * @brief Función auxiliar para mostrar/ocultar los sprites del buffer del bloque de bits.
 * @param display
 */
void matrix_displayBitBlockBuffer(bool display){
    matrix_hideBitBlockBuffer(!display);
}

/**
 * @brief Función auxiliar para mostrar/ocultar matrices.
 * @param hide
 */
void matrix_hideMatrix(bool hide){

    if(hide)
        isMatrixHidden = true;
    else
        isMatrixHidden = false;

    for(int i = 0; i < MATRIX_SIZE; i++)
        for (int j = 0; j < MATRIX_SIZE; j++)
            sprites_displaySprite(matrix[i][j]->sprite->index,
                                  MATRIX_X_POS + (j * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + (i * MATRIX_Y_PADDING),
                                  hide);
}

/**
 * @brief Función auxiliar para mostrar/ocultar bitblockbuffers.
 * @param hide
 */
void matrix_hideBitBlockBuffer(bool hide){

    if(hide)
        isBufferHidden = true;
    else
        isBufferHidden = false;

    for(int i = 0; i < BITBLOCK_SIZE; i++)
        for (int j = 0; j < BITBLOCK_SIZE; j++)
            sprites_displaySprite(bitBlockBuffer[i][j]->sprite->index,
                                  MATRIX_X_POS + (j * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + (i * MATRIX_Y_PADDING),
                                  hide);
}


/*
*********************
*********************
***** EFFECTS *******
*********************
*********************
*/

/**
 * @brief Función que será llamada en la frecuencia determinada por el eventMgr con objeto
 * de mostrar la animación de la matriz entera cayendo.
 * @return TRUE si todos los elementos de la matriz (@struct MatrixElement) están fuera de la pantalla
 * y FALSE en caso contrario.
 */
bool matrix_destroyMatrixEffect(){

    for(int i = 0; i < MATRIX_SIZE; i++)
        for(int j = 0; j < MATRIX_SIZE; j++)
            if((matrix[i][j]->sprite != NULL)
            && (matrix[i][j]->sprite->spriteEntry->y <= WINDOW_HEIGHT))
                matrix[i][j]->sprite->spriteEntry->y +=2;

    return matrix[MATRIX_FIRST][MATRIX_FIRST]->sprite->spriteEntry->y <= WINDOW_HEIGHT;
}

/**
 * @todo: Hacer esto con puntero a función y reducir código
 * @brief Función que será llamada en la frecuencia determinada por el eventMgr con objeto
 * de mostrar la animación del bloque de bits cayendo.
 * @return TRUE si todos los elementos del bitblock (@struct MatrixElement) están fuera de la pantalla
 * y FALSE en caso contrario.
 */
bool matrix_dropBitBlockEffect(){
    int out = 0;
    for(int i = -1; i <= 1; i++)
        for(int j = -1; j <= 1; j++)
            if(matrix[pivot->i + i][pivot->j + j]->sprite->spriteEntry->y >= WINDOW_HEIGHT)
                out++;
            else
                matrix[pivot->i + i][pivot->j + j]->sprite->spriteEntry->y +=2;
    return out != MATRIX_BLOCK;
}

/**
 * @brief Función pendiente si tengo tiempo. Animación especial  para la regeneración del bloque de bits
 * @return
 */
bool matrix_bitConjuctionEffect(){

    return true;
}

/**
 * @brief Animación intermitente en el eje X para que el jugador pueda observar el bit o elemento pivote de la matriz
 * que ha seleccionado de manera pasiva al desplazar a los dos Iñatrix.
 * @param state
 */
void matrix_bitShakeEffect(int8 state){
    matrix[pivot->i][pivot->j]->sprite->spriteEntry->x = (MATRIX_X_POS + (pivot->j * MATRIX_X_PADDING))+(state * 2);
}

/**
 * @brief Función auxiliar para dejar el bit en la posición original (precaución ante cualquier evento
 * fortuito como por ejemplo: regeneración de matriz, selección de bitblock por parte del jugador...etc
 * mientras el bit se está desplazando. Ésta función ayuda a solventar ese problema.
 */
void matrix_bitResetPosEffect(){
    matrix[pivot->i][pivot->j]->sprite->spriteEntry->x = (MATRIX_X_POS + (pivot->j * MATRIX_X_PADDING));
}

/*
*********************
*********************
*** REGENERATIONS ***
*********************
*********************
*/

/**
 * @brief Regenera el bloque de bits una vez destruido por el usuario.
* 1. Permutar elementos del bitBlockBuffer.
* 2. Salvar en un array temporal los MatrixElement (sprite+ digit).
* 3. Asignar referencias de elementos MatrixElement del bitBlockBuffer a la matriz (i,j).
* 4. Colocar esos elementos de matrix en las posiciones correctas (ya que son los que han caído).
* 5. Asignar las referencias guardadas en el array temporal al bitBlockBuffer.
* 6. Mostrar elementos nuevos de la matriz (en base al pivot).
* @todo: Permutar elementos de bitBlockBuffer
*/
void matrix_regenerateBitBlock(){

    MatrixElement* tmp[BITBLOCK_SIZE][BITBLOCK_SIZE];

    for(int i = -1; i <= 1; i++){
        for(int j = -1; j <= 1; j++){
            tmp[i+1][j+1] = matrix[pivot->i + i][pivot->j + j];
            matrix[pivot->i + i][pivot->j + j] = bitBlockBuffer[i+1][j+1];
            bitBlockBuffer[i+1][j+1] = tmp[i+1][j+1];
            sprites_displaySprite(matrix[pivot->i + i][pivot->j + j]->sprite->index,
                                  MATRIX_X_POS + ((pivot->j + j) * MATRIX_X_PADDING),
                                  MATRIX_Y_POS + ((pivot->i + i) * MATRIX_Y_PADDING),
                                  false);
        }
    }
}

/**
 * @brief Función para regenerar la matriz después de haber sido destruida,
 * mientras está oculta, se procede a su reordenación completa.
 *
 * Para ello, permuto la matriz con algoritmo de Fisher-Yates algoritmo (1938),
 * versión moderna por Durstenfeld (1964).
 *
 *
 * 1. Transpongo matriz.
 * 2. Cambio de base a array 1D.
 * 3. Permuto con algoritmo de Durstenfeld.
 * 4. Cambio de base a 2D.
 */
void matrix_regenerateMatrix(){

    MatrixElement* matrix1D[MATRIX_SIZE * MATRIX_SIZE];
    matrix_transposeMainMatrix();

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            matrix1D[(i*MATRIX_SIZE) +j] = matrix[i][j];
        }
    }

    matrix_permuteMatrix(matrix1D);

    int i = 0;
    int j = 0;

    for(int k = 0; k < MATRIX_SIZE*(MATRIX_SIZE-1); k++){
       if((k % MATRIX_SIZE) == 0){
           i++;
           j = 0;
       }
       matrix[i][j] = matrix1D[(i*MATRIX_SIZE) +j];
       j++;
    }
}

/*
 * @brief Transpone la matriz (cambio de filas por columnas).
 */
void matrix_transposeMainMatrix(){

    MatrixElement* tmpMatrix[MATRIX_SIZE][MATRIX_SIZE];

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
            tmpMatrix[i][j] = matrix[i][j];
        }
    }

    for(int i = 0; i < MATRIX_SIZE; i++){
        for(int j = 0; j < MATRIX_SIZE; j++){
           matrix[i][j] = tmpMatrix[j][i];
        }
    }
}

/**
 * @brief Permuta la matriz con algoritmo de Fisher-Yates algoritmo (1938),
 * versión moderna por Durstenfeld (1964).
 * @param matrix1D La matriz en 2D transformada en un vector para una mejor permutación.
 */
void matrix_permuteMatrix(MatrixElement* matrix1D[]){

    int upper = (MATRIX_SIZE*MATRIX_SIZE) - 1;
    srand(time(0));

    while(upper > 10 ){
        MatrixElement* tmp;
        int r = (rand() % upper);
        if(r >= MATRIX_SIZE){
            tmp = matrix1D[r];
            matrix1D[r] = matrix1D[upper];
            matrix1D[upper] = tmp;
            upper--;
        }
    }
}

/*
*********************
*********************
******* PIVOT *******
*********************
*********************
*/

/**
 * Función necesaria para que en todo momento se tenga bien localizado el bit que está
 * siendo seleccionado de manera pasiva con cada desplazamiento de cualquiera de los dos
 * Iñatrix.
 * @param i fila.
 * @param j columna.
 */
void matrix_updatePivot(uint8 i, uint8 j){
    if((i >= 1) && (i < MATRIX_SIZE-1) && (j >= 1) && (j < MATRIX_SIZE-1)){
        pivot->i = i;
        pivot->j = j;
    }
}

/**
 * @brief Función encargada de evaluar si existe overflow o no. Analiza cada fila,
 * tratando la combinación de sus bits como un número en binario, de manera que
 * si la suma de los números binarios resultantes de cada fila del bloque de bits es
 * superior al overflow definido al comienzo del juego (pastilla azul/roja), genera
 * overflow o no.
 * @return TRUE si existe Overflow, FALSE en caso contrario.
 */
bool matrix_evalBitBlockOverflow(){
    int decValue = 0;
    for(int i = -1; i <= 1; i++){
        double power = BITBLOCK_SIZE - 1;
        for(int j = -1; j <= 1; j++){
            decValue += matrix[pivot->i + i][pivot->j + j]->bit * pow(2, power);
            power--;
        }
    }

    return decValue > matrix_getOverflowLimit();
}

/*
*********************
*********************
****** HELPERS ******
*********************
*********************
*/

/**
 * @brief En base al modo de juego (normal/dificil) se obtiene el número límite.
 * @return Número que hará de límite a la hora de evaluar si se ha producido overflow o no.
 */
uint8 matrix_getOverflowLimit(){
    return gameData.mode == DIFFICULTY_NORMAL_MODE ? OVERFLOW_NM : OVERFLOW_HM;
}

/**
 * @brief
 * @param axis
 * @return
 */
uint8 matrix_getPositionX(uint8 axis){
    return  MATRIX_X_POS + (axis * MATRIX_X_PADDING);
}

/**
 * @brief
 * @param axis
 * @return
 */
uint8 matrix_getPositionY(uint8 axis){
    return  MATRIX_Y_POS + (axis * MATRIX_Y_PADDING);
}