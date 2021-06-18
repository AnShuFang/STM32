#include "stm32f10x.h"
#include "adc.h"
#include "delay.h"


//adc����ģʽ������ģʽ
//����ת��
//�������ת��
//ͨ��һPA1���ܵ�ѹ�ź�
//�����Ҷ���
void ADC_INIT(void)//����ADCͨ����ʼ��
{
	GPIO_InitTypeDef GPIO_Init_Struct;
	ADC_InitTypeDef ADC_Init_Struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//ʹ��adcʱ��
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ϵͳʱ��72MKz,adc����ʱ��С��14MHz,��������6��Ƶ��Ϊ����ʱ��
	ADC_DeInit(ADC1);//ADC��λ��ʼ��
	
	//����GPIO�ڹ���ģʽ��ͨ��һ��ӦPA1��ģ�����루ע�⣬��������ӳ�䣩
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_AIN;//ģ�����룬����CRH,CRL�Ĵ���
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_Init_Struct);
	
	//����ADC��ʼ����ʹ�乤���ڶ���ģʽ������������Ҷ����
	ADC_Init_Struct.ADC_ContinuousConvMode=DISABLE;//�ر�����ģʽ������CR2�Ĵ���
	ADC_Init_Struct.ADC_DataAlign=ADC_DataAlign_Right;//���ݶ��룬�Ҷ��룬����CR2�Ĵ���
	ADC_Init_Struct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//���ⲿ���������������������CR2�Ĵ���
	ADC_Init_Struct.ADC_Mode=ADC_Mode_Independent;//���ù���ģʽΪ����ģʽ������CR1�Ĵ���
	ADC_Init_Struct.ADC_NbrOfChannel=1;//ͨ������������SQR1�Ĵ���
	ADC_Init_Struct.ADC_ScanConvMode=DISABLE;//�ر�ɨ��ģʽ������CR1�Ĵ���
	ADC_Init(ADC1,&ADC_Init_Struct);
	
	//ʹ��ADC1
	ADC_Cmd(ADC1,ENABLE);//����CR2�Ĵ�����
	
	//adcУ׼����
	ADC_ResetCalibration(ADC1);//��λУ׼
	while(ADC_GetResetCalibrationStatus(ADC1));//�ȴ�У׼����
	ADC_StartCalibration(ADC1);//����adcУ׼
	while(ADC_GetCalibrationStatus(ADC1));//�ȴ�У׼����
}
//����ͨ�����������ڣ���ò���ֵ
u16 Get_Adc(void)// ��ȡ����ת������
{
	//ͨ���������ã�����ͨ��������˳�򣬲�������
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);//����ĳһ��ͨ����˳�򣬲������ڣ�����SQR1�Ĵ�����SMPR�Ĵ���
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//�����������ת��������CR2�Ĵ���
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//�ȴ�װ������
	return(ADC_GetConversionValue(ADC1));
}
//��β���ȡƽ��ֵ����߲�������
u16 Get_Adc_Average(u8 times)
{
  u32 temp_val=0;
	u8 t;
	for(t=0;t<=times;t++)
	{
		temp_val+=Get_Adc();
		delay_ms(5);
		
	}
	return temp_val/times;
}







