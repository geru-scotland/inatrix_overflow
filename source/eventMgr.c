//
// Created by Geru on 2/4/22.
//

#include "../include/eventMgr.h"
#include "../include/timer.h"
#include "../include/backgrounds.h"
#include "../include/sprites.h"
#include "nds.h"
#include "../include/game.h"
#include "../include/matrix.h"

Event* eventList[MAX_EVENTS];

int numEvents;
// Test
int pi = 3;
int pj = 3;
#ifdef DEBUG_MODE
int lineDelete = 8;
int lineAdd = 0;
#endif
void eventMgr_InitEventSystem(){
    numEvents = 0;
}

/**
 * Reorganizar el array en base al evento borrado
 * Liberar memoria del puntero al evento.
 * @param event puntero al evento.
 */
void eventMgr_DeleteEvent(Event *event){
    uint8 i = event->pos;

#ifdef DEBUG_MODE
    iprintf("\x1b[%i;00H [DEL] NE: %i e.pos: %i - e.id: %i", lineDelete, numEvents, event->pos, event->id);
    lineDelete += 1;
#endif // DEBUG_MODE

    while ((i < numEvents) && (eventList[i] != NULL))
    {
        eventList[i] = eventList[i+1];
        eventList[i]->pos = i;
        i++;
    }

    free(event);
    numEvents--;
#ifdef DEBUG_MODE
    iprintf("\x1b[%i;00H [ARRAY] ={%i, %i, %i, %i}", lineDelete+6, eventList[0]->id, eventList[1]->id,eventList[2]->id,eventList[3]->id);
    lineDelete += 1;
#endif // DEBUG_MODE
}

/**
 *
 * @param event
 */
void eventMgr_AddEvent(Event *event){
    if(numEvents < MAX_EVENTS)
    {
        eventList[numEvents] = event;
        event->pos = numEvents;
        numEvents++;
#ifdef DEBUG_MODE
        iprintf("\x1b[%i;00H [ADD] NE: %i e.pos: %i - e.id: %i", lineAdd, numEvents, event->pos, event->id);
        lineAdd += 1;
#endif // DEBUG_MODE
    }
}

/**
 * Función "Pública".
 * Llamar a éste desde fuera. eventMgr_AddEvent se gestiona de manera privada
 * o interna del eventMgr.
 * @param eventId
 * @param time
 * @return
 */
void eventMgr_ScheduleEvent(uint8 eventId, int time){
    /*
     * Geru: Reservo memoria dinámica en el heap, porque el stack se vacía
     * Una vez terminado el scope de la función, y queremos que persistan.
     * Importante liberar la memoria reservada correspondiente a cada evento.
     */
    if(numEvents < MAX_EVENTS) {
        Event* e = malloc(sizeof(Event));
        e->id = eventId;
        e->execTime = timer.time + time;
        eventMgr_AddEvent(e);
    }
}

/**
 *
 */
