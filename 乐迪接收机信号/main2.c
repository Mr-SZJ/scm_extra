/****************************
 pwm ?????P3.2??
/***************************/
#include <reg51.h>              
typedef unsigned char uint8;    
typedef unsigned int uint16;    //???????
uint8 t;
bit get;
long pwm_all,pwm_h;
void init()
{
    TMOD = 0x19;  //t0 gate = 1 ???????
    TH1 = 0;
    TL1 = 0;
    TH0 = 0;
    TL0 = 0;
    
    TR0 = 1;
    IT0 = 1;
    IT1 = 1;
    
    EX0 = 1;
    EA = 1;
    
    bit 
}
void main()
{ 
 uint16 pwm_w;
 init();
 while(1)
 {
    if(get)
    {
       pwm_w = (pwm_h*100)/pwm_all;   //?????
    }
 }
}
void ex0()  interrupt 0
{
    t++;
    if(t == 1)
      TR1 = 1;
    if(t == 2)
    {
      pwm_all = TH1;
      pwm_all = (pwm_all << 8) + TL1;
      TH1 = TL1 = 0;
      t == 0;
      get = 1;
      }
     pwm_h = TH0;
     pwm_h = (pwm_h << 8) + TL0;
     TH0 = TL0 = 0;
}