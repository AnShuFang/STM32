#include "stm32h10x.h" 
#include "sys.h"
#include "delay.h"
// 蜂鸣器接在三极管集电极，三极管基极与PB8相连，高电平有效 
void BEEP_Init(void)
{
	RCC->APB2ENR|=1<<3;//GPIOB时钟使能
	
	GPIOB->CRH &= oxFFFFFFF0;
	GPIOB->CRH |= ox00000003; //配置工作模式
	
	GPIOB->ODR &= oxFFFFFEFF;//初始输出低电平
	// GPIOB->BRR|=1<<8;//利用BRR寄存器初始化 
	//PBout(8)=0;//利用地址映射对应的bit位初始化，PBout是宏定义地址解引用 
	 
}
int main()
{
	delay_init(10);//防抖 
	BEEP_Init();
	while(1)
	{
		GPIOB->BSRR|=1<<8;
		delay_ms(1000);
		GPIOB->BR|=1<<8;
	}
	return 0;
}
