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
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file sprites.h
 */

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
