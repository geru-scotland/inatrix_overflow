/*---------------------------------------------------------------------------------
game.h
---------------------------------------------------------------------------------*/
#ifndef GAME_H
#define GAME_H
#define GAME_FPS_CAP 16

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
    PHASE_SHOW_STATS
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
#endif //GAME_H
