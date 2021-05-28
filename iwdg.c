#include "stm32f10x.h"
#include "iwdg.h"

void Iwdg_Init(uint8_t prescaler,uint16_t count)//ʹ�ô˺����������Ź��򿪣���ʱʱ����2����������
{
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);//��KR�Ĵ�����д��ox5555,����PR,RLR�Ĵ�����д��
	IWDG_SetPrescaler(prescaler);//����Ԥ��Ƶϵ��������PR�Ĵ���
	IWDG_SetReload(count);//���ü�������ֵ������RLR�Ĵ�����0-11λ��Ч��ֵС��0xfff;
	IWDG_Enable();//ʹ��iwdg,��KR�Ĵ�����д��oxcccc�����Ź���ʼ������IWDG_ReloadCounter����ι����������KR�Ĵ�����д��oxaaaa;
}