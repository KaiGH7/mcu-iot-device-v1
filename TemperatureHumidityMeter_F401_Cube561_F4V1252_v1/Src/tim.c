/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
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
#include "tim.h"

/* USER CODE BEGIN 0 */
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "IR_Rx_drv.h"
#include "IR_Tx_drv.h"

unsigned long Time2_i;
extern unsigned long Time10_i;
extern unsigned long Led_i;
extern unsigned long IIc_i;
unsigned long Key_i;
extern unsigned long Adc_i;
extern unsigned long Print_i;
extern UART_IRQ_RX_Handler Usart1Rx;
extern UART_IRQ_RX_Handler Usart2Rx;
extern UART_IRQ_RX_Handler Usart6Rx;

unsigned long TestTime = 0;

KeyF Key1F;
KeyS Key1S = KEY_UNKOW;
KeyS PreKey1S = KEY_UNKOW;
/* USER CODE END 0 */

TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim10;

/* TIM2 init function */
void MX_TIM2_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};

  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 79;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 19;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }

}
/* TIM5 init function */
void MX_TIM5_Init(void)
{
  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 79;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 25;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 9;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  HAL_TIM_MspPostInit(&htim5);

}
/* TIM10 init function */
void MX_TIM10_Init(void)
{

  htim10.Instance = TIM10;
  htim10.Init.Prescaler = 799;
  htim10.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim10.Init.Period = 99;
  htim10.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim10.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_Base_Init(&htim10) != HAL_OK)
  {
    Error_Handler();
  }

}

void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspInit 0 */

  /* USER CODE END TIM2_MspInit 0 */
    /* TIM2 clock enable */
    __HAL_RCC_TIM2_CLK_ENABLE();

    /* TIM2 interrupt Init */
    HAL_NVIC_SetPriority(TIM2_IRQn, 2, 0);
    HAL_NVIC_EnableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspInit 1 */

  /* USER CODE END TIM2_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM5)
  {
  /* USER CODE BEGIN TIM5_MspInit 0 */

  /* USER CODE END TIM5_MspInit 0 */
    /* TIM5 clock enable */
    __HAL_RCC_TIM5_CLK_ENABLE();
  /* USER CODE BEGIN TIM5_MspInit 1 */

  /* USER CODE END TIM5_MspInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM10)
  {
  /* USER CODE BEGIN TIM10_MspInit 0 */

  /* USER CODE END TIM10_MspInit 0 */
    /* TIM10 clock enable */
    __HAL_RCC_TIM10_CLK_ENABLE();

    /* TIM10 interrupt Init */
    HAL_NVIC_SetPriority(TIM1_UP_TIM10_IRQn, 7, 0);
    HAL_NVIC_EnableIRQ(TIM1_UP_TIM10_IRQn);
  /* USER CODE BEGIN TIM10_MspInit 1 */

  /* USER CODE END TIM10_MspInit 1 */
  }
}
void HAL_TIM_MspPostInit(TIM_HandleTypeDef* timHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(timHandle->Instance==TIM5)
  {
  /* USER CODE BEGIN TIM5_MspPostInit 0 */

  /* USER CODE END TIM5_MspPostInit 0 */
  
    __HAL_RCC_GPIOA_CLK_ENABLE();
    /**TIM5 GPIO Configuration    
    PA0-WKUP     ------> TIM5_CH1 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* USER CODE BEGIN TIM5_MspPostInit 1 */

  /* USER CODE END TIM5_MspPostInit 1 */
  }

}

