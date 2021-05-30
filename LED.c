#include "stm32f10x.h" //LED灯初始化函数-寄存器编程 

 void LED_Init()
	{
		//RCC->APB2ENR|=1<<3;//GPIOB时钟使能； 
		//RCC->APB2ENR|=1<<6; //GPIOE时钟使能；
	
		//GPIOB->CRL&=0xFF0FFFFF;
		//GPIOB->CRL|=0x00300000;//配置GPIOB_PIN5引脚工作模式；
		//GPIOB->ODR|=1<<5;//初始PIN_5引脚输出高电平；
		
		//GPIOE->CRL&=0xFF0FFFFF;
		//GPIOE->CRL|=0x00300000;//配置GPIOE_PIN5引脚工作模式；
	  //GPIOE->ODR|=1<<5;         //初始PIN_5引脚输出高电平；
		
		GPIO_InitTypeDef GPIO_Struct;
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOE,ENABLE);//操作时钟寄存器APB2ENR，使能GPIO端口时钟
		
		GPIO_Struct.GPIO_Mode=GPIO_Mode_Out_PP;
		GPIO_Struct.GPIO_Pin=GPIO_Pin_5;
		GPIO_Struct.GPIO_Speed=GPIO_Speed_50MHz;//操作CR寄存器，设置GPIO工作模式
		
	  GPIO_Init(GPIOB,&GPIO_Struct);//GPIOB_5初始化
		GPIO_Init(GPIOE,&GPIO_Struct);//GPIOE_5初始化
		
		GPIO_SetBits(GPIOB,GPIO_Pin_5);//初始置1
		GPIO_SetBits(GPIOE,GPIO_Pin_5);//同上
		
	}

