#include "oled.h"
#include "delay.h"
#include "stdlib.h"
#include "oledfont.h"
#include "iic.h"

void OLED_WriteByte(u8 add,u8 data)
{
	SDA_OUT()
	IIC_SDA=1;
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}









