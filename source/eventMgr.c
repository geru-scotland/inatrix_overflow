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
    while ((i < numEvents) && (eventList[i] != NULL))
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
