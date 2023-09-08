#include "ICapture.h"
#include "sys.h"
#include "ultrasonic.h"

void TIM3_ICap_Init(u32 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //TIM3时钟
	
	Ultrasonic_Init();
	
	TIM_TimeBaseInitStructure.TIM_Period=arr;									//自动重装载值
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;								//预分频
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;				//向上计数
	TIM_TimeBaseInitStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);							//TIM3初始化
	
	TIM_Cmd(TIM3,ENABLE);
	
	TIM_ICInitStructure.TIM_Channel =TIM_Channel_1;//通道1
	TIM_ICInitStructure.TIM_ICFilter =0X00;//不滤波
	TIM_ICInitStructure.TIM_ICPolarity =TIM_ICPolarity_Rising;//向上捕获
	TIM_ICInitStructure.TIM_ICSelection =TIM_ICSelection_DirectTI;//映射到TI1
	TIM_ICInitStructure.TIM_ICPrescaler =TIM_ICPSC_DIV1;//不分频
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
}


	u8 TIM3_ICapture_OFProtocol=0;  	//OF→overflow溢出  定义一个溢出标记协议
	u32 TIM3_ICapture_val;			//定义一个变量来存放 定时器5的值

//原子输入捕获试验的   服务函数改出来的
void TIM3_IRQHandler(void)  //TIM3中断服务函数
{

	
 	if((TIM3_ICapture_OFProtocol&0X80)==0)//还未成功捕获	 8*16  = 128 =2的7次方 第八位
	{

		if(TIM_GetITStatus(TIM3, TIM_IT_CC1) ==1)//捕获1发生捕获事件
		{	
			if(TIM3_ICapture_OFProtocol&0X40)		//捕获到一个下降沿 		//其实是判断前一次是否捕捉到了上升沿  如果是 0x40 第七位为高  如果捕捉过 那么这次一定是下降沿
			{	  			
				TIM3_ICapture_OFProtocol|=0X80;		//标记成功捕获到一次高电平脉宽
			  TIM3_ICapture_val=TIM_GetCapture1(TIM3);//获取当前的捕获值.
	 			TIM_OC1PolarityConfig(TIM3,TIM_OCPolarity_High); //CC1P=0 设置为上升沿捕获
			}else  								//还未开始,第一次捕获上升沿
			{
				TIM3_ICapture_OFProtocol=0;			//清空
				TIM3_ICapture_val=0;
				TIM3_ICapture_OFProtocol|=0X40;		//标记捕获到了上升沿
				TIM_Cmd(TIM3,DISABLE ); 	//关闭定时器5
	 			TIM_SetCounter(TIM3,0);
	 			TIM_OC1PolarityConfig(TIM3,TIM_OCPolarity_Low);		//CC1P=1 设置为下降沿捕获
				TIM_Cmd(TIM3,ENABLE ); 	//使能定时器3
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //清除中断标志位
}
