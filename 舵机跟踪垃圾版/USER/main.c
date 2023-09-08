#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "pwm.h"
#include <string.h>
#define BUFFER_SIZE 2
//void uart_send(uint8_t data) {
//    // �ȴ����ͻ�������
//    while (!(USART1->SR & USART_SR_TXE));
//    USART1->DR = (data & 0xFF);
//}

//// ���崮�ڽ��պ���
//uint8_t uart_receive(void) {
//    // �ȴ����ջ������ǿ�
//    while (!(USART1->SR & USART_SR_RXNE));
//    return (USART1->DR & 0xFF);
//}


uint8_t rx_buffer[BUFFER_SIZE];
uint8_t received_data = 0;
volatile uint8_t rx_index = 0;
void DrvUart1Init(u32 br_num)
{
    USART_InitTypeDef USART_InitStructure;
    USART_ClockInitTypeDef USART_ClockInitStruct;
    NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;

    USART_StructInit(&USART_InitStructure);

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); //����USART1ʱ��
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    //�����ж����ȼ�
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

    //����PA9��ΪUSART1��Tx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //����PA10��ΪUSART1��Rx
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    //
    USART_DeInit(USART1);
		//����USART1
    //�жϱ�������
    USART_InitStructure.USART_BaudRate = br_num;                                    //�����ʿ���ͨ������վ����
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;                     //8λ����
    USART_InitStructure.USART_StopBits = USART_StopBits_1;                          //��֡��β����1��ֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No;                             //������żУ��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //Ӳ��������ʧ��
    USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;                 //���͡�����ʹ��
    //����USART1ʱ��
    USART_ClockInitStruct.USART_Clock = USART_Clock_Disable;     //ʱ�ӵ͵�ƽ�
    USART_ClockInitStruct.USART_CPOL = USART_CPOL_Low;           //SLCK������ʱ������ļ���->�͵�ƽ
    USART_ClockInitStruct.USART_CPHA = USART_CPHA_2Edge;         //ʱ�ӵڶ������ؽ������ݲ���
    USART_ClockInitStruct.USART_LastBit = USART_LastBit_Disable; //���һλ���ݵ�ʱ�����岻��SCLK���

    USART_Init(USART1, &USART_InitStructure);
    USART_ClockInit(USART1, &USART_ClockInitStruct);

    //ʹ��USART1�����ж�
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    //ʹ��USART1
    USART_Cmd(USART1, ENABLE);
}


u8 Tx1Buffer[256];
u8 Tx1Counter = 0;
u8 count1 = 0;
void DrvUart1SendBuf(unsigned char *DataToSend, u8 data_num)
{
    u8 i;
    for (i = 0; i < data_num; i++)
    {
        Tx1Buffer[count1++] = *(DataToSend + i);
    }

    if (!(USART1->CR1 & USART_CR1_TXEIE))
    {
        USART_ITConfig(USART1, USART_IT_TXE, ENABLE); //�򿪷����ж�
    }
}

