//
// Created by Geru on 2/4/22.
//

#ifndef EVENTMGR_H
#define EVENTMGR_H

#include "defines.h"

#define MAX_EVENTS 20

enum TimeMarks {
    NO_WAIT      = 0,
    IN_1_SECONDS = 1,
    IN_2_SECONDS = 2,
    IN_3_SECONDS = 3,
    IN_4_SECONDS = 4,
    IN_5_SECONDS = 5,
    IN_7_SECONDS = 7,
    IN_8_SECONDS = 8,
    IN_10_SECONDS = 10,
    IN_20_SECONDS = 20,
};

enum Events{
    EVENT_INTRO_START = 0,
    EVENT_INTRO_TEXT1,
    EVENT_INTRO_TEXT2,
    EVENT_INTRO_TEXT3,
    EVENT_INTRO_TEXT4,
    EVENT_INTRO_TEXT5,
    EVENT_INTRO_SHOW_CAPSULES,
    EVENT_INTRO_CAPSULE_RED,
    EVENT_INTRO_CAPSULE_BLUE,
    EVENT_INTRO_SETBACKGROUND1,
    EVENT_INTRO_SETBACKGROUND2,
    EVENT_INTRO_FINISH,
    EVENT_GAME_START,
    EVENT_GAME_DROP_BITBLOCK,
    EVENT_GAME_HIDE_MATRIX,
    EVENT_GAME_DESTROY_MATRIX,
    EVENT_GAME_REGENERATE_BITBLOCK,
    EVENT_GAME_REGENERATE_MATRIX,
    EVENT_GAME_INATRIX_MOVE_X,
    EVENT_GAME_INATRIX_MOVE_Y,
    EVENT_NEXT_PHASE,
    /*
     * No correspondiente a ningún evento en concreto
     */
    EVENT_CLEAR_CONSOLE
};

typedef struct {
    uint8 id;
    int execTime;
    uint8 pos;
} Event;

extern Event* eventList[MAX_EVENTS];
extern int numEvents;
extern int it, jt;
//Funciones de Event Manager
extern void eventMgr_InitEventSystem();
extern void eventMgr_UpdateScheduledEvents();
extern void eventMgr_AddEvent(Event *event);
extern void eventMgr_ScheduleEvent(uint8 eventId, int time);
extern void eventMgr_DeleteEvent(Event* event);
extern void eventMgr_UpdatePhases();

#endif //EVENTMGR_H
