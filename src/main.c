/*
 * Copyright (c) 2014 - 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2016 - 2018, NXP.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 * Description:
 * ==============================================================================
 * A simple LPSPI transfer is performed using FIFOs which can improve throughput. 
 * After initialization, a 16 bit frame is transmitted at 1 Mbps. Software will 
 * poll flags rather than using interrupts and/or DMA.
 */

#include <LPSPI.h>
#include "device_registers.h"           /* include peripheral declarations */
#include "clocks_and_modes.h"
#include "bq79600.h"
#include "CRC16.h"
#include "systick.h"
//#include "fs4500.h"
//#include "fs4500_driver.h"

  //uint16_t tx_16bits = 0xFD00;
  //uint16_t LPSPI1_16bits_read;
  uint8_t test_buffer[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
  uint8_t part_id = 0;
void WDOG_disable (void)
{
	WDOG->CNT=0xD928C520;     /* Unlock watchdog 		*/
    WDOG->TOVAL=0x0000FFFF;   /* Maximum timeout value */
    WDOG->CS = 0x00002100;    /* Disable watchdog 		*/
}

void PORT_init (void)
{
	/*!
	 * Pins definitions
	 * ===================================================
	 *
	 * Pin number        | Function
	 * ----------------- |------------------
	 * PTA6              | LPSPI1_PCS1	(记得在TCR寄存器内也配置为PCS1；参考手册中说在CFGR1中配置了，pin muxing中就不用再配了？)
	 * PTB14             | LPSPI1_SCK
	 * PTB15			 | LPSPI1_SIN
	 * PTB16			 | LPSPI1_SOUT
	 * PTB13			 | SPI_DRY(BQ79600)
	 * PTA26			 | LPSPI0_PCS0
	 */
	PCC->PCCn[PCC_PORTA_INDEX]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTA //使能PORTA的时钟 ,这里为何不用把PR置1*/
	PCC->PCCn[PCC_PORTB_INDEX]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTB //使能PORTB的时钟 ,这里为何不用把PR置1*/
	PCC->PCCn[PCC_PORTC_INDEX]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTB //使能PORTB的时钟 ,这里为何不用把PR置1*/
	PCC->PCCn[PCC_PORTD_INDEX]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTD //使能PORTD的时钟 ,这里为何不用把PR置1*/
	PCC->PCCn[PCC_PORTE_INDEX]|=PCC_PCCn_CGC_MASK; /* Enable clock for PORTD //使能PORTE的时钟 ,这里为何不用把PR置1*/
	  PORTA->PCR[6]|=PORT_PCR_MUX(3); /* Port A6: MUX = ALT3, LPSPI1_PCS1 //*/
	  PORTB->PCR[14]|=PORT_PCR_MUX(3); /* Port B14: MUX = ALT3, LPSPI1_SCK */
	  PORTB->PCR[15]|=PORT_PCR_MUX(3); /* Port B15: MUX = ALT3, LPSPI1_SIN */
	  PORTB->PCR[16]|=PORT_PCR_MUX(3); /* Port B16: MUX = ALT3, LPSPI1_SOUT */

	  PORTA->PCR[30]|=PORT_PCR_MUX(4); /* Port A30: MUX = ALT4, LPSPI0_SOUT */
	  PORTD->PCR[16]|=PORT_PCR_MUX(4); /* Port D16: MUX = ALT4, LPSPI0_SIN */
	  PORTD->PCR[15]|=PORT_PCR_MUX(4); /* Port D15: MUX = ALT4, LPSPI0_SCK */
	  PORTA->PCR[26]|=PORT_PCR_MUX(4); /* Port A26: MUX = ALT4, LPSPI0_PCS0 */

	  //PTA->PDDR |= (1<<16);   			/* Port A6 CS PIN: Data Direction= output (default) */
	  //PORTA->PCR[6] =  PORT_PCR_MUX(1);	/* Port A6: MUX = GPIO, OUTput filter enabled */



	  PTC->PDDR |= (1<<10);   			/* Port C10 WAKE UP PIN: Data Direction= output (default) */
	  PORTC->PCR[10] =  PORT_PCR_MUX(1);	/* Port C10: MUX = GPIO, OUTput filter enabled */

	  PTE->PDDR |= (1<<9);   			/* Port E9 RST PIN: Data Direction= output (default) */
	  PORTE->PCR[9] =  PORT_PCR_MUX(1);	/* Port E9: MUX = GPIO, OUTput filter enabled */

	  PTB->PDDR |= (1<<28);   			/* Port B28 DEBUG PIN: Data Direction= output (default) */
	  PORTB->PCR[28] =  PORT_PCR_MUX(1);	/* Port B28: MUX = GPIO, OUTput filter enabled */


	  PTB->PDDR &= ~(1<<13);   			/* Port B13: Data Direction= input (default) */
	  PORTB->PCR[13] = PORT_PCR_MUX(1)
			    	  |PORT_PCR_PFE_MASK; 	/* Port B13: MUX = GPIO, input filter enabled */

	  //4500的IO2与MCU的PTC14连接，IO3与MCU的PTB25连接，用作4500的safety inputs(后续需要时进行设置)
	  //PTE->PDDR &= ~(1<<9);   			/* Port E9: Data Direction= input (default) */
	  //PORTE->PCR[9] = PORT_PCR_MUX(1)		//检测FS4500的RSTB引脚是否已经释放为低电平
			    	  //|PORT_PCR_PFE_MASK; 	/* Port E9: MUX = GPIO, input filter enabled */


}

int main(void)
{
	/*!
	 * Initialization:
	 * =======================
	 */
  WDOG_disable();		   /* Disable WDOG */

  SOSC_init_8MHz();        /* Initialize system oscillator for 8 MHz xtal //通过外部8M晶振配置系统时钟并使能 */

  /*设置工作模式为VLPR*/
  SMC->PMPROT = SMC_PMPROT_AVLP(1);
  SMC->PMCTRL = SMC_PMCTRL_RUNM(2)
			   |SMC_PMCTRL_STOPM(1);
  while (((SMC->PMSTAT & SMC_PMSTAT_PMSTAT_MASK) >> SMC_PMSTAT_PMSTAT_SHIFT ) != 4) {}
  /*设置工作模式为VLPR*/

  SPLL_init_160MHz();      /* Initialize SPLL to 160 MHz with 8 MHz SOSC  //通过8MHz的OSC初始化系统锁相环为160MHz*/
  NormalRUNmode_80MHz();   /* Init clocks: 80 MHz sysclk & core, 40 MHz bus, 20 MHz flash */
  s32_systick_init();
  //LPSPI1_init_master();    	/* Initialize LPSPI 1 as master */
  LSPI_INIT(0,2,1,0,15,0,1);	//LSPI0配置---fs4500
  LSPI_INIT(1,2,1,0,7,0,0);		//LSPI1配置---bq79600
  PORT_init();             		/* Configure ports */


  delay_ms(100);
  //PTA-> PSOR |= 1<<6;		//
  //PTB-> PSOR |= 1<<28;		//拉高后重启复位进DEBUG
  //PTB-> PCOR |= 1<<28;		//拉低后重启复位，退出DEBUG

	while(1)
	{
		BQ79600_Single_Read(0x00, Z_PARTID,0x00, test_buffer);
		//part_id = test_buffer[0];
	}

}
