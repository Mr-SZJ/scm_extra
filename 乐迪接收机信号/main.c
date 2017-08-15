#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit led = P0^0;

//定义信号线
sbit signal_port = P3^2;
uchar t = 0;
uint PWM_l;
uint PWM_l_pre;

void initEXIT(){
	//外部中断0接PWM信号
	EX0 = 1;
	IT0 = 1;

	//定时器0用于计算占空比
	TMOD = 0x01;
  TH0 = 0x00;
  TL0 = 0x00;
  EA = 1;
  ET0 = 1;
}


//主函数
void main(){
	initEXIT();
	while(1){
		if(signal_port == 1 && TR0 == 1){
			TR0 = 0;
			TH0 = 0x00;
			TL0 = 0x00;
			PWM_l = TH0;
			PWM_l = (PWM_l << 8) + TL0;
			if(PWM_l_pre != PWM_l){
				led = ~led;
			}
			PWM_l_pre = PWM_l;
		}
	}
}

void ex0() interrupt 0{
	TR0 = 1;//启动定时器0
}