void eventMgr_UpdateScheduledEvents(){
    if(numEvents == 0)
        return;
    for (int i = 0; i < numEvents; i++)
    {
        if(eventList[i]->execTime <= timer.time)
        {
            switch(eventList[i]->id)
            {
                /*
                *********************
                *********************
                ******* INTRO *******
                *********************
                *********************
                */
                case EVENT_INTRO_START:
                    iprintf("\x1b[09;10H _");
                    iprintf("\x1b[10;00H Wake up, Inatrix...");
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_INTRO_TEXT1, IN_4_SECONDS);
                    break;
                case EVENT_INTRO_TEXT1:
                    iprintf("\x1b[10;00H The Matrix has you...");
                    matrix_displayMatrix(true);
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_DROP_BITBLOCK, IN_5_SECONDS);
                    break;
                /*case EVENT_INTRO_TEXT2:
                    iprintf("\x1b[10;00H Follow the white rabbit.");
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);
                    break;
                case EVENT_INTRO_TEXT3:
                    iprintf("\x1b[09;15H _");
                    iprintf("\x1b[10;00H Knock, knock, Inatrix.");
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_INTRO_TEXT4, IN_4_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_INTRO_SETBACKGROUND2, IN_3_SECONDS);
                    break;
                case EVENT_INTRO_TEXT4:
                    iprintf("\x1b[10;00H So, what is your choice?");
                    iprintf("\x1b[20;00H Blue - A)");
                    iprintf("\x1b[20;20H Red - B)");
                    eventMgr_ScheduleEvent(EVENT_INTRO_SHOW_CAPSULES, IN_2_SECONDS);
                    break;
                case EVENT_INTRO_TEXT5:
                    iprintf("\x1b[10;00H I see... good choice");
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_2_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_INTRO_FINISH, IN_4_SECONDS);
                    break;
                case EVENT_INTRO_FINISH:
                    iprintf("\x1b[10;00H Or not? haha...");
                    sprites_displaySprite(GFX_CAPSULE_RED, 145, 80, true);
                    gameData.state = GAME_STATE_MENU; // O Game, es un ejemplo.
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);*/
                    break;
                case EVENT_DROP_BITBLOCK:
                    // Test
                    matrix_updatePivot(pi,pj);
                    gameData.phase = PHASE_BITBLOCK_FALLING;
                    //eventMgr_ScheduleEvent(EVENT_DESTROY_MATRIX, IN_7_SECONDS);
                    break;
                case EVENT_REGENERATE_BITBLOCK:
                    matrix_regenerateBitBlock();
                    pi++;
                    pj++;
                    eventMgr_ScheduleEvent(EVENT_DROP_BITBLOCK, IN_8_SECONDS);
                    break;
                /*case EVENT_REGENERATE_MATRIX:
                    //matrix_regenerateMatrix();
                    break;
                case EVENT_DESTROY_MATRIX:
                    gameData.phase = PHASE_DESTROYING_MATRIX;
                    break;
                case EVENT_HIDE_MATRIX:
                    matrix_displayMatrix(false);
                    matrix_displayBitBlockBuffer(true);
                    break;
                case EVENT_INTRO_SHOW_CAPSULES:
                    sprites_displaySprite(GFX_CAPSULE_RED, 95, 80, false);
                    sprites_displaySprite(GFX_CAPSULE_BLUE, 145, 80, false);
                    gameData.phase = PHASE_WAITING_PLAYER_INPUT;
                    break;
                case EVENT_INTRO_CAPSULE_RED:
                    iprintf("\x1b[2J"); // Forzamos un clear console
                    sprites_displaySprite(GFX_CAPSULE_BLUE, 145, 80, true);
                    eventMgr_ScheduleEvent(EVENT_INTRO_TEXT5, IN_2_SECONDS);
                    gameData.phase = PHASE_MOVE_RED_CAPSULE;
                    break;*/
                case EVENT_INTRO_SETBACKGROUND1:
                    background_setBackground(BG_MATRIX);
                    break;
                case EVENT_INTRO_SETBACKGROUND2:
                    background_setBackground(BG_MATRIX2);
                    break;
                case EVENT_CLEAR_CONSOLE:
                    iprintf("\x1b[2J"); // consoleClear();
                    break;
                case EVENT_NEXT_PHASE:
                    gameData.phase = game_getNextPhase();
                    break;
                /*
                *********************
                *********************
                ******* GAME ********
                *********************
                *********************
                */
                default:
                    break;
            }
            eventMgr_DeleteEvent(eventList[i]);
        }
    }
}

/**
 * Una idea simplemente, pensar esto bien
 * Esto sería trigueado por el handler del timer cada vez que
 * se produce una interrupción
 * Son los eventos que van ocurriendo en base al estado, de
 * manera instantánea
 */
void eventMgr_UpdatePhases(){
    if(timer.ticks % 13 != 0)
        return;
    switch(gameData.phase){
        case PHASE_BITBLOCK_FALLING:
            if(!matrix_dropBitBlockEffect()){
                // Si vas a hacer el efecto de spawn desde diferentes posiciones
                // Que se vean como 0,5sec después de que comience a caer el bitblock
                eventMgr_ScheduleEvent(EVENT_REGENERATE_BITBLOCK, IN_1_SECONDS);
                gameData.phase = PHASE_NULL;
            }
            break;
        case PHASE_DESTROYING_MATRIX:
            if(!matrix_destroyMatrixEffect()){
                eventMgr_ScheduleEvent(EVENT_REGENERATE_MATRIX, IN_3_SECONDS);
                gameData.phase = PHASE_NULL;
            }
            break;
        default:
            break;
    }

    oamUpdate(&oamMain);
}
