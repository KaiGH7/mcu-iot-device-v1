#ifndef __IR_Rx_drv_H
#define __IR_Rx_drv_H




#define Interrupt_Tim 20		//Interrupt period, unit(us)
#define IR_RX_ovtim 500			//当检测到连续的 (IR_RX_ovtim * Interrupt_Tim)us 时间的高电平时，本次接收结束。
#define IR_RX_Level_num 500	//存放高低电平时间数组长度。




void IR_RX_Init(void);
void IR_RX_Interrupt_fun(unsigned char IR_RX_Pin_state);

#endif

