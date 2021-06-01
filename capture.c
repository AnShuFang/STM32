#include "stm32f10x.h"
#include "capture.h"

void CAPTURE_Init(u16 count,u16 psc)
{
	GPIO_InitTypeDef GPIO_Struct;
	TIM_TimeBaseInitTypeDef TIM_TimeBase_Struct;
	TIM_ICInitTypeDef TIM_IC_Struct;
	NVIC_InitTypeDef NVIC_Struct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);//时钟使能
	
	//初始化gpio口
	GPIO_Struct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IPD;//下拉输入
	GPIO_Init(GPIOA,&GPIO_Struct);//初始化GPIO模式
	
	//初始化定时器5的值
	TIM_TimeBase_Struct.TIM_CounterMode=TIM_CounterMode_Up;//配置计数模式为向上计数
	TIM_TimeBase_Struct.TIM_Period=count;//配置ARR寄存器装载值
	TIM_TimeBase_Struct.TIM_Prescaler=psc;//配置分频系数
	TIM_TimeBaseInit(TIM5,&TIM_TimeBase_Struct);
	
	//初始化TIM5捕获通道
	TIM_IC_Struct.TIM_ICFilter=0x00;//不设置滤波，操作ccmr寄存器
	TIM_IC_Struct.TIM_ICPolarity=TIM_ICPolarity_Rising;//操作CCER寄存器，上升沿捕获
	TIM_IC_Struct.TIM_ICSelection=TIM_ICSelection_DirectTI;//选择通道，操作CCMR寄存器，直接捕获
	TIM_IC_Struct.TIM_ICPrescaler=TIM_ICPSC_DIV1;//操作ccmr寄存器，设置分频系数
	TIM_IC_Struct.TIM_Channel=TIM_Channel_1;//选择通道一
	TIM_ICInit(TIM5,&TIM_IC_Struct);
	
	//使能相应中断
	TIM_ITConfig(TIM5,TIM_IT_Update|TIM_IT_CC1,ENABLE);
	
	//中断优先级配置
	NVIC_Struct.NVIC_IRQChannel=TIM5_IRQn;
	NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_Struct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Struct);
	
	//计数器使能
	TIM_Cmd(TIM5,ENABLE);
	
}

//中断服务函数
void TIM5_IRQHandler(void)
{
	
	
	
}
