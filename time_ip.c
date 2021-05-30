#include "stm32f10x.h"
#include "time_ip.h"
#include "sys.h"

void Time_Init(u16 count,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_Struct;
	NVIC_InitTypeDef NVIC_Struct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
  TIM_Struct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_Struct.TIM_CounterMode=TIM_CounterMode_Up;//操作CR寄存器，设置模式
	TIM_Struct.TIM_Period=count;//操作RLR寄存器，设置计数器值，16位
	TIM_Struct.TIM_Prescaler=psc;//操作PR寄存器,设置分频系数，16位
	//不用，可不写.TIM_RepetitionCounter=
	TIM_TimeBaseInit(TIM2, &TIM_Struct);//初始化定时器2
	
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);中断使用前要分组

	
	 NVIC_Struct.NVIC_IRQChannel=TIM2_IRQn;
	 NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_Struct.NVIC_IRQChannelPreemptionPriority=0;
	 NVIC_Struct.NVIC_IRQChannelSubPriority=3;

 NVIC_Init(&NVIC_Struct);//中断初始化
 TIM_Cmd(TIM2, ENABLE);//使能定时器2
	}

	void TIM3_IRQHandler(void)
	{
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//判断SR寄存器是否满足中断条件
		{
			PBout(5)=!PBout(5);
			PEout(5)=!PEout(5);
		}
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//软件清除中断标志位
	}
	