//单片机调用函数需要的头文件
#include "sys.h"  
#include "delay.h"
#include "oled_iic.h"
#include "stdio.h"
#include "usart.h"	  
#include "key.h"
#include "exti.h"
#include "led.h"
#include "adc.h"
#include "beep.h"
#include "relay.h"
#include "gprs.h"
#include "timer.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
extern u8 temp1,temp2,temp3,temp4,tempsum1,tempsum2;//温度1/2
extern u8 temph1,temph2,flag1,flag2,templ1,templ2;//温湿阈值
void phone(void);//短信发送函数
int main(void)
{	
	delay_init();	//延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级	
	Usart1_Init(115200);//串口1初始化
	while(1){
	// 判断核心板状态是否正常
	if(check_status())                                   
	{
	   break;
	}
     delay_ms(100);
	}
	   LED1=1;
	   LED2=1;
			
	EXTIX_Init();	//外部中断初始化
	KEY_Init();		//初始化按键
	LED_Init();   //LED初始化
	Beep_Init();  //蜂鸣器初始化
	Relay_Init(); //继电器初始化
	OLED_Init();	//OLED屏幕初始化	
	OLED_Clear();//OLED清屏
	OLED_ShowCH(0,1,"Temp1:");		//显示Temp1
	OLED_ShowCH(68,1,"℃");		//显示℃
	
	OLED_ShowCH(0,5,"Temp2:");//显示
	OLED_ShowCH(68,5,"℃");//显示
	TIM3_Int_Init(999,7199);//10Khz的计数频率，计数到5000为500ms  
	TIM4_Int_Init(999,7199);//10Khz的计数频率，计数到5000为500ms 
	Usart2_Init(9600);//串口2初始化.
	while(1)
	{	
		if(flag1&&flag2)
		{	
			UsartPrintf(USART1, "ATH\r\n");
			flag1=flag2=0;			

				if((tempsum1>temph1)||(tempsum1<templ1))       //1节点超出
			{
					TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );  //使能指定的TIM3中断,允许更新中断,LED1翻转
			}	
       else	
			 {
				 	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE ); 
			 }				 
			if((tempsum2<templ2)||(tempsum2>temph2))       //1节点超出
			{
					TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //使能指定的TIM4中断,允许更新中断,LED2翻转
			}		
			else
			{
				  TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE );
			}
			if((tempsum1>temph1)||(tempsum2>temph2))       //1节点超出
			{
					Relay1=0;                                  //继电器1启动
			}		
			else
			{
					Relay1=1;
			}  
			
			if((tempsum1<templ1)||(tempsum2<templ2))
			{
				Relay2=0;
			}					
       else 
      {
        Relay2=1;
			}
			if((tempsum1>temph1)||(tempsum2>temph2)||(tempsum1<templ1)||(tempsum2<templ2))//如果超出阈值
			{
				Beep=0;//蜂鸣器开启	
				USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);//关闭串口接受中断
				USART_Cmd(USART2, DISABLE);//关闭串口
				
			if((tempsum1>temph1)&&(tempsum2>temph2))//如果超出阈值
			{		
				phone();				
			}
			if((tempsum1<templ1)&&(tempsum2<templ2))//如果超出阈值
			{		
				phone();				
			}
			
			  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
				USART_Cmd(USART2, ENABLE);//开启串口接收
		}
				else 
				{
					Beep=1;//蜂鸣器关闭
					LED1=1;
					LED2=1;
				}
		}
	}
}

void phone(void)
{
		{
			UsartPrintf(USART1, "ATD15254819559;\r\n"); //	
	    	
				delay_ms(1000);
		  	delay_ms(1000);
				delay_ms(1000);
			  delay_ms(1000);
			  delay_ms(1000);
			  delay_ms(1000);
				delay_ms(1000);
			  delay_ms(1000);
				delay_ms(1000);
			  delay_ms(1000);
			  delay_ms(1000);
			  delay_ms(1000);
				delay_ms(1000);
		}
}


