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
 * @file game.h
 */

#ifndef GAME_H
#define GAME_H
#define GAME_FPS_CAP 16
#define TIMER_REGEN 15

#include <stdbool.h>

void game_Loop();
void game_Update();

enum States {
    // Estados generales del juego
    GAME_STATE_MAIN_MENU = 0,
    GAME_STATE_INTRO,
    GAME_STATE_MENU,
    GAME_STATE_GAME,
    GAME_STATE_PAUSE,
    GAME_STATE_GAME_OVER,
    GAME_STATE_STATS,
    GAME_STATE_SURRENDER,
};

typedef enum {
    PHASE_NULL = 0,
    PHASE_WAITING_PLAYER_INPUT,
    /* MAIN MENU */
    /* INTRO */
    PHASE_INTRO_START,
    PHASE_INTRO_SCENE_ACTIVE,
    PHASE_MOVE_CAPSULE,
    /* MENU */
    /* GAME */
    PHASE_BITBLOCK_FALLING,
    PHASE_DESTROYING_MATRIX,
    PHASE_REGENERATING_MATRIX,
    PHASE_MOVE_INATRIX_X,
    PHASE_MOVE_INATRIX_Y,
    PHASE_SHOW_STATS,
    PHASE_GAME_PAUSE
} Phases;

typedef enum {
    DIFFICULTY_NORMAL_MODE = 0,
    DIFFICULTY_HARD_MODE = 1
} Difficulty;

/*
 * Información general del juego.
 * state: estado actual del juego.
 * phase: phase del estado.
 *
 * Desafortunadamente, switch no acepta otra
 * cosa más que int, así que no se pueden declarar
 * las variables como uint8 o similares.
 * */
typedef struct {
    int state;
    int phase;
    Difficulty mode;
    bool destroyMatrixActive;
    int destroyMatrixTime;
    int matrixRegens;
} GameData;

typedef struct {
    int overflowScore;
    int totalOverflows;
    int runOverflows;
    int failScore;
} PlayerData;

extern GameData gameData;
extern PlayerData playerData;

extern void game_Loop();
extern void game_manageScore(bool overflow);
extern void game_initData();
extern void game_launch();
extern void game_setDifficulty(Difficulty difficulty);
extern void game_setDestroyMatrix(bool active);
extern void game_enableDestroyMatrix();
extern void game_increaseMatrixRegens();
extern int game_getNextPhase();
extern void game_manageGameOver();
extern bool game_achievedMinimumOverflows();
#endif //GAME_H
