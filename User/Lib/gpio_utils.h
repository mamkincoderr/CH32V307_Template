/******************************************************************************
 * @file     gpio_utils.h
 * @author   Дима из Одессы (mamkincoderr)
 * @brief    GPIO helper macros for CH32V307
 * @repo     https://github.com/mamkincoderr/CH32V307_Template
 * @license  MIT License — see LICENSE in repository root
 * Copyright (c) 2026 Дима из Одессы
 *****************************************************************************/
#ifndef GPIO_UTILS_H
#define GPIO_UTILS_H

#include "ch32v30x_gpio.h"
#include "ch32v30x_rcc.h"

/* Clock enable helpers */
#define GPIO_CLK_ENABLE(PORT) \
    RCC_APB2PeriphClockCmd( \
        ((PORT) == GPIOA) ? RCC_APB2Periph_GPIOA : \
        ((PORT) == GPIOB) ? RCC_APB2Periph_GPIOB : \
        ((PORT) == GPIOC) ? RCC_APB2Periph_GPIOC : \
        ((PORT) == GPIOD) ? RCC_APB2Periph_GPIOD : \
        ((PORT) == GPIOE) ? RCC_APB2Periph_GPIOE : \
        RCC_APB2Periph_GPIOA, ENABLE)

/* Pin set / reset / toggle */
#define GPIO_SET(PORT, PIN)    ((PORT)->BSHR = (PIN))
#define GPIO_RESET(PORT, PIN)  ((PORT)->BCR  = (PIN))
#define GPIO_TOGGLE(PORT, PIN) ((PORT)->OUTDR ^= (PIN))
#define GPIO_READ(PORT, PIN)   (((PORT)->INDR & (PIN)) != 0)

/* Quick output push-pull init */
static inline void GPIO_InitOutput(GPIO_TypeDef *port, uint16_t pin, GPIOSpeed_TypeDef speed)
{
    GPIO_InitTypeDef cfg;
    GPIO_CLK_ENABLE(port);
    cfg.GPIO_Pin   = pin;
    cfg.GPIO_Mode  = GPIO_Mode_Out_PP;
    cfg.GPIO_Speed = speed;
    GPIO_Init(port, &cfg);
}

/* Quick input with pull-up init */
static inline void GPIO_InitInputPU(GPIO_TypeDef *port, uint16_t pin)
{
    GPIO_InitTypeDef cfg;
    GPIO_CLK_ENABLE(port);
    cfg.GPIO_Pin   = pin;
    cfg.GPIO_Mode  = GPIO_Mode_IPU;
    cfg.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(port, &cfg);
}

#endif /* GPIO_UTILS_H */
