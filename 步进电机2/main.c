#include <reg51.h>
#define MOTOR P0
#define uchar unsigned char

uchar code table[4] = {0x03,0x06,0x0c,0x09};
uchar dl = 250;

void delay(unsigned int i){
	while(i--);
}

void main(){
	uchar j=0;
	
	EX0 = 1;
	EX1 = 1;
	IT0 = 1;
	IT1 = 1;
	EA = 1;
	
	while(1){
		if(j == 4) j = 0;
		MOTOR = table[j++];
		delay(dl);
	}
}

void up() interrupt 0{
	if(dl > 50){
		dl -= 20;
	}
}

void down() interrupt 2{
	if(dl < 250){
		dl += 20;
	}
}