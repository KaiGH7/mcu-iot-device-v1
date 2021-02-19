#include "IR_Tx_encode.h"


unsigned short IR_TX_TimeSequence[IR_TX_Level_num];
unsigned short IR_TX_TimeSequence_len;




unsigned char IR_TX_DataToTimeSequence(unsigned char *data, unsigned char d_len, unsigned short *TimeSequence, unsigned short *ts_len)
{
	unsigned char d_i;
	unsigned char d_j;
	unsigned short ts_i = 0;
	unsigned char error = 0;
	
	for(d_i = 0; d_i < d_len; d_i++)
	{
		if( (d_i % 8) == 0 ) //Òýµ¼ÂëL
		{
			if(data[d_i] == 'L')
			{
				TimeSequence[ts_i] = L_ltim;ts_i++; if(ts_i >= IR_TX_Level_num) { ts_i = IR_TX_Level_num - 1; error = 1;}
				TimeSequence[ts_i] = L_htim;ts_i++; if(ts_i >= IR_TX_Level_num) { ts_i = IR_TX_Level_num - 1; error = 1;}
			}
		}
		else if((d_i % 8) == 7)//·Ö¸ô·ûS
		{
				TimeSequence[ts_i] = S_ltim;ts_i++; if(ts_i >= IR_TX_Level_num) { ts_i = IR_TX_Level_num - 1; error = 1;}
				TimeSequence[ts_i] = S_htim;ts_i++;	if(ts_i >= IR_TX_Level_num) { ts_i = IR_TX_Level_num - 1; error = 1;} 	
		}
		else//data
		{
			for(d_j = 0; d_j < 8; d_j++)
			{
				if(((data[d_i] >> (7 - d_j)) & 0x01) ==1)
				{
					TimeSequence[ts_i] = B1_ltim;ts_i++; if(ts_i >= IR_TX_Level_num) { ts_i = IR_TX_Level_num - 1; error = 1;}
					TimeSequence[ts_i] = B1_htim;ts_i++; if(ts_i >= IR_TX_Level_num) { ts_i = IR_TX_Level_num - 1; error = 1;}						
				}
				else
				{
					TimeSequence[ts_i] = B0_ltim;ts_i++; if(ts_i >= IR_TX_Level_num) { ts_i = IR_TX_Level_num - 1; error = 1;}
					TimeSequence[ts_i] = B0_htim;ts_i++; if(ts_i >= IR_TX_Level_num) { ts_i = IR_TX_Level_num - 1; error = 1;}				
				}
			}
		}
	}
	*ts_len = ts_i;
	return error;
}




