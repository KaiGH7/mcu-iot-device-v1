#include "IR_Tx_app.h"
#include "IR_Tx_encode.h"
#include "IR_Tx_drv.h"
#include "stdio.h"



unsigned char AC_buff[50];
unsigned char AC_buff_i;

extern unsigned short IR_TX_TimeSequence[];
extern unsigned short IR_TX_TimeSequence_len;
extern unsigned char IR_TX_Port_en;

void AirConditioner_ShutDown(void)
{
	unsigned short i;
	unsigned char error = 0;
	//关机命令
	AC_buff[0] = 'L';					//引导码
	AC_buff[1] = 0xb2;				//A
	AC_buff[2] = ~AC_buff[1];
	AC_buff[3] = 0x7b;				//B
	AC_buff[4] = ~AC_buff[3];
	AC_buff[5] = 0xe0;				//C
	AC_buff[6] = ~AC_buff[5];
	AC_buff[7] = 'S';					//分隔符S
	
	AC_buff[8] = 'L';					//引导码
	AC_buff[9] = 0xb2;				//A
	AC_buff[10] = ~AC_buff[1];
	AC_buff[11] = 0x7b;				//B
	AC_buff[12] = ~AC_buff[3];
	AC_buff[13] = 0xe0;				//C
	AC_buff[14] = ~AC_buff[5];
	AC_buff[15] = 'S';					//分隔符S
	
	AC_buff_i = 16;

	printf("\r\nIR TX data\r\n");
	for(i = 0; i < AC_buff_i; i++)
	{
		printf("0x%02x,",AC_buff[i]);
	}	
	printf("\r\n");
	
	//命令转为时序，即用数组存放高低电平的时间，单位us
	error = IR_TX_DataToTimeSequence(AC_buff, AC_buff_i, IR_TX_TimeSequence, &IR_TX_TimeSequence_len);
//	printf("\r\nIR TX Time Sequence error = %d\r\n", error);
//	for(i = 0; i < IR_TX_TimeSequence_len; i++)
//	{
//		printf("%d,",IR_TX_TimeSequence[i]);
//	}
	
	
	
	for(i = 0; i < IR_TX_TimeSequence_len; i++)
	{
		IR_TX_TimeSequence[i] = IR_TX_TimeSequence[i] / TX_Interrupt_Tim;
	}
	
	//使能发送
	IR_TX_Init();
	IR_TX_Port_en = 1;	
	
}


