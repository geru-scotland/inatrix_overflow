//
// Created by Geru on 31/3/22.
//

#include "../include/timer.h"
#include "../include/defines.h"
#include "../include/eventMgr.h"

TimerData timer;

/**
 * Configurar el timer.
 * //latch = 65.536 - (1/(ticks/seg)) * (33.554.432/x);
 * x = bits 1-0 del registro TIMER0_CNT(Ir probando hasta obtener);
 *
 * @param latch
 * @param mask
 */
void timer_ConfigureTimer(int latch, int mask)
{
    timer_EnableInterruptions();

    timer.ticks = 0;
    timer.latch = latch;
    timer.conf = mask;
    timer.time = 0;
    timer.totalTicks = 0;

    TIMER0_CNT |= 0x00C0 | timer.conf;
    TIMER0_DAT |= timer.latch;
    timer_StartTimer();
}

void timer_UpdateTimer()
{
    /*
     * Establecemos, 512 ticks - ~1 segundo.
     */
    timer.ticks++;
    timer.totalTicks++;
    eventMgr_UpdateScheduledEvents();
    if(timer.ticks == TIMER0_FREQ){
        timer.time++; // Seconds++
        timer.ticks = 0;
        /*
         * Como no es un segundo exacto, variará
         * TODO: Hacer esto de otra manera, que sea llamado
         * Desde el bucle principal cada X ms
         */
    }
}

/**
 * |= es un Or bit a bit; IRQ_TIMER0 = BIT(3);
 * Se pone a 1 el bit correspondiente en el registro IE
 */
void timer_EnableInterruptions(){
    IME = 0;
    IE |= IRQ_TIMER0;
    IME = 1;
}

/**
 * &= es un And bit a bit; IRQ_TIMER0 = BIT(3);
 * Se pone a 0 el bit correspondiente en el registro IE
 */
void timer_DisableInterruptions(){
    IME = 0;
    IE &= ~IRQ_TIMER0;
    IME = 1;
}

/**
 * Poner a 1 el bit 7 del registro TIMER0_CNT activa el temporizador
 */
void timer_StartTimer()
{
    TIMER0_CNT |= BIT(7);
}

/**
 * Poner a 0 el bit 7 del registro TIMERO_CNT desactiva el temporizador
 */
void timer_StopTimer()
{
    TIMER0_CNT &= ~BIT(7);
}

/**
 *
 * @param ticks
 * @return
 */
bool timer_TicksHavePassed(int total, int prev){
    return (total <= prev) ? true : false;
}