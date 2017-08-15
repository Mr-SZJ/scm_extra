#ifndef _LED_H_
#define _LED_H_

#define uchar unsigned char
#define MODE_RGB 0
#define MODE_LIST 1

//初始化
void led_init();

//设置颜色
void set_led_color(unsigned char r,unsigned char g,unsigned char b);
 
//启动指定颜色模式
void start_RGB_mode();
//显示颜色序列模式
void start_LIST_mode(unsigned char list);

void led_start();
#endif