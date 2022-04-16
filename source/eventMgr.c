//
// Created by Geru on 2/4/22.
//

#include "../include/eventMgr.h"
#include "../include/timer.h"
#include "../include/backgrounds.h"
#include "../include/sprites.h"
#include "nds.h"
#include "../include/game.h"

Event* eventList[MAX_EVENTS];

SpriteGlobalInfo spriteInfo;
int numEvents;

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
    while ((i < numEvents))
    {
        eventList[i] = eventList[i+1];
        i++;
    }
    free(event);
    numEvents--;
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
     *
     * TODO: Hacer un sistema para evitar duplicados.
     * Quizá un estado OnCooldown para el SheduleEvent.
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
                /**
                 * TODO: Hay un problema con la lista de eventos.
                 * Parece ser que si pongo:
                 * eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);
                 * eventMgr_ScheduleEvent(EVENT_INTRO_TEXT2, IN_5_SECONDS);
                 *
                 * No funciona, será alguna tonteria al eliminar un evento de entre
                 * medias en el array. Crear incidencia en Github.
                 *
                 * Es decir, sólo funciona si lo pongo en ascendente. Estoy ultra cansado
                 * asi que, mirar esto mañana.
                 */

                case EVENT_INTRO_START:
                    iprintf("\x1b[10;00H Wake up, Inatrix...");
                    eventMgr_ScheduleEvent(EVENT_INTRO_TEXT2, IN_5_SECONDS);
                    break;
                case EVENT_INTRO_TEXT2:
                    iprintf("\x1b[2J"); // consoleClear();
                    iprintf("\x1b[10;00H The Matrix has you...");
                    eventMgr_ScheduleEvent(EVENT_INTRO_TEXT3, IN_5_SECONDS);
                    break;
                case EVENT_INTRO_TEXT3:
                    iprintf("\x1b[2J"); // consoleClear();
                    iprintf("\x1b[14;00H Follow the white rabbit.");
                    eventMgr_ScheduleEvent(EVENT_NEXT_PHASE, IN_5_SECONDS);
                    break;
                case EVENT_INTRO_SETBACKGROUND1:
                    background_SetMatrixBackground();
                    break;
                case EVENT_CLEAR_CONSOLE:
                    iprintf("\x1b[2J"); // consoleClear();
                    break;
                case EVENT_NEXT_PHASE:
                    iprintf("\x1b[10;00H NEXT PHASE ");
                    gameData.phase = game_getNextPhase();
                    break;
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
void eventMgr_UpdateInstantEvents(){
    // Pruebas random
    oamUpdate(&oamMain);
}
