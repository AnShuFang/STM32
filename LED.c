#include "stm32f10x.h" //LED�Ƴ�ʼ������-�Ĵ������ 

 void LED_Init()
	{
		RCC->APB2ENR|=1<<3 ��//GPIOBʱ��ʹ�ܣ� 
		RCC->APB2ENR|=1<<6�� //GPIOEʱ��ʹ�ܣ�
		
		GPIOB->CRL&=oxFF0FFFFF;
		GPIOB->CRL|=ox00300000;//����GPIOB_PIN5���Ź���ģʽ��
		GPIOB->ODR|=1<<5;//��ʼPIN_5��������ߵ�ƽ��
		
		GPIOE->CRL&=oxFF0FFFFF;
		GPIOE->CRL|=ox00300000;//����GPIOE_PIN5���Ź���ģʽ��
		GPIOE->ODR|=1<<5;//��ʼPIN_5��������ߵ�ƽ��
			 
	}
	

