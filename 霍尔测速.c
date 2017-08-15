 #define uint unsigned int
 #define  N 2
 #define uchar unsigned char
 #include <reg51.h>
 #include <intrins.h>
 void delayms(uchar X);
 sbit Weila=P2^7;
 sbit VCC=P2^6;
 
  uint speed=0;	 //?????
  uint count=0;	 //?????????????
  uchar K=0;
  uchar code tableDuan[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
   uchar dat[4]={0,0,0,0};
   void display(uint k)
   {
   uchar temp,n;
   dat[0]=k/1000;
   dat[1]=k%1000/100;
   dat[2]=k%1000%100/10;
   dat[3]=k%1000%100%10;
   temp=0x07;
   for(n=0;n<4;n++)
   {
		 
		 P0=temp;
   P1=tableDuan[dat[n]];
		 //temp=_crol_(temp,1);
		 temp = temp >> 1;
		 temp |= 0x08;
		 delayms(10);
   }
   }
   void delayms(uchar X)
   {uchar i,j;
   for(i=X;i>0;i--)
   for(j=110;j>0;j--);
   }

   void main()
   {
   uchar n;
   TMOD=0x51;
   TH0=0x3C;
   TL0=0xB0;
   ET0=1;
   EA=1;
   TR0=1;
   TR1=1;
   Weila=1;
   VCC=1;
   while (1)
   {
		
   speed =count*10/N;
		 display(count);
		 TR0=1;
   TR1=1;
	 }
   }
void int0_fun()interrupt 1
{
 
 K++;
 TH0=0x3C;
 TL0=0xB0;
 if(K>=1)
 {
 TR0=0;
 TR1=0;
 count=TH1*256+TL1;
 TH1=0x00;
 TL1=0x00;
 K=0;
 }
}