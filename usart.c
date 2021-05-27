#include "stm32f10x.h"
#include "usart.h"

void usart_Init() //stm32����1��ʼ��
{
	GPIO_InitTypeDef GPIO_Struct;//gpio�˿�����
	USART_InitTypeDef USART_Struct;//���ڲ�������
	NVIC_InitTypeDef NVIC_Struct;//�ж�����
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);//ʹ��GPIOA�봮��1ʱ��
	
	GPIO_Struct.GPIO_Pin=GPIO_Pin_9;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Struct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Struct);//PA10�ڳ�ʼ����
	
	GPIO_Struct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Struct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIO_Struct);//PA10�ڳ�ʼ����
	
	USART_Struct.USART_BaudRate=115200;
	USART_Struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Struct.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Struct.USART_Parity=USART_Parity_No;
	USART_Struct.USART_StopBits=USART_StopBits_1;
	USART_Struct.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_Struct);//���ڲ�������
	
	USART_Cmd(USART1,ENABLE);//����ʹ��
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_Struct.NVIC_IRQChannel=USART1_IRQn;
	NVIC_Struct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Struct.NVIC_IRQChannelPreemptionPriority=2;
	NVIC_Struct.NVIC_IRQChannelSubPriority=2;
	NVIC_Init(&NVIC_Struct);//�ж����ȼ�����
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);//����USART���ж�����
	
}

void USART1_IQRHandler(void)
{
	u8 res;
	if(USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
	{
		res=USART_ReceiveData(USART1);
		 USART_SendData(USART1,res);
	}
	
}
