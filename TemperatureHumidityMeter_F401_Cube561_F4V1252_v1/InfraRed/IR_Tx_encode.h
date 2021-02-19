#ifndef __IR_Tx_encode_H
#define __IR_Tx_encode_H


#define TX_Interrupt_Tim 20		//Interrupt period, unit(us)


#define L_htim 4400	//定义引导码L高电平的时间，单位us

#define L_ltim 4400	//定义引导码L低电平的时间，单位us

#define S_htim 5220	//定义分隔符S高电平的时间，单位us

#define S_ltim 540	//定义分隔符S低电平的时间，单位us

#define B1_htim 1620	//定义分1高电平的时间，单位us

#define B1_ltim 540	//定义分1低电平时间，单位us

#define B0_htim 540	//定义分0高电平的时间，单位us

#define B0_ltim 540	//定义分0低电平的时间，单位us


#define IR_TX_Level_num 350	//存放高低电平时间数组长度。


unsigned char IR_TX_DataToTimeSequence(unsigned char *data, unsigned char d_len, unsigned short *TimeSequence, unsigned short *ts_len);





#endif

