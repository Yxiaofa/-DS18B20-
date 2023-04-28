#ifndef __MCU_CONFIG_H
#define __MCU_CONFIG_H

#include "stm32f10x.h"
#include <stdio.h>

/*---------------------------- 宏 定 义	----------------------------------------*/
#define BUF_MAX   128                                      // 串口2接收缓存长度


void usart3_init_config(void);                                // 串口2初始化 MCU与GPRS模块通信
void gprs_send_string(char* s);                               // MCU 发送字符串到GPRS
void nvic_init_config(void);                                  // 中断处理函数
void clear_gprs_buf(void);                                    // 清除接收到GPRS的缓存
u8 find_string(char* p);                                      // 查找字符串
u8 gprs_send_cmd(char *b,char *a,u8 times,u8 wait_time);      // MCU发送AT命令函数
char *str_delim(uint8_t num,char *temp,char *delim);          // 字符串分割函数
void send_end(void);                                          // 发送内容结束符
#endif
