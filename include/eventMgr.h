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
    IN_20_SECONDS = 20,
};

enum Events{
    EVENT_START_INTRO,
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
