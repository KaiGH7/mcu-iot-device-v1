#ifndef __sht30_i2c_drv_H
#define __sht30_i2c_drv_H


#include "main.h"


void PrintSdCard_CID(void);
void PrintSdCard_RCA(void);
void PrintSdCard_Type(void);
void PrintSdCard_Version(void);
void PrintSdCard_Class(void);
void PrintSdCard_BlockNbr(void);
void PrintSdCard_BlockSize(void);
void PrintSdCard_LogBlockNbr(void);
void PrintSdCard_LogBlockSize(void);

void PrintSdio_State(void);
void PrintSdCard_State(void);


#endif

