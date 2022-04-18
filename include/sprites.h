#define DEFAULT_SPRITE_SPEED 1

#ifndef SPRITES_H
#define SPRITES_H

#include "defines.h"
#include "gfxInfo.h"

extern void sprites_initSpriteSystem();
extern void sprites_setMainPalette();
extern void sprites_allocateMemory();
extern void sprites_memorySetup(GfxData* gfx);
extern void sprites_setNextMemoryAddress(GfxData* gfx);
extern void sprites_createSprite(GfxData* gfx);
extern void sprites_reAllocateMemory(GfxData* gfxData, u16* memAddress);
extern void sprites_dumpToMemory(GfxData* gfx);
extern void sprites_displaySprite(uint8 index, int x, int y, bool isHidden);
extern void sprites_updateSprite(uint8 index);
Sprite* sprites_getSpriteByIndex(uint8 index);
SpriteEntry* sprites_getSpriteEntryByIndex(uint8 index);
extern void sprites_freeMemory();

extern Sprite* sprites[GFX_SIZE];
#endif // SPRITES_H
