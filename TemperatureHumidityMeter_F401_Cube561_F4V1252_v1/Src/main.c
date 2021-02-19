/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "rtc.h"
#include "sdio.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "sht30_i2c_drv.h"
#include "tf_sdio_drv.h"
#include "wifi.h"
#include "IR_Rx_drv.h"
#include "IR_Rx_parse.h"
#include "IR_Tx_app.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
unsigned char myStrnCmp(unsigned char *str1, unsigned char *str2, unsigned long str_len);
unsigned long MySizeof(unsigned char * buff);
extern void IR_RX_Init(void);
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
extern unsigned long Time2_i;
unsigned long Time10_i = 0;
unsigned long Led_i = 0;
unsigned long Print_i = 0;

unsigned char *Usart1DataAdr;
unsigned char Usart1DataLen;
extern unsigned char Usart1RxBuff;
extern UART_IRQ_RX_Handler Usart1Rx;

unsigned char *Usart2DataAdr;
unsigned char Usart2DataLen;
extern unsigned char Usart2RxBuff;
extern UART_IRQ_RX_Handler Usart2Rx;

unsigned char *Usart6DataAdr;
unsigned char Usart6DataLen;
extern unsigned char Usart6RxBuff;
extern UART_IRQ_RX_Handler Usart6Rx;

//ADC variables
extern unsigned long Adc_i;
extern uint32_t Adc1Value[2];
float Adc1N1 = 0;	
float Adc1Vre = 0;	
unsigned char AdcChr[20] = "ADC";
unsigned char AdcChr1[50] = "ADC";
unsigned char IicChr[20] = "IIC";
unsigned char IicChr1[50] = "IIC";
unsigned char RtcChr[20] = "RTC";
unsigned char RtcChr1[50] = "RTC";
unsigned long AdcChrLen;
unsigned char Adc2ChrFlag = 0;

const unsigned char HeartBeat[7] = {0x55, 0xAA, 0, 0, 0, 0, 0xFF};
const unsigned char HeartBeat_len = 7;


//IIC
extern unsigned long IIc_i;
uint8_t recv_dat[6] = {0};
float temperature = 0.0;
float humidity = 0.0;

//SDIO
extern SD_HandleTypeDef hsd;
HAL_StatusTypeDef test1;
uint8_t mypData[512 *10];
uint8_t mypData1[512 *10];
unsigned long test_i = 0;

unsigned char SdioCase_i;

#define SdCardInfor  "SdCardInfor"
#define SdCardState  "SdCardState"
#define SdCardRead  "SdCardRead"
#define SdCardWrite  "SdCardWrite"
#define SdCardErase  "SdCardErase"


#define IrTxTest  "IrTxTest"
#define PWM_Start "PWM_Start"
#define PWM_Stop "PWM_Stop"



//key
extern KeyF Key1F;



extern unsigned long CurrentTemperature;
extern unsigned long CurrentHumidity;
extern unsigned long BatteryLevel;
extern unsigned char ChargeState;
extern unsigned long TemperatureCycleReport;
extern unsigned long HumidityPeriodicReport;
extern unsigned char SwitchState;
extern unsigned char LedState;


//IR
extern unsigned char IR_RX_Port_en;
extern unsigned short IR_RX_Level_h[];
extern unsigned short IR_RX_Level_l[];
extern unsigned short IR_RX_Level_i;
unsigned short i4;

unsigned char test_parse;
unsigned char test_parse_data[100];
unsigned char test_parse_data_len;
	
	

RTCTimeDates myRTCTimeDates;


