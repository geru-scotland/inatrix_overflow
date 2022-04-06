/*---------------------------------------------------------------------------------
game.h
---------------------------------------------------------------------------------*/

void game_Loop();
void game_Update();

/*
 * Información general del juego.
 * state: estado actual del juego.
 * diff: Tiempo de actualización, diferencia entre el frame actual y el anterior.
 * */
typedef struct {
    int state;
    int diff;
} GameData;

extern GameData data;
