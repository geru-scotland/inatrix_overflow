/*---------------------------------------------------------------------------------
Kode hau garatu da dovotoren "Simple sprite demo" adibidean eta Jaeden Ameronen beste
adibide batean oinarrituta.
---------------------------------------------------------------------------------*/

#include "../include/libnds/nds.h"
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		

#include "../include/sprites.h"
#include "../include/defines.h"
#include "../include/gfx_bitmaps.h"

u16* gfxrombo;
u16* gfxromboGrande;
Sprite* sprites[MAX_SPRITES];
u16* gfxList[MAX_GFX];

/* Reservar memoria para cada sprite que se quiera mostrar en pantalla.*/
void memoriaReserba()
{
	/* Pantaila nagusian gehitu nahi den sprite bakoitzarentzako horrelako bat egin behar da. */
	gfxrombo= oamAllocateGfx(&oamMain, SpriteSize_16x16, SpriteColorFormat_256Color);
	gfxromboGrande=oamAllocateGfx(&oamMain, SpriteSize_32x32, SpriteColorFormat_256Color);
}

/* A cada uno de los 256 valores que puede tomar un pixel en la PALETA PRINCIPAL
   se le puede asignar un color. El valor 0 es transparente. Los valores sin definir son negros. 
   MODIFICAR SEGÚN LOS COLORES QUE QUERAIS UTILIZAR EN VUESTROS SPRITES*/
void EstablecerPaletaPrincipal() {

	SPRITE_PALETTE[1] = RGB15(31,0,0); // los píxeles con valor 1 serán de color rojo.
	SPRITE_PALETTE[2] = RGB15(0,31,0); // los píxeles con valor 2 serán verdes.
	SPRITE_PALETTE[3] = RGB15(0,0,31); // los píxeles con valor 3 serán azules.
}

/* Carga en memoria cada uno de los sprites que hemos dibujado. */

/*TODO: Geru - Revisar bien esto, en la guía has visto algo de que era más óptimo guardar de otra manera. */
void GuardarSpritesMemoria(){ 
	
int i;
	//sprite de 16*16
	for(i = 0; i < 16 * 16 / 2; i++) 
	{	
		gfxrombo[i] = rombo[i*2] | (rombo[(i*2)+1]<<8);				
	}
	//sprite de 32x32
	for(i = 0; i < 32 * 32 / 2; i++) 
	{	
		gfxromboGrande[i] = romboGrande[i*2] | (romboGrande[(i*2)+1]<<8);				
	}
}

/* Esta función dibuja un rombo en la posición x-y de pantalla. A cada rombo que se quiera mostrar en pantalla se le debe asignar un indice distinto, un valor entre 0 y 126. */

void MostrarRombo(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,
		SpriteColorFormat_256Color, 
		gfxrombo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
	  
oamUpdate(&oamMain);  
}

/*Esta función borra de la pantalla el Rombo con el índice indicado*/
void BorrarRombo(int indice, int x, int y)
{

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_16x16,     
		SpriteColorFormat_256Color, 
		gfxrombo,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

void MostrarRomboGrande(int indice, int x, int y)
{ 

oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxromboGrande,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		false,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 

	  
oamUpdate(&oamMain);  
}

void BorrarRomboGrande(int indice, int x, int y)
{
oamSet(&oamMain, //main graphics engine context
		indice,           //oam index (0 to 127)  
		x, y,   //x and y pixle location of the sprite
		0,                    //priority, lower renders last (on top)
		0,					  //this is the palette index if multiple palettes or the alpha value if bmp sprite	
		SpriteSize_32x32,     
		SpriteColorFormat_256Color, 
		gfxromboGrande,//+16*16/2,                  //pointer to the loaded graphics
		-1,                  //sprite rotation data  
		false,               //double the size when rotating?
		true,			//hide the sprite?
		false, false, //vflip, hflip
		false	//apply mosaic
		); 
oamUpdate(&oamMain); 

}

// TODO: Borrar todas las funciones previas de mostrar/borrar.

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
void createSprite(int index, u8 gfxIndex, int x, int y, SpriteSize size, SpriteColorFormat colorFormat, bool isHidden){
    // Geru: Primero se crea el struct en memoria dinámica o heap
    // Luego tendremos que liberarla, si no -> memory leaks.
    Sprite* sprite = malloc( sizeof(Sprite));
    sprite->index = index;
    sprite->speed = DEFAULT_SPRITE_SPEED;
    sprite->gfx = gfxList[gfxIndex];
    sprite->size = size;
    sprite->colorFormat = colorFormat;

    // Ahora se define el nuevo sprite
    oamSet(&oamMain,
           sprite->index,
           x, y,
           0,
           0,
           sprite->size,
           sprite->colorFormat,
           sprite->gfx,
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
    sprite->spriteEntry = &oamMain.oamMemory[sprite->index];
    // Listo, insertamos en nuestro array de sprites
    sprites[sprite->index] = sprite;
}

//TODO: Liberar memoria de los punteros creados para cada sprite
//Cada vez que se haga un delete o similar.

void updateSprite(Sprite* sprite){
    oamSet(&oamMain, 	//main graphics engine context
           sprite->index,  		//oam index (0 to 127)
           sprite->spriteEntry->x, sprite->spriteEntry->y,    		//x and y pixel location of the sprite
           0,       		//priority, lower renders last (on top)
           0,	 			//this is the palette index if multiple palettes or the alpha value if bmp sprite
           sprite->size,
           sprite->colorFormat,
           sprite->gfx,		//+16*16/2, 	//pointer to the loaded graphics
           -1,            	//sprite rotation data
           false,         	//double the size when rotating?
           sprite->spriteEntry->isHidden,			//hide the sprite?
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
Sprite* getSpriteByIndex(int index){
    return sprites[index];
}

/**
 * Una vez en memoria oam (gracias al set que se ha hecho inicialmente)
 * podemos obtener su SpriteEntry
 * @param index
 * @return
 */
SpriteEntry* getSpriteEntryByIndex(int index){
    return &oamMain.oamMemory[index];
}

/**
* Borrar Sprites
 * Por ahora, poner a hidden en oamMain y que se updatee
 * A parte, hacer un free del puntero y gestionar la lista
 * Pero hay que mirar cómo se puede borrar totalmente de memoria
 * o si en su creación/mapeo inicial, se queda registrado de
 * manera persistente.
*/