/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM10_Init();
  MX_USART6_UART_Init();
  MX_USART1_UART_Init();
  MX_ADC1_Init();
  MX_I2C1_Init();
  MX_SDIO_SD_Init();
  MX_RTC_Init();
  MX_TIM2_Init();
  MX_TIM5_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim10);
	HAL_UART_Receive_IT(&huart6, &Usart6RxBuff, 1);
	HAL_UART_Receive_IT(&huart1, &Usart1RxBuff, 1);	
	HAL_UART_Receive_IT(&huart2, &Usart2RxBuff, 1);	
	HAL_ADC_Start_DMA(&hadc1, Adc1Value, 2);
	printf("system is run\r\n");
	HAL_TIM_Base_Start_IT(&htim2);
	
    SHT30_Reset();
    if(SHT30_Init() == HAL_OK)
        printf("sht30 init ok.\n");
    else
        printf("sht30 init fail.\n");
		
	wifi_protocol_init();
	IR_RX_Init();
	HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);
	HAL_Delay(10);
	HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_1);	
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	HAL_GPIO_WritePin(BUZ_GPIO_Port, BUZ_Pin, GPIO_PIN_RESET);
	HAL_Delay(1000);
	for(test_i = 0; test_i < 512 * 10; test_i++)
	{
		mypData[test_i] =  test_i;
	}
	
	//AirConditioner_ShutDown();
	
	//__HAL_TIM_SetCompare(&htim5,TIM_CHANNEL_1, 0);
	
	
	
  while (1)
  {		
//		if(Led_i >= 250)
//		{
//			Led_i = 0;
//			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
//		}
//		if(Time2_i >= 25000)
//		{
//			Time2_i = 0;
//			HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
//		}
		
		switch(mcu_get_wifi_work_state())
		{
				case SMART_CONFIG_STATE:
				{
					if(Led_i >= 250)
					{
						Led_i = 0;						HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
					}					
				}//处于 Smart 配置状态，即 LED 快闪
				break;
				case AP_STATE:
				{
					if(Led_i >= 1500)
					{
						Led_i = 0;						HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_8);
					}	
				}//处于 AP 配置状态，即 LED 慢闪
				break;
				case WIFI_NOT_CONNECTED:
				{
					if(Led_i >= 250)
					{
						Led_i = 0;						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_SET);
					}	
				}//Wi-Fi 配置完成，正在连接路由器，即 LED 常暗
				break;
				case WIFI_CONNECTED:
				{
					if(Led_i >= 250)
					{
						Led_i = 0;						HAL_GPIO_WritePin(GPIOA, GPIO_PIN_8,GPIO_PIN_RESET);
					}	
				}//路由器连接成功，即 LED 常亮
				break;
				default:break;
		}
		if(Print_i >=5000)
		{
			Print_i = 0;
			printf("Wifi Work State = %d\r\n", mcu_get_wifi_work_state());
			myRTCTimeDates = GetRTC();


			RtcChr1[0] = 't';RtcChr1[1] = '0';RtcChr1[2] = '.';RtcChr1[3] = 't';RtcChr1[4] = 'x';RtcChr1[5] = 't';RtcChr1[6] = '=';
			RtcChr1[7] = '"';
			sprintf((char *)RtcChr, "%d\r\n", myRTCTimeDates.RtcTime.Hours);
			if(myRTCTimeDates.RtcTime.Hours < 10)
			{
				RtcChr1[8] = '0';RtcChr1[9] = RtcChr[0];				
			}
			else
			{
				RtcChr1[8] = RtcChr[0];RtcChr1[9] = RtcChr[1];
			}
			RtcChr1[10] = ':';
			sprintf((char *)RtcChr, "%d\r\n", myRTCTimeDates.RtcTime.Minutes);
			if(myRTCTimeDates.RtcTime.Minutes < 10)
			{
				RtcChr1[11] = '0';RtcChr1[12] = RtcChr[0];				
			}
			else
			{
				RtcChr1[11] = RtcChr[0];RtcChr1[12] = RtcChr[1];	
			}			
			RtcChr1[13] = '"';
			RtcChr1[14] = 0xff;RtcChr1[15] = 0xff;RtcChr1[16] = 0xff;
			HAL_UART_Transmit(&huart2, RtcChr1, 17, 1000 );
		}
		
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
		/* IR task */
		if(IR_RX_Port_en == 0)
		{
//			printf("i = %d \r\n",IR_RX_Level_i);
//			printf("test_rx_l\r\n");
//			for(i4 = 0; i4 < (IR_RX_Level_i); i4++)
//			{
//				printf("%d,",IR_RX_Level_l[i4] * 20);
//			}
//			printf("\r\ntest_rx_h\r\n");
//			for(i4 = 0; i4 < (IR_RX_Level_i); i4++)
//			{
//				printf("%d,",IR_RX_Level_h[i4] * 20);
//			}
			
			test_parse = IR_RX_TimeSequence_parse(IR_RX_Level_h, IR_RX_Level_l, IR_RX_Level_i, test_parse_data, &test_parse_data_len);
			printf("\r\nIR RX data error = %d\r\n", test_parse);
			for(i4 = 0; i4 < test_parse_data_len; i4++)
			{
				printf("0x%02x,",test_parse_data[i4]);
			}
			IR_RX_Init();
		}

		/* Usart1 task (WBR3) */
		wifi_uart_service();
		if(Usart1Rx.State == RXend)
		{
			Usart1DataAdr = GetUsart1RxData();
			Usart1DataLen = GetUsart1RxDataLen();
			/* test WBR3 */
			printf("RX fr WBR3:");Uart6Tx_Hex2Char(Usart1DataAdr, Usart1DataLen);
					
			Usart1Rx.State = Idle;
			Usart1Rx.Enable = ENABLE;
		}/* task end */

		if(Key1F.UpToDownFlag == 1)//按键按下执行的任务
		{		
			printf("Key1 UpToDown\r\n");	
			mcu_reset_wifi();
			Key1F.UpToDownFlag = 0;
		}
