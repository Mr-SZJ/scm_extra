#ifndef _LED_H_
#define _LED_H_

#define uchar unsigned char
#define MODE_RGB 0
#define MODE_LIST 1

//��ʼ��
void led_init();

//������ɫ
void set_led_color(unsigned char r,unsigned char g,unsigned char b);
 
//����ָ����ɫģʽ
void start_RGB_mode();
//��ʾ��ɫ����ģʽ
void start_LIST_mode(unsigned char list);

void led_start();
#endif