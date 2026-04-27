/**
  ******************************************************************************
  * @file    sys.c
  * @brief   System support functions: NVIC configuration for STM32F103RCT6
  ******************************************************************************
  */

#include "sys.h"

/**
  * @brief  Configure the NVIC interrupt priority group.
  * @param  NVIC_PriorityGroup: NVIC priority group (use NVIC_PriorityGroup_x macros)
  * @retval None
  */
void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup)
{
    SCB->AIRCR = (uint32_t)0x05FA0000 | NVIC_PriorityGroup;
}

/**
  * @brief  Initialize NVIC for the specified interrupt.
  * @param  IRQn:               Interrupt number
  * @param  PreemptPriority:    Pre-emption priority
  * @param  SubPriority:        Sub-priority
  * @param  NVIC_PriorityGroup: NVIC priority group currently configured
  * @retval None
  */
void NVIC_Init_Config(IRQn_Type IRQn, uint32_t PreemptPriority,
                      uint32_t SubPriority, uint32_t NVIC_PriorityGroup)
{
    uint32_t tmp_priority;
    uint32_t preempt_bits, sub_bits;

    /* Determine number of preemption and sub-priority bits */
    tmp_priority = (0x700 - (NVIC_PriorityGroup & 0x700)) >> 8;  /* preempt bits */
    preempt_bits = tmp_priority;
    sub_bits     = 4 - tmp_priority;

    tmp_priority  = (PreemptPriority & ((1 << preempt_bits) - 1)) << sub_bits;
    tmp_priority |= (SubPriority     & ((1 << sub_bits)     - 1));
    tmp_priority <<= (8 - 4);  /* __NVIC_PRIO_BITS = 4 */

    NVIC->IP[(uint32_t)(IRQn)] = (uint8_t)tmp_priority;
    NVIC->ISER[(uint32_t)(IRQn) >> 5] = (uint32_t)1 << ((uint32_t)(IRQn) & 0x1F);
}