unsigned char AirConditioner_Set(AirConditionerTypeDef A_TypeDef)
{
	unsigned short i;
	unsigned char error = 0;
	
	unsigned char A_A = 0xb2;
	unsigned char A_B = 0x1f;
	unsigned char A_C = 0x00;
	unsigned char A_Q = 0x00;
	unsigned char A_Y = 0x00;

	A_A = 0xb2;
	if(A_TypeDef.A_Mode == MAUTO )				{		A_C = A_C | (0x02 << 2);	}
	else if(A_TypeDef.A_Mode == CODE )		{		A_C = A_C | (0x00 << 2);	}
	else if(A_TypeDef.A_Mode == DEWATER )	{		A_C = A_C | (0x01 << 2);	}
	else if(A_TypeDef.A_Mode == HEAT )		{		A_C = A_C | (0x03 << 2);	}
	else if(A_TypeDef.A_Mode == WIND )		{		A_C = A_C | (0x01 << 2);	}
	else																	{		error = 1;	}
		
	if(A_TypeDef.A_WindSpeed == WAUTO)				{		A_B = A_B | (0x05 << 5);	}
	else if(A_TypeDef.A_WindSpeed == LOW)			{		A_B = A_B | (0x04 << 5);	}
	else if(A_TypeDef.A_WindSpeed == MEDIUM)	{		A_B = A_B | (0x02 << 5);	}
	else if(A_TypeDef.A_WindSpeed == HIGH)		{		A_B = A_B | (0x01 << 5);	}
	else if(A_TypeDef.A_WindSpeed == FIXED)		{		A_B = A_B | (0x00 << 5);	}
	else																			{		error = 1;	}
	
	if(A_TypeDef.A_Temperature <= 17)				{		A_C = A_C | (0x00 << 4);	}
	else if(A_TypeDef.A_Temperature == 18)	{		A_C = A_C | (0x01 << 4);	}
	else if(A_TypeDef.A_Temperature == 19)	{		A_C = A_C | (0x03 << 4);	}
	else if(A_TypeDef.A_Temperature == 20)	{		A_C = A_C | (0x02 << 4);	}
	else if(A_TypeDef.A_Temperature == 21)	{		A_C = A_C | (0x06 << 4);	}
	else if(A_TypeDef.A_Temperature == 22)	{		A_C = A_C | (0x07 << 4);	}
	else if(A_TypeDef.A_Temperature == 23)	{		A_C = A_C | (0x05 << 4);	}
	else if(A_TypeDef.A_Temperature == 24)	{		A_C = A_C | (0x04 << 4);	}
	else if(A_TypeDef.A_Temperature == 25)	{		A_C = A_C | (0x0c << 4);	}
	else if(A_TypeDef.A_Temperature == 26)	{		A_C = A_C | (0x0d << 4);	}
	else if(A_TypeDef.A_Temperature == 27)	{		A_C = A_C | (0x09 << 4);	}
	else if(A_TypeDef.A_Temperature == 28)	{		A_C = A_C | (0x08 << 4);	}
	else if(A_TypeDef.A_Temperature == 29)	{		A_C = A_C | (0x0a << 4);	}
	else if(A_TypeDef.A_Temperature == 30)	{		A_C = A_C | (0x0b << 4);	}	
	else if(A_TypeDef.A_Mode == WIND)				{		A_C = A_C | (0x0e << 4);	}
	else																		{		error = 1;	}	
	
	
	
	AC_buff[0] = 'L';					//引导码
	AC_buff[1] = A_A;				//A
	AC_buff[2] = ~AC_buff[1];
	AC_buff[3] = A_B;				//B
	AC_buff[4] = ~AC_buff[3];
	AC_buff[5] = A_C;				//C
	AC_buff[6] = ~AC_buff[5];
	AC_buff[7] = 'S';					//分隔符S
	
	AC_buff[8] = 'L';					//引导码
	AC_buff[9] = A_A;				//A
	AC_buff[10] = ~AC_buff[1];
	AC_buff[11] = A_B;				//B
	AC_buff[12] = ~AC_buff[3];
	AC_buff[13] = A_C;				//C
	AC_buff[14] = ~AC_buff[5];
	AC_buff[15] = 'S';					//分隔符S

	AC_buff[16] = 'L';					//引导码
	AC_buff[17] = 0xd5;				//A
	AC_buff[18] = 0x66;
	AC_buff[19] = A_Q;				//B
	AC_buff[20] = A_Q;
	AC_buff[21] = A_Y;				//C
	AC_buff[22] = 0x3b;
	AC_buff[23] = 'S';					//分隔符S
	
	AC_buff_i = 24;	

	printf("\r\nIR TX data\r\n");
	for(i = 0; i < AC_buff_i; i++)
	{
		printf("0x%02x,",AC_buff[i]);
	}	
	printf("\r\n");
	
	//命令转为时序，即用数组存放高低电平的时间，单位us
	error = IR_TX_DataToTimeSequence(AC_buff, AC_buff_i, IR_TX_TimeSequence, &IR_TX_TimeSequence_len);
//	printf("\r\nIR TX Time Sequence error = %d\r\n", error);
//	for(i = 0; i < IR_TX_TimeSequence_len; i++)
//	{
//		printf("%d,",IR_TX_TimeSequence[i]);
//	}

	
	
	for(i = 0; i < IR_TX_TimeSequence_len; i++)
	{
		IR_TX_TimeSequence[i] = IR_TX_TimeSequence[i] / TX_Interrupt_Tim;
	}
	
	//使能发送
	IR_TX_Init();
	IR_TX_Port_en = 1;		
	
	return error;
}




