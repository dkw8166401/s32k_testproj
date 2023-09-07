/*
 * systick.h
 *
 *  Created on: 2023Äê8ÔÂ25ÈÕ
 *      Author: fnadmin
 */

#ifndef SYSTICK_H_
#define SYSTICK_H_

#include "device_registers.h"	  /* include peripheral declaration*/

void delay_ms(uint32_t nms);
void delay_us(uint32_t nus);
int s32_systick_init(void);



#endif /* SYSTICK_H_ */
