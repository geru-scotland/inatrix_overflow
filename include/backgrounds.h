/*-------------------------------------
backgrounds.h
-------------------------------------*/
#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

//enum para los backgrounds:
//IMPORTANTE: Actualizar cada vez que se añada un nuevo background
typedef enum {
    BG_PUERTA = 0,
    BG_PUERTAABIERTA,
    BG_MATRIX,
    BG_MATRIX2
} Backgrounds;

void visualizarPuerta();
void visualizarPuertaAbierta();
void background_SetMatrixBackground();
void background_SetMatrixBackground2();
extern void background_setBackground(Backgrounds bg);

#endif //BACKGROUNDS_H
