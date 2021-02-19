#ifndef __IR_Rx_parse_H
#define __IR_Rx_parse_H


#define L_htim_min 4200
#define L_htim_max 4600	//����������L�ߵ�ƽ��ʱ�����䣬��λus

#define L_ltim_min 4200
#define L_ltim_max 4600	//����������L�͵�ƽ��ʱ�����䣬��λus

#define S_htim_min 5000
#define S_htim_max 10000	//����ָ���S�ߵ�ƽ��ʱ�����䣬��λus

#define S_ltim_min 430
#define S_ltim_max 650	//����ָ���S�͵�ƽ��ʱ�����䣬��λus

#define B1_htim_min 1450
#define B1_htim_max 1800	//�����1�ߵ�ƽ��ʱ�����䣬��λus

#define B1_ltim_min 430
#define B1_ltim_max 650	//�����1�͵�ƽʱ�����䣬��λus

#define B0_htim_min 430
#define B0_htim_max 650	//�����0�ߵ�ƽ��ʱ�����䣬��λus

#define B0_ltim_min 430
#define B0_ltim_max 650	//�����0�͵�ƽ��ʱ�����䣬��λus


unsigned char IR_RX_TimeSequence_parse(unsigned short *Level_htim, unsigned short *Level_ltim, unsigned short Level_i, unsigned char *data, unsigned char *data_len);

#endif

