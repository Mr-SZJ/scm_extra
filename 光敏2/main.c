#include <reg52.h> 
#define uint unsigned int
#define uchar unsigned char
uchar abs(uchar a, uchar b);
void InitTimer0(void);
void initEt0(void);

sbit BEE=P3^0;

uint f_pre;//��һ�ε�������
uint f_now;//���ε�������
uchar var_t0;

/*�ⲿ�ж�0��ʼ��*/
void initEt0(void){
	IT0 = 1;
	EX0 = 1;
	EA = 1;
}

/*��ʱ��0��ʼ������ʱ50ms*/
void InitTimer0(void)
{
    TMOD = 0x01;
    TH0 = 0x3C;
    TL0 = 0x0B0;
    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

void main(void){
	initEt0();
	InitTimer0();
	var_t0 = 0;
	while(1);
}

/*���������ľ���ֵ*/
uchar abs(uchar a, uchar b){
	if(a > b){
		return a-b;
	}else{
		return b-a;
	}
}

/*�ⲿ�ж�0������¼������*/
void Exit0(void) interrupt 0{
	f_now++;
}

void Timer0Interrupt(void) interrupt 1
{
		EA = 0;//�ر��ж��ܿ���
    TH0 = 0x3C;
    TL0 = 0x0B0;
    var_t0++;
		if(var_t0 >= 5){//ÿ250msɨ��������
			var_t0 = 0;
			if(abs(f_now,f_pre) < 2){
				//����ɨ�����������ͬ
				
			}else{
				//����ɨ�����������ͬ
				BEE = ~BEE;
			}
			
			f_pre = f_now;//��ǰ��������ֵΪ��һ��������
			f_now = 0;//���㵱ǰ������
			
		}
		EA = 1;//���ж��ܿ���
}
