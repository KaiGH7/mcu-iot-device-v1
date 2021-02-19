
#include "IR_Rx_drv.h"


unsigned char IR_RX_Port_en;	//红外接收端口使能，默认使能。
unsigned long IR_RX_tim;			//中断次数，用来计算红外接收高低电平时间，时间单位为us。

unsigned char IR_RX_Pin_pre;	//红外接收端口上一次进中断时，电平状态。默认状态为高电平。
unsigned char IR_RX_Pin_now;	//红外接收端口本次进中断时，电平状态。用来检测红外电平的上升沿和下降沿。默认状态为高电平。

unsigned long IR_RX_Pin_state_tim1;	//记录下降沿时刻 IR_RX_tim 的值。
unsigned long IR_RX_Pin_state_tim2;	//记录上升沿时刻 IR_RX_tim 的值。
unsigned long IR_RX_Pin_state_tim3;	//存放接收结束时的 IR_RX_tim 的值，为 IR_RX_Pin_state_tim2 + IR_RX_ovtim

unsigned char DataStart_flag;				//数据起始标志，初始为0，每次检测到下降沿至1，数据接收结束置0
unsigned char DataDownToUp_flag;		//检测到上升沿标志，初始为0，每次检测到上升沿置置1，检测到下降沿置0，数据接收结束置0

unsigned long IR_RX_Pin_state_lowtim;		//记录红外低电平的时间
unsigned long IR_RX_Pin_state_higtim;		//记录红外高电平的时间


unsigned short IR_RX_Level_h[IR_RX_Level_num] = {0};
unsigned short IR_RX_Level_l[IR_RX_Level_num] = {0};
unsigned short IR_RX_Level_i = 0;

extern unsigned char IR_TX_Port_en;

/**
 * @brief  红外接收中断函数初始化。
 * @param[in] 无。
 * @return 无
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
 * @brief  红外接收中断函数，将红外的高低电平的时间分别存放在2个数组中。
 * @param[in] 当前红外端口的电平状态，高电平为1，低电平为0。
 * @return 无
 */
void IR_RX_Interrupt_fun(unsigned char IR_RX_Pin_state)
{
		
		if((IR_RX_Port_en == 1) & (IR_TX_Port_en == 0))
		//if(IR_RX_Port_en == 1)
		{
			IR_RX_tim++;
			IR_RX_Pin_pre = IR_RX_Pin_now;
			IR_RX_Pin_now = IR_RX_Pin_state;
			
			if((IR_RX_Pin_pre == 1) & (IR_RX_Pin_now == 0))//下降沿 数据开始
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
			else if((IR_RX_Pin_pre == 0) & (IR_RX_Pin_now == 1))//上升沿
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
					IR_RX_Pin_state_tim3 = IR_RX_Pin_state_tim2 + IR_RX_ovtim;//最后一个数据超时10ms 为计数终点				
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





