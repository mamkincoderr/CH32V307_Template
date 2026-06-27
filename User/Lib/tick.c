/******************************************************************************
 * @file     tick.c
 * @author   Дима из Одессы (mamkincoderr)
 * @brief    Millisecond tick counter via SysTick
 * @repo     https://github.com/mamkincoderr/CH32V307_Template
 * @license  MIT License — see LICENSE in repository root
 * Copyright (c) 2026 Дима из Одессы
 *****************************************************************************/
#include "tick.h"
#include "ch32v30x.h"

static volatile uint32_t g_tick_ms = 0;

void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void SysTick_Handler(void)
{
    g_tick_ms++;
    SysTick->SR = 0;
}

void Tick_Init(void)
{
    /* 1 ms tick at current SystemCoreClock */
    SysTick->CMP  = SystemCoreClock / 1000 - 1;
    SysTick->CNT  = 0;
    SysTick->SR   = 0;
    SysTick->CTLR = (1 << 0) | /* enable */
                    (1 << 1) | /* STE: reload on match */
                    (1 << 2) | /* STIE: interrupt enable */
                    (1 << 3);  /* STRE: HCLK source */

    NVIC_SetPriority(SysTicK_IRQn, 15);
    NVIC_EnableIRQ(SysTicK_IRQn);
}

uint32_t Tick_GetMs(void)
{
    return g_tick_ms;
}

void Tick_DelayMs(uint32_t ms)
{
    uint32_t start = g_tick_ms;
    while ((g_tick_ms - start) < ms)
        __asm volatile("nop");
}
