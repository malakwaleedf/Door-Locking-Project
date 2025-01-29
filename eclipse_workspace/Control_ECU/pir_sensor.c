/*
 *  File name: pir_sensor.c
 *  Description: Source file for PIR Sensor driver
 *  Created on: Nov 1, 2024
 *  Author: Malak Waleed
 */

#include "pir_sensor.h"
#include "gpio.h"
#include "common_macros.h"

void PIRSensor_init(void)
{
	/*set the direction of flame sensor's pin to output*/
	GPIO_setupPinDirection(PIR_SENSOR_PORT, PIR_SENSOR_PIN, PIN_OUTPUT);
}

uint8 PIRSensor_getValue(void)
{
	/*return flame sensors's reading*/
	return GPIO_readPin(PIR_SENSOR_PORT, PIR_SENSOR_PIN);
}
