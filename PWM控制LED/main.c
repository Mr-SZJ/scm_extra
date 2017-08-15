#include <reg52.h>
#include "led.h"
#include "uart.h"
#define uchar unsigned char

void main(){
	led_init();
	uart_init();
  led_start();
	while(1);
}