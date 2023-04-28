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

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//使能复用功能时钟

    //GPIOB8 中断线以及中断初始化配置   下降沿触发
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;	
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   

  	NVIC_InitStructure.NVIC_IRQChannel =EXTI15_10_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
 
}
//外部中断0服务程序 
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
	OLED_Clear();//清全屏白色
	delay_ms(100);
		OLED_ShowCH(0,0,"Tempmax1:   ℃");		//显示中文：距离
	OLED_ShowNum(72,0,temph1,2,16);		//显示温度整数
	while(KEY0!=0)
	{

	if(KEY2==0)
	
	 {
			temph1--;
			if(temph1<1)
				temph1=0;
			OLED_ShowNum(72,0,temph1,2,16);		//显示温度整数
			delay_ms(250);
	 }
	if(KEY1==0) 
	{
		temph1++;
		if(temph1>100)
			temph1=100;
		OLED_ShowNum(72,0,temph1,2,16);		//显示温度整数
		
		delay_ms(250);
		
	}
	}
	delay_ms(10);
	while(KEY0==0);
	delay_ms(10);
	while(KEY0!=0)
		{
		OLED_ShowCH(0,2,"Tempmin1:   ℃");
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
		OLED_ShowCH(0,4,"Tempmax2:   ℃");
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
		OLED_ShowCH(0,6,"Tempmin2:   ℃");
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
	EXTI_ClearITPendingBit(EXTI_Line15); //清除LINE12上的中断标志位
				OLED_Clear();
	OLED_ShowCH(0,1,"Temp1:");		//显示Temp
	OLED_ShowCH(68,1,"℃");		//显示℃
	
	OLED_ShowCH(0,5,"Temp2:");//显示
	OLED_ShowCH(68,5,"℃");//显示
	}
  } 
	  
}
 
