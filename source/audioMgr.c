//
// Created by Gerun on 19/4/22.
//

#include "audioMgr.h"

void audioMgr_initAudio(){
    mmInitDefaultMem((mm_addr)soundbank_bin);

    // Carga de canciones
    mmLoad(SFX_AUDIO);
    mmSetModuleVolume(VOLUME); // Poner con define

    mmStart(SFX_AUDIO, MM_PLAY_LOOP);

    // Carga de efectos con mmLoadEffect(SFX_);
}

void audioMgr_unloadSounds(){
    mmStop();
    mmUnload(SFX_AUDIO);
    // UnloadEffects
}