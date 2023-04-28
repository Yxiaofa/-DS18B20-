/***************************************************************************
 * 文件名称 ：gprs.c
 * 描    述 ：GPRS核心板测试函数库，包含了发送英文短信的部分AT命令        
 * 实验平台 ：STM32F103vet6开发板
 * 硬件连接 ：无
 * 库版本   ：STM32F10x_StdPeriph_Lib_V3.5.0
 * 说    明 ：本例程对短信接收方号码已做修改，直接测试会出现短信发送失败，
 *            所以测试前请先修改好短信接收方号码
*****************************************************************************/
#include "gprs.h"
#include "mcu_config.h"
#include "string.h"
#include "sys.h"
#include "delay.h"
/*-------------------------- 变 量 声 明 ---------------------------------------*/

extern u8   buf_address;                                            // 缓存首地址初始值为0
extern char gprs_buf[BUF_MAX];                                      // 串口1接收缓存
extern u8 tempsum1,tempsum2,temph1,temph2;

/*-------------------------- 常 量 声 明 ---------------------------------------*/
static char *SMS_NUM = "AT+CMGS=\"15689316332\"";                   // 11位短信接收方号码，请自行修改
/******************************************************************************
* 函数名称: check_status
* 描    述: 核心板基本状态测试
* 输入参数: 
* 输    出: 
* 返    回: 0 --- 出错  1 --- 正确
* 说    明: 核心板开机后，先判断AT命令是否正常、能否读到卡、能否注册网络。确认无误后
*           再进行其他功能测试
*******************************************************************************/
int check_status(void)
{

  // 同步波特率   	
	if(!gprs_send_cmd("AT","OK",2,10)) 	 return 0;

  // 查询核心板能否读到SIM卡            
	if(!gprs_send_cmd("AT+CPIN?","+CPIN: READY",2,10))	return 0;	

	// 查询核心板是否注册成功             
	if(!gprs_send_cmd("AT+CREG?","+CREG: 0,1",5,100))	 return 0;

	// 取消回显             
	if(!gprs_send_cmd("ATE0","OK",1,10))	 return 0;
	
	return 1;
}

/******************************************************************************
* 函数名称: send_sms
* 描    述: 发送英文短信
* 输入参数: 无
* 输    出: 无
* 返    回: 0 -- 短信配置失败    1 -- 短信配置成功
* 说    明:
*******************************************************************************/
int send_sms(void)
{
	if(!gprs_send_cmd("AT+CMGF=1","OK",1,10)) 
		 return 0;
	if(!gprs_send_cmd("AT+CSMP=17,11,0,0","OK",1,10)) 
		 return 0;
	if(!gprs_send_cmd("AT+CSCS= \"IRA\"","OK",1,10)) 		 return 0;

	if(gprs_send_cmd(SMS_NUM,">",1,10)) 
		
	{		
		if(tempsum1>temph1)
		 gprs_send_string("Temp1 is too high!\r\n");
		if(tempsum2>temph2)
			gprs_send_string("Temp2 is too high!\r\n");
	   delay_ms(50);
	   send_end();	
	}
	else
	{
		 return 0;
	}

	return 1;
}



