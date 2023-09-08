#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h" 

/*下面的方式是通过直接操作库函数方式读取IO*/

#define KEY1 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)	//PE3 
#define KEY2 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6) //PE2
#define KEY3 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7) //PE4
#define KEY4 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_8)	//PE3 
#define KEY5 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_9) //PE2#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY6 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)	//PE3 
#define KEY7 		GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2) //PE2#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY8 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)	//PE3 
#define KEY9 		GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11) //PE2#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY10 	GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)	//PE3 
#define KEY11 	GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_13) //PE2#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY12 	GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_12)	//PE3 
#define KEY13		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_9) //PE2#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY14		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_10)	//PE3 
#define KEY15		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11) //PE2#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY17 	GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_13) //PE2
#define KEY18		GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_14) //PE2#define KEY0 		GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4) //PE4
#define KEY19 	GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_15)	//PE3 



/*下面方式是通过位带操作方式读取IO*/
/*
#define KEY0 		PEin(4)   	//PE4
#define KEY1 		PEin(3)		//PE3 
#define KEY2 		PEin(2)		//P32
#define WK_UP 	PAin(0)		//PA0
*/

//机械臂

#define KEY19_PRES 20
#define KEY1_PRES		2

#define KEY2_PRES		3
#define	KEY3_PRES 	4	

#define KEY4_PRES 	5
#define KEY5_PRES 6

#define KEY6_PRES 7
#define KEY7_PRES 8

#define KEY8_PRES 9
#define KEY9_PRES 10

#define KEY10_PRES 11
#define KEY11_PRES 12



//摄像头

#define KEY12_PRES 13
#define KEY13_PRES 14



//调速

#define KEY17_PRES 18


//空闲
#define KEY18_PRES 19
#define KEY14_PRES 15
#define KEY15_PRES 16


void KEY_Init(void);	//IO初始化
u8 KEY_Scan(u8);  		//按键扫描函数	
void calkey(u16 i,u16 *x);
#endif






























