//
// Created by Geru on 31/3/22.
//

#include "../include/timer.h"
#include "../include/defines.h"

TimerData timer;

void timer_UpdateTimer(){
    // Establecemos, 512 ticks - 1 segundo.
    timer.ticks++;
    if(timer.ticks >= TIMER0_FREQ){
        timer.time++; // Seconds++
    }
}

void timer_ConfigureTimer(int latch, int conf)
{
    TIMER0_DAT = 0;
    timer.ticks = 0;
    timer.ticks = 0;
    timer.interruptionRate = 0;
    timer.latch = latch;
    timer.conf = conf;
}

void timer_StartTimer()
{
    IME = 0;
    TIMER0_CNT |= timer.conf;
    IME = 1;
}

void timer_StopTimer()
{
    IME = 0;
    TIMER0_CNT &= ~timer.conf;
    IME = 1;
}
