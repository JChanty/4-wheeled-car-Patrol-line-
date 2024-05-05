
#include <STC8G.H>
#include "intrins.H"
#define u8 unsigned char
#define u16 unsigned int
sbit m1_0=P3^4;
sbit m1_1=P3^5;
sbit m2_0=P3^6;
sbit m2_1=P3^7;
sbit m3_0=P1^0;
sbit m3_1=P1^1;
sbit m4_0=P1^6;
sbit m4_1=P1^7;
sbit INT0 = P3^2;
sbit INT1 = P3^3;
u8 speed = 0;
u8 i = 0;


//void delay(unsigned int time)
//{
//    unsigned int i, j;
//    for (i = 0; i < time; i++)
//        for (j = 0; j < 120; j++);
//}
//
//void Delay20ms()		//@12.000MHz
//{
//	unsigned char data i, j, k;
//
//	i = 2;
//	j = 56;
//	k = 172;
//	do
//	{
//		do
//		{
//			while (--k);
//		} while (--j);
//	} while (--i);
//}
//
//
//
void CD()
{
	m1_0 = 0;
	m2_0 = 0;
	m3_0 = 0;
	m4_0 = 0;
	m1_1 = 0;
	m2_1 = 0;
	m3_1 = 0;
	m4_1 = 0;
}

void Delay1000ms()		//@12.000MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 61;
	j = 225;
	k = 62;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}



void wheel_1(unsigned char i)
{
	m1_0 = i;
	m1_1 = !i;
}
void wheel_2(unsigned char i)
{
	m2_0 = i;
	m2_1 = !i;
}
void wheel_3(unsigned char i)
{
	m4_0 = i;
	m4_1 = !i;
}
void wheel_4(unsigned char i)
{
	m3_0 = i;
	m3_1 = !i;
}

void run_mode(unsigned char w1,unsigned char w2,unsigned char w3,unsigned char w4)
{
	CD();
	wheel_1(w1);
	wheel_2(w2);
	wheel_3(w3);
	wheel_4(w4);
}

void Timer0_Init(void)		//8毫秒@12.000MHz
{
	EA=1;
	ET0=1;
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TL0 = 0xC0;				//设置定时初始值
	TH0 = 0xE0;				//设置定时初始值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}




void main()
{
	
	P1M0=0X00;P1M1=0X00;    //设置I/O
	P3M0=0X00;P3M1=0X00;
	P5M0=0X00;P5M1=0X00;
	Timer0_Init();
	EX0=1;
	EX1=1;
//	IE0=1;IE1=1;
//	i=0;
//	CD();
	while(1)
	{
//		if((INT0 == 0)&(INT1 == 0) == 1)
//		{
//			run_mode(1,1,1,1,250);
//		}
//		else if(INT0 == 0)
//		{
//			run_mode(0,1,0,1,375);
//		}
//		else if(INT1 == 0)
//		{
//			run_mode(1,0,1,0,375);
//		}
		
		speed=5;

	}
}

void left() interrupt 0
{
	if(INT0 == 1)run_mode(1,0,1,0);
	
}

void right() interrupt 2
{
	if(INT1 == 1)run_mode(0,1,0,1);
}

void V4WD() interrupt 1
{
	TL0 = 0xC0;				//设置定时初始值
	TH0 = 0xE0;				//设置定时初始值
	if(i<speed)
	{
		m1_0=1;m1_1=0;
		m2_0=1;m2_1=0;
		m3_0=1;m3_1=0;
		m4_0=1;m4_1=0;
	
	}
	else
	{  	
		m1_0=0;m1_1=0;
		m2_0=0;m2_1=0;
		m3_0=0;m3_1=0;	
		m4_0=0;m4_1=0;		 	
	} 
	i++;
	if(i>9) i=0;		
}

