#include <reg51.h>
#define LED P2

void main(){
	//设置波特率，由定时器1的溢出率决定
  TMOD=0x20;//定时器1设置为工作方式2，,8位自动装载的定时器
  TH1=0XF4;
  TL1=0xF4;//波特率4800
  ET1=1;
  TR1=1;

  //设置串口工作方式
  SCON=0x50; //方式1，允许接收
  PCON=0x00;
  TI= 0;
  RI= 0;
  ES=1;
  EA=1;
	while(1);
}

void receive() interrupt 4{
	EA = 0;
	LED = SBUF;
	RI = 0;
	EA = 1;
}