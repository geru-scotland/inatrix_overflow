//
// Created by Geru on 2/4/22.
//

#ifndef EVENTMGR_H_
#define EVENTMGR_H_

#include "defines.h"

#define MAX_EVENTS 20

enum TimeMarks {
    IN_1_SECOND = 1,
    IN_2_SECONDS = 2,
    IN_3_SECONDS = 3,
    IN_5_SECONDS = 5,
    IN_10_SECONDS = 10,
    IN_20_SECONDS = 20,
};

enum Events{
    EVENT_INTRO_START = 0,
    EVENT_INTRO_TEXT2,
    EVENT_INTRO_TEXT3,
    EVENT_INTRO_SETBACKGROUND1,
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
//Funciones de Event Manager
extern void eventMgr_InitEventSystem();
extern void eventMgr_UpdateScheduledEvents();
extern void eventMgr_AddEvent(Event *event);
extern void eventMgr_ScheduleEvent(uint8 eventId, int time);
extern void eventMgr_DeleteEvent(Event* event);
extern void eventMgr_UpdateInstantEvents();

#endif //EVENTMGR_H_
