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
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

#include "audioMgr.h"

/**
 * @author Geru-Scotland.
 * @file audioMgr.c
 * @brief Gestión del audio - no funcional aún por falta de tiempo.
 */

/**
 *
 */
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
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */mmUnload(SFX_AUDIO);
    // UnloadEffects
}