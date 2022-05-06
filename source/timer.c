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
 *
 * Github: https://github.com/Geru-Scotland/inatrix_overflow
 */

/**
 * @author Geru-Scotland.
 * @file timer.c
 * @brief Gestión y configuración parcial del timer.
 */

#include "timer.h"
#include "defines.h"
#include "eventMgr.h"

TimerData timer;

/**
 * @brief Configurara el timer.
 * Latch = 65.536 - (1/(ticks/seg)) * (33.554.432/x);
 * x = bits 1-0 del registro TIMER0_CNT (Ir probando hasta obtener);
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

/**
 * @brief Invocada por la rutina de atención del timer.
 * Establecemos, 512 ticks - ~1 segundo.
 */
void timer_UpdateTimer()
{
    timer.ticks++;
    timer.totalTicks++;
    eventMgr_UpdateScheduledEvents();
    eventMgr_UpdateAnimations();
    if(timer.ticks == TIMER0_FREQ){
        timer.time++; // Seconds++
        timer.ticks = 0;
    }
}

/**
 * @brief Habilitar interrupciones para el timer.
 */
void timer_EnableInterruptions(){
    IME = 0;
    IE |= IRQ_TIMER0;
    IME = 1;
}

/**
 * @brief Deshabilitar interrupciones para el timer.
 */
void timer_DisableInterruptions(){
    IME = 0;
    IE &= ~IRQ_TIMER0;
    IME = 1;
}

/**
 * @brief Iniciar timer.
 * Poner a 1 el bit 7 del registro TIMER0_CNT activa el temporizador
 */
void timer_StartTimer()
{
    TIMER0_CNT |= BIT(7);
}

/**
 * @brief Desactivar el temporizador.
 * Poner a 0 el bit 7 del registro TIMERO_CNT desactiva el temporizador
 */
void timer_StopTimer()
{
    TIMER0_CNT &= ~BIT(7);
}

/**
 * @brief Función auxiliar para saber el número de ticks de diferencia
 * entre dos momentos distinto.s
 * @param ticks
 * @return true si ha pasado - false en caso contrario.
 */
bool timer_TicksHavePassed(int total, int prev){
    return (total <= prev) ? true : false;
}