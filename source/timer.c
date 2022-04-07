//
// Created by Geru on 31/3/22.
//

#include "../include/timer.h"
#include "../include/defines.h"

TimerData timer;

void timer_UpdateTimer()
{
    // Establecemos, 512 ticks - ~1 segundo.
    timer.ticks++;
    iprintf("\x1b[11;00H ticks: %i", timer.ticks);
    if(timer.ticks == TIMER0_FREQ){ //TIMER0_FREQ = 512
        timer.time++; // Seconds++
        timer.ticks = 0;
    }
}

void timer_ConfigureTimer(int latch, int mask)
{
    timer_EnableInterruptions();

    timer.ticks = 0;
    timer.interruptionRate = 0;
    timer.latch = latch;    //latch = 65.536 - (1/(ticks/seg)) * (33.554.432/x); x = bits 1-0 del registro TIMER0_CNT(Ir probando hasta obtener);
    timer.conf = mask;
    timer.time = 0;

    TIMER0_CNT |= timer.conf;
    TIMER0_DAT = timer.latch;
}

void timer_EnableInterruptions(){
    IME = 0;
    IE |= IRQ_TIMER0;   //  |= es un Or bit a bit; IRQ_TIMER0 = BIT(3); Se pone a 1 el bit correspondiente en el registro IE
    IME = 1;
}

void timer_DisableInterruptions(){
    IME = 0;
    IE &= ~IRQ_TIMER0;  //  &= es un And bit a bit; IRQ_TIMER0 = BIT(3); Se pone a 0 el bit correspondiente en el registro IE
    IME = 1;
}

void timer_StartTimer()
{
    TIMER0_CNT |= BIT(7);   //Poner a 1 el bit 7 del registro TIMER0_CNT activa el temporizador
}

void timer_StopTimer()
{
    TIMER0_CNT &= ~BIT(7);  //Poner a 0 el bit 7 del registro TIMERO_CNT desactiva el temporizador
}
