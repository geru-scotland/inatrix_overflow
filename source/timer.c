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
    if(timer.ticks == TIMER0_FREQ){
        timer.time++; // Seconds++
        timer.ticks = 0;
    }
}

void timer_ConfigureTimer(int latch, int mask)
{
    timer_EnableInterruptions();

    timer.ticks = 0;
    timer.interruptionRate = 0;
    timer.latch = latch;
    timer.conf = mask;
    timer.time = 0;

    TIMER0_CNT |= timer.conf;
    TIMER0_DAT = timer.latch;
}

void timer_EnableInterruptions(){
    IME = 0;
    IE |= IRQ_TIMER0;
    IME = 1;
}

void timer_DisableInterruptions(){
    IME = 0;
    IE &= ~IRQ_TIMER0;
    IME = 1;
}

void timer_StartTimer()
{
    TIMER0_CNT |= BIT(7);
}

void timer_StopTimer()
{
    TIMER0_CNT &= ~BIT(7);
}
