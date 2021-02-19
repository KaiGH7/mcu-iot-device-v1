#include "IR_Tx_drv.h"

#include "main.h"
#include "tim.h"

unsigned char IR_TX_Port_en = 0;
unsigned long IR_TX_tim = 0;
unsigned short IR_TX_i = 0;

extern unsigned short IR_TX_TimeSequence[];
extern unsigned short IR_TX_TimeSequence_len;

void IR_TX_Init(void)
{
	IR_TX_Port_en = 0;
	IR_TX_tim = 0;
	IR_TX_i = 0;

}



void IR_TX_Interrupt_fun(void)
{
	if(IR_TX_Port_en == 1)
	{
		
		if((IR_TX_i % 2) == 0)//低电平 输出PWM
		{
			if(IR_TX_tim == 0)
			{
				//设置PWM
				HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
				IR_TX_tim++;
			}
			else
			{
				IR_TX_tim++;
				if(IR_TX_tim > IR_TX_TimeSequence[IR_TX_i])
				{
					//终止PWM
					HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_1);	
					(IR_TX_i)++;
					IR_TX_tim = 0;
				}
			}
		}
		else//高电平 不输出PWM
		{
			if(IR_TX_tim == 0)
			{
				//终止PWM
				HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_1);	
				IR_TX_tim++;
			}
			else
			{
				IR_TX_tim++;
				if(IR_TX_tim > IR_TX_TimeSequence[IR_TX_i])
				{
					//终止PWM
					HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_1);
					(IR_TX_i)++;
					IR_TX_tim = 0;
				}
			}
		}
		
		if(IR_TX_i > IR_TX_TimeSequence_len)
		{
			IR_TX_Port_en = 0;
			IR_TX_Init();
		}
	}
}

