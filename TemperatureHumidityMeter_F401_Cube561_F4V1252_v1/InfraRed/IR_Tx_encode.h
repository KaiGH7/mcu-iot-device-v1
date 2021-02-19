#ifndef __IR_Tx_encode_H
#define __IR_Tx_encode_H


#define TX_Interrupt_Tim 20		//Interrupt period, unit(us)


#define L_htim 4400	//����������L�ߵ�ƽ��ʱ�䣬��λus

#define L_ltim 4400	//����������L�͵�ƽ��ʱ�䣬��λus

#define S_htim 5220	//����ָ���S�ߵ�ƽ��ʱ�䣬��λus

#define S_ltim 540	//����ָ���S�͵�ƽ��ʱ�䣬��λus

#define B1_htim 1620	//�����1�ߵ�ƽ��ʱ�䣬��λus

#define B1_ltim 540	//�����1�͵�ƽʱ�䣬��λus

#define B0_htim 540	//�����0�ߵ�ƽ��ʱ�䣬��λus

#define B0_ltim 540	//�����0�͵�ƽ��ʱ�䣬��λus


#define IR_TX_Level_num 350	//��Ÿߵ͵�ƽʱ�����鳤�ȡ�


unsigned char IR_TX_DataToTimeSequence(unsigned char *data, unsigned char d_len, unsigned short *TimeSequence, unsigned short *ts_len);





#endif

