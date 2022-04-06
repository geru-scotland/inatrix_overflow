//
// Created by Geru on 31/3/22.
//

#ifndef INATRIX_OVERFLOW_TIMER_H
#define INATRIX_OVERFLOW_TIMER_H

extern void _timer_HabilitarIntTempo();
extern void _timer_InhibirIntTempo();
extern void _timer_PonerEnMarchaTempo();
extern void _timer_PararTempo();
extern void _timer_ConfigurarTemporizador(int Latch, int Conf_Tempo);

typedef struct {
    int currentTime; // Tiempo desde que se ejecutó el juego (actualizar en cada tick)
    int latch;
    int interruptionRate;
} TimerData;

extern TimerData timer;

#endif //INATRIX_OVERFLOW_TIMER_H
