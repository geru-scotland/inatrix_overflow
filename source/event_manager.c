//
// Created by Eideann on 2/4/22.
//

#include "../include/event_manager.h"

Event* eventList[MAX_EVENTS];

void updateEvents(){

}

bool addEvent(Event *event){
    return false;
}

// Si hay algún evento a ejecutar (execTime <= timer.currentTime)
// Devolver y borrar
int getEvent(){
    int id = eventList[0]->id;
    deleteEvent(eventList[0]);
    return id;
}

bool executeEvent(Event *event){
    return false;
}

// En el switch del game, llamar
// a delete event.
// Liberar el puntero al evento
// y borrar del array esa posición
bool deleteEvent(Event *event){
    return false;
}