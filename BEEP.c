#include "stm32h10x.h" 
#include "sys.h"
#include "delay.h"
// ���������������ܼ��缫�������ܻ�����PB8�������ߵ�ƽ��Ч 
void BEEP_Init(void)
{
	RCC->APB2ENR|=1<<3;//GPIOBʱ��ʹ��
	
	GPIOB->CRH &= oxFFFFFFF0;
	GPIOB->CRH |= ox00000003; //���ù���ģʽ
	
	GPIOB->ODR &= oxFFFFFEFF;//��ʼ����͵�ƽ
	// GPIOB->BRR|=1<<8;//����BRR�Ĵ�����ʼ�� 
	//PBout(8)=0;//���õ�ַӳ���Ӧ��bitλ��ʼ����PBout�Ǻ궨���ַ������ 
	 
}
int main()
{
	delay_init(10);//���� 
	BEEP_Init();
	while(1)
	{
		GPIOB->BSRR|=1<<8;
		delay_ms(1000);
		GPIOB->BSR|=1<<8;
	}
	return 0;
}
