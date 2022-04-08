//
// Created by Geru on 2/4/22.
//

#ifndef EVENTMGR_H_
#define EVENTMGR_H_

#include "defines.h"

#define MAX_EVENTS 20

enum TimeMarks {
    IN_5_SECONDS = 5,
    IN_10_SECONDS = 10,
    IN_20_SECONDS = 20
};

enum States {
    // States temporales.
    // Quitar una vez entregada segunda actividad.
    WAIT = 0,
    CLOSED,
    OPEN,
    TIMER_TESTS,

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
    EVENT_REGENERATE_MATRIX,
    // Requerido por segunda actividad.
    EVENT_TEST_2ND_ACTIVITY,
    EVENT_OPEN_DOOR,
};

typedef struct {
    uint8 id;
    int execTime;
    uint8 pos;
} Event;

extern Event* eventList[MAX_EVENTS];
extern int numEvents;
//Funciones de Event Manager
extern void eventMgr_InitEventSystem();
extern void eventMgr_UpdateEvents();
extern void eventMgr_AddEvent(Event *event);
extern void eventMgr_ScheduleEvent(uint8 eventId, int time);
extern void eventMgr_DeleteEvent(Event* event);


#endif //EVENTMGR_H_