u8 U1RxDataTmp[100];
u8 U1RxInCnt = 0;
u8 U1RxoutCnt = 0;
u8 imagex1,imagex2,image_y1,image_y2;
u16 image_x_a, image_x_b ,image_y_a, image_y_b;
void drvU1GetByte(u8 data)
{	
		static u8 cnt_b;
		static u8 cnt_a;
		static u8 cnt_c;
		static u8 cnt_d;
//	U1RxDataTmp[U1RxInCnt++] = data;
//	if(U1RxInCnt >= 100)
//		U1RxInCnt = 0;
		static u8 image_x_flag;
		static u8 image_y_flag;
//	if(data == 'x')
//	{
//		image_x_flag = 1;
//		
//	}else if(data =='b' && image_x==1)
//	{
//		image_x = 2;
//	}
//	else if(image_x_flag == 2)
//	{
//		imagex1 = data;
//		image_x_flag=3;
//		cnt+=1;
//	}else if(image_x_flag == 3)
//	{
//		imagex2 =data;
//		cnt+=1;
//	}
//	if(cnt==2)
//	{
//		image_x = imagex1 <<8|imagex2;
//		cnt=0;
//		image_x_flag =0;
//	}
//	
	
	if(data == 'x')
	{
		image_x_flag = 1;
		
	}
	else if(data =='a' && image_x_flag==1)
	{
		image_x_flag = 4;
	}else if(data =='b' && image_x_flag==1)
	{
		image_x_flag = 2;
	}else if(image_x_flag == 4)
	{
		imagex1 = data;
		image_x_flag=5;
		cnt_a+=1;
	}
	else if(image_x_flag == 2)
	{
		imagex1 = data;
		image_x_flag=3;
		cnt_b+=1;
	}else if(image_x_flag == 5)
	{
		imagex2 =data;
		cnt_a+=1;
	}else if(image_x_flag == 3)
	{
		imagex2 =data;
		cnt_b+=1;
	}
	if(cnt_a==2)
	{
		image_x_a = imagex1 <<8|imagex2;
		cnt_a=0;
		image_x_flag =0;
	}
	if(cnt_b==2)
	{
		image_x_b = imagex1 <<8|imagex2;
		cnt_b=0;
		image_x_flag =0;
	}
	
	
	if(data == 'y')
	{
		image_y_flag = 1;
		
	}
	else if(data =='c' && image_y_flag==1)
	{
		image_y_flag = 4;
	}else if(data =='d' && image_y_flag==1)
	{
		image_y_flag = 2;
	}else if(image_y_flag == 4)
	{
		image_y1 = data;
		image_y_flag=5;
		cnt_c+=1;
	}
	else if(image_y_flag == 2)
	{
		image_y1 = data;
		image_y_flag=3;
		cnt_d+=1;
	}else if(image_y_flag == 5)
	{
		image_y2 =data;
		cnt_c+=1;
	}else if(image_y_flag == 3)
	{
		image_y2 =data;
		cnt_d+=1;
	}
	if(cnt_c==2)
	{
		image_y_a = image_y1 <<8|image_y2;
		cnt_c=0;
		image_y_flag =0;
	}
	if(cnt_d==2)
	{
		image_y_b = image_y1 <<8|image_y2;
		cnt_d=0;
		image_y_flag =0;
	}
	
	
}



void drvU1DataCheck(void)
{
	while(U1RxInCnt!=U1RxoutCnt)
	{	
		U1RxoutCnt=U1RxoutCnt+1;
		drvU1GetByte(U1RxDataTmp[U1RxoutCnt]);
		if(U1RxoutCnt >= 100)
			U1RxoutCnt = 0;
	}
}


void USART1_IRQHandler(void)
{
    u8 com_data;

    if (USART1->SR & USART_SR_ORE) //ORE�ж�
    {
        com_data = USART1->DR;
    }
    //�����ж�
    if (USART_GetITStatus(USART1, USART_IT_RXNE))
    {
        USART_ClearITPendingBit(USART1, USART_IT_RXNE); //����жϱ�־
        com_data = USART1->DR;
        drvU1GetByte(com_data);
    }
    //���ͣ�������λ���ж�
    if (USART_GetITStatus(USART1, USART_IT_TXE))
    {
        USART1->DR = Tx1Buffer[Tx1Counter++]; //дDR����жϱ�־
        if (Tx1Counter == count1)
        {
            USART1->CR1 &= ~USART_CR1_TXEIE; //�ر�TXE�������жϣ��ж�
        }
    }
}

//void USART2_IRQHandler(void) {
//    if (USART_GetITStatus(USART2, USART_IT_RXNE) != RESET) {
//        uint8_t data = USART2->DR;
//        
//        if (rx_index < BUFFER_SIZE) {
//            rx_buffer[rx_index++] = data;
//        }
//        
//        if (rx_index == BUFFER_SIZE) {
//            // ��ɽ��������ֽڵ����ݣ����д���
//            // �����������Ĵ��룬������յ�������
//            received_data = (rx_buffer[0] << 8) | rx_buffer[1];
//            
//            // ���ý��ջ�����������
//            rx_index = 0;
//            memset(rx_buffer, 0, sizeof(rx_buffer));
//        }
//    }
//}








//s16 Pid_conformity()//pid����x��y�����ٶȣ����ص�ʵʱ����֡��װ����ʹ��
//{
//	s16 Speed_x = Flight_Tracking_x(image_x);
//	s16 Speed_y = Flight_Tracking_y(image_y);
//	
//	s16 Fight_speed = sqrt(Speed_x*Speed_x + Speed_y*Speed_y);
//	
//	return Fight_speed;
//}

//Pid_trrack pid;
//s16 Image_Pid_x,Image_Pid_y,last_Image_Pid_x,last_Image_Pid_y;

//s16 Flight_Tracking_x(s16 Image_Pid_x)//��ݮ�ɷ���x�����ֵpid����
//{	
//	pid.Image_Pid_x_P = 2 ;
//	pid.Image_Pid_x_D = 1 ;

//	pid.OutPut_tracking_x = Image_Pid_x / pid.Image_Pid_x_P + (Image_Pid_x - last_Image_Pid_x) / pid.Image_Pid_x_D;
//	last_Image_Pid_x = Image_Pid_x;
//	return pid.OutPut_tracking_x;
//}

