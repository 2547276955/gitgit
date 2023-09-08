#include "ultrasonic.h"
#include "delay.h"
#include "sys.h"

void Ultrasonic_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
//Trig
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//ECHO
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);
}
void Ultrasonic_StartMeasure(void)
{
 Trig =1;
 delay_ms(20);
 Trig=0;

}



