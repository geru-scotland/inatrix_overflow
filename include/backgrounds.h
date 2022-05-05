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
    BG_BLACK,
    BG_GAME_OVER
} Backgrounds;

void background_SetMatrixBackground();
void background_SetMatrixBackground2();
void background_SetMainBackground();
void background_SetBlackBackground();
void background_SetGameOverBackground();

extern void background_setBackground(Backgrounds bg);

#endif //BACKGROUNDS_H
