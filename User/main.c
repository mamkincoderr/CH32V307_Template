/******************************************************************************
 * @file     main.c
 * @author   Дима из Одессы (mamkincoderr)
 * @brief    CH32V307 Template — точка входа
 * @repo     https://github.com/mamkincoderr/CH32V307_Template
 * @license  MIT License — see LICENSE in repository root
 * Copyright (c) 2026 Дима из Одессы
 *****************************************************************************/
#include "debug.h"
#include "tick.h"
#include "gpio_utils.h"

int main(void)
{
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    Tick_Init();
    USART_Printf_Init(115200);

    printf("CH32V307 Template ready. SysClk=%lu Hz\r\n", (unsigned long)SystemCoreClock);

    while (1)
    {
        Tick_DelayMs(500);
        printf("tick %lu\r\n", Tick_GetMs());
    }
}