//		if(Key1F.DownToUpFlag == 1)//按键抬起执行的任务
//		{		
//			printf("Key1F.DownToUp\r\n");	
//			Key1F.DownToUpFlag = 0;
//		}	

		
		/* Usart2 task (DISPLAY) */
		if(Usart2Rx.State == RXend)
		{
			Usart2DataAdr = GetUsart2RxData();
			Usart2DataLen = GetUsart2RxDataLen();

			//HAL_UART_Transmit(&huart2, Usart2DataAdr, Usart2DataLen, 1000 );

					
			Usart2Rx.State = Idle;
			Usart2Rx.Enable = ENABLE;
		}/* task end */

		
		/* IIC task (SHT30) */
		if(IIc_i >= 10000)
		{
			
			IIc_i = 0;
			if(SHT30_Read_Dat(recv_dat) == HAL_OK)
			{
				if(SHT30_Dat_To_Float(recv_dat, &temperature, &humidity)==0)
				{
					CurrentTemperature = (unsigned long)(temperature * 10);
					CurrentHumidity = (unsigned long)humidity;
					//printf("temperature = %f, humidity = %f\n", temperature, humidity);
					//printf("temperature = %ld  humidity = %ld\r\n", CurrentTemperature, CurrentHumidity);
					sprintf((char *)IicChr, "%f\r\n", temperature);
					IicChr1[0] = 't';IicChr1[1] = '1';IicChr1[2] = '.';IicChr1[3] = 't';IicChr1[4] = 'x';IicChr1[5] = 't';IicChr1[6] = '=';
					IicChr1[7] = '"';
					IicChr1[8] = IicChr[0];IicChr1[9] = IicChr[1];IicChr1[10] = IicChr[2];IicChr1[11] = IicChr[3];IicChr1[12] = IicChr[4];
					IicChr1[13] = '"';
					IicChr1[14] = 0xff;IicChr1[15] = 0xff;IicChr1[16] = 0xff;
					HAL_UART_Transmit(&huart2, IicChr1, 17, 1000 );
					sprintf((char *)IicChr, "%f\r\n", humidity);
					IicChr1[0] = 't';IicChr1[1] = '2';IicChr1[2] = '.';IicChr1[3] = 't';IicChr1[4] = 'x';IicChr1[5] = 't';IicChr1[6] = '=';
					IicChr1[7] = '"';
					IicChr1[8] = IicChr[0];IicChr1[9] = IicChr[1];IicChr1[10] = IicChr[2];IicChr1[11] = IicChr[3];IicChr1[12] = IicChr[4];
					IicChr1[13] = '"';
					IicChr1[14] = 0xff;IicChr1[15] = 0xff;IicChr1[16] = 0xff;
					HAL_UART_Transmit(&huart2, IicChr1, 17, 1000 );
				}
				else
				{
					printf("crc check fail.\n");
				}
			}
			else
			{
				printf("read data from sht30 fail.\n");
			}
			all_data_update();			
		}/* task end */


		/* ADC task (battery voltage) */
		if(Adc_i >= 10000)
		{
			Adc_i = 0;
			//Adc1N1 = Adc1Value[0] * 3.3 / 4096;	
			Adc1N1 = 1.2 * (float)Adc1Value[0] / (float)(Adc1Value[1]+1);
			//printf("Vbat=%f Adc1N1=%f Adc1Vre=%d \r\n", Adc1N1*2, Adc1N1, Adc1Value[1]);
			BatteryLevel = (unsigned long)(Adc1N1 * 2 * 10);
			sprintf((char *)AdcChr, "%f\r\n", Adc1N1*2);
			AdcChr1[0] = 't';AdcChr1[1] = '3';AdcChr1[2] = '.';AdcChr1[3] = 't';AdcChr1[4] = 'x';AdcChr1[5] = 't';AdcChr1[6] = '=';
			AdcChr1[7] = '"';
			AdcChr1[8] = AdcChr[0];AdcChr1[9] = AdcChr[1];AdcChr1[10] = AdcChr[2];AdcChr1[11] = AdcChr[3];
			AdcChr1[12] = '"';
			AdcChr1[13] = 0xff;AdcChr1[14] = 0xff;AdcChr1[15] = 0xff;
			HAL_UART_Transmit(&huart2, AdcChr1, 16, 1000 );
			
			Adc1Value[0] = 0;
			HAL_ADC_Start_DMA(&hadc1, Adc1Value, 2);			
		}/* task end */

		/* Usart6 task (USB) */
		if(Usart6Rx.State == RXend)
		{
			Usart6DataAdr = GetUsart6RxData();
			Usart6DataLen = GetUsart6RxDataLen();
			/* test TFcard */
			if(strncmp((char const*)Usart6DataAdr, SdCardInfor, strlen(SdCardInfor)) == 0)
			{
				PrintSdCard_CID();
				PrintSdCard_RCA();
				PrintSdCard_Type();
				PrintSdCard_Version();
				PrintSdCard_Class();
				PrintSdCard_BlockNbr();
				PrintSdCard_BlockSize();
				PrintSdCard_LogBlockNbr();
				PrintSdCard_LogBlockSize();						
			}
			else if(strncmp((char const*)Usart6DataAdr, SdCardState, strlen(SdCardState)) == 0)
			{
				PrintSdio_State();
				PrintSdCard_State();				
			}
			else if(strncmp((char const*)Usart6DataAdr, SdCardRead, strlen(SdCardRead)) == 0)
			{
				test1 = HAL_SD_ReadBlocks_DMA(&hsd, mypData1, 0, 5);
				if(test1 == HAL_OK)
				{
					printf("SD Card Read Block OK\r\n");
					Uart6Tx_Hex2Char(mypData1, 512);
				}
				else
				{
					printf("SD Card Read Block ERROR:%d\r\n",test1);
				}						
			}
			else if(strncmp((char const*)Usart6DataAdr, SdCardWrite, strlen(SdCardWrite)) == 0)
			{
				test1 = HAL_SD_WriteBlocks_DMA(&hsd, mypData, 0, 5);
				if(test1 == HAL_OK)
				{
					printf("SD Card Write Block OK\r\n");
				}
				else
				{
					printf("SD Card Write Block ERROR:%d\r\n",test1);
				}					
			}
			else if(strncmp((char const*)Usart6DataAdr, SdCardErase, strlen(SdCardErase)) == 0)
			{
				test1 = HAL_SD_Erase(&hsd, 0, 7626751);
				/* after SD card Erase, can not write and read SD card */
				if(test1 == HAL_OK)
				{
					printf("SD Card Erase OK\r\n");
				}
				else
				{
					printf("SD Card Erase ERROR:%d\r\n",test1);
				}					
			}
			else if(strncmp((char const*)Usart6DataAdr, IrTxTest, strlen(IrTxTest)) == 0)
			{
				AirConditioner_ShutDown();			
			}
			else if(strncmp((char const*)Usart6DataAdr, PWM_Start, strlen(PWM_Start)) == 0)
			{
				//HAL_TIM_PWM_Start(&htim5,TIM_CHANNEL_1);		
			}
			else if(strncmp((char const*)Usart6DataAdr, PWM_Stop, strlen(PWM_Stop)) == 0)
			{
				//HAL_TIM_PWM_Stop(&htim5,TIM_CHANNEL_1);				
			}
			else
			{
				/* test Usart6 */
				HAL_UART_Transmit(&huart6, Usart6DataAdr, Usart6DataLen, 1000 );;printf("\r\n");				
			}
			
			
					
			Usart6Rx.State = Idle;
			Usart6Rx.Enable = ENABLE;
		}/* task end */		
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 160;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInitStruct.RTCClockSelection = RCC_RTCCLKSOURCE_LSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
unsigned char myStrnCmp(unsigned char *str1, unsigned char *str2, unsigned long str_len)
{
	unsigned long i = 0;
	unsigned char cmp;
	
	for(i = 0; i < str_len; i++)
	{
		if(str1[i] !=  str2[i])
		{
			cmp = 1;
			break;
		}
	}
	if(i == str_len)
	{
		cmp = 0;
	}
	return cmp;
}

unsigned long MySizeof(unsigned char * buff)
{
	unsigned long i = 0;
	while (buff[i] != '\0')
	{
		i++;
	}
	
	return (i);
}






/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
