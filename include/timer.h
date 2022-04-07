//
// Created by Geru on 31/3/22.
//

#ifndef INATRIX_OVERFLOW_TIMER_H
#define INATRIX_OVERFLOW_TIMER_H

#define TIMER0_CNT  (*(vuint16*)0x04000102)
#define TIMER0_DAT  (*(vuint16*)0x04000100)

#define TIMER0_FREQ 512

extern void timer_UpdateTimer();
extern void timer_ConfigureTimer(int latch, int conf_Tempo);

extern void timer_StartTimer();
extern void timer_StopTimer();

typedef struct {
    int ticks; // Temp
    int time; // Tiempo desde que se ejecutó el juego (actualizar en cada tick)
    int latch;
    int conf;
    int interruptionRate;
} TimerData;

extern TimerData timer;

#endif //INATRIX_OVERFLOW_TIMER_H
