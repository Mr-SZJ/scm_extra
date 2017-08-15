#include "led.h"
#include <reg52.h>
#define LENGTH_MODE_LIST1 4
#define LENGTH_MODE_LIST2 4
#define LENGTH_MODE_LIST3 4
#define LENGTH_MODE_LIST4 4

//定义三色LED灯的各个颜色对应的引脚
sbit LED1_RED = P2^0;
sbit LED1_GREEN = P2^1;
sbit LED1_BLUE = P2^2;
sbit LED2_RED = P2^3;
sbit LED2_GREEN = P2^4;
sbit LED2_BLUE = P2^5;
sbit LED3_RED = P0^0;
sbit LED3_GREEN = P0^1;
sbit LED3_BLUE = P0^2;
sbit LED4_RED = P0^3;
sbit LED4_GREEN = P0^4;
sbit LED4_BLUE = P0^5;
sbit TEST = P0^0;

struct mode_structure{
	uchar ms;//单位50毫秒,20为1秒,最大值255(时间12.7秒)
	uchar r;
	uchar g;
	uchar b;
};

code struct mode_structure mode_list1[LENGTH_MODE_LIST1][4] = {
	{{10,0x7f,0x3d,0x34},{10,0,0,0},{10,0,0,0},{10,0,0,0}},
	{{10,0,0,0},{10,0x7f,0x3d,0x34},{10,0,0,0},{10,0,0,0}},
	{{10,0,0,0},{10,0,0,0},{10,0x7f,0x3d,0x34},{10,0,0,0}},
	{{10,0,0,0},{10,0,0,0},{10,0,0,0},{10,0x7f,0x3d,0x34}},	
};

code struct mode_structure mode_list2[LENGTH_MODE_LIST1][4] = {
	{{10,0x7f,0x3d,0x34},{10,0x7f,0x3d,0x34},{10,0,0,0},{10,0,0,0}},
	{{10,0,0,0},{10,0x7f,0x3d,0x34},{10,0x7f,0x3d,0x34},{10,0,0,0}},
	{{10,0,0,0},{10,0,0,0},{10,0x7f,0x3d,0x34},{10,0x7f,0x3d,0x34}},
	{{10,0x7f,0x3d,0x34},{10,0,0,0},{10,0,0,0},{10,0x7f,0x3d,0x34}},	
};

code struct mode_structure mode_list3[LENGTH_MODE_LIST1][4] = {
	{{10,0x7f,0x3d,0x34},{10,0x7f,0x3d,0x34},{10,0,0,0},{10,0,0,0}},
	{{10,0,0,0},{10,0,0,0},{10,0x7f,0x3d,0x34},{10,0x7f,0x3d,0x34}},
	{{10,0x7f,0x3d,0x34},{10,0x7f,0x3d,0x34},{10,0,0,0},{10,0,0,0}},
	{{10,0,0,0},{10,0,0,0},{10,0x7f,0x3d,0x34},{10,0x7f,0x3d,0x34}},	
};

code struct mode_structure mode_list4[LENGTH_MODE_LIST1][4] = {
	{{10,0xff,0xff,0xff},{10,0,0,0},{10,0,0,0},{10,0,0,0}},
	{{10,0,0,0},{10,0x7f,0x3d,0x34},{10,0,0,0},{10,0,0,0}},
	{{10,0,0,0},{10,0,0,0},{10,0xff,0xff,0xff},{10,0,0,0}},
	{{10,0,0,0},{10,0,0,0},{10,0,0,0},{10,0x7f,0x3d,0x34}},	
};

//工作模式
uchar mode;
struct mode_structure* mode_instance;

//静态模式颜色值
uchar COLOR_RED = 0xf4;
uchar COLOR_GREEN = 0xa4;
uchar COLOR_BLUE = 0x3d;
//静态模式

uchar temp = 0;
uchar counter = 0;
uchar mode_list_index = 0;
uchar mode_list_length = 0;

