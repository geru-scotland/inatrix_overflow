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
#include "../include/movementMgr.h"
#include "../include/objectMgr.h"
#include "../include/consoleUI.h"

Event* eventList[MAX_EVENTS];

int numEvents;

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
                    eventMgr_ScheduleEvent(EVENT_GAME_START, IN_4_SECONDS);
                    break;
                case EVENT_INTRO_TEXT1:
                    iprintf("\x1b[10;00H The Matrix has you...");
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_INTRO_TEXT2, IN_5_SECONDS);
                    break;
                case EVENT_INTRO_TEXT2:
                    iprintf("\x1b[10;00H Follow the white rabbit.");
                    eventMgr_ScheduleEvent(EVENT_INTRO_TEXT3, IN_5_SECONDS);
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
                    iprintf("\x1b[20;00H Blue - Normal");
                    iprintf("\x1b[20;18H Red - Hard");
                    eventMgr_ScheduleEvent(EVENT_INTRO_SHOW_CAPSULES, IN_2_SECONDS);
                    break;
                case EVENT_INTRO_SHOW_CAPSULES:
                    objectMgr_spawnCapsules();
                    gameData.phase = PHASE_WAITING_PLAYER_INPUT;
                    break;
                case EVENT_INTRO_CAPSULE_SELECTED:
                    iprintf("\x1b[2J");
                    iprintf("\x1b[10;00H I see... good choice.");
                    objectMgr_manageSelectedCapsule(gameData.mode);
                    gameData.phase = PHASE_MOVE_CAPSULE;
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_2_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_INTRO_FINISH1, IN_4_SECONDS); // Ojo, algo más introductorio rollo into the matrix.
                    break;
                case EVENT_INTRO_FINISH1:
                    iprintf("\x1b[10;00H Or not? haha...");
                    objectMgr_manageSelectedCapsule(gameData.mode == DIFFICULTY_NORMAL_MODE ? GFX_CAPSULE_RED : GFX_CAPSULE_BLUE);
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_INTRO_FINISH2, IN_4_SECONDS);
                    break;
                case EVENT_INTRO_FINISH2:
                    consoleUI_showIntro1();
                    // Hacer algo con fondo.
                    eventMgr_ScheduleEvent(EVENT_GAME_START, IN_4_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_CLEAR_CONSOLE, IN_3_SECONDS);
                    break;
                /*
                *********************
                *********************
                ******* GAME ********
                *********************
                *********************
                */
                case EVENT_GAME_START:
                    gameData.state = GAME_STATE_GAME;
                    gameData.phase = PHASE_WAITING_PLAYER_INPUT;
                    matrix_displayMatrix(true);
                    objectMgr_spawnInatrix();
                    consoleUI_showIntro2();
                    eventMgr_ScheduleEvent(EVENT_GAME_START_DEST_MATRIX, IN_5_SECONDS);
                    eventMgr_ScheduleEvent(EVENT_GAME_UI_SHOW_BASE, IN_5_SECONDS);
                    break;
                case EVENT_GAME_START_DEST_MATRIX:
                    game_enableDestroyMatrix();
                    eventMgr_ScheduleEvent(EVENT_GAME_DESTROY_MATRIX_CHECK, IN_1_SECONDS);
                    break;
                case EVENT_GAME_DESTROY_MATRIX_CHECK:
                    if(gameData.destroyMatrixActive){
                        gameData.destroyMatrixTime -= 1;
                        consoleUI_showUI();
                        if(gameData.destroyMatrixTime <= 0){
                            game_setDestroyMatrix(false);
                            eventMgr_ScheduleEvent(EVENT_GAME_DESTROY_MATRIX, NO_WAIT);
                        }
                        eventMgr_ScheduleEvent(EVENT_GAME_DESTROY_MATRIX_CHECK, IN_1_SECONDS);
                    }
                    break;
                case EVENT_GAME_DROP_BITBLOCK:
                    gameData.phase = PHASE_BITBLOCK_FALLING;
                    break;
                case EVENT_GAME_REGENERATE_BITBLOCK:
                    matrix_regenerateBitBlock();
                    game_setDestroyMatrix(true);
                    gameData.phase = PHASE_WAITING_PLAYER_INPUT;
                    eventMgr_ScheduleEvent(EVENT_GAME_DESTROY_MATRIX_CHECK, IN_1_SECONDS);
                    break;
                case EVENT_GAME_HIDE_MATRIX:
                    gameData.phase = PHASE_REGENERATING_MATRIX;
                    matrix_displayMatrix(false);
                    eventMgr_ScheduleEvent(EVENT_GAME_REGENERATE_MATRIX, IN_5_SECONDS);
                    break;
                case EVENT_GAME_REGENERATE_MATRIX:
                    matrix_regenerateMatrix();
                    matrix_displayMatrix(true);
                    game_enableDestroyMatrix();
                    game_setDestroyMatrix(true);
                    game_increaseMatrixRegens();
                    gameData.phase = PHASE_WAITING_PLAYER_INPUT;
                    eventMgr_ScheduleEvent(EVENT_GAME_DESTROY_MATRIX_CHECK, IN_1_SECONDS);
                    break;
                case EVENT_GAME_DESTROY_MATRIX:
                    gameData.phase = PHASE_DESTROYING_MATRIX;
                    break;
                case EVENT_GAME_INATRIX_MOVE_X:
                    movementMgr_movePosition(MOVEMENT_INATRIX_X);
                    objectMgr_setAnimationActive(ANIMATION_BIT_SHAKE, false);
                    gameData.phase = PHASE_MOVE_INATRIX_X;
                    break;
                case EVENT_GAME_INATRIX_MOVE_Y:
                    movementMgr_movePosition(MOVEMENT_INATRIX_Y);
                    objectMgr_setAnimationActive(ANIMATION_BIT_SHAKE, false);
                    gameData.phase = PHASE_MOVE_INATRIX_Y;
                    break;
                case EVENT_GAME_EVALUATE_BITBLOCK:
                    objectMgr_setAnimationActive(ANIMATION_BIT_SHAKE, false);
                    bool ovf = matrix_evalBitBlockOverflow();
                    game_manageScore(ovf);
                    if(ovf){
                        game_setDestroyMatrix(false);
                        consoleUI_showOverflow();
                        eventMgr_ScheduleEvent(EVENT_GAME_UI_SHOW_BASE, IN_4_SECONDS);
                    }else{
                        game_setDestroyMatrix(false);
                        consoleUI_showFail();
                        eventMgr_ScheduleEvent(EVENT_GAME_UI_SHOW_BASE, IN_4_SECONDS);
                    }
                    eventMgr_ScheduleEvent(EVENT_GAME_DROP_BITBLOCK, IN_2_SECONDS);
                    break;
                case EVENT_GAME_UI_SHOW_BASE:
                    game_setDestroyMatrix(true);
                    consoleUI_showUI();
                    break;
                case EVENT_INTRO_SETBACKGROUND1:
                    background_setBackground(BG_MATRIX);
                    break;
                case EVENT_INTRO_SETBACKGROUND2:
                    background_setBackground(BG_MATRIX2);
                    break;
                case EVENT_CLEAR_CONSOLE:
                    iprintf("\x1b[2J");
                    break;
                case EVENT_NEXT_PHASE:
                    gameData.phase = game_getNextPhase();
                    break;
                case EVENT_GAME_OVER:
                    consoleUI_showGameOver();
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
void eventMgr_UpdatePhases(){
    if(timer.ticks % 15 != 0)
        return;
    switch(gameData.phase){
        case PHASE_BITBLOCK_FALLING:
            if(!matrix_dropBitBlockEffect()){
                // Si vas a hacer el efecto de spawn desde diferentes posiciones
                // Que se vean como 0,5sec después de que comience a caer el bitblock
                eventMgr_ScheduleEvent(EVENT_GAME_REGENERATE_BITBLOCK, IN_1_SECONDS);
                gameData.phase = PHASE_NULL;
            }
            break;
        case PHASE_DESTROYING_MATRIX:
            if(!matrix_destroyMatrixEffect()){
                eventMgr_ScheduleEvent(EVENT_GAME_REGENERATE_MATRIX, IN_3_SECONDS);
                gameData.phase = PHASE_NULL;
            }
            break;
        case PHASE_MOVE_INATRIX_X:
            if(movementMgr_nextPositionReached(MOVEMENT_INATRIX_X)){
                matrix_updatePivot(movementMgr_getPositionY(), movementMgr_getPositionX());
                objectMgr_setAnimationActive(ANIMATION_BIT_SHAKE, true);
                gameData.phase = PHASE_WAITING_PLAYER_INPUT;
            }
            break;
        case PHASE_MOVE_INATRIX_Y:
            if(movementMgr_nextPositionReached(MOVEMENT_INATRIX_Y)){
                matrix_updatePivot(movementMgr_getPositionY(), movementMgr_getPositionX());
                objectMgr_setAnimationActive(ANIMATION_BIT_SHAKE, true);
                gameData.phase = PHASE_WAITING_PLAYER_INPUT;
            }
            break;
        case PHASE_MOVE_CAPSULE: // Hacer con objectMgr y para ambas cápsulas
            if(movementMgr_hasGfxReachedDest(
                    gameData.mode == DIFFICULTY_NORMAL_MODE ? GFX_CAPSULE_BLUE : GFX_CAPSULE_RED)){
                gameData.phase = PHASE_NULL;
            }
            break;
        default:
            break;
    }

    oamUpdate(&oamMain);
}

void eventMgr_UpdateAnimations(){
    if(timer.ticks % 3 != 0)
        return;

    // Comprobar si hay animaciones activas
    for(int anim = 0; anim < ANIMATIONS_SIZE; anim++){
        if(animations[anim]->active){
            switch(anim){
                case ANIMATION_BIT_SHAKE:
                    animations[anim]->state *= -1;
                    matrix_bitShakeEffect(animations[anim]->state);
                    break;
            }
        }
    }
}