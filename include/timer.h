/*
 * This file is part of the Iñatrix Overflow Project.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file timer.h
 */

#ifndef INATRIX_OVERFLOW_TIMER_H
#define INATRIX_OVERFLOW_TIMER_H
#include <stdint.h>
#include <stdbool.h>

#define TIMER0_CNT  (*(vuint16*)0x04000102)
#define TIMER0_DAT  (*(vuint16*)0x04000100)

#define TIMER0_FREQ 512
#define EVENT_FREQ 100

/**
 * @struct TimerData
 * @brief Estructura que contiene datos útiles relacionados al timer.
 * @var ticks: Contador de ticks, ayudará a determinar cuando ha transcurrido un segundo
 * @var time: tiempo en segundos desde que se ejecutó la aplicación
 * @var latch: latch para configurar el timer
 * @var conf: para configurar el timer
 * @var totalTicks: ticks totales desde que se ejecutó la aplicación.
 * @todo: totalTicks, hacer uint64 para que no haya overflow.
 */
typedef struct {
    int ticks;
    int time;
    int latch;
    int conf;
    int totalTicks;
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
