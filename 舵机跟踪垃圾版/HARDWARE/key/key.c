#include "key.h"
#include "delay.h" 
 	 
//按键初始化函数
void KEY_Init(void)
{
	
	GPIO_InitTypeDef  GPIO_InitStructure1;
	GPIO_InitTypeDef	GPIO_InitStructure2;
	GPIO_InitTypeDef	GPIO_InitStructure3;
	GPIO_InitTypeDef	GPIO_InitStructure4;

		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA,GPIOE时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);//使能GPIOA,GPIOE时钟
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);//使能GPIOA,GPIOE时钟
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);//使能GPIOA,GPIOE时钟
	  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);//使能GPIOA,GPIOE时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);//使能GPIOA,GPIOE时钟
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOA,GPIOE时钟
 
 
  GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_8; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure1);//初始化GPIOE2,3,4
	 

	
	 GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_15; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOB, &GPIO_InitStructure1);//初始化GPIOE2,3,4
	
	
  GPIO_InitStructure2.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_8|GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_13; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure2.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure2.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure2.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOC, &GPIO_InitStructure2);//初始化GPIOE2,3,4
	
	
	
	 GPIO_InitStructure3.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_13; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure3.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure3.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure3.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure3);//初始化GPIOE2,3,4
	
	
	
	GPIO_InitStructure4.GPIO_Pin =  GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15; //KEY0 KEY1 KEY2对应引脚
  GPIO_InitStructure4.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
  GPIO_InitStructure4.GPIO_Speed = GPIO_Speed_100MHz;//100M
  GPIO_InitStructure4.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOG, &GPIO_InitStructure4);//初始化GPIOE2,3,4
	
	
	
		GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_7|GPIO_Pin_8;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
	GPIO_Init(GPIOE, &GPIO_InitStructure1);//初始化GPIOE2,3,4
	
	
	
		GPIO_InitStructure1.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_1;
	GPIO_InitStructure1.GPIO_Mode = GPIO_Mode_IN;//普通输入模式
	GPIO_InitStructure1.GPIO_Speed = GPIO_Speed_100MHz;//100M
	GPIO_InitStructure1.GPIO_PuPd = GPIO_PuPd_DOWN;//上拉
	GPIO_Init(GPIOF, &GPIO_InitStructure1);//初始化GPIOE2,3,4
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
} 
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，WKUP按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>WK_UP!!
u8 KEY_Scan(u8 mode)
{	
	
	 static u8 key_down=1;//按键按松开标志
	static u8 key_up=1;//按键按松开标志
	
		
	if(0)key_down=1;  //支持连按		  
	if(key_down&&(KEY17==0||KEY18==0))
	{
		delay_ms(10);//去抖动 
		key_down=0;
		if(KEY17==0)return 18;
		else if(KEY18==0)return 19;
	
		
	}else if(KEY17==1&&KEY18==1)key_down=1; 	    
		
	
	
	
	
	if(1)key_up=1;  //支持连按		  
	if(key_up&&(KEY19==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0||KEY7==0||KEY8==0||KEY9==0||KEY10==0||KEY11==0||KEY12==0||KEY13==0||KEY14==0||KEY15==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		
		
		if (KEY19==0)return 20;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
		else if(KEY3==0)return 4;
		else if(KEY4==0)return 5;
		else if(KEY5==0)return 6;
		else if(KEY6==0)return 7;
		else if(KEY7==0)return 8;
		else if(KEY8==0)return 9;
		else if(KEY9==0)return 10;
		else if(KEY10==0)return 11;
		else if(KEY11==0)return 12;
		else if(KEY12==0)return 13;
		else if(KEY13==0)return 14;
		else if(KEY14==0)return 15;
		else if(KEY15==0)return 16;

	}else if(KEY19==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1&&KEY7==1&&KEY8==1&&KEY9==1&&KEY10==1&&KEY11==1&&KEY12==1&&KEY13==1&&KEY14==1&&KEY15==1)key_up=1; 	    

	
	
	
}



void calkey(u16 i,u16 *x)
{
			switch(i)
		{
			case KEY19_PRES  :    x[7]=x[7]-30;if(x[7]<=1050)x[7]=1050;  break;	         
			case KEY1_PRES	 :    x[7]=x[7]+30;if(x[7]>=3950)x[7]=3950;break;       
			case KEY2_PRES	 :    x[6]=x[6]-40;if(x[6]<=520)x[6]=520;  break;	
			case KEY3_PRES	 :    x[6]=x[6]+40;if(x[6]>=1980)x[6]=1980;break;     
			case KEY4_PRES	 :    x[4]=x[4]+35;if(x[4]>=4500)x[4]=4500;break;	
			case KEY5_PRES	 :    x[4]=x[4]-35;if(x[4]<=2000)x[4]=2000;  break;
			case KEY6_PRES	 :  	x[5]=x[5]-35;if(x[5]<=200)x[5]=200;  break;
			case KEY7_PRES	 :    x[5]=x[5]+35;if(x[5]>=2980)x[5]=2980;break;
			case KEY8_PRES	 :    x[2]=x[2]+35;if(x[2]>=4960)x[2]=4960;break;	
			case KEY9_PRES	 :    x[2]=x[2]-35;if(x[2]<=3000)x[2]=3000;  break;
			case KEY10_PRES	 :    x[3]=x[3]+30;if(x[3]>=2300)x[3]=2300;break;	
			case KEY11_PRES	 :    x[3]=x[3]-30;if(x[3]<=480)x[3]=480;  break;
			case KEY12_PRES	 :    x[0]=x[0]-20;if(x[0]<=300)x[0]=300;  break;	
			case KEY13_PRES	 :    x[0]=x[0]+20;if(x[0]>=2500)x[0]=2500;break;
			case KEY17_PRES	 :    x[1]=x[1]+25;if(x[1]>=100)x[1]=50;break;	
		
		}
	 
}
















