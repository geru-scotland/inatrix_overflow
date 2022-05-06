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
 * @file audioMgr.h
 */

#ifndef INATRIX_OVERFLOW_AUDIOMGR_H
#define INATRIX_OVERFLOW_AUDIOMGR_H

#define SFX_AUDIO 0


#define VOLUME 512 // 0-1024

#include "defines.h"
#include <maxmod9.h>
#include "soundbank.h"

extern void audioMgr_initAudio();
extern void audioMgr_unloadSounds();

extern const u8 soundbank_bin_end[];
extern const u8 soundbank_bin[];
extern const u32 soundbank_bin_size;

#endif //INATRIX_OVERFLOW_AUDIOMGR_H
