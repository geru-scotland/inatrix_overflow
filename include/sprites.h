#define MAX_SPRITES 20
#define DEFAULT_SPRITE_SPEED 1

#include "gfxInfo.h"
// TODO: SpriteManager (create, modify, etc)

// Indices asociados a cada sprite (nuestro y en oamMemory)
typedef enum {
    INDEX_BALL = 0, // Testing purposes
    INDEX_BALL2,
    INDEX_INATRIX_1,
    INDEX_INATRIX_2,
    INDEX_MATRIX_1_1,
    INDEX_MATRIX_1_2,
    INDEX_MATRIX_1_3,
    INDEX_MATRIX_2_1
    //..
} SpriteIndex;

// Información global de los sprites
typedef struct {
    OamState oam;
} SpriteGlobalInfo;

typedef struct {
    uint8 index;
    SpriteEntry* spriteEntry;
    int speed;
    GfxData* gfx;
} Sprite;

extern void sprites_initSpriteSystem();
extern void sprites_setMainPalette();
extern void sprites_allocateMemory();
extern void sprites_displaySprite(uint8 index, int x, int y, bool isHidden);
extern void sprites_updateSprite(uint8 index);
Sprite* sprites_getSpriteByIndex(uint8 index);
SpriteEntry* sprites_getSpriteEntryByIndex(uint8 index);
void initGlobalSpriteInfo();
extern void sprites_loadGfx();

extern SpriteGlobalInfo spriteInfo;
extern Sprite* sprites[MAX_SPRITES];
