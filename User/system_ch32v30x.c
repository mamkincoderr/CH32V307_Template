/********************************** (C) COPYRIGHT *******************************
* File Name          : system_ch32v30x.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2024/03/05
* Description        : CH32V30x Device Peripheral Access Layer System Source File.
*                      For HSE = 8Mhz
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/
#include "ch32v30x.h"

/*
* Uncomment the line corresponding to the desired System clock (SYSCLK) frequency (after
* reset the HSI is used as SYSCLK source).
* If none of the define below is enabled, the HSI is used as System clock source.
*/
//#define SYSCLK_FREQ_HSE    HSE_VALUE
//#define SYSCLK_FREQ_48MHz_HSE  48000000
//#define SYSCLK_FREQ_56MHz_HSE  56000000
//#define SYSCLK_FREQ_72MHz_HSE  72000000
//#define SYSCLK_FREQ_96MHz_HSE  96000000
//#define SYSCLK_FREQ_120MHz_HSE  120000000
#define SYSCLK_FREQ_144MHz_HSE  144000000
//#define SYSCLK_FREQ_HSI    HSI_VALUE
//#define SYSCLK_FREQ_48MHz_HSI  48000000
//#define SYSCLK_FREQ_56MHz_HSI  56000000
//#define SYSCLK_FREQ_72MHz_HSI  72000000
//#define SYSCLK_FREQ_96MHz_HSI  96000000
//#define SYSCLK_FREQ_120MHz_HSI  120000000
//#define SYSCLK_FREQ_144MHz_HSI  144000000

/* Clock Definitions */
#ifdef SYSCLK_FREQ_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;
#elif defined SYSCLK_FREQ_48MHz_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_48MHz_HSE;
#elif defined SYSCLK_FREQ_56MHz_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_56MHz_HSE;
#elif defined SYSCLK_FREQ_72MHz_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_72MHz_HSE;
#elif defined SYSCLK_FREQ_96MHz_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_96MHz_HSE;
#elif defined SYSCLK_FREQ_120MHz_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_120MHz_HSE;
#elif defined SYSCLK_FREQ_144MHz_HSE
uint32_t SystemCoreClock         = SYSCLK_FREQ_144MHz_HSE;
#elif defined SYSCLK_FREQ_48MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_48MHz_HSI;
#elif defined SYSCLK_FREQ_56MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_56MHz_HSI;
#elif defined SYSCLK_FREQ_72MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_72MHz_HSI;
#elif defined SYSCLK_FREQ_96MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_96MHz_HSI;
#elif defined SYSCLK_FREQ_120MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_120MHz_HSI;
#elif defined SYSCLK_FREQ_144MHz_HSI
uint32_t SystemCoreClock         = SYSCLK_FREQ_144MHz_HSI;
#else
uint32_t SystemCoreClock         = HSI_VALUE;
#endif

__I uint8_t AHBPrescTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};

/* system_private_function_proto_types */
static void SetSysClock(void);

#ifdef SYSCLK_FREQ_HSE
static void SetSysClockToHSE( void );
#elif defined SYSCLK_FREQ_48MHz_HSE
static void SetSysClockTo48_HSE( void );
#elif defined SYSCLK_FREQ_56MHz_HSE
static void SetSysClockTo56_HSE( void );
#elif defined SYSCLK_FREQ_72MHz_HSE
static void SetSysClockTo72_HSE( void );
#elif defined SYSCLK_FREQ_96MHz_HSE
static void SetSysClockTo96_HSE( void );
#elif defined SYSCLK_FREQ_120MHz_HSE
static void SetSysClockTo120_HSE( void );
#elif defined SYSCLK_FREQ_144MHz_HSE
static void SetSysClockTo144_HSE( void );
#elif defined SYSCLK_FREQ_48MHz_HSI
static void SetSysClockTo48_HSI( void );
#elif defined SYSCLK_FREQ_56MHz_HSI
static void SetSysClockTo56_HSI( void );
#elif defined SYSCLK_FREQ_72MHz_HSI
static void SetSysClockTo72_HSI( void );
#elif defined SYSCLK_FREQ_96MHz_HSI
static void SetSysClockTo96_HSI( void );
#elif defined SYSCLK_FREQ_120MHz_HSI
static void SetSysClockTo120_HSI( void );
#elif defined SYSCLK_FREQ_144MHz_HSI
static void SetSysClockTo144_HSI( void );
#endif

