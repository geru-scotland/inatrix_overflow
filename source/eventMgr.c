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
                case EVENT_REGENERATE_MATRIX:
                    break;
                case EVENT_ADD_POINT:
                    break;
                case EVENT_EXPLODE_BIT_BLOCK:
                    break;
                case EVENT_NEXT_STATE:
                    break;
                case EVENT_NEXT_PHASE:
                    break;
                case EVENT_TEST_2ND_ACTIVITY:
                    //Mostrar
                    //sprites_displaySprite(INDEX_BALL, 50, 50, false);
                    //Create ball
                    sprites_displaySprite(INDEX_BALL, 15, 120, false);

                    /* La empezamos a mover de inmediato - pero si quisíeramos
                     * que se empezara a mover en 15 segundos, pues no tendríamos más que
                     * schedulear un evento aquí
                     */
                    data.state = STATE_BALL_MOVING;
                    eventMgr_ScheduleEvent(EVENT_SET_MATRIX_BACKGROUND, IN_5_SECONDS);
                    break;
                case EVENT_OPEN_DOOR:
                    break;
                case EVENT_SET_MATRIX_BACKGROUND:
                    //Test: spawn second ball
                    sprites_displaySprite(INDEX_BALL2, 120, 120, false);
                    background_SetMatrixBackground();
                    eventMgr_ScheduleEvent(EVENT_SET_MATRIX_BACKGROUND2, 1);
                    break;
                case EVENT_SET_MATRIX_BACKGROUND2:
                    background_SetMatrixBackground2();
                    eventMgr_ScheduleEvent(EVENT_SET_MATRIX_BACKGROUND, 1);
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
    if((data.state == STATE_BALL_MOVING) && (timer.ticks % 16 == 0)){

        Sprite* ball1 = sprites[INDEX_BALL];
        if(ball1 && !ball1->spriteEntry->isHidden)
        {
            ball1->spriteEntry->x += 1;
            ball1->spriteEntry->y -= 1;
        }
        Sprite* ball2 = sprites[INDEX_BALL2];
        if(ball2 && !ball2->spriteEntry->isHidden){
            ball2->spriteEntry->x += 1;
            ball2->spriteEntry->y -= 1;
        }
        oamUpdate(&oamMain);
    }
}
