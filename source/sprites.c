/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include "nds.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "../include/sprites.h"
#include "../include/defines.h"
#include "../include/gfxInfo.h"

Sprite* sprites[GFX_SIZE];

void sprites_initSpriteSystem(){
    gfxInfo_init();
    sprites_setMainPalette();
    sprites_allocateMemory();
}

/* Reservar memoria para cada sprite que se quiera mostrar en pantalla.*/
void sprites_allocateMemory()
{
    for (int i = 0; i < gfxGUID; i++){
        sprites_memorySetup(gfxList[i]);
    }
}

void sprites_memorySetup(GfxData* gfx){
    sprites_setNextMemoryAddress(gfx);
    sprites_dumpToMemory(gfx);
    sprites_createSprite(gfx);
}

void sprites_setNextMemoryAddress(GfxData* gfx){
    gfx->memAddress = oamAllocateGfx(&oamMain, gfx->size, gfx->colorFormat);
}

void sprites_createSprite(GfxData* gfx){
    sprites[gfx->GUID] = malloc(sizeof(Sprite));
    sprites[gfx->GUID]->index = gfx->GUID; // TODO: cambiar
    sprites[gfx->GUID]->speed = DEFAULT_SPRITE_SPEED;
    sprites[gfx->GUID]->gfx = gfx;
}

void sprites_reAllocateMemory(GfxData* gfx, u16* memAddress){
    gfx->memAddress = memAddress;
    sprites_dumpToMemory(gfx);
}

void sprites_dumpToMemory(GfxData* gfx){
    int gfxSize = (gfx->size == SpriteSize_16x16) ? (16 * 16)/2 : (32 * 32)/2;
    for(int pos = 0; pos < gfxSize; pos++){
        gfx->memAddress[pos] = gfx->bitmap[pos * 2] | (gfx->bitmap[(pos*2)+1] << 8);
    }
}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros.
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES*/
void sprites_setMainPalette() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); // Rojo.
	SPRITE_PALETTE[2] = RGB15(0,31,0); // Verde
	SPRITE_PALETTE[3] = RGB15(0,0,31); // Azul
    SPRITE_PALETTE[4] = RGB15(0,31,0); // Azul
    SPRITE_PALETTE[21] = RGB15(0,12,0); // Verde oscuro.

}

/**
 * Función que gestiona lo necesario para la creación de cualquier
 * sprite. Tanto de memoria y asociaciones de libnds, como por nuestra parte
 * para la fácil manipulación de sprites.
 * @param index
 * @param gfxIndex
 * @param x
 * @param y
 * @param size
 * @param colorFormat
 * @param isHidden
 */
void sprites_displaySprite(uint8 index, int x, int y, bool isHidden){
    // Ahora se define el nuevo sprite
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
    // Se actualiza la memoria con el nuevo sprite (lo dibuja)
    oamUpdate(&oamMain);

    // Se obtiene el SpriteEntry creado por libnds
    // Y se asigna al struct Sprite
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
 * sprites[] es un array de punteros a structs.
 * @param index
 * @return Puntero al struct del sprite asociado al index
 */
Sprite* getSpriteByIndex(uint8 index){
    return sprites[index];
}

/**
 * Una vez en memoria oam (gracias al set que se ha hecho inicialmente)
 * podemos obtener su SpriteEntry
 * @param index
 * @return
 */
SpriteEntry* getSpriteEntryByIndex(uint8 index){
    return &oamMain.oamMemory[index];
}

/**
 * TODO: Liberar memoria de los punteros creados para cada sprite
 * Por ahora, poner a hidden en oamMain y que se updatee
 * A parte, hacer un free del puntero y gestionar la lista
 * Pero hay que mirar cómo se puede borrar totalmente de memoria
 * o si en su creación/mapeo inicial, se queda registrado de
 * manera persistente.
*/
void sprites_freeMemory(){
    for(int i = 0; i < GFX_SIZE; i++){
        free(gfxList[i]);
    }
}