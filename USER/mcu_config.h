#ifndef __MCU_CONFIG_H
#define __MCU_CONFIG_H

#include "stm32f10x.h"
#include <stdio.h>

/*---------------------------- �� �� ��	----------------------------------------*/
#define BUF_MAX   128                                      // ����2���ջ��泤��


void usart3_init_config(void);                                // ����2��ʼ�� MCU��GPRSģ��ͨ��
void gprs_send_string(char* s);                               // MCU �����ַ�����GPRS
void nvic_init_config(void);                                  // �жϴ�����
void clear_gprs_buf(void);                                    // ������յ�GPRS�Ļ���
u8 find_string(char* p);                                      // �����ַ���
u8 gprs_send_cmd(char *b,char *a,u8 times,u8 wait_time);      // MCU����AT�����
char *str_delim(uint8_t num,char *temp,char *delim);          // �ַ����ָ��
void send_end(void);                                          // �������ݽ�����
#endif
