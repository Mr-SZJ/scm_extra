#include <reg52.h>
void SendOneByte(unsigned char c);
unsigned char i = 0;
unsigned int j = 0;
unsigned char ch;
void delay(){
	j = 15000;
	while(j--);
}
void InitUART(void)
{
    
	 TMOD = 0x20;
    SCON = 0x50;
    TH1 = 0xFD;
    TL1 = TH1;
    PCON = 0x00;
    ES = 1;
	
		EX0 = 1;
	  IT0 = 1;
		PX0 = 1;
		EA = 1;
	   TR1 = 1;
}


void main(void)
{
    InitUART();
		P0 = 0x01;
	  while(1);
}


void int0() interrupt 0{
	i++;
	if(i > 9) i=0;
	P0 = i;
	SendOneByte('0'+i);
}

void uart() interrupt 4{
	if(TI){
		TI = 0;
	}else{
		ch = SBUF;
		P0 = ch;
		RI = 0;
	}
}

void SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

