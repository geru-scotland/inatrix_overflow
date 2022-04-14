#define MAX_SPRITES 20
#define MAX_GFX 15
#define DEFAULT_SPRITE_SPEED 1

// TODO: SpriteManager (create, modify, etc)

// Indices asociados a cada sprite (nuestro y en oamMemory)
typedef enum {
    INDEX_BALL = 0, // Testing purposes
    INDEX_INATRIX_1,
    INDEX_INATRIX_2,
    INDEX_MATRIX_1_1,
    INDEX_MATRIX_1_2,
    INDEX_MATRIX_1_3,
    INDEX_MATRIX_2_1
    //..
} SpriteIndex;

// Identificadores para los GFX, asociamos uno a cada sprite.
typedef enum{
    GFX_BALL = 0,
    GFX_ONE,
    GFX_ZERO,
    GFX_INATRIX_1
} Gfx;

// Información global de los sprites
typedef struct {
    OamState oam;
} SpriteGlobalInfo;

typedef struct {
    int index;
    SpriteEntry* spriteEntry;
    int speed;
    u16* gfx;
    SpriteSize size; // Enum sprite size {SpriteSize_16x16, SpriteSize_32x32} etc.
    SpriteColorFormat colorFormat; // Enum {SpriteColorFormat_16Color, SpriteColorFormat_256Color} etc.
} Sprite;

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



void createSprite(int index, u8 gfxIndex, int x, int y, SpriteSize size, SpriteColorFormat colorFormat, bool isHidden);
void updateSprite(Sprite* sprite);
Sprite* getSpriteByIndex(int index);
SpriteEntry* getSpriteEntryByIndex(int index);
void initGlobalSpriteInfo();



extern u16* gfxrombo;
extern u16* gfxromboGrande;

extern u16* gfxList[MAX_GFX];
extern SpriteGlobalInfo spriteInfo;
extern Sprite* sprites[MAX_SPRITES];