//
// Created by Eideann on 31/3/22.
//

#ifndef INATRIX_OVERFLOW_TIMER_H
#define INATRIX_OVERFLOW_TIMER_H
extern void HabilitarIntTempo();
extern void InhibirIntTempo();
extern void PonerEnMarchaTempo();
extern void PararTempo();
extern void ConfigurarTemporizador(int Latch, int Conf_Tempo);

typedef struct {
    int currentTime; // Tiempo desde que se ejecutó el juego (actualizar en cada tick)
    int latch;
    int interruptions;
} TimerData;

extern TimerData timer;

#endif //INATRIX_OVERFLOW_TIMER_H
