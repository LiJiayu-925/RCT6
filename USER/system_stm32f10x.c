/**
  ******************************************************************************
  * @file    system_stm32f10x.c
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer System Source File.
  *
  *   This file configures the system clock as follows:
  *   - STM32F103RCT6 (High Density)
  *   - HSE = 8MHz external crystal
  *   - PLL x9 => SYSCLK = 72MHz
  *   - AHB  (HCLK)  = 72MHz
  *   - APB1 (PCLK1) = 36MHz
  *   - APB2 (PCLK2) = 72MHz
  *   - Flash latency = 2 wait states
  ******************************************************************************
  */

#include "stm32f10x.h"

/* This variable is updated in two ways:
    1) by calling CMSIS function SystemCoreClockUpdate()
    2) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency */
uint32_t SystemCoreClock = 72000000;

static void SetSysClock(void);

/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit(void)
{
    /* Reset the RCC clock configuration to the default reset state */
    /* Set HSION bit */
    RCC->CR |= RCC_CR_HSION;

    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    RCC->CFGR &= (uint32_t)0xF8FF0000;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLSRC (bit 16), PLLXTPRE (bit 17), PLLMUL (bits 21:18) */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;

    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x009F0000;

    /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
    /* Configure the Flash Latency cycles and enable prefetch buffer */
    SetSysClock();
}

/**
  * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;

    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= RCC_CR_HSEON;

    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != 0)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;

        /* Flash 2 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_2;

        /* HCLK = SYSCLK (AHB prescaler = 1) */
        RCC->CFGR |= (uint32_t)0x00000000;  /* HPRE[3:0] = 0000 => no division */

        /* PCLK2 = HCLK (APB2 prescaler = 1) */
        RCC->CFGR |= (uint32_t)0x00000000;  /* PPRE2[2:0] = 000 => no division */

        /* PCLK1 = HCLK / 2 (APB1 prescaler = 2) */
        RCC->CFGR |= (uint32_t)0x00000400;  /* PPRE1[2:0] = 100 => divide by 2 */

        /* PLL configuration: PLLCLK = HSE * 9 = 72 MHz */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_PLLSRC | RCC_CFGR_PLLXTPRE |
                                            RCC_CFGR_PLLMULL));
        /* PLL source = HSE, PLLMUL = x9 */
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL9);

        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }

        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;

        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL)
        {
        }
    }
    else
    {
        /* If HSE fails to start-up, fall back to HSI at 8MHz */
        /* The application can have error handling here */
        SystemCoreClock = 8000000;
    }
}

/**
  * @brief  Update SystemCoreClock variable according to Clock Register Values.
  *         The SystemCoreClock variable contains the core clock (HCLK), it can
  *         be used by the user application to setup the SysTick timer or configure
  *         other parameters.
  * @param  None
  * @retval None
  */
void SystemCoreClockUpdate(void)
{
    uint32_t tmp = 0, pllmull = 0, pllsource = 0;

    /* Get SYSCLK source */
    tmp = RCC->CFGR & RCC_CFGR_SWS;

    switch (tmp)
    {
        case 0x00:  /* HSI used as system clock */
            SystemCoreClock = HSI_VALUE;
            break;
        case 0x04:  /* HSE used as system clock */
            SystemCoreClock = HSE_VALUE;
            break;
        case 0x08:  /* PLL used as system clock */
            /* Get PLL clock source and multiplication factor */
            pllmull   = RCC->CFGR & RCC_CFGR_PLLMULL;
            pllsource = RCC->CFGR & RCC_CFGR_PLLSRC;
            pllmull   = (pllmull >> 18) + 2;
            if (pllsource == 0x00)
            {
                /* HSI oscillator clock divided by 2 selected as PLL clock entry */
                SystemCoreClock = (HSI_VALUE >> 1) * pllmull;
            }
            else
            {
                /* HSE selected as PLL clock entry */
                if ((RCC->CFGR & RCC_CFGR_PLLXTPRE) != (uint32_t)0)
                {
                    /* HSE oscillator clock divided by 2 */
                    SystemCoreClock = (HSE_VALUE >> 1) * pllmull;
                }
                else
                {
                    SystemCoreClock = HSE_VALUE * pllmull;
                }
            }
            break;
        default:
            SystemCoreClock = HSI_VALUE;
            break;
    }

    /* Compute HCLK clock frequency */
    tmp = (RCC->CFGR & RCC_CFGR_HPRE) >> 4;
    if (tmp >= 8)
    {
        /* AHB prescaler is active: divide by the prescaler value */
        uint32_t ahb_presc_tbl[8] = {2, 4, 8, 16, 64, 128, 256, 512};
        SystemCoreClock /= ahb_presc_tbl[tmp - 8];
    }
}