void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle)
{

  if(tim_baseHandle->Instance==TIM2)
  {
  /* USER CODE BEGIN TIM2_MspDeInit 0 */

  /* USER CODE END TIM2_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM2_CLK_DISABLE();

    /* TIM2 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM2_IRQn);
  /* USER CODE BEGIN TIM2_MspDeInit 1 */

  /* USER CODE END TIM2_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM5)
  {
  /* USER CODE BEGIN TIM5_MspDeInit 0 */

  /* USER CODE END TIM5_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM5_CLK_DISABLE();
  /* USER CODE BEGIN TIM5_MspDeInit 1 */

  /* USER CODE END TIM5_MspDeInit 1 */
  }
  else if(tim_baseHandle->Instance==TIM10)
  {
  /* USER CODE BEGIN TIM10_MspDeInit 0 */

  /* USER CODE END TIM10_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_TIM10_CLK_DISABLE();

    /* TIM10 interrupt Deinit */
    HAL_NVIC_DisableIRQ(TIM1_UP_TIM10_IRQn);
  /* USER CODE BEGIN TIM10_MspDeInit 1 */

  /* USER CODE END TIM10_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */
unsigned char IR_RX_Pin_state;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	
	if(htim->Instance == TIM2)
	{
		
		IR_TX_Interrupt_fun();
		
		if(HAL_GPIO_ReadPin(IR_RX_GPIO_Port, IR_RX_Pin))
			IR_RX_Pin_state = 1;
		else
			IR_RX_Pin_state = 0;
		
		IR_RX_Interrupt_fun(IR_RX_Pin_state);
	}
	
	

	if(htim->Instance == TIM10)
	{
		Time10_i++;
		Led_i++;
		Key_i++;
		Adc_i++;
		IIc_i++;
		Print_i++;
		
		if(Usart1Rx.OverTimeCountEnable == ENABLE)
		{
			Usart1Rx.OverTimeCount++;
			if(Usart1Rx.OverTimeCount > Usart1Rx.OverTimeValueSet)
			{
				/* Rx data end */
				Usart1Rx.Enable = DISABLE;
				Usart1Rx.OverTimeCountEnable = DISABLE;
				Usart1Rx.OverTimeCount = 0;
				Usart1Rx.State = RXend;			
			}
		}	
		
		if(Usart2Rx.OverTimeCountEnable == ENABLE)
		{
			Usart2Rx.OverTimeCount++;
			if(Usart2Rx.OverTimeCount > Usart2Rx.OverTimeValueSet)
			{
				/* Rx data end */
				Usart2Rx.Enable = DISABLE;
				Usart2Rx.OverTimeCountEnable = DISABLE;
				Usart2Rx.OverTimeCount = 0;
				Usart2Rx.State = RXend;			
			}
		}
		
		if(Usart6Rx.OverTimeCountEnable == ENABLE)
		{
			Usart6Rx.OverTimeCount++;
			if(Usart6Rx.OverTimeCount > Usart6Rx.OverTimeValueSet)
			{
				/* Rx data end */
				Usart6Rx.Enable = DISABLE;
				Usart6Rx.OverTimeCountEnable = DISABLE;
				Usart6Rx.OverTimeCount = 0;
				Usart6Rx.State = RXend;			
			}
		}
		
		if(Key_i > 9)
		{
			Key_i = 0;
			
			if(HAL_GPIO_ReadPin(Key1_GPIO_Port, Key1_Pin ) == RESET)
			{
				Key1F.DownCount++; Key1F.UpCount = 0;
				if(Key1F.DownCount > 200) { Key1F.DownCount = 200; }
			}
			else
			{
				Key1F.DownCount = 0; Key1F.UpCount++;
				if(Key1F.UpCount > 200) {	Key1F.UpCount = 200; }
			}
			
			if(Key1F.DownCount > 7)
			{
				Key1S = KEY_DOWN;
				if(PreKey1S == KEY_UP) { Key1F.UpToDownFlag = 1; } //一次有效按键按下
				PreKey1S = KEY_DOWN;
			}
			else if(Key1F.UpCount > 7) 
			{
				Key1S = KEY_UP;
				if(PreKey1S == KEY_DOWN) { Key1F.DownToUpFlag = 1; }//一次有效按键抬起
				PreKey1S = KEY_UP;
			}
			else { /*Key1S = KEY_UNKOW;*/ }
			
			//if(Key1F.UpToDownFlag == 1)//按键按下执行的任务
			//{		
			//	printf("Key1 UpToDown\r\n");
			//	
			//	Key1F.UpToDownFlag = 0;
			//}
			//if(Key1F.DownToUpFlag == 1)//按键抬起执行的任务
			//{		
			//	printf("Key1F.DownToUp\r\n");
			//	
			//	Key1F.DownToUpFlag = 0;
			//}			
		}		
	}
}
/* USER CODE END 1 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
