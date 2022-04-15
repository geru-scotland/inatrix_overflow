/*---------------------------------------------------------------------------------
Definición del sistema de video, NO SE NECESITA CAMBIAR NADA AQUÍR
---------------------------------------------------------------------------------*/

#include "../include/libnds/nds.h"
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>		
#include "../include/engine.h"
#include "../include/sprites.h"


void inicializarVideo() {
    /*  Mapeo de memoria para mostrar imagenes en las dos pantallas. */
    vramSetMainBanks(VRAM_A_MAIN_BG_0x06000000,
                     VRAM_B_MAIN_BG_0x06020000,
                     VRAM_C_SUB_BG_0x06200000,
                     VRAM_E_LCD);

    vramSetBankE(VRAM_E_MAIN_SPRITE);
    vramSetBankD(VRAM_D_SUB_SPRITE);

    /* Modo de video para la pantalla principal*/
    videoSetMode(MODE_5_2D | // Modo de video 5
                 DISPLAY_BG2_ACTIVE | // Activar el fondo 2
                 DISPLAY_BG3_ACTIVE); // Activar el fondo 3

    /*  Modo de video de la segunda pantalla */
    videoSetModeSub(MODE_5_2D | // Modo de video 5
                    DISPLAY_BG3_ACTIVE); // Activar fondo 3
}


/* ---- CONFIGURACIÓN DE FONDOS, NO HAY QUE MODIFICARLO ---- */

/* Procedimiento para configurar el sistema de fondos */
void inicializarFondos() {
    /*  Establecer la afinidad del fondo 3 de la pantalla principal para colores de 16 bits. */
    REG_BG3CNT = BG_BMP16_256x256 |
                 BG_BMP_BASE(0) | // Dirección de comienzo de la memoria
                 BG_PRIORITY(3); // Prioridad baja

    /*  Asignar la matriz de identidad a la matriz de transformación del fondo 3 de la pantalla principal. */
    REG_BG3PA = 1 << 8;
    REG_BG3PB = 0;
    REG_BG3PC = 0;
    REG_BG3PD = 1 << 8;

/*******************************************************************************************/
    /*  Definir el estado del fondo 3 de la pantalla principal. */
    /*  Si se quiere poner el grafico en otra posicion hay que modificar esto. */
    REG_BG3X = 0;
    REG_BG3Y = 0;
/*******************************************************************************************/

    /*  Definir la afinidad del fondo 3 de la pantalla principal para colores de 16 bits.*/
    REG_BG2CNT = BG_BMP16_128x128 |
                 BG_BMP_BASE(8) | // Dirección de comienzo de memoria
                 BG_PRIORITY(2);  // Baja prioridad

    /*Asignar la matriz identidad a la matriz de transformación del fondo 3 de la pantalla principal. */
    REG_BG2PA = 1 << 8;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 1 << 8;

/*******************************************************************************************/
    /*  Definir el estado del fondo 3 de la pantalla principal. */
    /*  Cambiar lo siguiente si el grafico se quiere establecer en otro lugar. */
    REG_BG2X = -(SCREEN_WIDTH / 2 - 32) << 8;
    REG_BG2Y = -32 << 8;
/*******************************************************************************************/
   
    /*  Definir la afinidad del fondo 3 de la pantalla secundaria para colores de 16 bits.*/
    REG_BG3CNT_SUB = BG_BMP16_256x256 |
                     BG_BMP_BASE(0) | // Comienzo de direcciónn de memoria
                     BG_PRIORITY(3); // Prioridad baja

    /*Asignar la matriz identidad a la matriz de transformación del fondo 3 de la pantalla secundario. */
    REG_BG3PA_SUB = 1 << 8;
    REG_BG3PB_SUB = 0;
    REG_BG3PC_SUB = 0;
    REG_BG3PD_SUB = 1 << 8;

/*******************************************************************************************/
    /*  Definir el estado del fondo 3 de la pantalla secundaria. */
    /*  Cambiar lo siguiente si el grafiko se quiere establecer en otro lugar. */ 
    REG_BG3X_SUB = 0;
    REG_BG3Y_SUB = 0;
/*******************************************************************************************/
}


void inicializarGraficos()
{
    powerOn(POWER_ALL_2D);
    lcdMainOnBottom();
    inicializarVideo();
    PrintConsole* console = consoleDemoInit(); //La pantalla superior se utilizará en modo texto y la inferior en modo gráfico.
    ConsoleFont font;
    font.numColors = 1;
    font.convertSingleColor = true;
    consoleSetFont(console, &font);
}


//************************************************
//Sprites
//************************************************

/* Inicializar la memoria para los Sprites.*/
void initSpriteMem() {

	oamInit(&oamMain, SpriteMapping_1D_32, false);
	oamInit(&oamSub, SpriteMapping_1D_32, false);

}



void inicializarGraficosSprites()
{
	inicializarGraficos();
	inicializarFondos();
	initSpriteMem();
    sprites_initSpriteSystem();
}
