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

u16* gfxrombo;
u16* gfxromboGrande;
Sprite* sprites[MAX_SPRITES];
GfxData* gfxList[GFX_SIZE];


u8 ball[256] =
        {
                0,0,0,0,0,0,2,2,
                0,0,0,0,0,2,2,2,	//	0,0,0,0,0,0,2,2, 2,2,0,0,0,0,0,0,
                0,0,0,0,2,2,2,2,
                0,0,0,2,2,2,2,2,	//	0,0,0,0,0,2,2,2, 2,2,2,0,0,0,0,0,
                0,0,2,2,2,2,2,2,
                0,2,2,2,2,2,2,2,	//	0,0,0,0,2,2,2,2, 2,2,2,2,0,0,0,0,
                2,2,2,2,2,2,2,2,
                2,2,2,2,2,2,2,2,	//	0,0,0,2,2,2,2,2, 2,2,2,2,2,0,0,0,

                2,2,0,0,0,0,0,0,
                2,2,2,0,0,0,0,0,	//	0,0,2,2,2,2,2,2, 2,2,2,2,2,2,0,0,
                2,2,2,2,0,0,0,0,
                2,2,2,2,2,0,0,0,	//	0,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,0,
                2,2,2,2,2,2,0,0,
                2,2,2,2,2,2,2,0,	//	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,
                2,2,2,2,2,2,2,2,
                2,2,2,2,2,2,2,2,	//	2,2,2,2,2,2,2,2, 2,2,2,2,2,2,2,2,

                1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
                0,1,1,1,1,1,1,1,
                0,0,1,1,1,1,1,1,	//	1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,
                0,0,0,1,1,1,1,1,
                0,0,0,0,1,1,1,1,	//	0,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,0,
                0,0,0,0,0,1,1,1,
                0,0,0,0,0,0,1,1,	//	0,0,1,1,1,1,1,1, 1,1,1,1,1,1,0,0,

                1,1,1,1,1,1,1,1,
                1,1,1,1,1,1,1,1,	//	0,0,0,1,1,1,1,1, 1,1,1,1,1,0,0,0,
                1,1,1,1,1,1,1,0,
                1,1,1,1,1,1,0,0,	//	0,0,0,0,1,1,1,1, 1,1,1,1,0,0,0,0,
                1,1,1,1,1,0,0,0,
                1,1,1,1,0,0,0,0,	//	0,0,0,0,0,1,1,1, 1,1,1,0,0,0,0,0,
                1,1,1,0,0,0,0,0,
                1,1,0,0,0,0,0,0,	//	0,0,0,0,0,0,1,1, 1,1,0,0,0,0,0,0,
        };

void sprites_initSpriteSystem(){
    sprites_loadGfx();
    sprites_setMainPalette();
    sprites_allocateMemory();
}

/* Reservar memoria para cada sprite que se quiera mostrar en pantalla.*/
void sprites_allocateMemory()
{
    for (int i = 0; i < GFX_SIZE; i++){

        gfxList[i]->memAddress = oamAllocateGfx(&oamMain, gfxList[i]->size, gfxList[i]->colorFormat);

        int gfxSize = (gfxList[i]->size == SpriteSize_16x16) ? (16 * 16)/2 : (32 * 32)/2;

        for(int pos = 0; pos < gfxSize; pos++){
            gfxList[i]->memAddress[pos] = gfxList[i]->bitmap[pos * 2] | (gfxList[i]->bitmap[(pos*2)+1] << 8);
        }

        sprites[i] = malloc(sizeof(Sprite));
        sprites[i]->index = i;
        sprites[i]->speed = DEFAULT_SPRITE_SPEED;
        sprites[i]->gfx = gfxList[i];
    }
}

void sprites_loadGfx(){

    // Geru: Primero se crea el struct en memoria dinámica o heap
    // Luego tendremos que liberarla, si no -> memory leaks.

    /* BALL */
    gfxList[GFX_BALL] = malloc(sizeof(GfxData));
    gfxList[GFX_BALL]->memAddress = NULL;
    gfxList[GFX_BALL]->bitmap = ball;
    gfxList[GFX_BALL]->id = GFX_BALL;
    gfxList[GFX_BALL]->size = SpriteSize_16x16;
    gfxList[GFX_BALL]->colorFormat = SpriteColorFormat_256Color;

    /* BALL 2 */

    /*
     * Se pueden nutrir del mismo bitmap, porque en el loadGfx
     * lo copian en la memoria reservada por el oam
     */
    gfxList[GFX_BALL2] = malloc(sizeof(GfxData));
    gfxList[GFX_BALL2]->memAddress = NULL;
    gfxList[GFX_BALL2]->bitmap = ball;
    gfxList[GFX_BALL2]->id = GFX_BALL2;
    gfxList[GFX_BALL2]->size = SpriteSize_16x16;
    gfxList[GFX_BALL2]->colorFormat = SpriteColorFormat_256Color;

    /* INATRIX */

    /* NUMBER_1 */
}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros.
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES*/
void sprites_setMainPalette() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); // los píxeles con valor 1 serán de color rojo.
	SPRITE_PALETTE[2] = RGB15(0,31,0); // los píxeles con valor 2 serán verdes.
	SPRITE_PALETTE[3] = RGB15(0,0,31); // los píxeles con valor 3 serán azules.
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
    sprites[index]->spriteEntry = &oamMain.oamMemory[sprites[index]->index];
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
