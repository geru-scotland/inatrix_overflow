
#include "nds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* Si queremos visualizar distintos fondos, aquí se debe incluir el fichero de cabecera (fichero .h) de cada fondo. Estos ficheros de cabecera se generan automáticamente durante la compilación. */

#include "backgrounds.h"
#include "engine.h"

#include "MatrixBackground.h"
#include "MatrixBackground2.h"
#include "MainBackground.h"
#include "BlackBackground.h"
#include "GameOverBackground.h"
#include "MatrixBackgroundInatrix.h"
#include "MatrixBackgroundRabbit.h"
#include "MatrixBackgroundRabbit2.h"
#include "MatrixBackgroundRabbit3.h"


static const int DMA_CHANNEL = 3;
void background_SetMatrixBackground() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MatrixBackgroundBitmap, /* Variable que se genera automaticamente */
                     (uint16 *)BG_BMP_RAM(0), /* Dirección del fondo principal */
                     MatrixBackgroundBitmapLen); /* Longitud en bytes, variable que se genera automáticamente */
}

void background_SetMatrixBackground2() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MatrixBackground2Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     MatrixBackground2BitmapLen);
}

void background_SetMainBackground() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MainBackgroundBitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     MainBackgroundBitmapLen);
}

void background_SetBlackBackground() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     BlackBackgroundBitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     BlackBackgroundBitmapLen);
}


void background_SetGameOverBackground() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     GameOverBackgroundBitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     GameOverBackgroundBitmapLen);
}

void background_SetMatrixBackgroundInatrix() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MatrixBackgroundInatrixBitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     MatrixBackgroundInatrixBitmapLen);
}

void background_SetMatrixBackgroundRabbit() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MatrixBackgroundRabbitBitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     MatrixBackgroundRabbitBitmapLen);
}

void background_SetMatrixBackgroundRabbit2() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MatrixBackgroundRabbit2Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     MatrixBackgroundRabbit2BitmapLen);
}

void background_SetMatrixBackgroundRabbit3() {

    dmaCopyHalfWords(DMA_CHANNEL,
                     MatrixBackgroundRabbit3Bitmap,
                     (uint16 *)BG_BMP_RAM(0),
                     MatrixBackgroundRabbit3BitmapLen);
}


/**
 * Función auxiliar para establecer diferentes
 * fondos.
 * @param bg ID del Background
 */
void background_setBackground(Backgrounds bg){
    switch (bg) {
        case BG_MATRIX:
            background_SetMatrixBackground();
            break;
        case BG_MATRIX2:
            background_SetMatrixBackground2();
            break;
        case BG_MAIN:
            background_SetMainBackground();
            break;
        case BG_BLACK:
            background_SetBlackBackground();
            break;
        case BG_GAME_OVER:
            background_SetGameOverBackground();
            break;
        case BG_MATRIX_INATRIX:
            background_SetMatrixBackgroundInatrix();
            break;
        case BG_RABBIT:
            background_SetMatrixBackgroundRabbit();
            break;
        case BG_RABBIT2:
            background_SetMatrixBackgroundRabbit2();
            break;
        case BG_RABBIT3:
            background_SetMatrixBackgroundRabbit3();
            break;
        default:
            break;
    }
}