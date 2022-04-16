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

typedef enum {
    PHASE_NULL = 0,
    /* INTRO */
    PHASE_INTRO_START,
    PHASE_INTRO_WAITING,

    /* MENU */
    /* GAME */
} Phases;

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
} GameData;

extern GameData gameData;

extern int game_getNextPhase();