/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* USER CODE BEGIN 0 */
#include "stdio.h"
#include "wifi.h"

unsigned char Usart1RxBuff;
unsigned char Usart1RxData[255];
unsigned char Usart1TxData[255];
unsigned char Usart1RxData_i=0;
#define UART_IRQ_RX_Handler_DEFAULTS {Idle , ENABLE, 10, 0, DISABLE }
UART_IRQ_RX_Handler Usart1Rx = UART_IRQ_RX_Handler_DEFAULTS;

unsigned char Usart2RxBuff;
unsigned char Usart2RxData[255];
unsigned char Usart2RxData_i=0;
#define UART_IRQ_RX_Handler_DEFAULTS {Idle , ENABLE, 10, 0, DISABLE }
UART_IRQ_RX_Handler Usart2Rx = UART_IRQ_RX_Handler_DEFAULTS;

unsigned char Usart6RxBuff;
unsigned char Usart6RxData[255];
unsigned char Usart6RxData_i=0;
#define UART_IRQ_RX_Handler_DEFAULTS {Idle , ENABLE, 10, 0, DISABLE }
UART_IRQ_RX_Handler Usart6Rx = UART_IRQ_RX_Handler_DEFAULTS;

/* USER CODE END 0 */

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart6;

/* USART1 init function */

void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 9600;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART2 init function */

void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }

}
/* USART6 init function */

void MX_USART6_UART_Init(void)
{

  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspInit 0 */

  /* USER CODE END USART2_MspInit 0 */
    /* USART2 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART2 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspInit 1 */

  /* USER CODE END USART2_MspInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspInit 0 */

  /* USER CODE END USART6_MspInit 0 */
    /* USART6 clock enable */
    __HAL_RCC_USART6_CLK_ENABLE();
  
    __HAL_RCC_GPIOC_CLK_ENABLE();
    /**USART6 GPIO Configuration    
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF8_USART6;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* USART6 interrupt Init */
    HAL_NVIC_SetPriority(USART6_IRQn, 6, 0);
    HAL_NVIC_EnableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspInit 1 */

  /* USER CODE END USART6_MspInit 1 */
  }
}

void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART2_MspDeInit 0 */

  /* USER CODE END USART2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART2 GPIO Configuration    
    PA2     ------> USART2_TX
    PA3     ------> USART2_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART2_MspDeInit 1 */

  /* USER CODE END USART2_MspDeInit 1 */
  }
  else if(uartHandle->Instance==USART6)
  {
  /* USER CODE BEGIN USART6_MspDeInit 0 */

  /* USER CODE END USART6_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART6_CLK_DISABLE();
  
    /**USART6 GPIO Configuration    
    PC6     ------> USART6_TX
    PC7     ------> USART6_RX 
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_6|GPIO_PIN_7);

    /* USART6 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART6_IRQn);
  /* USER CODE BEGIN USART6_MspDeInit 1 */

  /* USER CODE END USART6_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
int fputc(int ch, FILE *f)
{
	while((USART6->SR&0x40) == 0);
	
	USART6->DR = (uint8_t)ch;
	return ch;
}

char Hex2Char[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
void Uart6Tx_Hex2Char(unsigned char * data, unsigned long len)
{
	unsigned long i;
	uint8_t tep[3];
	uint8_t	tcr[2] = "\r\n";
	
	for(i = 0; i < len; i++)
	{
		tep[0] =  Hex2Char[(data[i] >> 4) & 0x0fUL];
		tep[1] =  Hex2Char[(data[i] >> 0) & 0x0fUL];
		tep[2] = ' ';
		
		HAL_UART_Transmit(&huart6, tep, 3, 1000 );
	}
	HAL_UART_Transmit(&huart6, tcr, 2, 1000 );	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart->Instance == USART1)
	{
		/* test code */
		//Usart1RxData[Usart1RxData_i] = Usart1RxBuff;
		//Usart1RxData_i++;
		
		uart_receive_input(Usart1RxBuff);
		
		if(Usart1Rx.Enable == ENABLE)
		{
			Usart1Rx.OverTimeCount = 0;
			Usart1Rx.OverTimeCountEnable = ENABLE;			
			Usart1Rx.State = RXing;			
			Usart1RxData[Usart1RxData_i] = Usart1RxBuff;
			Usart1RxData_i++;
			if(Usart1RxData_i >= 255)
			{
				/* Rx data over */
				Usart1Rx.Enable = DISABLE;
				Usart1Rx.OverTimeCountEnable = DISABLE;
				Usart1Rx.OverTimeCount = 0;
				Usart1Rx.State = RXover;
			}			
		}						
	}
	HAL_UART_Receive_IT(&huart1, &Usart1RxBuff, 1);	

	if(huart->Instance == USART2)
	{
		/* test code */
		//Usart2RxData[Usart2RxData_i] = Usart2RxBuff;
		//Usart2RxData_i++;
		
		if(Usart2Rx.Enable == ENABLE)
		{
			Usart2Rx.OverTimeCount = 0;
			Usart2Rx.OverTimeCountEnable = ENABLE;			
			Usart2Rx.State = RXing;			
			Usart2RxData[Usart2RxData_i] = Usart2RxBuff;
			Usart2RxData_i++;
			if(Usart2RxData_i >= 255)
			{
				/* Rx data over */
				Usart2Rx.Enable = DISABLE;
				Usart2Rx.OverTimeCountEnable = DISABLE;
				Usart2Rx.OverTimeCount = 0;
				Usart2Rx.State = RXover;
			}			
		}						
	}
	HAL_UART_Receive_IT(&huart2, &Usart2RxBuff, 1);	

	if(huart->Instance == USART6)
	{
		/* test code */
		//Usart2RxData[Usart2RxData_i] = Usart2RxBuff;
		//Usart2RxData_i++;
		
		if(Usart6Rx.Enable == ENABLE)
		{
			Usart6Rx.OverTimeCount = 0;
			Usart6Rx.OverTimeCountEnable = ENABLE;			
			Usart6Rx.State = RXing;			
			Usart6RxData[Usart6RxData_i] = Usart6RxBuff;
			Usart6RxData_i++;
			if(Usart6RxData_i >= 255)
			{
				/* Rx data over */
				Usart6Rx.Enable = DISABLE;
				Usart6Rx.OverTimeCountEnable = DISABLE;
				Usart6Rx.OverTimeCount = 0;
				Usart6Rx.State = RXover;
			}			
		}						
	}
	HAL_UART_Receive_IT(&huart6, &Usart6RxBuff, 1);	


}

unsigned char GetUsart1RxDataLen(void)
{
	unsigned char temp = 0;
	temp = Usart1RxData_i;
	Usart1RxData_i = 0;
	
	return temp;
}
	
unsigned char *GetUsart1RxData(void)
{
		return Usart1RxData;
}


unsigned char GetUsart2RxDataLen(void)
{
	unsigned char temp = 0;
	temp = Usart2RxData_i;
	Usart2RxData_i = 0;
	
	return temp;
}
	
unsigned char *GetUsart2RxData(void)
{
		return Usart2RxData;
}

unsigned char GetUsart6RxDataLen(void)
{
	unsigned char temp = 0;
	temp = Usart6RxData_i;
	Usart6RxData_i = 0;
	
	return temp;
}
	
unsigned char *GetUsart6RxData(void)
{
		return Usart6RxData;
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
