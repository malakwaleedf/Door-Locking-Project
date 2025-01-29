/*
 *  File name: pir_sensor.h
 *  Description: Header file for PIR Sensor driver
 *  Created on: Nov 1, 2024
 *  Author: Malak Waleed
 */

#ifndef PIR_SENSOR_H_
#define PIR_SENSOR_H_

#include "std_types.h"

#define PIR_SENSOR_PORT PORTC_ID
#define PIR_SENSOR_PIN PIN2_ID

/*Function prototypes*/
void PIRSensor_init(void);
uint8 PIRSensor_getValue(void);

#endif /* PIR_SENSOR_H_ */