void led_init(){
	
	//刚开始灭灯
	LED1_RED = LED1_GREEN = LED1_BLUE = 0;
	LED2_RED = LED2_GREEN = LED2_BLUE = 0;
	LED3_RED = LED3_GREEN = LED3_BLUE = 0;
	LED4_RED = LED4_GREEN = LED4_BLUE = 0;
	
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
		if(mode == MODE_RGB){
			for(temp = 0;temp<256;temp++){
				if(temp < COLOR_RED){
					LED1_RED = 1;
					LED2_RED = 1;
					LED3_RED = 1;
					LED4_RED = 1;
				}else{
					LED1_RED = 0;
					LED2_RED = 0;
					LED3_RED = 0;
					LED4_RED = 0;
				}
				if(temp < COLOR_GREEN){
					LED1_GREEN = 1;
					LED2_GREEN = 1;
					LED3_GREEN = 1;
					LED4_GREEN = 1;
				}else{
					LED1_GREEN = 0;
					LED2_GREEN = 0;
					LED3_GREEN = 0;
					LED4_GREEN = 0;
				}
				if(temp < COLOR_BLUE){
					LED1_BLUE = 1;
					LED2_BLUE = 1;
					LED3_BLUE = 1;
					LED4_BLUE = 1;
				}else{
					LED1_BLUE = 0;
					LED2_BLUE = 0;
					LED3_BLUE = 0;
					LED4_BLUE = 0;
				}
			}
			continue;
		}
		for(temp = 0;temp<256;temp++){
			//LED1的PWM
			if(temp < (mode_instance+mode_list_index)->r){
				LED1_RED = 1;
			}else{
				LED1_RED = 0;
			}
			if(temp < (mode_instance+mode_list_index)->g){
				LED1_GREEN = 1;
			}else{
				LED1_GREEN = 0;
			}
			if(temp < (mode_instance+mode_list_index)->b){
				LED1_BLUE = 1;
			}else{
				LED1_BLUE = 0;
			}
			//LED2的PWM
			if(temp < (mode_instance+mode_list_index+1)->r){
				LED2_RED = 1;
			}else{
				LED2_RED = 0;
			}
			if(temp < (mode_instance+mode_list_index+1)->g){
				LED2_GREEN = 1;
			}else{
				LED2_GREEN = 0;
			}
			if(temp < (mode_instance+mode_list_index+1)->b){
				LED2_BLUE = 1;
			}else{
				LED2_BLUE = 0;
			}
			//LED3的PWM
			if(temp < (mode_instance+mode_list_index+2)->r){
				LED3_RED = 1;
			}else{
				LED3_RED = 0;
			}
			if(temp < (mode_instance+mode_list_index+2)->g){
				LED3_GREEN = 1;
			}else{
				LED3_GREEN = 0;
			}
			if(temp < (mode_instance+mode_list_index+2)->b){
				LED3_BLUE = 1;
			}else{
				LED3_BLUE = 0;
			}
			//LED4的PWM
			if(temp < (mode_instance+mode_list_index+3)->r){
				LED4_RED = 1;
			}else{
				LED4_RED = 0;
			}
			if(temp < (mode_instance+mode_list_index+3)->g){
				LED4_GREEN = 1;
			}else{
				LED4_GREEN = 0;
			}
			if(temp < (mode_instance+mode_list_index+3)->b){
				LED4_BLUE = 1;
			}else{
				LED4_BLUE = 0;
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
			mode_instance = &mode_list1[0];
			mode_list_length = LENGTH_MODE_LIST1;
			break;
		case 1:
			mode_instance = &mode_list2[0];
			mode_list_length = LENGTH_MODE_LIST2;
			break;
		case 2:
			mode_instance = &mode_list3[0];
			mode_list_length = LENGTH_MODE_LIST3;
			break;
		case 3:
			mode_instance = &mode_list4[0];
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
			mode_list_index+=4;
			counter = 0;
			//结构体数组循环
			if(mode_list_index >= ((mode_list_length-1) * 4)){
			mode_list_index = 0;
			}
		}
		//P0 = (mode_instance+mode_list_index)->ms;
		
	}
}