void SystemInit (void)
{
    RCC->CTLR |= (uint32_t)0x00000001;
    RCC->CFGR0 &= (uint32_t)0xF0FF0000;
    RCC->CTLR &= (uint32_t)0xFEF6FFFF;
    RCC->CTLR &= (uint32_t)0xFFFBFFFF;
    RCC->CFGR0 &= (uint32_t)0xFF00FFFF;

#ifdef CH32V30x_D8C
    RCC->CTLR &= (uint32_t)0xEBFFFFFF;
    RCC->INTR = 0x00FF0000;
    RCC->CFGR2 = 0x00000000;
#else
    RCC->INTR = 0x009F0000;
#endif
    SetSysClock();
}

void SystemCoreClockUpdate (void)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0;
    uint8_t Pll_6_5 = 0;

#ifdef CH32V30x_D8C
    uint8_t Pll2mull = 0;
#endif

    tmp = RCC->CFGR0 & RCC_SWS;

    switch (tmp)
    {
        case 0x00: SystemCoreClock = HSI_VALUE; break;
        case 0x04: SystemCoreClock = HSE_VALUE; break;
        case 0x08:
            pllmull = RCC->CFGR0 & RCC_PLLMULL;
            pllsource = RCC->CFGR0 & RCC_PLLSRC;
            pllmull = ( pllmull >> 18) + 2;
#ifdef CH32V30x_D8
            if(pllmull == 17) pllmull = 18;
#else
            if(pllmull == 2) pllmull = 18;
            if(pllmull == 15){ pllmull = 13; Pll_6_5 = 1; }
            if(pllmull == 16) pllmull = 15;
            if(pllmull == 17) pllmull = 16;
#endif
            if (pllsource == 0x00)
            {
                if(EXTEN->EXTEN_CTR & EXTEN_PLL_HSI_PRE) SystemCoreClock = HSI_VALUE * pllmull;
                else SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
            }
            else
            {
#ifdef CH32V30x_D8
                if ((RCC->CFGR0 & RCC_PLLXTPRE) != (uint32_t)RESET)
                    SystemCoreClock = (HSE_VALUE >> 1) * pllmull;
                else
                    SystemCoreClock = HSE_VALUE * pllmull;
#else
                if(RCC->CFGR2 & (1<<16)){
                    SystemCoreClock = HSE_VALUE/(((RCC->CFGR2 & 0xF0)>>4) + 1);
                    Pll2mull = (uint8_t)((RCC->CFGR2 & 0xF00)>>8);
                    if(Pll2mull == 0) SystemCoreClock = (SystemCoreClock * 5)>>1;
                    else if(Pll2mull == 1) SystemCoreClock = (SystemCoreClock * 25)>>1;
                    else if(Pll2mull == 15) SystemCoreClock = SystemCoreClock * 20;
                    else  SystemCoreClock = SystemCoreClock * (Pll2mull + 2);
                    SystemCoreClock = SystemCoreClock/((RCC->CFGR2 & 0xF) + 1);
                }
                else{
                    SystemCoreClock = HSE_VALUE/((RCC->CFGR2 & 0xF) + 1);
                }
                SystemCoreClock = SystemCoreClock * pllmull;
#endif
            }
            if(Pll_6_5 == 1) SystemCoreClock = (SystemCoreClock / 2);
            break;
        default: SystemCoreClock = HSI_VALUE; break;
    }
    tmp = AHBPrescTable[((RCC->CFGR0 & RCC_HPRE) >> 4)];
    SystemCoreClock >>= tmp;
}

static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
    SetSysClockToHSE();
