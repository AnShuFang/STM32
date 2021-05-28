#include "stm32f10x.h"
#include "iwdg.h"

void Iwdg_Init(uint8_t prescaler,uint16_t count)//使用此函数独立看门狗打开，超时时间由2个参数决定
{
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//往KR寄存器中写人ox5555,解锁PR,RLR寄存器可写入
	IWDG_SetPrescaler(prescaler);//设置预分频系数，操作PR寄存器
	IWDG_SetReload(count);//设置计数器初值，操作RLR寄存器，0-11位有效，值小于0xfff;
	IWDG_Enable();//使能iwdg,在KR寄存器中写入oxcccc，看门狗开始工作，IWDG_ReloadCounter函数喂狗，或者在KR寄存器中写入oxaaaa;
}