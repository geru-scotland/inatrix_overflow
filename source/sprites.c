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
 * @file sprites.c
 * @brief Encargado de generar sprites de una manera reducida y óptima, así como
 * de su gestión tanto en nuestra memoria dinámica con en el banco de memoria
 * de la pantalla Main de la NDS.
 */

#include "nds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sprites.h"
#include "defines.h"
#include "gfxInfo.h"

/**
 * @var sprites[GFX_SIZE]: Array de punteros a struct @struct Sprite almacenados en memoría dinámica.
 */
Sprite* sprites[GFX_SIZE];

/**
 * @brief Inicializa los GFX (aúna su información de @struct GfxData y genera un array de punteros), paleta de colores y escribe en el banco de memoria
 * los bitmaps asociados a cada gráfico.
 */
void sprites_initSpriteSystem(){
    gfxInfo_init();
    sprites_setMainPalette();
    sprites_allocateMemory();
}

/**
 * @brief Reservar memoria para cada sprite que se quiera mostrar en pantalla.
 * */
void sprites_allocateMemory()
{
    for (int i = 0; i < gfxGUID; i++){
        sprites_memorySetup(gfxList[i]);
    }
}

/**
 * @brief Proceso de transferencia del GFX al banco de memoria de la NDS.
 * @param gfx Información del gráfico, puntero a @struct GfxData
 */
void sprites_memorySetup(GfxData* gfx){
    sprites_setNextMemoryAddress(gfx);
    sprites_dumpToMemory(gfx);
    sprites_createSprite(gfx);
}

/**
 * @brief Solicita al oamMain la dirección del primer elemento del bloque
 * que ha reservado en memoria en función de la configuración de GFX que le damos.
 * El GFX pasado como parámetro contendrá dicha dirección en su @var memAddress una
 * vez ejecutada esta instrucción.
 * @param gfx Información del gráfico, puntero a @struct GfxData
 */
void sprites_setNextMemoryAddress(GfxData* gfx){
    gfx->memAddress = oamAllocateGfx(&oamMain, gfx->size, gfx->colorFormat);
}

/**
 * @brief Reserva memoria dinámica en el heap para el @struct Sprite y lo
 * inserta en el array de punteros a @struct Sprite, asociándolo al Identificador
 * global del GFX.
 * @param gfx
 */
void sprites_createSprite(GfxData* gfx){
    sprites[gfx->GUID] = malloc(sizeof(Sprite));
    sprites[gfx->GUID]->index = gfx->GUID; // @todo: cambiar
    sprites[gfx->GUID]->speed = DEFAULT_SPRITE_SPEED;
    sprites[gfx->GUID]->gfx = gfx;
}

/**
 * @brief Función que reescribe la memoria del banco de Memoria.
 * @param gfx struct del tipo @struct GfxData
 * @param memAddress Primera posición del bloque de memoria a escribir el bitmap.
 */
void sprites_reAllocateMemory(GfxData* gfx, u16* memAddress){
    gfx->memAddress = memAddress;
    sprites_dumpToMemory(gfx);
}

/**
 * @brief Escribe el bitmap del GFX en la posición dada por @memAddress
 * @param gfx puntero a struct del tipo @struct GfxData
 */
void sprites_dumpToMemory(GfxData* gfx){
    int gfxSize = (gfx->size == SpriteSize_16x16) ? (16 * 16)/2 : (32 * 32)/2;
    for(int pos = 0; pos < gfxSize; pos++){
        gfx->memAddress[pos] = gfx->bitmap[pos * 2] | (gfx->bitmap[(pos*2)+1] << 8);
    }
}

/**
 * @brief Especificación de la paleta de colores.
 * El índice del array indica el número que se ha de escribir
 * en el bitmap del sprite para que el pixel correspondiente sea
 * coloreado con el mismo.
 */
