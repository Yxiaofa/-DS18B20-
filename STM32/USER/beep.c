#include "stm32f10x.h"
#include "beep.h"


void Beep_Init(void)
{ 
 GPIO_InitTypeDef  GPIO_InitStructure;	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	//使能GPIOA时钟 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;				  //PA8
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;    
 GPIO_Init(GPIOB,&GPIO_InitStructure);
 GPIO_SetBits(GPIOB,GPIO_Pin_11);						 
					 
}
