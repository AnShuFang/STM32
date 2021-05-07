#include "stm32f10x.h" //LED灯初始化函数-寄存器编程 

 void LED_Init()
	{
		RCC->APB2ENR|=1<<3 ；//GPIOB时钟使能； 
		RCC->APB2ENR|=1<<6； //GPIOE时钟使能；
		
		GPIOB->CRL&=oxFF0FFFFF;
		GPIOB->CRL|=ox00300000;//配置GPIOB_PIN5引脚工作模式；
		GPIOB->ODR|=1<<5;//初始PIN_5引脚输出高电平；
		
		GPIOE->CRL&=oxFF0FFFFF;
		GPIOE->CRL|=ox00300000;//配置GPIOE_PIN5引脚工作模式；
		GPIOE->ODR|=1<<5;//初始PIN_5引脚输出高电平；
			 
	}
	

