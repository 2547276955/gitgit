#include "ICapture.h"
#include "sys.h"
#include "ultrasonic.h"

void TIM3_ICap_Init(u32 arr,u16 psc)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);   //TIM3ʱ��
	
	Ultrasonic_Init();
	
	TIM_TimeBaseInitStructure.TIM_Period=arr;									//�Զ���װ��ֵ
	TIM_TimeBaseInitStructure.TIM_Prescaler=psc;								//Ԥ��Ƶ
	TIM_TimeBaseInitStructure.TIM_CounterMode =TIM_CounterMode_Up;				//���ϼ���
	TIM_TimeBaseInitStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);							//TIM3��ʼ��
	
	TIM_Cmd(TIM3,ENABLE);
	
	TIM_ICInitStructure.TIM_Channel =TIM_Channel_1;//ͨ��1
	TIM_ICInitStructure.TIM_ICFilter =0X00;//���˲�
	TIM_ICInitStructure.TIM_ICPolarity =TIM_ICPolarity_Rising;//���ϲ���
	TIM_ICInitStructure.TIM_ICSelection =TIM_ICSelection_DirectTI;//ӳ�䵽TI1
	TIM_ICInitStructure.TIM_ICPrescaler =TIM_ICPSC_DIV1;//����Ƶ
	TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);
}


	u8 TIM3_ICapture_OFProtocol=0;  	//OF��overflow���  ����һ��������Э��
	u32 TIM3_ICapture_val;			//����һ����������� ��ʱ��5��ֵ

//ԭ�����벶�������   �������ĳ�����
void TIM3_IRQHandler(void)  //TIM3�жϷ�����
{

	
 	if((TIM3_ICapture_OFProtocol&0X80)==0)//��δ�ɹ�����	 8*16  = 128 =2��7�η� �ڰ�λ
	{

		if(TIM_GetITStatus(TIM3, TIM_IT_CC1) ==1)//����1���������¼�
		{	
			if(TIM3_ICapture_OFProtocol&0X40)		//����һ���½��� 		//��ʵ���ж�ǰһ���Ƿ�׽����������  ����� 0x40 ����λΪ��  �����׽�� ��ô���һ�����½���
			{	  			
				TIM3_ICapture_OFProtocol|=0X80;		//��ǳɹ�����һ�θߵ�ƽ����
			  TIM3_ICapture_val=TIM_GetCapture1(TIM3);//��ȡ��ǰ�Ĳ���ֵ.
	 			TIM_OC1PolarityConfig(TIM3,TIM_OCPolarity_High); //CC1P=0 ����Ϊ�����ز���
			}else  								//��δ��ʼ,��һ�β���������
			{
				TIM3_ICapture_OFProtocol=0;			//���
				TIM3_ICapture_val=0;
				TIM3_ICapture_OFProtocol|=0X40;		//��ǲ�����������
				TIM_Cmd(TIM3,DISABLE ); 	//�رն�ʱ��5
	 			TIM_SetCounter(TIM3,0);
	 			TIM_OC1PolarityConfig(TIM3,TIM_OCPolarity_Low);		//CC1P=1 ����Ϊ�½��ز���
				TIM_Cmd(TIM3,ENABLE ); 	//ʹ�ܶ�ʱ��3
			}		    
		}			     	    					   
 	}
	TIM_ClearITPendingBit(TIM3, TIM_IT_CC1|TIM_IT_Update); //����жϱ�־λ
}
