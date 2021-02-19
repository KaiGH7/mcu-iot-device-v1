#ifndef __IR_Rx_parse_H
#define __IR_Rx_parse_H


#define L_htim_min 4200
#define L_htim_max 4600	//定义引导码L高电平的时间区间，单位us

#define L_ltim_min 4200
#define L_ltim_max 4600	//定义引导码L低电平的时间区间，单位us

#define S_htim_min 5000
#define S_htim_max 10000	//定义分隔符S高电平的时间区间，单位us

#define S_ltim_min 430
#define S_ltim_max 650	//定义分隔符S低电平的时间区间，单位us

#define B1_htim_min 1450
#define B1_htim_max 1800	//定义分1高电平的时间区间，单位us

#define B1_ltim_min 430
#define B1_ltim_max 650	//定义分1低电平时间区间，单位us

#define B0_htim_min 430
#define B0_htim_max 650	//定义分0高电平的时间区间，单位us

#define B0_ltim_min 430
#define B0_ltim_max 650	//定义分0低电平的时间区间，单位us


unsigned char IR_RX_TimeSequence_parse(unsigned short *Level_htim, unsigned short *Level_ltim, unsigned short Level_i, unsigned char *data, unsigned char *data_len);

#endif

