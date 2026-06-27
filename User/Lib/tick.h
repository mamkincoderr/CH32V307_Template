/******************************************************************************
 * @file     tick.h
 * @author   Дима из Одессы (mamkincoderr)
 * @brief    Millisecond tick counter via SysTick
 * @repo     https://github.com/mamkincoderr/CH32V307_Template
 * @license  MIT License — see LICENSE in repository root
 * Copyright (c) 2026 Дима из Одессы
 *****************************************************************************/
#ifndef TICK_H
#define TICK_H

#include <stdint.h>

void     Tick_Init(void);
uint32_t Tick_GetMs(void);
void     Tick_DelayMs(uint32_t ms);

#endif /* TICK_H */
