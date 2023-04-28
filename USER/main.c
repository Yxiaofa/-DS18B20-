//��Ƭ�����ú�����Ҫ��ͷ�ļ�
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
extern u8 temp1,temp2,temp3,temp4,tempsum1,tempsum2;//�¶�1/2
extern u8 temph1,temph2,flag1,flag2,templ1,templ2;//��ʪ��ֵ
void phone(void);//���ŷ��ͺ���
int main(void)
{	
	delay_init();	//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�	
	Usart1_Init(115200);//����1��ʼ��
	while(1){
	// �жϺ��İ�״̬�Ƿ�����
	if(check_status())                                   
	{
	   break;
	}
     delay_ms(100);
	}
	   LED1=1;
	   LED2=1;
			
	EXTIX_Init();	//�ⲿ�жϳ�ʼ��
	KEY_Init();		//��ʼ������
	LED_Init();   //LED��ʼ��
	Beep_Init();  //��������ʼ��
	Relay_Init(); //�̵�����ʼ��
	OLED_Init();	//OLED��Ļ��ʼ��	
	OLED_Clear();//OLED����
	OLED_ShowCH(0,1,"Temp1:");		//��ʾTemp1
	OLED_ShowCH(68,1,"��");		//��ʾ��
	
	OLED_ShowCH(0,5,"Temp2:");//��ʾ
	OLED_ShowCH(68,5,"��");//��ʾ
	TIM3_Int_Init(999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  
	TIM4_Int_Init(999,7199);//10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms 
	Usart2_Init(9600);//����2��ʼ��.
	while(1)
	{	
		if(flag1&&flag2)
		{	
			UsartPrintf(USART1, "ATH\r\n");
			flag1=flag2=0;			

				if((tempsum1>temph1)||(tempsum1<templ1))       //1�ڵ㳬��
			{
					TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE );  //ʹ��ָ����TIM3�ж�,��������ж�,LED1��ת
			}	
       else	
			 {
				 	TIM_ITConfig(TIM3,TIM_IT_Update,DISABLE ); 
			 }				 
			if((tempsum2<templ2)||(tempsum2>temph2))       //1�ڵ㳬��
			{
					TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM4�ж�,��������ж�,LED2��ת
			}		
			else
			{
				  TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE );
			}
			if((tempsum1>temph1)||(tempsum2>temph2))       //1�ڵ㳬��
			{
					Relay1=0;                                  //�̵���1����
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
			if((tempsum1>temph1)||(tempsum2>temph2)||(tempsum1<templ1)||(tempsum2<templ2))//���������ֵ
			{
				Beep=0;//����������	
				USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);//�رմ��ڽ����ж�
				USART_Cmd(USART2, DISABLE);//�رմ���
				
			if((tempsum1>temph1)&&(tempsum2>temph2))//���������ֵ
			{		
				phone();				
			}
			if((tempsum1<templ1)&&(tempsum2<templ2))//���������ֵ
			{		
				phone();				
			}
			
			  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
				USART_Cmd(USART2, ENABLE);//�������ڽ���
		}
				else 
				{
					Beep=1;//�������ر�
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


