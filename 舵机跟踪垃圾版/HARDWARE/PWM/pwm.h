#ifndef _TIMER_H
#define _TIMER_H
#include "sys.h"
#define SOFT_DELAY Delay(0x0FFFFF);
void TIM2_PWM_Init(u32 arr,u32 psc);
void TIM1_PWM_Init(u16 arr,u16 psc);
void TIM4_PWM_Init(u32 arr,u32 psc);
void TIM5_PWM_Init(u32 arr,u32 psc);
void TIM9_PWM_Init(u32 arr,u32 psc);
void TIM10_PWM_Init(u32 arr,u32 psc);
void TIM11_PWM_Init(u32 arr,u32 psc);
void TIMER12_PWM_Init(u32 arr,u32 psc);
void TIMER13_PWM_Init(u32 arr,u32 psc);
void TIMER14_PWM_Init(u32 arr,u32 psc);

#endif
