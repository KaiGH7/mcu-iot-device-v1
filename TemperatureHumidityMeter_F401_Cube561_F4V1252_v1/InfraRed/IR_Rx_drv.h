#ifndef __IR_Rx_drv_H
#define __IR_Rx_drv_H




#define Interrupt_Tim 20		//Interrupt period, unit(us)
#define IR_RX_ovtim 500			//����⵽������ (IR_RX_ovtim * Interrupt_Tim)us ʱ��ĸߵ�ƽʱ�����ν��ս�����
#define IR_RX_Level_num 500	//��Ÿߵ͵�ƽʱ�����鳤�ȡ�




void IR_RX_Init(void);
void IR_RX_Interrupt_fun(unsigned char IR_RX_Pin_state);

#endif

