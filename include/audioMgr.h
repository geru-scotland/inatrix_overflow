//
// Created by Eideann on 19/4/22.
//

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
