/*
 * CRC16.h
 *
 *  Created on: 2023Äê8ÔÂ25ÈÕ
 *      Author: fnadmin
 */

#ifndef CRC16_H_
#define CRC16_H_

#include "device_registers.h"           /* include peripheral declarations */
#include "stdio.h"


extern const unsigned int crc_table[256];

unsigned short do_crc_table(unsigned char *ptr, int len);
#endif /* CRC16_H_ */