//s16 Flight_Tracking_y(s16 Image_Pid_y)//��ݮ�ɷ���y�����ֵpid����
//{
//	pid.Image_Pid_y_P = 2 ;
//	pid.Image_Pid_y_D = 1 ;
//	
//	pid.OutPut_tracking_y = Image_Pid_y / pid.Image_Pid_y_P + (Image_Pid_y - last_Image_Pid_y) / pid.Image_Pid_y_D;
//	last_Image_Pid_y = Image_Pid_y;
//	
//	return pid.OutPut_tracking_y;
//}








int main(void)
	  
{     
			uint8_t x;
			uint8_t flag;
			uint8_t y;
			static int16_t date;
			static int16_t Laser_distance;
			static uint8_t data_high;
			static uint8_t	data_low;
//			static u8 Laser_Tof_low,Laser_Tof_high;
			static u8 accept_flag,accept_cnt;
			int setpwm_1 = 3000;
			int setpwm_2 = 3500;
			int x_pwm = 1600;
	    float bin_a = 0;
			float bin_b = 0;
			float bin_c = 0;
			float bin_d = 0;
 			int pwm_go = 0;
			float Image_Pid_x_P = 2 ;
			float Image_Pid_x_D = 1 ;
			int last_Image_Pid_x;
			int tt[3];
			SystemInit();
			DrvUart1Init(500000);			
			delay_init(168);  //��ʼ����ʱ����
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����
			TIM9_PWM_Init(40000-1,84-1);	//84M/84=1Mhz�ļ���Ƶ��,��װ��ֵ1000������PWMƵ��Ϊ 1M/1000=1Khz.   
			TIM10_PWM_Init(40000-1,84-1);
			TIM_SetCompare1(TIM9,3000);	//�޸ıȽ�ֵ���޸�ռ�ձ�  1000-3000-5000
			TIM_SetCompare1(TIM10,3500);
						
						
	while(1)
	{
	     //TIM_SetCompare1(TIM9,setpwm_1);	//�޸ıȽ�ֵ���޸�ռ�ձ�  1000-3000-5000
				
				
				
				if(image_x_a>0)
				{
				bin_a = image_x_a;
				//x_pwm = setpwm_1 + ((bin_a/320)*300);
				setpwm_1 = setpwm_1 + 20;	
					if(setpwm_1 > 4950)
					{
						setpwm_1 = 4950;
					}
				TIM_SetCompare1(TIM9,setpwm_1);
					
				bin_a = 0;	
				image_x_a = 0;
				}
				else if(image_x_b>0)
				{
				bin_b = image_x_b;
				//x_pwm = setpwm_1 - ((bin_b/320)*300);
				setpwm_1 = setpwm_1 - 20;
					if(setpwm_1 < 1050)
					{
						setpwm_1 = 1050;
					}
				TIM_SetCompare1(TIM9,setpwm_1);
					
				bin_b = 0;	
				image_x_b = 0;
				}	
				
				
				
			
				if(image_y_a>0)
				{
				bin_c = image_y_a;
				//x_pwm = setpwm_1 + ((bin_a/320)*300);
				setpwm_2 = setpwm_2 - 10;	
					if(setpwm_2 < 3000)
					{
						setpwm_2 = 3000;
					}
				TIM_SetCompare1(TIM10,setpwm_2);
					
				bin_c = 0;	
				image_y_a = 0;
				}
				else if(image_y_b>0)
				{
				bin_d = image_y_b;
				//x_pwm = setpwm_1 - ((bin_b/320)*300);
				setpwm_2 = setpwm_2 + 10;
					if(setpwm_2 > 4000)
					{
						setpwm_2 = 4000;
					}
				TIM_SetCompare1(TIM10,setpwm_2);
					
				bin_d = 0;	
				image_y_b = 0;
				}
				
				
				
				
//					if(image_x_a>0)
//				{
//				bin_a = image_x_a;
//				
//				x_pwm = x_pwm + ((bin_a/320)*2000);
//				x_pwm = x_pwm / Image_Pid_x_P + (x_pwm - last_Image_Pid_x) / Image_Pid_x_D;
//				last_Image_Pid_x = x_pwm;
//				if (x_pwm >2900)
//				{
//				
//						x_pwm = 2850;
//		
//				}
//				//setpwm_1 = setpwm_1 + 30;	
//				TIM_SetCompare1(TIM9,x_pwm);
//					
//				bin_a = 0;	
//				image_x_a = 0;
//				}
//				if(image_x_b>0)
//				{
//				bin_b = image_x_b;
//				x_pwm = x_pwm - ((bin_b/320)*2000);
//				x_pwm = x_pwm / Image_Pid_x_P + (x_pwm - last_Image_Pid_x) / Image_Pid_x_D;
//				last_Image_Pid_x = x_pwm;
//				if(x_pwm < 1200)
//					{
//						x_pwm = 1000;
//					}
//				//setpwm_1 = setpwm_1 - 30;
//				TIM_SetCompare1(TIM9,x_pwm);
//				
//				bin_b = 0;	
//				image_x_b = 0;
//				}				
//				if (x_pwm >2500)
//				{
//				
//						x_pwm = 2450;
//		
//				}
//				if(x_pwm < 700)
//					{
//						x_pwm = 700;
//					}				
				
//				if(tt[0]=='x')
//				{
//						if(tt[1]=='a')
//						{
//						
//							Laser_distance = tt[2];
//							
//							//pwm_go = (Laser_distance/320)*1500;
//							setpwm_1 = setpwm_1 + 30;
//							TIM_SetCompare1(TIM9,setpwm_1);
//						
//						}
//						
//						if(tt[1]=='b')
//						{
//						
//							Laser_distance = tt[2];
//							
//							//pwm_go = (Laser_distance/320)*1500;
//							setpwm_1 = setpwm_1 - 30;
//							TIM_SetCompare1(TIM9,setpwm_1);
//						
//						}
//				
//				}
				
				
				
				
				
				
				
				
				
				
				
				
				
//						if(date == 'x'&& setpwm_1 < 4470 && setpwm_1 > 1530)
//				{		
//						
//					
//								USART2_IRQHandler();
//								date = received_data;
//					
//					
//					
//					
//					
//					
//					
//								
////							if(accept_flag == 0)
////								{
////									Laser_Tof_low = date;
////									accept_flag = 1;
////									accept_cnt =0;
////								}else if(accept_flag ==1)
////								{
////									Laser_Tof_high = date;
////									accept_flag = 0;
////									accept_cnt =1;
////								}
////								if(accept_cnt == 1)
////								{	
////									Laser_distance = (Laser_Tof_high<<8) | Laser_Tof_low;
////									accept_cnt = 0;
////								}
////							flag = uart_receive();
//								if(date == 'a')
//						{	
//							setpwm_1 = setpwm_1+30;
////								USART2_IRQHandler();
////								date = received_data;
////							pwm_go = (date/320)*1500;
////							setpwm_1 = setpwm_1 + pwm_go;
//							TIM_SetCompare1(TIM9,setpwm_1);
//							if(setpwm_1>4450)
////						
//						{
//					
//							setpwm_1 = 4540;
//					
//						}
//						}		


//							if(date == 'b')
//						{	
////							USART2_IRQHandler();
////							date = received_data;
////							pwm_go = (date/320)*1500;
////							setpwm_1 = setpwm_1 - pwm_go;
//							setpwm_1 = setpwm_1-30;
//							TIM_SetCompare1(TIM9,setpwm_1);
//										if(setpwm_1<1540)
//					{
//					
//							setpwm_1 = 1550;
//					
//					
//							
//						}				
//				}
//						
//				}
				
				
				
//						if(x == 'x'&& setpwm_1 < 4470 && setpwm_1 > 1530)
//				{		
//						flag = uart_receive();
//						if(flag == 'b')
//						{
////							data_high = uart_receive();
////							data_low = uart_receive();
////							data = (data_high << 8) | data_low;		
//							pwm_go = (data/320)*1500;
//							setpwm_1 = setpwm_1 - pwm_go;
//							flag = 0;
//							TIM_SetCompare1(TIM9,setpwm_1);
//						}	

//				
//						
//						
//				}
						

//						if(x == 'b'&& setpwm_1 > 1530)
//				{		
//					if(setpwm_1<1540)
//					{
//					
//							setpwm_1 = 1550;
//					
//					}
//						setpwm_1 = setpwm_1 - 30;
//						
//						TIM_SetCompare1(TIM9,setpwm_1);
//						}							
//						
//				
//						if(x == 'a'&& setpwm_1 < 4470 && setpwm_1 > 1530)
//				{		
//					if(setpwm_1>4450)
//						
//					{
//					
//							setpwm_1 = 4540;
//					
//					}

//						setpwm_1 = setpwm_1+30;
//					  
//						TIM_SetCompare1(TIM9,setpwm_1);
//						
//						
//				}
					
			}
				
				
				
		}	

	
		
		

		
		
		
		
		
		
		
		
		
		
		