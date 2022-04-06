//
// Created by Geru on 2/4/22.
//

#include "../include/eventMgr.h"

Event* eventList[MAX_EVENTS];

void eventMgr_updateEvents(){
}

bool eventMgr_addEvent(Event *event){
    return false;
}

// Si hay algún evento a ejecutar (execTime <= timer.currentTime)
// Devolver y borrar
int eventMgr_getEvent(){
    return NULL;
}

bool eventMgr_executeEvent(Event *event){
    return false;
}

// En el switch del game, llamar
// a delete event.
// Liberar el puntero al evento
// y borrar del array esa posición
bool eventMgr_deleteEvent(Event *event){
    return false;
}