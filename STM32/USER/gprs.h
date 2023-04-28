#ifndef __GPRS_H
#define __GPRS_H

#include "stm32f10x.h"

/*-------------------------- 函 数 声 明	--------------------------*/

int check_status(void);                                 // 检查模块状态，AT、读卡、注册
int send_sms(void);                                     // 发送英文短信

#endif
