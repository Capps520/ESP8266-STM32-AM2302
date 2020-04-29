#ifndef _DHT22_H
#define _DHT22_H

#include "system.h"


/*  DHT22时钟端口、引脚定义 */
#define GPIO_DHT22       GPIOA
#define DHT22_PIN 			 GPIO_Pin_4
#define RCC_GPIO_DHT22	RCC_APB2Periph_GPIOA


#define DHT22_IO_IN()  {GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=8<<16;}	//PA4
#define DHT22_IO_OUT() {GPIOA->CRL&=0XFFF0FFFF;GPIOA->CRL|=3<<16;}	//PA4
											   
#define	DHT22_DQ_OUT PAout(4) 
#define	DHT22_DQ_IN  PAin(4)   





u8 DHT22_Init(void); //Init DHT22
u8 DHT22_Read_Data(float *temperature,float *humidity); //Read DHT22 Value
u8 DHT22_Read_Byte(void);//Read One Byte
u8 DHT22_Read_Bit(void);//Read One Bit
u8 DHT22_Check(void);//Chack DHT22
void DHT22_Rst(void);//Reset DHT22 




#endif
