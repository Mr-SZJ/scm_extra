#include "led.h"
#include <reg52.h>
#define LENGTH_MODE_LIST1 45
#define LENGTH_MODE_LIST2 4
#define LENGTH_MODE_LIST3 4
#define LENGTH_MODE_LIST4 4

//定义三色LED灯的各个颜色对应的引脚
sbit LED_RED = P2^0;
sbit LED_GREEN = P2^1;
sbit LED_BLUE = P2^2;
sbit TEST = P0^0;

struct mode_structure{
	uchar ms;//单位50毫秒,20为1秒,最大值255(时间12.7秒)
	uchar r;
	uchar g;
	uchar b;
};

code struct mode_structure mode_list1[LENGTH_MODE_LIST1] = {
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	
	
	{15,0xdd,0x02,0xfb},
	{15,0x45,0x23,0x34},
	{15,0xdd,0x02,0xfb},
	{15,0x45,0x23,0x34},
	{15,0xdd,0x02,0xfb},
	{15,0x45,0x23,0x34},
	
	{40,0x4c,0xa9,0xa4},
	{40,0x81,0x3a,0x74},
	
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	{10,0xff,0x3d,0x34},
	{5,0x33,0x99,0xa4},
	
	{10,0xfd,0x4d,0xf2},
	{10,0x88,0xa2,0xe4},
	{10,0xfd,0x4d,0xf2},
	{10,0x88,0xa2,0xe4},
	
	{20,0x33,0xcc,0x5c},
	{20,0x69,0x00,0x55},
		{20,0x33,0xcc,0x5c},
	{20,0x69,0x00,0x55},
		{20,0x33,0xcc,0x5c},
	{20,0x69,0x00,0x55},
		{20,0x33,0xcc,0x5c},
	{20,0x69,0x00,0x55},
		{20,0x33,0xcc,0x5c},
	{20,0x69,0x00,0x55},
		{20,0x33,0xcc,0x5c},
	{20,0x69,0x00,0x55},
	
	{100,0xff,0xff,0xff}
};
code struct mode_structure mode_list2[LENGTH_MODE_LIST2] = {
	{100,0xf3,0xf3,0x5b},
	{100,0x1f,0x3d,0x3a},
	{100,0x4c,0xa9,0xa4},
	{100,0x81,0x3a,0x74}
};
struct mode_structure mode_list3[LENGTH_MODE_LIST3] = {
	{15,0xfa,0xad,0xf3},
	{5,0x4f,0xdd,0xa3},
	{3,0x33,0xcc,0x5c},
	{8,0x69,0x00,0x55}
};
struct mode_structure mode_list4[LENGTH_MODE_LIST4] = {
	{5,0xfa,0x6d,0xff},
	{4,0xa5,0xcc,0xa3},
	{7,0xfd,0x4d,0xf2},
	{10,0x88,0xa2,0xe4}
};

//工作模式
uchar mode;
struct mode_structure* mode_instance;

//颜色值
uchar COLOR_RED = 0xf4;
uchar COLOR_GREEN = 0xa4;
uchar COLOR_BLUE = 0x3d;

uchar temp = 0;
uchar counter = 0;
uchar mode_list_index = 0;
uchar mode_list_length = 0;

void led_init(){
	
	//刚开始灭灯
	LED_RED = LED_GREEN = LED_BLUE = 0;
	start_LIST_mode(0);
	
	//启动定时器0
	TMOD = 0x01;
  TH0 = 0x4C;//定时50ms,PWM波20Hz
  TL0 = 0x00;
	EA = 1;
	ET0 = 1;
	PT0 = 1;
	TR0 = 1;
}

//启动PWM控制ＬＥＤ灯
void led_start(){
	while(1){
		for(temp = 0;temp<256;temp++){
				if(temp < COLOR_RED){
				LED_RED = 1;
			}else{
				LED_RED = 0;
			}
			if(temp < COLOR_GREEN){
				LED_GREEN = 1;
			}else{
				LED_GREEN = 0;
			}
			if(temp < COLOR_BLUE){
				LED_BLUE = 1;
			}else{
				LED_BLUE = 0;
			}	
		}
	}
}


//设置静态模式下LED灯的颜色值
void set_led_color(unsigned char r,unsigned char g,unsigned char b){
	COLOR_RED = r;
	COLOR_GREEN = g;
	COLOR_BLUE = b;
}

//启动静态模式
void start_RGB_mode(){
	mode = MODE_RGB;
}

//启动动态模式
void start_LIST_mode(unsigned char list){
	mode = MODE_LIST;
	mode_list_index = 0;
	counter = 0;
	switch(list){
		case 0:
			mode_instance = mode_list1;
			mode_list_length = LENGTH_MODE_LIST1;
			break;
		case 1:
			mode_instance = mode_list2;
			mode_list_length = LENGTH_MODE_LIST2;
			break;
		case 2:
			mode_instance = mode_list3;
			mode_list_length = LENGTH_MODE_LIST3;
			break;
		case 3:
			mode_instance = mode_list4;
			mode_list_length = LENGTH_MODE_LIST4;
			break;
	}
}

//20Hz频率，用于动态模式下改变颜色值
void timer0() interrupt 1{
	TH0 = 0x4C;
  TL0 = 0x00;
	if(mode == MODE_RGB){
		
	}else{
		//动态变化颜色模式
		counter++;
		if(counter > (mode_instance+mode_list_index)->ms){
			//显示下一种颜色
			mode_list_index++;
			counter = 0;
			COLOR_RED = (mode_instance+mode_list_index)->r;
			COLOR_GREEN = (mode_instance+mode_list_index)->g;
			COLOR_BLUE = (mode_instance+mode_list_index)->b;
			//结构体数组循环
			if(mode_list_index >= mode_list_length-1){
			mode_list_index = 0;
			}
		}
		//P0 = (mode_instance+mode_list_index)->ms;
		
	}
}
