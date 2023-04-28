/*************************************************************************
 * 文件名称 ：mcu_config.c
 * 描    述 ：串口通信驱动函数         
 * 实验平台 ：STM32F103vet6开发板
 * 硬件连接 ：串口1用于与电脑通讯及程序下载，串口2用于与评估板通讯
 *    （开发板串口2）
 *         Usart2 ---------GPRS模块
 *        PA2  (TXD)----------->  RXD   
 *			  PA3  (RXD) ---------->  TXD   
 *        GND  ---------------> GND
 *    (开发板串口1)
 *         Usart1 : -------  电 脑
 *			  PA9 （TXD） ------->   TXD  
 *		    PA10 （RXD）------->   RXD  
 *        GND   -------------->  GND
 * 库版本  ：STM32F10x_StdPeriph_Lib_V3.5.0
*****************************************************************************/
#include "mcu_config.h"
#include "string.h"
#include "delay.h"
#include "stm32f10x_usart.h"
/*---------------------------- 函 数 声 明	---------------------------------*/
void USART1_gpio_config(void);
void USART1_parameter_config(void);

/*---------------------------- 变 量 声 明	---------------------------------*/
u8   buf_address = 0;                             // 缓存首地址初始值为0
char gprs_buf[BUF_MAX];                           // 串口2接收缓存

/*************************************************************************
* 函数名称: usart1_init_config
* 描    述: 串口1初始化配置
* 输    入: 无
* 输    出: 无
* 返    回: 无 
* 说    明: 无
*************************************************************************/

/*************************************************************************
* 函数名称: usart2_init_config
* 描    述: 串口2初始化设置
* 输    入: 无
* 输    出: 无
* 返    回: 无 
* 说    明: 无
*************************************************************************/




/*void USART1_IRQHandler(void)                	
{
			u8 res=0;
  res =USART_ReceiveData(USART1);
	USART_ClearFlag(USART1, USART_FLAG_RXNE);
			gprs_buf[buf_address] = res;        // 将接收到的字符串存到缓存中
	
			buf_address++;                      // 缓存指针向后移动
			if(buf_address > BUF_MAX)       		// 如果缓存满,将缓存指针指向缓存的首地址
			{
				buf_address = 0;
			}      
} */

void USART1_IRQHandler(void)  
{
	u8 res;	 
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)//接收到数据
	{	 
	res =USART_ReceiveData(USART1);
		USART_ClearFlag(USART1, USART_FLAG_RXNE);
			gprs_buf[buf_address] = res;        // 将接收到的字符串存到缓存中
	
			buf_address++;                      // 缓存指针向后移动
			if(buf_address > BUF_MAX)       		// 如果缓存满,将缓存指针指向缓存的首地址
			{
				buf_address = 0;
			}     
  }
}

/*************************************************************************
* 函数名称: clear_gprs_buf
* 描    述: 清除串口2缓存数据
* 输    入: 无
* 输    出: 无
* 返    回: 无 
* 说    明: 无
*************************************************************************/
void clear_gprs_buf(void)
{
	 memset(gprs_buf,0,BUF_MAX);
   buf_address = 0;                                        // 接收字符串的起始存储位置
}


/*******************************************************************************
* 函数名称: find_string
* 描    述: 判断缓存中是否含有指定的字符串
* 输入参数: 字符串 p
* 输    出: 无
* 返    回: unsigned char:1 找到指定字符，0 未找到指定字符
* 说    明: 调用extern char *strstr(char *str1, char *str2)该函数，
*******************************************************************************/

u8 find_string(char* p)
{ 
	if(strstr(gprs_buf,p)!=NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*******************************************************************************
* 函数名称: gprs_send_cmd 
* 描    述: 发送AT指令函数
* 输入参数: b--- 发送数据的指针(命令)
*           a--- 希望接收到的应答数据指针（应答）
*           times---如果应答数据有误，循环发送AT命令的次数
*						wait_time ----发送等待时间(单位：20ms)
* 输    出: 无
* 返    回: 正确---1   错误---0
* 说    明: 无
*******************************************************************************/
u8 gprs_send_cmd(char *b,char *a,u8 times,u8 wait_time)         
{
	u8 i;
	i = 0;
	clear_gprs_buf();                    // 清除串口2缓存数据
	while(i < times)                    
	{
    gprs_send_string(b);
		gprs_send_string("\r\n");	         // 回车换行
	  delay_ms(wait_time*50);
    if(find_string(a))
	  {
	     return 1;
	  }
	  i++;
	}
	return 0;
}

/*******************************************************************************
* 函数名  : gprs_send_string
* 描述    : USART2发送字符串
* 输入    : *s 字符串指针
* 输出    : 无
* 返回    : 无 
* 说明    : 无
*******************************************************************************/
void gprs_send_string(char* s)
{
	while(*s)                                                   // 检测字符串结束符
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
		USART_SendData(USART1 ,*s++);                             // 发送当前字符
	}
}

/******************************************************************************
* 函数名称:str_delim
* 描    述:字符串分割函数
* 输入参数: num   0---取出分隔字符串（delim）前面的字符串  1---取出分隔字符串（delim）后面的字符串
*           temp  要分割的字符串
*           delim 分隔符字符串
* 输    出: 无
* 返    回: 分割后的字符串
* 说    明:          
*******************************************************************************/
char *str_delim(uint8_t num,char *temp,char *delim)
{
	int i;
	char *str[2]={0};
	char *tok=temp;
	char *restr;
	for(i=0;i<2;i++)
	{
		tok=strtok(tok,delim);
		str[i]=tok;
		tok = NULL;
	}
	restr=str[num];
  return restr;
}

/******************************************************************************
* 函数名称: send_end
* 描    述: 发送内容结束符
* 输入参数: 无
* 输    出: 无
* 返    回: 无
* 说    明:当输入完内容后，以16进制发送内容结束符0x1A
*******************************************************************************/
void send_end(void)
{
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC)==RESET); 
	USART_SendData(USART1 ,0X1A);   
}

