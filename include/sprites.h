extern u16* gfx;
extern u16* gfx2;
extern u16* gfx3;
extern u16* gfxSub;

extern void memoriaReserba();

/* Para cada uno de los 256 valores que puede tomar un Pixel le da un color en la pantalla principal. El valor 0 es transparente y los valores sin definir negros */
extern void EstablecerPaletaPrindipal();


/* Para cada uno de los 256 valores que puede tomar un Pixel le da un color en la pantalla secundaria. El valor 0 es transparente y los valores sin definir negros */
extern void EstablecerPaletaSecundaria();


/* Carga en memoria los Sprites dibujados.*/
extern void GuardarSpritesMemoria();


/* Esta función dibuja un rombo en la posición de pantalla x-y. A cada rombo que queramos sacar en pantalla se le debe asignar un índice distinto que puede tomara valores entre 0 y 126. */
extern void MostrarRombo(int indice, int x, int y);


/*Esta función borra de la pantalla el rombo con el índice que se le indique como parámetro */
extern void BorrarRombo(int indice, int x, int y);


extern void MostrarRomboGrande(int indice, int x, int y);
extern void BorrarRomboGrande(int indice, int x, int y);


