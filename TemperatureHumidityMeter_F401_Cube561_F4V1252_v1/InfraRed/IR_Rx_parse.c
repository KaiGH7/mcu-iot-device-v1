

#include "IR_Rx_drv.h"
#include "IR_Rx_parse.h"



unsigned char IR_RX_TimeSequence_parse(unsigned short *Level_htim, unsigned short *Level_ltim, unsigned short Level_i, unsigned char *data, unsigned char *data_len)
{
	unsigned short i;
	unsigned short j;
	unsigned char error = 0;
	unsigned char d_i = 0;
	
	for(i = 0; i < Level_i; i++)
	{
		Level_ltim[i] = Level_ltim[i] * Interrupt_Tim; 
		Level_htim[i] = Level_htim[i] * Interrupt_Tim; 
	}
	
	for(i = 0; i < Level_i; i=i+2)
	{
		if((Level_ltim[i] >= L_ltim_min) & (Level_ltim[i] <= L_ltim_max))	//������L�ĵ͵�ƽ
		{		
			if((Level_htim[i+1] >= L_htim_min) & (Level_htim[i+1] <= L_htim_max))	//������L�ߵ�ƽ
			{
				//������
				data[d_i] = 'L';d_i++;
			}
			else
			{
				error = 1;data[d_i] = 0xff;d_i++;//error
			}
		}
		else if((Level_ltim[i] >= S_ltim_min) & (Level_ltim[i] <= S_ltim_max)) //�ָ���S��BIT1��BIT0�ĵ͵�ƽ
		{
			if((Level_htim[i+1] >= S_htim_min) & (Level_htim[i+1] <= S_htim_max))//�ָ���S�ĸߵ�ƽ
			{
				//�ָ���
				data[d_i] = 'S';d_i++;
			}
			else
			{
				j = i + 16;
				for(i = i; i < j; i = i + 2)
				{
					if((Level_htim[i+1] >= B1_htim_min) & (Level_htim[i+1] <= B1_htim_max))//BIT1�ĸߵ�ƽ
					{
						//BIT1
						data[d_i] = (data[d_i] << 1) | 0x01;
					}
					else if((Level_htim[i+1] >= B0_htim_min) & (Level_htim[i+1] <= B0_htim_max))//BIT0�ĸߵ�ƽ
					{
						//BIT0
						data[d_i] = (data[d_i] << 1) | 0x00;
					}
					else
					{
						//error
						error = 1;data[d_i] = 0xff;
					}					
				}
				i = i - 2;
				d_i++;		
			}				
		}
	}
	*data_len = d_i;

return error;
	
}





