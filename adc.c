#include "stm32f10x.h"
#include "adc.h"
#include "delay.h"


//adc工作模式：独立模式
//当次转换
//软件触发转换
//通道一PA1接受电压信号
//数据右对齐
void ADC_INIT(void)//配置ADC通道初始化
{
	GPIO_InitTypeDef GPIO_Init_Struct;
	ADC_InitTypeDef ADC_Init_Struct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//使能adc时钟
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//系统时钟72MKz,adc采样时钟小于14MHz,所以至少6分频作为采样时间
	ADC_DeInit(ADC1);//ADC复位初始化
	
	//配置GPIO口工作模式，通道一对应PA1，模拟输入（注意，这里无重映射）
	GPIO_Init_Struct.GPIO_Mode=GPIO_Mode_AIN;//模拟输入，配置CRH,CRL寄存器
	GPIO_Init_Struct.GPIO_Pin=GPIO_Pin_1;
	GPIO_Init(GPIOA,&GPIO_Init_Struct);
	
	//配置ADC初始化，使其工作在独立模式，软件触发，右对齐等
	ADC_Init_Struct.ADC_ContinuousConvMode=DISABLE;//关闭连续模式，操作CR2寄存器
	ADC_Init_Struct.ADC_DataAlign=ADC_DataAlign_Right;//数据对齐，右对齐，操作CR2寄存器
	ADC_Init_Struct.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;//无外部触发，由软件触发，操作CR2寄存器
	ADC_Init_Struct.ADC_Mode=ADC_Mode_Independent;//配置工作模式为独立模式，操作CR1寄存器
	ADC_Init_Struct.ADC_NbrOfChannel=1;//通道个数，设置SQR1寄存器
	ADC_Init_Struct.ADC_ScanConvMode=DISABLE;//关闭扫描模式，操作CR1寄存器
	ADC_Init(ADC1,&ADC_Init_Struct);
	
	//使能ADC1
	ADC_Cmd(ADC1,ENABLE);//操作CR2寄存器、
	
	//adc校准配置
	ADC_ResetCalibration(ADC1);//复位校准
	while(ADC_GetResetCalibrationStatus(ADC1));//等待校准结束
	ADC_StartCalibration(ADC1);//开启adc校准
	while(ADC_GetCalibrationStatus(ADC1));//等待校准结束
}
//设置通道规则与周期，获得采样值
u16 Get_Adc(void)// 获取采样转换参数
{
	//通道规则配置，采样通道，采样顺序，采样周期
	ADC_RegularChannelConfig(ADC1,ADC_Channel_1,1,ADC_SampleTime_239Cycles5);//配置某一个通道的顺序，采样周期，操作SQR1寄存器与SMPR寄存器
	ADC_SoftwareStartConvCmd(ADC1,ENABLE);//开启软件触发转换，操作CR2寄存器
	while(ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));//等待装换结束
	return(ADC_GetConversionValue(ADC1));
}
//多次采样取平均值，提高采样精度
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







