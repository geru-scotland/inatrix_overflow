/*-------------------------------------
backgrounds.h
-------------------------------------*/
#ifndef BACKGROUNDS_H
#define BACKGROUNDS_H

void visualizarPuerta();
void visualizarPuertaAbierta();
void background_SetMatrixBackground();
void background_SetMatrixBackground2();
extern void background_setBackground(int);

//enum para los backgrounds:
//IMPORTANTE: Actualizar cada vez que se añada un nuevo background
enum background{puerta, puertaAbierta, matrix, matrix2};

#endif //BACKGROUNDS_H