#elif defined SYSCLK_FREQ_48MHz_HSE
    SetSysClockTo48_HSE();
#elif defined SYSCLK_FREQ_56MHz_HSE
    SetSysClockTo56_HSE();
#elif defined SYSCLK_FREQ_72MHz_HSE
    SetSysClockTo72_HSE();
#elif defined SYSCLK_FREQ_96MHz_HSE
    SetSysClockTo96_HSE();
#elif defined SYSCLK_FREQ_120MHz_HSE
    SetSysClockTo120_HSE();
#elif defined SYSCLK_FREQ_144MHz_HSE
    SetSysClockTo144_HSE();
#elif defined SYSCLK_FREQ_48MHz_HSI
    SetSysClockTo48_HSI();
#elif defined SYSCLK_FREQ_56MHz_HSI
    SetSysClockTo56_HSI();
#elif defined SYSCLK_FREQ_72MHz_HSI
    SetSysClockTo72_HSI();
#elif defined SYSCLK_FREQ_96MHz_HSI
    SetSysClockTo96_HSI();
#elif defined SYSCLK_FREQ_120MHz_HSI
    SetSysClockTo120_HSI();
#elif defined SYSCLK_FREQ_144MHz_HSI
    SetSysClockTo144_HSI();
#endif
}

#ifdef SYSCLK_FREQ_HSE
static void SetSysClockToHSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    RCC->CTLR |= ((uint32_t)RCC_HSEON);
    do { HSEStatus = RCC->CTLR & RCC_HSERDY; StartUpCounter++; }
    while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    if ((RCC->CTLR & RCC_HSERDY) != RESET) HSEStatus = (uint32_t)0x01;
    else HSEStatus = (uint32_t)0x00;
    if (HSEStatus == (uint32_t)0x01)
    {
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV1;
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_HSE;
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x04) {}
    }
}

#elif defined SYSCLK_FREQ_48MHz_HSE
static void SetSysClockTo48_HSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    RCC->CTLR |= ((uint32_t)RCC_HSEON);
    do { HSEStatus = RCC->CTLR & RCC_HSERDY; StartUpCounter++; }
    while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    if ((RCC->CTLR & RCC_HSERDY) != RESET) HSEStatus = (uint32_t)0x01;
    else HSEStatus = (uint32_t)0x00;
    if (HSEStatus == (uint32_t)0x01)
    {
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL6);
#else
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL6_EXTEN);
#endif
        RCC->CTLR |= RCC_PLLON;
        while((RCC->CTLR & RCC_PLLRDY) == 0) {}
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
    }
}

#elif defined SYSCLK_FREQ_72MHz_HSE
static void SetSysClockTo72_HSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    RCC->CTLR |= ((uint32_t)RCC_HSEON);
    do { HSEStatus = RCC->CTLR & RCC_HSERDY; StartUpCounter++; }
    while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    if ((RCC->CTLR & RCC_HSERDY) != RESET) HSEStatus = (uint32_t)0x01;
    else HSEStatus = (uint32_t)0x00;
    if (HSEStatus == (uint32_t)0x01)
    {
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL9);
#else
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL9_EXTEN);
#endif
        RCC->CTLR |= RCC_PLLON;
        while((RCC->CTLR & RCC_PLLRDY) == 0) {}
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
    }
}

#elif defined SYSCLK_FREQ_96MHz_HSE
static void SetSysClockTo96_HSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    RCC->CTLR |= ((uint32_t)RCC_HSEON);
    do { HSEStatus = RCC->CTLR & RCC_HSERDY; StartUpCounter++; }
    while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    if ((RCC->CTLR & RCC_HSERDY) != RESET) HSEStatus = (uint32_t)0x01;
    else HSEStatus = (uint32_t)0x00;
    if (HSEStatus == (uint32_t)0x01)
    {
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL12);
#else
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL12_EXTEN);
#endif
        RCC->CTLR |= RCC_PLLON;
        while((RCC->CTLR & RCC_PLLRDY) == 0) {}
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
    }
}

