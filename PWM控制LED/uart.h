#ifndef _UART_H_
#define _UART_H_

/*
接收到的数据帧格式为：
	a5 5a 长度 命令字 多字节的内容数据 校验字 aa
*/


//命令包的命令位值
#define CMD_RGB 0
#define CMD_MODE 1

void uart_init();

#endif