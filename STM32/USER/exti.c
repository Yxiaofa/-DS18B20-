#include "exti.h"
#include "key.h"
#include "delay.h"
#include "stm32f10x_it.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "oled_iic.h"
#include "delay.h"
#include "beep.h"
#include "led.h"
u8 temph1=30,temph2=30,templ1=20,templ2=20;
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

    //GPIOB8 �ж����Լ��жϳ�ʼ������   �½��ش���
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   

  	NVIC_InitStructure.NVIC_IRQChannel =EXTI15_10_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
 
}
//�ⲿ�ж�0������� 
void EXTI15_10_IRQHandler(void)
{
	LED0=0;
	Beep=1;
	if(KEY0==0)
	{
		OLED_Clear();
		LED0=1;
	delay_ms(10);
//	while(KEY0==0);
	delay_ms(10);
	OLED_Clear();//��ȫ����ɫ
	delay_ms(100);
		OLED_ShowCH(0,0,"Tempmax1:   ��");		//��ʾ���ģ�����
	OLED_ShowNum(72,0,temph1,2,16);		//��ʾ�¶�����
	while(KEY0!=0)
	{

	if(KEY2==0)
	
	 {
			temph1--;
			if(temph1<1)
				temph1=0;
			OLED_ShowNum(72,0,temph1,2,16);		//��ʾ�¶�����
			delay_ms(250);
	 }
	if(KEY1==0) 
	{
		temph1++;
		if(temph1>100)
			temph1=100;
		OLED_ShowNum(72,0,temph1,2,16);		//��ʾ�¶�����
		
		delay_ms(250);
		
	}
	}
	delay_ms(10);
	while(KEY0==0);
	delay_ms(10);
	while(KEY0!=0)
		{
		OLED_ShowCH(0,2,"Tempmin1:   ��");
		OLED_ShowNum(72,2,templ1,2,16);
		if(KEY2==0)
		{
			templ1--;
			if(templ1<1)
				templ1=0;
			OLED_ShowNum(72,2,templ1,2,16);
			delay_ms(250);
		}
		if(KEY1==0) 
	{
		templ1++;
		if(templ1>100)
			templ1=100;
		OLED_ShowNum(72,2,templ1,2,16);
		delay_ms(250);
		
	}
		}
  delay_ms(10);
	while(KEY0==0);
	delay_ms(10);
	while(KEY0!=0)
		{
		OLED_ShowCH(0,4,"Tempmax2:   ��");
		OLED_ShowNum(72,4,temph2,2,16);
		if(KEY2==0)
		{
			temph2--;
			if(temph2<1)
				temph2=0;
			OLED_ShowNum(72,4,temph2,2,16);
			delay_ms(250);
		}
		if(KEY1==0) 
	{
		temph2++;
		if(temph2>100)
			temph2=100;
		OLED_ShowNum(72,4,temph2,2,16);
		delay_ms(250);
		
	}
		}
		delay_ms(10);
	while(KEY0==0);
	delay_ms(10);
	while(KEY0!=0)
		{
		OLED_ShowCH(0,6,"Tempmin2:   ��");
		OLED_ShowNum(72,6,templ2,2,16);
		if(KEY2==0)
		{
			templ2--;
			if(templ2<1)
				templ2=0;
			OLED_ShowNum(72,6,templ2,2,16);
			delay_ms(250);
		}
		if(KEY1==0) 
	{
		templ2++;
		if(templ2>100)
			templ2=100;
		OLED_ShowNum(72,6,templ2,2,16);
		delay_ms(250);
		
	}
		}
	
	{			
	EXTI_ClearITPendingBit(EXTI_Line15); //���LINE12�ϵ��жϱ�־λ
				OLED_Clear();
	OLED_ShowCH(0,1,"Temp1:");		//��ʾTemp
	OLED_ShowCH(68,1,"��");		//��ʾ��
	
	OLED_ShowCH(0,5,"Temp2:");//��ʾ
	OLED_ShowCH(68,5,"��");//��ʾ
	}
  } 
	  
}
 