#elif defined SYSCLK_FREQ_120MHz_HSE
static void SetSysClockTo120_HSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    RCC->CTLR |= ((uint32_t)RCC_HSEON);
    do { HSEStatus = RCC->CTLR & RCC_HSERDY; StartUpCounter++; }
    while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    if ((RCC->CTLR & RCC_HSERDY) != RESET) HSEStatus = (uint32_t)0x01;
    else HSEStatus = (uint32_t)0x00;
    if (HSEStatus == (uint32_t)0x01)
    {
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL15);
#else
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL15_EXTEN);
#endif
        RCC->CTLR |= RCC_PLLON;
        while((RCC->CTLR & RCC_PLLRDY) == 0) {}
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
    }
}

#elif defined SYSCLK_FREQ_144MHz_HSE
static void SetSysClockTo144_HSE(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
    RCC->CTLR |= ((uint32_t)RCC_HSEON);
    do { HSEStatus = RCC->CTLR & RCC_HSERDY; StartUpCounter++; }
    while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));
    if ((RCC->CTLR & RCC_HSERDY) != RESET) HSEStatus = (uint32_t)0x01;
    else HSEStatus = (uint32_t)0x00;
    if (HSEStatus == (uint32_t)0x01)
    {
        RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
        RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL18);
#else
        RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSE | RCC_PLLXTPRE_HSE | RCC_PLLMULL18_EXTEN);
#endif
        RCC->CTLR |= RCC_PLLON;
        while((RCC->CTLR & RCC_PLLRDY) == 0) {}
        RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
        RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
        while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
    }
}

#elif defined SYSCLK_FREQ_48MHz_HSI
static void SetSysClockTo48_HSI(void)
{
    EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL6);
#else
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL6_EXTEN);
#endif
    RCC->CTLR |= RCC_PLLON;
    while((RCC->CTLR & RCC_PLLRDY) == 0) {}
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
}

#elif defined SYSCLK_FREQ_72MHz_HSI
static void SetSysClockTo72_HSI(void)
{
    EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL9);
#else
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL9_EXTEN);
#endif
    RCC->CTLR |= RCC_PLLON;
    while((RCC->CTLR & RCC_PLLRDY) == 0) {}
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
}

#elif defined SYSCLK_FREQ_96MHz_HSI
static void SetSysClockTo96_HSI(void)
{
    EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL12);
#else
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL12_EXTEN);
#endif
    RCC->CTLR |= RCC_PLLON;
    while((RCC->CTLR & RCC_PLLRDY) == 0) {}
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
}

#elif defined SYSCLK_FREQ_120MHz_HSI
static void SetSysClockTo120_HSI(void)
{
    EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL15);
#else
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL15_EXTEN);
#endif
    RCC->CTLR |= RCC_PLLON;
    while((RCC->CTLR & RCC_PLLRDY) == 0) {}
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
}

#elif defined SYSCLK_FREQ_144MHz_HSI
static void SetSysClockTo144_HSI(void)
{
    EXTEN->EXTEN_CTR |= EXTEN_PLL_HSI_PRE;
    RCC->CFGR0 |= (uint32_t)RCC_HPRE_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE2_DIV1;
    RCC->CFGR0 |= (uint32_t)RCC_PPRE1_DIV2;
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_PLLSRC | RCC_PLLXTPRE | RCC_PLLMULL));
#ifdef CH32V30x_D8
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL18);
#else
    RCC->CFGR0 |= (uint32_t)(RCC_PLLSRC_HSI_Div2 | RCC_PLLMULL18_EXTEN);
#endif
    RCC->CTLR |= RCC_PLLON;
    while((RCC->CTLR & RCC_PLLRDY) == 0) {}
    RCC->CFGR0 &= (uint32_t)((uint32_t)~(RCC_SW));
    RCC->CFGR0 |= (uint32_t)RCC_SW_PLL;
    while ((RCC->CFGR0 & (uint32_t)RCC_SWS) != (uint32_t)0x08) {}
}

#endif