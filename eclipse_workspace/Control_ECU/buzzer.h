/*
 *  File name: buzzer.h
 *  Description: Header file for Buzzer driver
 *  Created on: Oct 6, 2024
 *  Author: Malak Waleed
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "std_types.h"

#define BUZZER_PORT PORTC_ID
#define BUZZER_PIN PIN7_ID

/*Function prototypes*/
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);


#endif /* BUZZER_H_ */
