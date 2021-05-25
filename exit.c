#include "stm32f10x.h"
#include "key.h"
#include "exit.h"

void Exit_Init(void)
{
	EXTI_InitTypeDef EXTI_Struct;
	NVIC_InitTypeDef NVIC_Struct;
	Key_Init();
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//使能映射寄存器
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
	
	EXTI_Struct.EXTI_Line=EXTI_Line3;
	EXTI_Struct.EXTI_LineCmd=ENABLE;
	EXTI_Struct.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTI_Struct.EXTI_Trigger=EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_Struct);//EXTI控制器初始化
	
	NVIC_Struct.NVIC_IRQChannel=EXTI3_IRQn;
	NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Struct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Struct);//NVIC中断控制器初始化
}