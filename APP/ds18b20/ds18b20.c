#include "ds18b20.h"
#include "SysTick.h"
#include <stdio.h>


u8 DHT22_Init(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	RCC_APB2PeriphClockCmd(RCC_GPIO_DHT22 , ENABLE);	 
 	GPIO_InitStructure.GPIO_Pin = DHT22_PIN;				 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIO_DHT22, &GPIO_InitStructure);				 
 	GPIO_SetBits(GPIO_DHT22,DHT22_PIN);						 
			    
	DHT22_Rst();  
	return DHT22_Check();
} 

//Reset DHT11
void DHT22_Rst(void)	   
{                 
    DHT22_IO_OUT(); 	//输出模式
    DHT22_DQ_OUT=0; 	//拉低
    delay_ms(30);    	//Pull down Least 800us
    DHT22_DQ_OUT=1; 	//拉高 
		delay_us(30);     	//Pull up 20~40us
}

u8 DHT22_Check(void) 	   
{   
	u8 retry=0;
	DHT22_IO_IN();      //输入模式 
  while (DHT22_DQ_IN&&retry<100)   //DHT22 Pull down 40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)
	{
		return 1;	
	}
	else 
		retry=0;
  while (!DHT22_DQ_IN&&retry<100) //DHT22 Pull up 40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)
  {
		return 1;   //chack error	
				
  }        
	return 0;
}

u8 DHT22_Read_Bit(void) 			 
{
 	u8 retry=0;
	while(DHT22_DQ_IN&&retry<100)//wait become Low level
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT22_DQ_IN&&retry<100)//wait become High level
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);         //wait 40us
	if(DHT22_DQ_IN)
		return 1;
	else 
		return 0;		   
}

u8 DHT22_Read_Byte(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT22_Read_Bit();
    }						    
    return dat;
}

u8 DHT22_Read_Data(float *humidity,float *temperature)    
{     
	
 	u8 buf[5];
//	float buffer[5] = {0};
	float tme = 0;
	u8 i;
	u8 sum;
	*humidity=0;
	*temperature=0;
	
	DHT22_Rst();
	
	if(DHT22_Check()==0)
	{
		for(i=0;i<5;i++)
		{
			buf[i]=DHT22_Read_Byte();
		}
		sum = buf[0]+buf[1]+buf[2]+buf[3];
		if(sum == buf[4])
		{
			*humidity=(float)((buf[0]<<8)+buf[1])/10;
			*temperature=(float)((buf[2]<<8)+buf[3])/10;
		}
		else
		{
			*humidity=(float)((buf[0]<<8)+buf[1])/10;
			*temperature=(float)((buf[2]<<8)+buf[3])/10;
		}	
	}
	else 
	{
		return 1;
	}
	return 0;
}