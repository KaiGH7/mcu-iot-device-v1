#include "tf_sdio_drv.h"

#include "usart.h"
#include "stdio.h"
#include "sdio.h"




extern SD_HandleTypeDef hsd;




void PrintSdCard_State(void)
{
	HAL_SD_CardStateTypeDef temp;
	temp = HAL_SD_GetCardState(&hsd);
	printf("SD Card State:%d\r\n", temp);
	
}
void PrintSdio_State(void)
{
	printf("SDIO State:%d\r\n", hsd.State);
}



void PrintSdCard_LogBlockSize(void)
{
	printf("SD Card logical Block Size:%d\r\n", hsd.SdCard.LogBlockSize);
}



void PrintSdCard_LogBlockNbr(void)
{
	printf("SD Card logical Block Number:%d\r\n", hsd.SdCard.LogBlockNbr);
}



void PrintSdCard_BlockSize(void)
{
	printf("SD Card Block Size:%d\r\n", hsd.SdCard.BlockSize);
}


void PrintSdCard_BlockNbr(void)
{
	printf("SD Card Block Number:%d\r\n", hsd.SdCard.BlockNbr);
}


void PrintSdCard_Class(void)
{
	printf("SD Card Class:%d\r\n", hsd.SdCard.Class);
}


void PrintSdCard_Version(void)
{
	if(hsd.SdCard.CardVersion == 0)
	{
		printf("SD Card Version: V1_X\r\n");
	}
	else if(hsd.SdCard.CardVersion == 1)
	{
		printf("SD Card Version: V2_X\r\n");
	}
	else
	{
		printf("SD Card Version: unknwon\r\n");
	}
}



void PrintSdCard_Type(void)
{
	if(hsd.SdCard.CardType == 0)
	{
		printf("SD Card Type: SDSC\r\n");
	}
	else if(hsd.SdCard.CardType == 1)
	{
		printf("SD Card Type: SDHC/SDXC\r\n");
	}
	else
	{
		printf("SD Card Type: unknwon\r\n");
	}
}



void PrintSdCard_RCA(void)
{
	unsigned short temp;
	temp = hsd.SdCard.RelCardAdd;
	printf("SD Card RCA:%d\r\n", temp);
}

void PrintSdCard_CID(void)
{
	unsigned char temp[16];
	temp[0] = hsd.CID[0];
	temp[1] = hsd.CID[0] >> 8;
	temp[2] = hsd.CID[0] >> 16;
	temp[3] = hsd.CID[0] >> 24;

	temp[4] = hsd.CID[1];
	temp[5] = hsd.CID[1] >> 8;
	temp[6] = hsd.CID[1] >> 16;
	temp[7] = hsd.CID[1] >> 24;
	
	temp[8] = hsd.CID[2];
	temp[9] = hsd.CID[2] >> 8;
	temp[10] = hsd.CID[2] >> 16;
	temp[11] = hsd.CID[2] >> 24;
	
	temp[12] = hsd.CID[3];
	temp[13] = hsd.CID[3] >> 8;
	temp[14] = hsd.CID[3] >> 16;
	temp[15] = hsd.CID[3] >> 24;
	printf("SD Card CID:");
	Uart6Tx_Hex2Char(temp, 16);
}

