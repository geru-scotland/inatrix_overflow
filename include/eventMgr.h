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
    IN_6_SECONDS = 6,
    IN_7_SECONDS = 7,
    IN_8_SECONDS = 8,
    IN_10_SECONDS = 10,
    IN_20_SECONDS = 20,
};

enum Events{
    /**
     * MENU
     */
    EVENT_MAIN_MENU_START = 0,
    EVENT_MAIN_MENU_HIDE_UI,
    EVENT_MAIN_MENU_SHOW_UI,
    /**
     * INTRO
     */
    EVENT_INTRO_PRE_START,
    EVENT_INTRO_START,
    EVENT_INTRO_TEXT1,
    EVENT_INTRO_TEXT2,
    EVENT_INTRO_TEXT3,
    EVENT_INTRO_TEXT4,
    EVENT_INTRO_TEXT5,
    EVENT_INTRO_SHOW_CAPSULES,
    EVENT_INTRO_CAPSULE_SELECTED,
    EVENT_INTRO_SETBG_MAIN,
    EVENT_INTRO_SETBG_2,
    EVENT_INTRO_SETBG_3,
    EVENT_INTRO_FINISH1,
    EVENT_INTRO_FINISH2,

    /**
     * GAME
     */
    EVENT_GAME_START,
    EVENT_GAME_DROP_BITBLOCK,
    EVENT_GAME_HIDE_MATRIX,
    EVENT_GAME_DESTROY_MATRIX,
    EVENT_GAME_REGENERATE_BITBLOCK,
    EVENT_GAME_REGENERATE_MATRIX,
    EVENT_GAME_INATRIX_MOVE_X,
    EVENT_GAME_INATRIX_MOVE_Y,
    EVENT_GAME_EVALUATE_BITBLOCK,
    EVENT_GAME_START_DEST_MATRIX,
    EVENT_GAME_UI_SHOW_BASE,
    EVENT_GAME_UI_SHOW_OVERFLOW,
    EVENT_GAME_UI_SHOW_FAIL,
    EVENT_GAME_DESTROY_MATRIX_CHECK,
    /**
     * GAME OVER
     */
    EVENT_GAME_OVER,
    EVENT_SHOW_STATS,
    EVENT_RESET, // Reset data y empezar de nuevo.
    //
    EVENT_LISTEN_INPUT,
    EVENT_GAME_PAUSE,
    EVENT_CLEAR_CONSOLE
};

typedef struct {
    uint8 id;
    int execTime;
    uint8 pos;
} Event;

extern Event* eventList[MAX_EVENTS];
extern int numEvents;

extern void eventMgr_InitEventSystem();
extern void eventMgr_UpdateScheduledEvents();
extern void eventMgr_AddEvent(Event *event);
extern void eventMgr_ScheduleEvent(uint8 eventId, int time);
extern void eventMgr_DeleteEvent(Event* event);
extern void eventMgr_UpdatePhases();
extern void eventMgr_UpdateAnimations();
extern void eventMgr_cancelAllEvents();
#endif //EVENTMGR_H
