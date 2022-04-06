//
// Created by Geru on 31/3/22.
//

#ifndef INATRIX_OVERFLOW_TIMER_H
#define INATRIX_OVERFLOW_TIMER_H

extern void timer_UpdateTimer();
extern void timer_HabilitarIntTempo();
extern void timer_InhibirIntTempo();
extern void timer_PonerEnMarchaTempo();
extern void timer_PararTempo();
extern void timer_ConfigureTimer(int Latch, int Conf_Tempo);

typedef struct {
    int currentTime; // Tiempo desde que se ejecutó el juego (actualizar en cada tick)
    int latch;
    int interruptionRate;
} TimerData;

extern TimerData timer;

#endif //INATRIX_OVERFLOW_TIMER_H
