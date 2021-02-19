
#include "IR_Rx_drv.h"


unsigned char IR_RX_Port_en;	//������ն˿�ʹ�ܣ�Ĭ��ʹ�ܡ�
unsigned long IR_RX_tim;			//�жϴ������������������ոߵ͵�ƽʱ�䣬ʱ�䵥λΪus��

unsigned char IR_RX_Pin_pre;	//������ն˿���һ�ν��ж�ʱ����ƽ״̬��Ĭ��״̬Ϊ�ߵ�ƽ��
unsigned char IR_RX_Pin_now;	//������ն˿ڱ��ν��ж�ʱ����ƽ״̬�������������ƽ�������غ��½��ء�Ĭ��״̬Ϊ�ߵ�ƽ��

unsigned long IR_RX_Pin_state_tim1;	//��¼�½���ʱ�� IR_RX_tim ��ֵ��
unsigned long IR_RX_Pin_state_tim2;	//��¼������ʱ�� IR_RX_tim ��ֵ��
unsigned long IR_RX_Pin_state_tim3;	//��Ž��ս���ʱ�� IR_RX_tim ��ֵ��Ϊ IR_RX_Pin_state_tim2 + IR_RX_ovtim

unsigned char DataStart_flag;				//������ʼ��־����ʼΪ0��ÿ�μ�⵽�½�����1�����ݽ��ս�����0
unsigned char DataDownToUp_flag;		//��⵽�����ر�־����ʼΪ0��ÿ�μ�⵽����������1����⵽�½�����0�����ݽ��ս�����0

unsigned long IR_RX_Pin_state_lowtim;		//��¼����͵�ƽ��ʱ��
unsigned long IR_RX_Pin_state_higtim;		//��¼����ߵ�ƽ��ʱ��


unsigned short IR_RX_Level_h[IR_RX_Level_num] = {0};
unsigned short IR_RX_Level_l[IR_RX_Level_num] = {0};
unsigned short IR_RX_Level_i = 0;

extern unsigned char IR_TX_Port_en;

/**
 * @brief  ��������жϺ�����ʼ����
 * @param[in] �ޡ�
 * @return ��
 */
void IR_RX_Init(void)
{
	unsigned long i;
	IR_RX_Port_en = 1;
	IR_RX_tim = 0;
	IR_RX_Pin_pre = 1;
	IR_RX_Pin_now = 1;
	DataStart_flag = 0;
	DataDownToUp_flag = 0;
	IR_RX_Level_i = 0;
	for(i = 0; i < IR_RX_Level_num; i++)
	{
		IR_RX_Level_h[i] = 0;
		IR_RX_Level_l[i] = 0;
	}
	
}

/**
 * @brief  ��������жϺ�����������ĸߵ͵�ƽ��ʱ��ֱ�����2�������С�
 * @param[in] ��ǰ����˿ڵĵ�ƽ״̬���ߵ�ƽΪ1���͵�ƽΪ0��
 * @return ��
 */
void IR_RX_Interrupt_fun(unsigned char IR_RX_Pin_state)
{
		
		if((IR_RX_Port_en == 1) & (IR_TX_Port_en == 0))
		//if(IR_RX_Port_en == 1)
		{
			IR_RX_tim++;
			IR_RX_Pin_pre = IR_RX_Pin_now;
			IR_RX_Pin_now = IR_RX_Pin_state;
			
			if((IR_RX_Pin_pre == 1) & (IR_RX_Pin_now == 0))//�½��� ���ݿ�ʼ
			{
				IR_RX_Pin_state_tim1 = IR_RX_tim;
				if(DataStart_flag != 0)
				{
					if(IR_RX_Pin_state_tim1 < IR_RX_Pin_state_tim2)
					{
						IR_RX_Pin_state_higtim = (0xffffffff - IR_RX_Pin_state_tim2) + IR_RX_Pin_state_tim1;
					}
					else
					{
						IR_RX_Pin_state_higtim = IR_RX_Pin_state_tim1 - IR_RX_Pin_state_tim2;
					}
					IR_RX_Level_h[IR_RX_Level_i] = IR_RX_Pin_state_higtim; IR_RX_Level_i++; 
					if(IR_RX_Level_i >= IR_RX_Level_num) IR_RX_Level_i = IR_RX_Level_num;
				}		
				DataStart_flag = 1;	DataDownToUp_flag = 0;
			}
			else if((IR_RX_Pin_pre == 0) & (IR_RX_Pin_now == 1))//������
			{
				IR_RX_Pin_state_tim2 = IR_RX_tim;
				if(IR_RX_Pin_state_tim2 < IR_RX_Pin_state_tim1)
				{
					IR_RX_Pin_state_lowtim = (0xffffffff - IR_RX_Pin_state_tim1) + IR_RX_Pin_state_tim2;
				}
				else
				{
					IR_RX_Pin_state_lowtim = IR_RX_Pin_state_tim2 - IR_RX_Pin_state_tim1;
				}
				IR_RX_Level_l[IR_RX_Level_i] = IR_RX_Pin_state_lowtim; IR_RX_Level_i++;
				if(IR_RX_Level_i > IR_RX_Level_num) IR_RX_Level_i = IR_RX_Level_num;
				
				if((0xffffffff - IR_RX_Pin_state_tim2) < IR_RX_ovtim)
				{
					IR_RX_Pin_state_tim3 = IR_RX_ovtim - (0xffffffff - IR_RX_Pin_state_tim2);
				}
				else
				{
					IR_RX_Pin_state_tim3 = IR_RX_Pin_state_tim2 + IR_RX_ovtim;//���һ�����ݳ�ʱ10ms Ϊ�����յ�				
				}
				DataDownToUp_flag =1;

			}
			
			if(DataDownToUp_flag == 1)
			{
				if(IR_RX_tim > IR_RX_Pin_state_tim3)
				{
					IR_RX_Port_en = 0;
					IR_RX_Level_h[IR_RX_Level_i] = 500; IR_RX_Level_i++;
					DataStart_flag = 0;
					DataDownToUp_flag = 0;
				}
			}			
		}	
}





