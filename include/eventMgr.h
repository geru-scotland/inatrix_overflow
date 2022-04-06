//
// Created by Geru on 2/4/22.
//

#ifndef INATRIX_OVERFLOW_EVENT_MANAGER_H
#define INATRIX_OVERFLOW_EVENT_MANAGER_H

#include "defines.h"

#define MAX_EVENTS 15

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

// Por ahora, sin más. Un array de Eventos
// Y que cuando se borre uno, se muevan todos los demás
// eventList[i] = EventList[i+1]
extern Event* eventList[MAX_EVENTS];

//Funciones de Event Manager
extern void eventMgr_updateEvents();
extern bool eventMgr_addEvent(Event *event);
extern int eventMgr_getEvent();
extern bool eventMgr_executeEvent(Event *event);
extern bool eventMgr_deleteEvent(Event* event);


#endif //INATRIX_OVERFLOW_EVENT_MANAGER_H
