#include "stm32f10x.h"
#include "key.h"
void Key_Init(void)
{
  GPIO_InitTypeDef GPIO_Struct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//ʹ��GPIOE����
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOA����
	
  GPIO_Struct.GPIO_Pin=GPIO_Pin_3;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOE,&GPIO_Struct);//PE.3��ʼ��
	
	GPIO_Struct.GPIO_Pin=GPIO_Pin_4;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOE,&GPIO_Struct);//PE.4��ʼ��
	
	GPIO_Struct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init(GPIOA,&GPIO_Struct);//PA.0��ʼ��
   
}