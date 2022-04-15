/*---------------------------------------------------------------------------------
game.h
---------------------------------------------------------------------------------*/

#define GAME_FPS_CAP 1600

void game_Loop();
void game_Update();


enum States {
    // Estados generales del juego
    GAME_STATE_INTRO,
    GAME_STATE_MENU,
    GAME_STATE_GAME,
    GAME_STATE_PAUSE,
    GAME_STATE_GAME_OVER,
    GAME_STATE_STATS,
    GAME_STATE_SURRENDER,
};

enum Phases{
    PHASE_INTRO_TEXT = 0,
    PHASE_INTRO_WAITING,
};

/*
 * Información general del juego.
 * state: estado actual del juego.
 * */
typedef struct {
    int state;
} GameData;

extern GameData gameData;
