#ifndef __SYS_H
#define __SYS_H

#include "stm32f10x.h"

/* NVIC interrupt priority group configuration */
#define NVIC_PriorityGroup_0    ((uint32_t)0x700)  /* 0 bits for pre-emption, 4 bits for sub-priority */
#define NVIC_PriorityGroup_1    ((uint32_t)0x600)  /* 1 bit  for pre-emption, 3 bits for sub-priority */
#define NVIC_PriorityGroup_2    ((uint32_t)0x500)  /* 2 bits for pre-emption, 2 bits for sub-priority */
#define NVIC_PriorityGroup_3    ((uint32_t)0x400)  /* 3 bits for pre-emption, 1 bit  for sub-priority */
#define NVIC_PriorityGroup_4    ((uint32_t)0x300)  /* 4 bits for pre-emption, 0 bits for sub-priority */

void NVIC_PriorityGroupConfig(uint32_t NVIC_PriorityGroup);
void NVIC_Init_Config(IRQn_Type IRQn, uint32_t PreemptPriority,
                      uint32_t SubPriority, uint32_t NVIC_PriorityGroup);

#endif /* __SYS_H */
