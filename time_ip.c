#include "stm32f10x.h"
#include "time_ip.h"
#include "sys.h"

void Time_Init(u16 count,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_Struct;
	NVIC_InitTypeDef NVIC_Struct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
  TIM_Struct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_Struct.TIM_CounterMode=TIM_CounterMode_Up;//����CR�Ĵ���������ģʽ
	TIM_Struct.TIM_Period=count;//����RLR�Ĵ��������ü�����ֵ��16λ
	TIM_Struct.TIM_Prescaler=psc;//����PR�Ĵ���,���÷�Ƶϵ����16λ
	//���ã��ɲ�д.TIM_RepetitionCounter=
	TIM_TimeBaseInit(TIM2, &TIM_Struct);//��ʼ����ʱ��2
	
	TIM_ITConfig(TIM2,TIM_IT_Update, ENABLE);
//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);�ж�ʹ��ǰҪ����

	
	 NVIC_Struct.NVIC_IRQChannel=TIM2_IRQn;
	 NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;
	 NVIC_Struct.NVIC_IRQChannelPreemptionPriority=0;
	 NVIC_Struct.NVIC_IRQChannelSubPriority=3;

 NVIC_Init(&NVIC_Struct);//�жϳ�ʼ��
 TIM_Cmd(TIM2, ENABLE);//ʹ�ܶ�ʱ��2
	}

	void TIM3_IRQHandler(void)
	{
		if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)//�ж�SR�Ĵ����Ƿ������ж�����
		{
			PBout(5)=!PBout(5);
			PEout(5)=!PEout(5);
		}
		
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);//�������жϱ�־λ
	}
	