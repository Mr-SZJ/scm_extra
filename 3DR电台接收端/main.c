#include <reg51.h>
#define LED P2

void main(){
	//���ò����ʣ��ɶ�ʱ��1������ʾ���
  TMOD=0x20;//��ʱ��1����Ϊ������ʽ2��,8λ�Զ�װ�صĶ�ʱ��
  TH1=0XF4;
  TL1=0xF4;//������4800
  ET1=1;
  TR1=1;

  //���ô��ڹ�����ʽ
  SCON=0x50; //��ʽ1���������
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