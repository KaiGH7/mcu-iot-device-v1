#ifndef __IR_Tx_app_H
#define __IR_Tx_app_H




typedef enum 
{
	MAUTO = 0U, 
	CODE,
	DEWATER,
	HEAT,
	WIND
}AirConditioner_Mode;
	
typedef enum 
{
	WAUTO = 0U, 
	LOW,
	MEDIUM,
	HIGH,
	FIXED
}AirConditioner_WindSpeed;


typedef struct
{
	AirConditioner_Mode      A_Mode;
	AirConditioner_WindSpeed A_WindSpeed;
	unsigned char 					 A_Temperature;

}AirConditionerTypeDef;



void AirConditioner_ShutDown(void);
unsigned char AirConditioner_Set(AirConditionerTypeDef A_TypeDef);

#endif

