#include <reg51.h>
#define uchar unsigned char
#define uint unsigned int
sbit led = P0^0;

//�����ź���
sbit signal_port = P3^2;
uchar t = 0;
uint PWM_l;
uint PWM_l_pre;

void initEXIT(){
	//�ⲿ�ж�0��PWM�ź�
	EX0 = 1;
	IT0 = 1;

	//��ʱ��0���ڼ���ռ�ձ�
	TMOD = 0x01;
  TH0 = 0x00;
  TL0 = 0x00;
  EA = 1;
  ET0 = 1;
}


//������
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
	TR0 = 1;//������ʱ��0
}
