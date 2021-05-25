#include "stm32f10x.h"
#include "key.h"
void Key_Init(void)
{
  GPIO_InitTypeDef GPIO_Struct;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);//使能GPIOE外设
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA外设
	
  GPIO_Struct.GPIO_Pin=GPIO_Pin_3;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOE,&GPIO_Struct);//PE.3初始化
	
	GPIO_Struct.GPIO_Pin=GPIO_Pin_4;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIOE,&GPIO_Struct);//PE.4初始化
	
	GPIO_Struct.GPIO_Pin=GPIO_Pin_0;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init(GPIOA,&GPIO_Struct);//PA.0初始化
   
}