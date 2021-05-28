#include "stm32f10x.h"
#include "wwdg.h"

void Wwdg_Init(uint32_t WWDG_Prescaler,uint8_t WindowValue,uint8_t Counter)//wwdg初始化函数，包括中断
{
	WWDG_DeInit();//将WWDG外设时钟使能在解除使能
	NVIC_InitTypeDef NVIC_Struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//wwdg外设接在APB1总线上，Pclc1为其时钟，使用时需要对其总线外设使能，iwdg是内部LSI时钟
	
	WWDG_SetPrescaler(WWDG_Prescaler);//操作CFR寄存器（7-8）位，设置分频系数
  WWDG_SetWindowValue(WindowValue);//操作CFR寄存器低0-6位，设置窗值，小于0x7f
  WWDG_EnableIT();//操作CFR寄存器第9位，开启早气中断唤醒，即计数器达到0x04f时，开启中断，
	
	NVIC_Struct.NVIC_IRQChannel=WWDG_IRQn;//确定中断线
	NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;//操作ISER寄存器，使相应通道使能
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority=2;//操作IP寄存器，划分通道中断优先级
	NVIC_Struct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Struct);//初始化WWDG中断，并设置其优先级
	
  //WWDG_SetCounter(Counter);喂狗,操作CR寄存器，往低6位写值
  WWDG_Enable(Counter);//操作CR寄存器，0-6位写入初值，第7位使能WWDG外设，WWDG开始工作
	
}

void WWDG_IRQHandler()//wwdg外设中断服务函数
{
	WWDG_SetCounter(0x7F);//喂狗，
	WWDG_ClearFlag();//清除标志位，使得中断能够不断产生，操作SR寄存器第0位
	
}