void sprites_setMainPalette() {

    SPRITE_PALETTE[1]  = RGB15(31,0,0);   // ROJO
    SPRITE_PALETTE[2]  = RGB15(31,31,0);  // AMARILLO
    SPRITE_PALETTE[3]  = RGB15(31,31,31); // BLANCO
    SPRITE_PALETTE[4]  = RGB15(0,31,0);   // VERDE
    SPRITE_PALETTE[5]  = RGB15(0,0,31);   // AZUL
    SPRITE_PALETTE[6]  = RGB15(0,0,0);    // NEGRO
    SPRITE_PALETTE[7]  = RGB15(0,31,31);  // CYAN
    SPRITE_PALETTE[8]  = RGB15(31,0,31);  // MAGENTA
    SPRITE_PALETTE[9]  = RGB15(16,16,16); // GRIS
    SPRITE_PALETTE[10] = RGB15(25,25,25); // GRIS CLARO
    SPRITE_PALETTE[11] = RGB15(8,8,8);    // GRIS OSCURO
    SPRITE_PALETTE[12] = RGB15(31,19,0);  // NARANJA
    SPRITE_PALETTE[13] = RGB15(19,0,4);   // GRANATE
    SPRITE_PALETTE[14] = RGB15(25,0,0);   // MARRON
    SPRITE_PALETTE[15] = RGB15(16,0,16);  // MORADO
    SPRITE_PALETTE[16] = RGB15(25,19,31); // LILA
    SPRITE_PALETTE[17] = RGB15(31,19,25); // ROSA
    SPRITE_PALETTE[18] = RGB15(23,21,21); // AZUL CLARO
    SPRITE_PALETTE[19] = RGB15(0,0,16);   // AZUL MARINO
    SPRITE_PALETTE[20] = RGB15(0,16,16);  // VERDE AZULADO
    SPRITE_PALETTE[21] = RGB15(0,12,0);   // VERDE OSCURO
    SPRITE_PALETTE[22] = RGB15(16,16,0);  // VERDE OLIVA
    SPRITE_PALETTE[23] = RGB15(19,31,19); // VERDE CLARO
    SPRITE_PALETTE[24] = RGB15(31,31,19); // AMARILLO CLARO
}

/**
 * @brief Función que muestra o esconde cualquier
 * sprite. También almacena el SpriteEntry creado por libnds y lo asigna al
 * @struct Sprite
 * @param index
 * @param gfxIndex
 * @param x
 * @param y
 * @param size
 * @param colorFormat
 * @param isHidden
 */
void sprites_displaySprite(uint8 index, int x, int y, bool isHidden){
    oamSet(&oamMain,
           index,
           x, y,
           0,
           0,
           sprites[index]->gfx->size,
           sprites[index]->gfx->colorFormat,
           sprites[index]->gfx->memAddress,
           -1,
           false,
           isHidden,
           false, false,
           false
    );
    oamUpdate(&oamMain);

    sprites[index]->spriteEntry = &oamMain.oamMemory[index];
}

void sprites_updateSprite(uint8 index){
    oamSet(&oamMain, 	//main graphics engine context
           index,  		//oam index (0 to 127)
           sprites[index]->spriteEntry->x, sprites[index]->spriteEntry->y,    		//x and y pixel location of the sprite
           0,       		//priority, lower renders last (on top)
           0,	 			//this is the palette index if multiple palettes or the alpha value if bmp sprite
           sprites[index]->gfx->size,
           sprites[index]->gfx->colorFormat,
           sprites[index]->gfx->memAddress,		//+16*16/2, 	//pointer to the loaded graphics
           -1,            	//sprite rotation data
           false,         	//double the size when rotating?
           sprites[index]->spriteEntry->isHidden,			//hide the sprite?
           false, false, 	//vflip, hflip
           false			//apply mosaic
    );
    oamUpdate(&oamMain);
}

/**
 * @brief Obtener el sprite a través del índice.
 * @param index
 * @return Puntero a elemento @struct Sprite.
 */
Sprite* getSpriteByIndex(uint8 index){
    return sprites[index];
}

/**
 * @brief Una vez en memoria oam (gracias al set que se ha hecho inicialmente)
 * podemos obtener su SpriteEntry
 * @param index
 * @return
 */
SpriteEntry* getSpriteEntryByIndex(uint8 index){
    return &oamMain.oamMemory[index];
}

/**
 * @brief Liberar memoria dinámica
 */
void sprites_freeMemory(){
    for(int i = 0; i < GFX_SIZE; i++){
        free(gfxList[i]);
    }
}