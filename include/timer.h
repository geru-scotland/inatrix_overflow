//
// Created by Geru on 31/3/22.
//

#ifndef INATRIX_OVERFLOW_TIMER_H
#define INATRIX_OVERFLOW_TIMER_H
#include <stdint.h>
#include <stdbool.h>

#define TIMER0_CNT  (*(vuint16*)0x04000102)
#define TIMER0_DAT  (*(vuint16*)0x04000100)

#define TIMER0_FREQ 512
#define EVENT_FREQ 100

typedef struct {
    int ticks; // Temp
    int time; // Tiempo en segundos desde que se ejecutó el juego (actualizar en cada tick)
    int latch;
    int conf;
    int totalTicks; // Geru: Cambiar nombres de variables, estoy cansado.
} TimerData;

extern void timer_UpdateTimer();
extern void timer_ConfigureTimer(int latch, int mask);

void timer_EnableInterruptions();
void timer_DisableInterruptions();

extern void timer_StartTimer();
extern void timer_StopTimer();
extern bool timer_TicksHavePassed(int total, int prev);

extern TimerData timer;

#endif //INATRIX_OVERFLOW_TIMER_H
