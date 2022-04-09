/*---------------------------------------------------------------------------------
game.h
---------------------------------------------------------------------------------*/

#define GAME_FPS_CAP 1600

void game_Loop();
void game_Update();

/*
 * Información general del juego.
 * state: estado actual del juego.
 * diff: Tiempo de actualización, diferencia entre el frame actual y el anterior.
 * */
typedef struct {
    int state;
    float diff;
} GameData;

extern GameData data;
