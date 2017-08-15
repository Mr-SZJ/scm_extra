#include <reg52.h> 
#define uint unsigned int
#define uchar unsigned char
uchar abs(uchar a, uchar b);
void InitTimer0(void);
void initEt0(void);

sbit BEE=P3^0;

uint f_pre;//上一次的脉冲数
uint f_now;//本次的脉冲数
uchar var_t0;

/*外部中断0初始化*/
void initEt0(void){
	IT0 = 1;
	EX0 = 1;
	EA = 1;
}

/*定时器0初始化，定时50ms*/
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

/*求两个数的绝对值*/
uchar abs(uchar a, uchar b){
	if(a > b){
		return a-b;
	}else{
		return b-a;
	}
}

/*外部中断0用来记录脉冲数*/
void Exit0(void) interrupt 0{
	f_now++;
}

void Timer0Interrupt(void) interrupt 1
{
		EA = 0;//关闭中断总开关
    TH0 = 0x3C;
    TL0 = 0x0B0;
    var_t0++;
		if(var_t0 >= 5){//每250ms扫描脉冲数
			var_t0 = 0;
			if(abs(f_now,f_pre) < 2){
				//两次扫描的脉冲数相同
				
			}else{
				//两次扫描的脉冲数不同
				BEE = ~BEE;
			}
			
			f_pre = f_now;//当前脉冲数赋值为上一次脉冲数
			f_now = 0;//清零当前脉冲数
			
		}
		EA = 1;//开中断总开关
}
