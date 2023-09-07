/*
 * bq79600.c
 *
 *  Created on: 2023年8月25日
 *      Author: fnadmin
 */

#include <LPSPI.h>
#include "device_registers.h"           /* include peripheral declarations */
#include "CRC16.h"
#include "bq79600.h"
#include "systick.h"


uint8_t send_buf[20];
/* BQ79600单设备读取 */
uint8_t BQ79600_Single_Read(uint8_t DEV_adr, uint16_t REG_adr, uint8_t DATA, uint8_t *readbuf)
{
	uint16_t i,buf_crc;
	uint8_t count = 0,trash_can = 0;
	uint8_t save_read[8] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

	send_buf[0] = Single_Device_Read;		//Always 0x80
	//send_buf[0] = 0x01;
	send_buf[1] = DEV_adr;					//设备地址，BQ79600地址为0x00;其范围为:0x00~0x3F，菊花链路上每增加1个设备，地址加1
	send_buf[2] = (uint8_t)(REG_adr>>8);
	send_buf[3] = (uint8_t)(REG_adr);		//需操作的寄存器地址，头文件内有宏定义
	send_buf[4] = DATA;    //读取的字节数		//读操作中，此字节均为0
	buf_crc = do_crc_table(send_buf, 5);
	send_buf[5] = (uint8_t)(buf_crc >> 8);
	send_buf[6] = (uint8_t)(buf_crc);

	while (BQ79600_RDY == 0)
	{
		delay_us(50);
		count++;

		if (5 <= count)
		{
			BQ79600_Comm_Clear();
			return 0;
		}
	}
	//LPSPI1_transmit_8bits(0xFF);
	//trash_can = LPSPI1_receive_8bits();

	//PTA-> PCOR |= 1<<6;		//拉低cs

	for(i=0;i<7;i++)
	{
		LPSPI1_transmit_8bits(send_buf[i]);
		//LPSPI1_transmit_8bits(0x80);
		readbuf[i] = LPSPI1_receive_8bits();
		save_read[i] = readbuf[0];
	}

	count = 0;
	//PTA-> PSOR |= 1<<6;		//拉高cs脚


    while(BQ79600_RDY == 0)
    {
        delay_us(10);
        count++;

        if ((100 + (7 + DATA) * 10) < count * 10) //wait time: 100us + m*10us
        {
            BQ79600_Comm_Clear();
            return 0;
        }
    }

    //PTA-> PCOR |= 1<<6;		//拉低cs

    if(BQ79600_RDY == 1)
    {
    	for(i = 0; i < (DATA + 7); i++)
    	{
    		LPSPI1_transmit_8bits(0xFF); //循环写数
    		readbuf[i] = LPSPI1_receive_8bits();
    		save_read[i] = readbuf[i];
    	}
    }

    //PTA-> PSOR |= 1<<6;		//拉高cs脚

    //for(i=0;i<8;i++)
    	//save_read[i] = readbuf[i];

    buf_crc = do_crc_table(readbuf, 5);
    BQ79600_Comm_Clear();

    if (buf_crc != ((readbuf[DATA + 4] << 8) | readbuf[DATA + 5]))
    	return 0;
    else
        return 1;
}

uint8_t BQ79600_Single_Wr(uint8_t datanum, uint8_t devadr, uint16_t regadr, uint8_t *DATA)
{
    uint16_t i, bufcrc;
    uint8_t sendbuf[20];
    uint8_t count = 0;
    sendbuf[0] = Single_Device_Write | datanum;
    sendbuf[1] = devadr;
    sendbuf[2] = (uint8_t)(regadr >> 8);
    sendbuf[3] = (uint8_t)(regadr);

    for (i = 0; i < datanum + 1; i++)
        sendbuf[4 + i] = *DATA++;  //验证一下

    bufcrc = do_crc_table(sendbuf, datanum + 5);
    sendbuf[4 + i] = (uint8_t)(bufcrc >> 8);
    sendbuf[5 + i] = (uint8_t)(bufcrc);

    while (BQ79600_RDY == 0)
    {
        delay_us(50);
        count++;

        if (5 <= count)
        {
            BQ79600_Comm_Clear();
            return 0;
        }
    }

    PTA-> PCOR |= 1<<6;		//拉低cs

    for (i = 0; i < (7 + datanum); i++)
    	LPSPI1_transmit_8bits(sendbuf[i]); //循环写数

    PTA-> PSOR |= 1<<6;		//拉高cs脚
    return 1;
}

void BQ79600_Comm_Clear()
{
	LPSPI1_transmit_8bits(0x00);

}

