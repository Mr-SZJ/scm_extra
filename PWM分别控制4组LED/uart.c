#include "uart.h"
#include "led.h"
#include <reg52.h>

uchar ch;
uchar pre_char;
uchar is_ready = 0;
uchar rowdata[4];
uchar rowdata_index = 0;

void uart_init(){

	TMOD = TMOD|0x20;
	SCON = 0x50;
	TH1 = 0xfd;
	TL1 = TH1;
	PCON = 0x00;
	PS = 1;
	ES = 1;	
	EA = 1;
	TR1 = 1;

}

void UART() interrupt 4{
	if(TI){
		TI = 0;
	}else{
		ch = SBUF;
		
		if(is_ready){
		//把三个颜色保存到数组 
			rowdata[rowdata_index++] = ch;
			
			if(rowdata_index > 3){
				if(rowdata[0] == CMD_RGB){
					// RGB color
					set_led_color(rowdata[1],rowdata[2],rowdata[3]);
					start_RGB_mode();
				}else if(rowdata[0] == CMD_MODE){
					//list mode
					start_LIST_mode(rowdata[1]);
				}
				is_ready = 0;
				rowdata_index = 0;
				//P1 = rowdata[0];
			}
		}
		
		//检测到数据包头
		if(pre_char == 0xa5 && ch == 0x5a){
			is_ready = 1;
			rowdata_index = 0;
			//P1 = 0x00;
		}
		
		pre_char = ch;
		RI = 0;
	}
}
