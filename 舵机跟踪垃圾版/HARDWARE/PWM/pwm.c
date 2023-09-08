
#include "pwm.h"
#include "stm32f4xx_gpio.h"
void TIM2_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);  	//TIM2ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource15,GPIO_AF_TIM2); //GPIOF9����Ϊ��ʱ��14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV2; 
	
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);//��ʼ����ʱ��2
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM2,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM2, ENABLE);  //ʹ��TIM2
	TIM_CtrlPWMOutputs(TIM2, ENABLE);//ʹ��TIM1��PWM�����TIM1��TIM8��Ч,���û�����л�����
	
									
}  
     

void TIM1_PWM_Init(u16 arr,u16 psc)
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM2ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); 	//ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_TIM1); //GPIOF9����Ϊ��ʱ��14
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;           //GPIOF9
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOE,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV2; 
	
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��2
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM2��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM2
	TIM_CtrlPWMOutputs(TIM1, ENABLE);//ʹ��TIM1��PWM�����TIM1��TIM8��Ч,���û�����л�����
		 
// TIM_SetCompare1(TIM1,25);	//�޸ıȽ�ֵ���޸�ռ�ձ�
}  
 
  



void TIM4_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource12,GPIO_AF_TIM4); //GPIOA5����Ϊ��ʱ��5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;           //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOD,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);  //ʹ��TIM5��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM5
 
							
									
}  

  void TIM5_PWM_Init(u32 arr,u32 psc)
{		 					 
	//�˲������ֶ��޸�IO������
	
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);  	//TIM5ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource0,GPIO_AF_TIM5); //GPIOA5����Ϊ��ʱ��5
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;           //GPIOA0
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PF9
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseStructure);//��ʼ����ʱ��14
	
	//��ʼ��TIM14 Channel1 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM5, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1

	TIM_OC1PreloadConfig(TIM5, TIM_OCPreload_Enable);  //ʹ��TIM5��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM5,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM5, ENABLE);  //ʹ��TIM5
 
				
									
}  

void TIM9_PWM_Init(u32 arr,u32 psc)
{   
    
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9,ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12|RCC_APB1Periph_TIM13|RCC_APB1Periph_TIM14,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);

	
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource5,GPIO_AF_TIM9);  	//GPIOA2����Ϊ��ʱ��9

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOE,&GPIO_InitStructure);
		GPIO_SetBits(GPIOE,GPIO_Pin_5);
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM9,&TIM_TimeBaseStructure);//��ʼ����ʱ��9

    //��ʼ��TIM14 Channel1 PWMģʽ	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
    TIM_OC1Init(TIM9, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
    TIM_OC1PreloadConfig(TIM9,TIM_OCPreload_Enable);
		TIM_Cmd(TIM9,ENABLE);
    TIM_ARRPreloadConfig(TIM9,ENABLE);



}

void TIM10_PWM_Init(u32 arr,u32 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10,ENABLE);
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12|RCC_APB1Periph_TIM13|RCC_APB1Periph_TIM14,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	
    GPIO_PinAFConfig(GPIOB,GPIO_PinSource8,GPIO_AF_TIM10);  	//GPIOA2����Ϊ��ʱ��9

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_8;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_SetBits(GPIOB,GPIO_Pin_8);
    TIM_TimeBaseStructure.TIM_Prescaler=psc;  //��ʱ����Ƶ
    TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_Period=arr;   //�Զ���װ��ֵ
    TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
    TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM10,&TIM_TimeBaseStructure);//��ʼ����ʱ��9

    //��ʼ��TIM14 Channel1 PWMģʽ	 
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ե�
    TIM_OC1Init(TIM10, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
    TIM_OC1PreloadConfig(TIM10,TIM_OCPreload_Enable);
		TIM_Cmd(TIM10,ENABLE);
    TIM_ARRPreloadConfig(TIM10,ENABLE);


}

void TIM11_PWM_Init(u32 arr,u32 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

    GPIO_PinAFConfig(GPIOB,GPIO_PinSource9,GPIO_AF_TIM11);  //GPIOA7����Ϊ��ʱ��11
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInit(TIM11,&TIM_TimeBaseInitStructure);

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;           //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //�������:TIM����Ƚϼ��Ե�
   TIM_OC1Init(TIM11, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM14 OC1

   TIM_OC1PreloadConfig(TIM11,TIM_OCPreload_Enable);
   TIM_ARRPreloadConfig(TIM11,ENABLE);
   TIM_Cmd(TIM11,ENABLE);

//   TIM_SetCompare1(TIM11,10000);	//�޸ıȽ�ֵ���޸�ռ�ձ�

}

void TIMER12_PWM_Init(u32 arr,u32 psc)
{  
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

   GPIO_PinAFConfig(GPIOB,GPIO_PinSource14,GPIO_AF_TIM12);  //GPIOA7����Ϊ��ʱ��11


    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_14;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOB,&GPIO_InitStructure);

   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInit(TIM12,&TIM_TimeBaseInitStructure);

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1  ;         //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //�������:TIM����Ƚϼ��Ե�
   TIM_OC1Init(TIM12, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM14 OC1

   TIM_OC1PreloadConfig(TIM12,TIM_OCPreload_Enable);
   TIM_ARRPreloadConfig(TIM12,ENABLE);
   TIM_Cmd(TIM12,ENABLE);

//  TIM_SetCompare1(TIM12,5000);	//�޸ıȽ�ֵ���޸�ռ�ձ�
}

void TIMER13_PWM_Init(u32 arr,u32 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	
    GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM13);        //GPIOA6����Ϊ��ʱ��13

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);
	
   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInit(TIM13,&TIM_TimeBaseInitStructure);
	
   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;           //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //�������:TIM����Ƚϼ��Ե�
   TIM_OC1Init(TIM13, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM14 OC1

   TIM_OC1PreloadConfig(TIM13,TIM_OCPreload_Enable);
   TIM_ARRPreloadConfig(TIM13,ENABLE);
   TIM_Cmd(TIM13,ENABLE);



}

void TIMER14_PWM_Init(u32 arr,u32 psc)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14,ENABLE);
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF,ENABLE);
	
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource9,GPIO_AF_TIM14);  //GPIOA7����Ϊ��ʱ��14

    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
    GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
    GPIO_Init(GPIOF,&GPIO_InitStructure);

   TIM_TimeBaseInitStructure.TIM_ClockDivision=TIM_CKD_DIV2;
   TIM_TimeBaseInitStructure.TIM_CounterMode=TIM_CounterMode_Up;
   TIM_TimeBaseInitStructure.TIM_Period=arr;
   TIM_TimeBaseInitStructure.TIM_Prescaler=psc;
   TIM_TimeBaseInit(TIM14,&TIM_TimeBaseInitStructure);

   TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;           //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
   TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
   TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;      //�������:TIM����Ƚϼ��Ե�
   TIM_OC1Init(TIM14, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM14 OC1

   TIM_OC1PreloadConfig(TIM14,TIM_OCPreload_Enable);
   TIM_ARRPreloadConfig(TIM14,ENABLE);
   TIM_Cmd(TIM14,ENABLE);

	 
	 
}









