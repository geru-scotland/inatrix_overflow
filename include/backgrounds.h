/*-------------------------------------
backgrounds.h
-------------------------------------*/
#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

//enum para los backgrounds:
//IMPORTANTE: Actualizar cada vez que se añada un nuevo background
typedef enum {
    BG_MATRIX = 0,
    BG_MATRIX2,
    BG_MAIN,
    BG_MATRIX_INATRIX,
    BG_RABBIT,
    BG_RABBIT2,
    BG_RABBIT3,
    BG_BLACK,
    BG_GAME_OVER,
} Backgrounds;

void background_SetMatrixBackground();
void background_SetMatrixBackground2();
void background_SetMainBackground();
void background_SetBlackBackground();
void background_SetGameOverBackground();
void background_setMatrixBackgroundInatrix();
void background_SetMatrixBackgroundRabbit();
void background_SetMatrixBackgroundRabbit2();
void background_SetMatrixBackgroundRabbit3();

extern void background_setBackground(Backgrounds bg);

#endif //BACKGROUNDS_H
