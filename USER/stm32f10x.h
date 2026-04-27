/**
  ******************************************************************************
  * @file    stm32f10x.h
  * @brief   CMSIS Cortex-M3 Device Peripheral Access Layer Header File.
  *          This file contains all the peripheral register's definitions, bits
  *          definitions and memory mapping for STM32F10x Connectivity line,
  *          High density, High density value line, Medium density,
  *          Medium density Value line, Low density, Low density Value line
  *          and XL-density devices.
  *
  *          The file is the unique include file that the application programmer
  *          is using in the C source code, usually in main.c. This file contains:
  *           - Configuration section that allows to select:
  *              - The device used in the target application
  *              - To use or not the peripheral's drivers in application code(i.e.
  *                code will be based on direct access to peripheral's registers
  *                rather than drivers API), this option is controlled by
  *                "#define USE_STDPERIPH_DRIVER"
  *              - To change few application-specific parameters such as the HSE
  *                crystal frequency
  *           - Data structures and the address mapping for all peripherals
  *           - Peripheral's registers declarations and bits definition
  *           - Macros to access peripheral's registers hardware
  *
  ******************************************************************************
  */

#ifndef __STM32F10x_H
#define __STM32F10x_H

#ifdef __cplusplus
 extern "C" {
#endif

/* STM32F103RCT6: High Density device */
#if !defined (STM32F10X_HD)
  #define STM32F10X_HD
#endif

#ifndef HSE_VALUE
  #define HSE_VALUE    ((uint32_t)8000000)  /*!< Value of the External oscillator in Hz */
#endif

#ifndef HSE_STARTUP_TIMEOUT
  #define HSE_STARTUP_TIMEOUT   ((uint16_t)0x0500)   /*!< Time out for HSE start up */
#endif

#ifndef HSI_VALUE
  #define HSI_VALUE    ((uint32_t)8000000)  /*!< Value of the Internal oscillator in Hz */
#endif

#define __CM3_REV                 0x0200  /*!< Core Revision r2p0                        */
#define __MPU_PRESENT             0       /*!< STM32 does not provide a MPU              */
#define __NVIC_PRIO_BITS          4       /*!< STM32 uses 4 Bits for the Priority Levels */
#define __Vendor_SysTickConfig    0       /*!< Set to 1 if different SysTick Config used */

typedef enum IRQn
{
  NonMaskableInt_IRQn         = -14,
  MemoryManagement_IRQn       = -12,
  BusFault_IRQn               = -11,
  UsageFault_IRQn             = -10,
  SVCall_IRQn                 = -5,
  DebugMonitor_IRQn           = -4,
  PendSV_IRQn                 = -2,
  SysTick_IRQn                = -1,
  WWDG_IRQn                   = 0,
  PVD_IRQn                    = 1,
  TAMPER_IRQn                 = 2,
  RTC_IRQn                    = 3,
  FLASH_IRQn                  = 4,
  RCC_IRQn                    = 5,
  EXTI0_IRQn                  = 6,
  EXTI1_IRQn                  = 7,
  EXTI2_IRQn                  = 8,
  EXTI3_IRQn                  = 9,
  EXTI4_IRQn                  = 10,
  DMA1_Channel1_IRQn          = 11,
  DMA1_Channel2_IRQn          = 12,
  DMA1_Channel3_IRQn          = 13,
  DMA1_Channel4_IRQn          = 14,
  DMA1_Channel5_IRQn          = 15,
  DMA1_Channel6_IRQn          = 16,
  DMA1_Channel7_IRQn          = 17,
  ADC1_2_IRQn                 = 18,
  USB_HP_CAN1_TX_IRQn         = 19,
  USB_LP_CAN1_RX0_IRQn        = 20,
  CAN1_RX1_IRQn               = 21,
  CAN1_SCE_IRQn               = 22,
  EXTI9_5_IRQn                = 23,
  TIM1_BRK_IRQn               = 24,
  TIM1_UP_IRQn                = 25,
  TIM1_TRG_COM_IRQn           = 26,
  TIM1_CC_IRQn                = 27,
  TIM2_IRQn                   = 28,
  TIM3_IRQn                   = 29,
  TIM4_IRQn                   = 30,
  I2C1_EV_IRQn                = 31,
  I2C1_ER_IRQn                = 32,
  I2C2_EV_IRQn                = 33,
  I2C2_ER_IRQn                = 34,
  SPI1_IRQn                   = 35,
  SPI2_IRQn                   = 36,
  USART1_IRQn                 = 37,
  USART2_IRQn                 = 38,
  USART3_IRQn                 = 39,
  EXTI15_10_IRQn              = 40,
  RTCAlarm_IRQn               = 41,
  USBWakeUp_IRQn              = 42,
  TIM8_BRK_IRQn               = 43,
  TIM8_UP_IRQn                = 44,
  TIM8_TRG_COM_IRQn           = 45,
  TIM8_CC_IRQn                = 46,
  ADC3_IRQn                   = 47,
  FSMC_IRQn                   = 48,
  SDIO_IRQn                   = 49,
  TIM5_IRQn                   = 50,
  SPI3_IRQn                   = 51,
  UART4_IRQn                  = 52,
  UART5_IRQn                  = 53,
  TIM6_IRQn                   = 54,
  TIM7_IRQn                   = 55,
  DMA2_Channel1_IRQn          = 56,
  DMA2_Channel2_IRQn          = 57,
  DMA2_Channel3_IRQn          = 58,
  DMA2_Channel4_5_IRQn        = 59,
} IRQn_Type;

#include "core_cm3.h"
#include "system_stm32f10x.h"
#include <stdint.h>

#define __IO volatile
#define __I  volatile const
#define __O  volatile

/* ========================= Memory Map ========================= */
#define FLASH_BASE            ((uint32_t)0x08000000)
#define SRAM_BASE             ((uint32_t)0x20000000)
#define PERIPH_BASE           ((uint32_t)0x40000000)

#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x10000)
#define AHBPERIPH_BASE        (PERIPH_BASE + 0x20000)

/* APB1 peripherals */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define TIM3_BASE             (APB1PERIPH_BASE + 0x0400)
#define TIM4_BASE             (APB1PERIPH_BASE + 0x0800)
#define TIM5_BASE             (APB1PERIPH_BASE + 0x0C00)
#define TIM6_BASE             (APB1PERIPH_BASE + 0x1000)
#define TIM7_BASE             (APB1PERIPH_BASE + 0x1400)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)
#define USART3_BASE           (APB1PERIPH_BASE + 0x4800)

/* APB2 peripherals */
#define AFIO_BASE             (APB2PERIPH_BASE + 0x0000)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x0400)
#define GPIOA_BASE            (APB2PERIPH_BASE + 0x0800)
#define GPIOB_BASE            (APB2PERIPH_BASE + 0x0C00)
#define GPIOC_BASE            (APB2PERIPH_BASE + 0x1000)
#define GPIOD_BASE            (APB2PERIPH_BASE + 0x1400)
#define GPIOE_BASE            (APB2PERIPH_BASE + 0x1800)
#define ADC1_BASE             (APB2PERIPH_BASE + 0x2400)
#define ADC2_BASE             (APB2PERIPH_BASE + 0x2800)
#define TIM1_BASE             (APB2PERIPH_BASE + 0x2C00)
#define SPI1_BASE             (APB2PERIPH_BASE + 0x3000)
#define USART1_BASE           (APB2PERIPH_BASE + 0x3800)

/* AHB peripherals */
#define DMA1_BASE             (AHBPERIPH_BASE + 0x0000)
#define DMA1_Channel1_BASE    (AHBPERIPH_BASE + 0x0008)
#define DMA1_Channel2_BASE    (AHBPERIPH_BASE + 0x001C)
#define DMA1_Channel3_BASE    (AHBPERIPH_BASE + 0x0030)
#define DMA1_Channel4_BASE    (AHBPERIPH_BASE + 0x0044)
#define DMA1_Channel5_BASE    (AHBPERIPH_BASE + 0x0058)
#define DMA1_Channel6_BASE    (AHBPERIPH_BASE + 0x006C)
#define DMA1_Channel7_BASE    (AHBPERIPH_BASE + 0x0080)
#define RCC_BASE              (AHBPERIPH_BASE + 0x1000)
#define FLASH_R_BASE          (AHBPERIPH_BASE + 0x2000)

/* ========================= Peripheral Structures ========================= */

typedef struct
{
  __IO uint32_t CRL;
  __IO uint32_t CRH;
  __IO uint32_t IDR;
  __IO uint32_t ODR;
  __IO uint32_t BSRR;
  __IO uint32_t BRR;
  __IO uint32_t LCKR;
} GPIO_TypeDef;

typedef struct
{
  __IO uint32_t EVCR;
  __IO uint32_t MAPR;
  __IO uint32_t EXTICR[4];
  uint32_t      RESERVED0;
  __IO uint32_t MAPR2;
} AFIO_TypeDef;

typedef struct
{
  __IO uint32_t CR;
  __IO uint32_t CFGR;
  __IO uint32_t CIR;
  __IO uint32_t APB2RSTR;
  __IO uint32_t APB1RSTR;
  __IO uint32_t AHBENR;
  __IO uint32_t APB2ENR;
  __IO uint32_t APB1ENR;
  __IO uint32_t BDCR;
  __IO uint32_t CSR;
} RCC_TypeDef;

typedef struct
{
  __IO uint16_t SR;
  uint16_t  RESERVED0;
  __IO uint16_t CR1;
  uint16_t  RESERVED1;
  __IO uint16_t CR2;
  uint16_t  RESERVED2;
  __IO uint16_t CR3;
  uint16_t  RESERVED3;
  __IO uint16_t GTPR;
  uint16_t  RESERVED4;
} USART_TypeDef;

typedef struct
{
  __IO uint32_t CR1;
  __IO uint32_t CR2;
  __IO uint32_t SMCR;
  __IO uint32_t DIER;
  __IO uint32_t SR;
  __IO uint32_t EGR;
  __IO uint32_t CCMR1;
  __IO uint32_t CCMR2;
  __IO uint32_t CCER;
  __IO uint32_t CNT;
  __IO uint32_t PSC;
  __IO uint32_t ARR;
  __IO uint32_t RCR;
  __IO uint32_t CCR1;
  __IO uint32_t CCR2;
  __IO uint32_t CCR3;
  __IO uint32_t CCR4;
  __IO uint32_t BDTR;
  __IO uint32_t DCR;
  __IO uint32_t DMAR;
} TIM_TypeDef;

typedef struct
{
  __IO uint32_t ACR;
  __IO uint32_t KEYR;
  __IO uint32_t OPTKEYR;
  __IO uint32_t SR;
  __IO uint32_t CR;
  __IO uint32_t AR;
  __IO uint32_t RESERVED;
  __IO uint32_t OBR;
  __IO uint32_t WRPR;
} FLASH_TypeDef;

/* ========================= Peripheral Instances ========================= */
#define GPIOA               ((GPIO_TypeDef *)  GPIOA_BASE)
#define GPIOB               ((GPIO_TypeDef *)  GPIOB_BASE)
#define GPIOC               ((GPIO_TypeDef *)  GPIOC_BASE)
#define GPIOD               ((GPIO_TypeDef *)  GPIOD_BASE)
#define GPIOE               ((GPIO_TypeDef *)  GPIOE_BASE)
#define AFIO                ((AFIO_TypeDef *)  AFIO_BASE)
#define RCC                 ((RCC_TypeDef *)   RCC_BASE)
#define USART1              ((USART_TypeDef *) USART1_BASE)
#define USART2              ((USART_TypeDef *) USART2_BASE)
#define USART3              ((USART_TypeDef *) USART3_BASE)
#define TIM1                ((TIM_TypeDef *)   TIM1_BASE)
#define TIM2                ((TIM_TypeDef *)   TIM2_BASE)
#define TIM3                ((TIM_TypeDef *)   TIM3_BASE)
#define TIM4                ((TIM_TypeDef *)   TIM4_BASE)
#define TIM5                ((TIM_TypeDef *)   TIM5_BASE)
#define TIM6                ((TIM_TypeDef *)   TIM6_BASE)
#define TIM7                ((TIM_TypeDef *)   TIM7_BASE)
#define FLASH               ((FLASH_TypeDef *) FLASH_R_BASE)

/* ========================= RCC Bit Definitions ========================= */
#define RCC_CR_HSION                     ((uint32_t)0x00000001)
#define RCC_CR_HSIRDY                    ((uint32_t)0x00000002)
#define RCC_CR_HSITRIM                   ((uint32_t)0x000000F8)
#define RCC_CR_HSICAL                    ((uint32_t)0x0000FF00)
#define RCC_CR_HSEON                     ((uint32_t)0x00010000)
#define RCC_CR_HSERDY                    ((uint32_t)0x00020000)
#define RCC_CR_HSEBYP                    ((uint32_t)0x00040000)
#define RCC_CR_CSSON                     ((uint32_t)0x00080000)
#define RCC_CR_PLLON                     ((uint32_t)0x01000000)
#define RCC_CR_PLLRDY                    ((uint32_t)0x02000000)

#define RCC_CFGR_SW                      ((uint32_t)0x00000003)
#define RCC_CFGR_SW_HSI                  ((uint32_t)0x00000000)
#define RCC_CFGR_SW_HSE                  ((uint32_t)0x00000001)
#define RCC_CFGR_SW_PLL                  ((uint32_t)0x00000002)
#define RCC_CFGR_SWS                     ((uint32_t)0x0000000C)
#define RCC_CFGR_SWS_PLL                 ((uint32_t)0x00000008)
#define RCC_CFGR_HPRE                    ((uint32_t)0x000000F0)
#define RCC_CFGR_PPRE1                   ((uint32_t)0x00000700)
#define RCC_CFGR_PPRE2                   ((uint32_t)0x00003800)
#define RCC_CFGR_ADCPRE                  ((uint32_t)0x0000C000)
#define RCC_CFGR_PLLSRC                  ((uint32_t)0x00010000)
#define RCC_CFGR_PLLXTPRE                ((uint32_t)0x00020000)
#define RCC_CFGR_PLLMULL                 ((uint32_t)0x003C0000)
#define RCC_CFGR_PLLMULL9                ((uint32_t)0x001C0000)
#define RCC_CFGR_MCO                     ((uint32_t)0x07000000)

/* RCC APB2 Enable */
#define RCC_APB2ENR_AFIOEN               ((uint32_t)0x00000001)
#define RCC_APB2ENR_IOPAEN               ((uint32_t)0x00000004)
#define RCC_APB2ENR_IOPBEN               ((uint32_t)0x00000008)
#define RCC_APB2ENR_IOPCEN               ((uint32_t)0x00000010)
#define RCC_APB2ENR_IOPDEN               ((uint32_t)0x00000020)
#define RCC_APB2ENR_IOPEEN               ((uint32_t)0x00000040)
#define RCC_APB2ENR_ADC1EN               ((uint32_t)0x00000200)
#define RCC_APB2ENR_ADC2EN               ((uint32_t)0x00000400)
#define RCC_APB2ENR_TIM1EN               ((uint32_t)0x00000800)
#define RCC_APB2ENR_SPI1EN               ((uint32_t)0x00001000)
#define RCC_APB2ENR_USART1EN             ((uint32_t)0x00004000)

/* RCC APB1 Enable */
#define RCC_APB1ENR_TIM2EN               ((uint32_t)0x00000001)
#define RCC_APB1ENR_TIM3EN               ((uint32_t)0x00000002)
#define RCC_APB1ENR_TIM4EN               ((uint32_t)0x00000004)
#define RCC_APB1ENR_TIM5EN               ((uint32_t)0x00000008)
#define RCC_APB1ENR_TIM6EN               ((uint32_t)0x00000010)
#define RCC_APB1ENR_TIM7EN               ((uint32_t)0x00000020)
#define RCC_APB1ENR_USART2EN             ((uint32_t)0x00020000)
#define RCC_APB1ENR_USART3EN             ((uint32_t)0x00040000)

/* ========================= GPIO Bit Definitions ========================= */
#define GPIO_CRL_MODE                    ((uint32_t)0x33333333)
#define GPIO_CRL_MODE0                   ((uint32_t)0x00000003)
#define GPIO_CRL_CNF0                    ((uint32_t)0x0000000C)
#define GPIO_CRL_MODE1                   ((uint32_t)0x00000030)
#define GPIO_CRL_CNF1                    ((uint32_t)0x000000C0)
#define GPIO_CRL_MODE2                   ((uint32_t)0x00000300)
#define GPIO_CRL_CNF2                    ((uint32_t)0x00000C00)
#define GPIO_CRL_MODE3                   ((uint32_t)0x00003000)
#define GPIO_CRL_CNF3                    ((uint32_t)0x0000C000)
#define GPIO_CRL_MODE4                   ((uint32_t)0x00030000)
#define GPIO_CRL_CNF4                    ((uint32_t)0x000C0000)
#define GPIO_CRL_MODE5                   ((uint32_t)0x00300000)
#define GPIO_CRL_CNF5                    ((uint32_t)0x00C00000)
#define GPIO_CRL_MODE6                   ((uint32_t)0x03000000)
#define GPIO_CRL_CNF6                    ((uint32_t)0x0C000000)
#define GPIO_CRL_MODE7                   ((uint32_t)0x30000000)
#define GPIO_CRL_CNF7                    ((uint32_t)0xC0000000)

/* ========================= USART Bit Definitions ========================= */
#define USART_SR_PE                      ((uint16_t)0x0001)
#define USART_SR_FE                      ((uint16_t)0x0002)
#define USART_SR_NE                      ((uint16_t)0x0004)
#define USART_SR_ORE                     ((uint16_t)0x0008)
#define USART_SR_IDLE                    ((uint16_t)0x0010)
#define USART_SR_RXNE                    ((uint16_t)0x0020)
#define USART_SR_TC                      ((uint16_t)0x0040)
#define USART_SR_TXE                     ((uint16_t)0x0080)
#define USART_CR1_SBK                    ((uint16_t)0x0001)
#define USART_CR1_RWU                    ((uint16_t)0x0002)
#define USART_CR1_RE                     ((uint16_t)0x0004)
#define USART_CR1_TE                     ((uint16_t)0x0008)
#define USART_CR1_IDLEIE                 ((uint16_t)0x0010)
#define USART_CR1_RXNEIE                 ((uint16_t)0x0020)
#define USART_CR1_TCIE                   ((uint16_t)0x0040)
#define USART_CR1_TXEIE                  ((uint16_t)0x0080)
#define USART_CR1_PEIE                   ((uint16_t)0x0100)
#define USART_CR1_PS                     ((uint16_t)0x0200)
#define USART_CR1_PCE                    ((uint16_t)0x0400)
#define USART_CR1_WAKE                   ((uint16_t)0x0800)
#define USART_CR1_M                      ((uint16_t)0x1000)
#define USART_CR1_UE                     ((uint16_t)0x2000)
#define USART_CR1_OVER8                  ((uint16_t)0x8000)
#define USART_CR2_STOP                   ((uint16_t)0x3000)
#define USART_CR3_RTSE                   ((uint16_t)0x0100)
#define USART_CR3_CTSE                   ((uint16_t)0x0200)

/* ========================= FLASH Bit Definitions ========================= */
#define FLASH_ACR_LATENCY                ((uint8_t)0x03)
#define FLASH_ACR_LATENCY_2              ((uint8_t)0x02)
#define FLASH_ACR_PRFTBE                 ((uint8_t)0x10)
#define FLASH_ACR_PRFTBS                 ((uint8_t)0x20)

/* ========================= TIM Bit Definitions ========================= */
#define TIM_CR1_CEN                      ((uint16_t)0x0001)
#define TIM_CR1_UDIS                     ((uint16_t)0x0002)
#define TIM_CR1_URS                      ((uint16_t)0x0004)
#define TIM_CR1_OPM                      ((uint16_t)0x0008)
#define TIM_CR1_DIR                      ((uint16_t)0x0010)
#define TIM_CR1_ARPE                     ((uint16_t)0x0080)
#define TIM_DIER_UIE                     ((uint16_t)0x0001)
#define TIM_SR_UIF                       ((uint16_t)0x0001)
#define TIM_EGR_UG                       ((uint16_t)0x0001)

/* ========================= Bit banding macros ========================= */
#define PERIPH_BB_BASE        ((uint32_t)0x42000000)
#define PERIPH_OFFSET         ((uint32_t)(PERIPH_BASE))
#define BB_REG(reg, bit)      (*(__IO uint32_t *)(PERIPH_BB_BASE + \
                               ((uint32_t)(&(reg)) - PERIPH_OFFSET) * 32 + \
                               (bit) * 4))

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))
#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))
#define READ_BIT(REG, BIT)    ((REG) & (BIT))
#define CLEAR_REG(REG)        ((REG) = (0x0))
#define WRITE_REG(REG, VAL)   ((REG) = (VAL))
#define READ_REG(REG)         ((REG))
#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

#ifdef __cplusplus
}
#endif

#endif /* __STM32F10x_H */
