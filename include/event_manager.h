//
// Created by Geru on 2/4/22.
//

#ifndef INATRIX_OVERFLOW_EVENT_MANAGER_H
#define INATRIX_OVERFLOW_EVENT_MANAGER_H

#include "defines.h"

enum States {
    // States temporales.
    // Quitar una vez entregada segunda actividad.
    WAIT = 0,
    CLOSED,
    OPEN,

    // States reales del juego.
    STATE_INTRO,
    STATE_MENU,
    STATE_GAME,
    STATE_PAUSE,
    STATE_GAME_OVER,
    STATE_STATS,
    STATE_SURRENDER
};

enum Events{
    // Eventos Iniciales, ejemplos.
    EVENT_NEXT_PHASE = 0,
    EVENT_NEXT_STATE,
    EVENT_ADD_POINT,
    EVENT_EXPLODE_BIT_BLOCK,
    EVENT_REGENERATE_MATRIX
};

typedef struct {
    int id;
    int execTime;
} Event;

extern Event* eventList[MAX_EVENTS];

//Funciones de Event Manager
void updateEvents();
bool addEvent(Event *event);
bool executeEvent(Event *event);


#endif //INATRIX_OVERFLOW_EVENT_MANAGER_H
