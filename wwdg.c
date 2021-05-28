#include "stm32f10x.h"
#include "wwdg.h"

void Wwdg_Init(uint32_t WWDG_Prescaler,uint8_t WindowValue,uint8_t Counter)//wwdg��ʼ�������������ж�
{
	WWDG_DeInit();//��WWDG����ʱ��ʹ���ڽ��ʹ��
	NVIC_InitTypeDef NVIC_Struct;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG,ENABLE);//wwdg�������APB1�����ϣ�Pclc1Ϊ��ʱ�ӣ�ʹ��ʱ��Ҫ������������ʹ�ܣ�iwdg���ڲ�LSIʱ��
	
	WWDG_SetPrescaler(WWDG_Prescaler);//����CFR�Ĵ�����7-8��λ�����÷�Ƶϵ��
  WWDG_SetWindowValue(WindowValue);//����CFR�Ĵ�����0-6λ�����ô�ֵ��С��0x7f
  WWDG_EnableIT();//����CFR�Ĵ�����9λ�����������жϻ��ѣ����������ﵽ0x04fʱ�������жϣ�
	
	NVIC_Struct.NVIC_IRQChannel=WWDG_IRQn;//ȷ���ж���
	NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;//����ISER�Ĵ�����ʹ��Ӧͨ��ʹ��
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority=2;//����IP�Ĵ���������ͨ���ж����ȼ�
	NVIC_Struct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Struct);//��ʼ��WWDG�жϣ������������ȼ�
	
  //WWDG_SetCounter(Counter);ι��,����CR�Ĵ���������6λдֵ
  WWDG_Enable(Counter);//����CR�Ĵ�����0-6λд���ֵ����7λʹ��WWDG���裬WWDG��ʼ����
	
}

void WWDG_IRQHandler()//wwdg�����жϷ�����
{
	WWDG_SetCounter(0x7F);//ι����
	WWDG_ClearFlag();//�����־λ��ʹ���ж��ܹ����ϲ���������SR�Ĵ�����0λ
	
}
