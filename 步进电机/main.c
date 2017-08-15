/*
单片机P0口接电机驱动线的IN1-IN4
*/
#include <reg51.h>
#define MOTOR P0
#define uchar unsigned char
uchar code table[4] = {0x03,0x06,0x0c,0x09};
void delay(unsigned int i){
	while(i--);
}
void main(){
	uchar j=0;
	while(1){
		if(j == 4) j = 0;
		MOTOR = table[j++];
		delay(250);
	}
}