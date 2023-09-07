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

#include "device_registers.h"	  /* include peripheral declarations */

void LPSPI1_init_master(void)
{
	/*!
	 * LPSPI1 Clocking:
	 * ===================================================
	 */
	PCC->PCCn[PCC_LPSPI1_INDEX] = 0;          		/* Disable clocks to modify PCS ( default) //初始化LSPI1的外围时钟控制器全0	*/
	PCC->PCCn[PCC_LPSPI1_INDEX] = PCC_PCCn_PR_MASK	/* (default) Peripheral is present.		//设置LSPI1为可用状态	*/
								 |PCC_PCCn_CGC_MASK	/* Enable PCS=SIRC_DIV2 (4 MHz func'l clock) //给外设配置时钟源，并使能	*/
								 |PCC_PCCn_PCS(2);	//此3位是用于外设时钟源的选择,对于外设选择不同的时钟源 ，此项需根据需求进行配置(clock option 2---SIRCDIV2_CLK)，在CGC=0时才可配置
	/*!
	 * LPSPI1 Initialization:						//对LPSPI1寄存器进行初始化
	 * ===================================================
	 */
  LPSPI1->CR    = 0x00000000;   			/* Disable module for configuration  //对CR寄存器全0配置，取消LSPI1的使能，以便配置		*/
  LPSPI1->IER   = 0x00000000;   			/* Interrupts not used 		//禁止使用中断				*/
  LPSPI1->DER   = 0x00000000;   			/* DMA not used 			//禁止使用DMA					*/
  LPSPI1->CFGR0 = 0x00000000;   			/* Defaults: 				//默认CFGR0配置					*/
                                			/* RDM0=0: rec'd data to FIFO as normal //将接收到的数据存入FIFO中		*/
                                			/* CIRFIFO=0; Circular FIFO is disabled //禁止FIFO回环功能		*/
                                			/* HRSEL, HRPOL, HREN=0: Host request disabled  //禁止Host Request*/

  LPSPI1->CFGR1 = LPSPI_CFGR1_MASTER_MASK;  /* Configurations: master mode		//需在LPSPI 未使能时配置						*/
											/* PCSCFG=0: PCS[3:2] are enabled 	//配置为主机模式，其余默认配置							*/
											/* OUTCFG=0: Output data retains last value when CS negated	*/
											/* PINCFG=0: SIN is input, SOUT is output 						*/
											/* MATCFG=0: Match disabled 									*/
											/* PCSPOL=0: PCS is active low 								*/
											/* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full 			*/
											/* AUTOPCS=0: does not apply for master mode 					*/
											/* SAMPLE=0: input data sampled on SCK edge 					*/
											/* MASTER=1: Master mode 										*/

  LPSPI1->TCR   = LPSPI_TCR_CPOL(0)
		  	     |LPSPI_TCR_CPHA(0)
		  	  	 |LPSPI_TCR_PRESCALE(2)		//配置发送寄存器,Transmit command register
				 |LPSPI_TCR_PCS(1)			//设置PRESCALE为010,4分频
		         |LPSPI_TCR_FRAMESZ(7); 	//?此项需要配置为与硬件一致的PCSn,此项目配置LPSPI1_PCS1(与79600相连的CS信号，PTA6)
				    ///数据长度8位 Transmit cmd: PCS1, 8 bits, prescale func'l clk by 4, etc	*/
											/* CPOL=0改为CPOL=0: SCK inactive state is low时钟空闲时为低电平 							*/
											/* CPHA=0改为cpha=0: 时钟第二个变化沿有效	*/
											/* PRESCALE=2: Functional clock divided by 2**2 = 4 			*/
											/* PCS=1: Transfer using PCS1 									*/
											/* LSBF=0: Data is transfered MSB first 						*/
											/* BYSW=0: Byte swap disabled 									*/
											/* CONT, CONTC=0: Continuous transfer disabled 				*/
											/* RXMSK=0: Normal transfer: rx data stored in rx FIFO 		*/
											/* TXMSK=0: Normal transfer: data loaded from tx FIFO 			*/
											/* WIDTH=0: Single bit transfer 								*/
											/* FRAMESZ=15: # bits in frame = 15+1=16 						*/
  //CCR寄存器只在配置为主机模式时才使用，必须在LPSPI未使能时配置
  LPSPI1->CCR   = LPSPI_CCR_SCKPCS(4)		//配置最后一个SCK到PCS的延时为5个周期
				  |LPSPI_CCR_PCSSCK(4)		//配置PCS assertion到第一个SCK边沿的延迟时间为5个周期
				  |LPSPI_CCR_DBT(8)			//Delay between Transfers = 8+2 = 10
				  |LPSPI_CCR_SCKDIV(8);   	/* Clock dividers based on prescaled func'l clk of 100 nsec 	*/
											/* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec) 			*/
											/* PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) 				*/
											/* DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) 			*/
											/* SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) 	*/

  LPSPI1->FCR   = LPSPI_FCR_TXWATER(3);   	/* RXWATER=0: Rx flags set when Rx FIFO >0 //RX FIFO大于0时RX标志位将会置位	*/
                                			/* TXWATER=3: Tx flags set when Tx FIFO <= 3 	//TX FIFO小于3时Tx标志位将会置位*/

  LPSPI1->CR    = LPSPI_CR_MEN_MASK			//使能LPSPI1外设
		  	  	  |LPSPI_CR_DBGEN_MASK;   	/* Enable module for operation 			*/
											/* DBGEN=1: module enabled in debug mode 	*/
											/* DOZEN=0: module enabled in Doze mode 	*/
											/* RST=0: Master logic not reset 			*/
											/* MEN=1: Module is enabled 				*/

	/*!
	 * LPSPI0 Clocking:
	 * ===================================================
	 */
	PCC->PCCn[PCC_LPSPI0_INDEX] = 0;          		/* Disable clocks to modify PCS ( default) //初始化LSPI1的外围时钟控制器全0	*/
	PCC->PCCn[PCC_LPSPI0_INDEX] = PCC_PCCn_PR_MASK	/* (default) Peripheral is present.		//设置LSPI1为可用状态	*/
								 |PCC_PCCn_CGC_MASK	/* Enable PCS=SIRC_DIV2 (4 MHz func'l clock) //给外设配置时钟源，并使能	*/
								 |PCC_PCCn_PCS(2);	//此3位是用于外设时钟源的选择,对于外设选择不同的时钟源 ，此项需根据需求进行配置(clock option 2---SIRCDIV2_CLK)，在CGC=0时才可配置
	/*!
	 * LPSPI0 Initialization:						//对LPSPI1寄存器进行初始化
	 * ===================================================
	 */
	LPSPI0->CR    = 0x00000000;   			/* Disable module for configuration  //对CR寄存器全0配置，取消LSPI1的使能，以便配置		*/
	LPSPI0->IER   = 0x00000000;   			/* Interrupts not used 		//禁止使用中断				*/
	LPSPI0->DER   = 0x00000000;   			/* DMA not used 			//禁止使用DMA					*/
	LPSPI0->CFGR0 = 0x00000000;   			/* Defaults: 				//默认CFGR0配置					*/
											/* RDM0=0: rec'd data to FIFO as normal //将接收到的数据存入FIFO中		*/
											/* CIRFIFO=0; Circular FIFO is disabled //禁止FIFO回环功能		*/
											/* HRSEL, HRPOL, HREN=0: Host request disabled  //禁止Host Request*/

	LPSPI0->CFGR1 = LPSPI_CFGR1_MASTER_MASK;  /* Configurations: master mode		//需在LPSPI 未使能时配置						*/
												/* PCSCFG=0: PCS[3:2] are enabled 	//配置为主机模式，其余默认配置							*/
												/* OUTCFG=0: Output data retains last value when CS negated	*/
												/* PINCFG=0: SIN is input, SOUT is output 						*/
												/* MATCFG=0: Match disabled 									*/
												/* PCSPOL=0: PCS is active low 								*/
												/* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full 			*/
												/* AUTOPCS=0: does not apply for master mode 					*/
												/* SAMPLE=0: input data sampled on SCK edge 					*/
												/* MASTER=1: Master mode 										*/

	LPSPI0->TCR   = LPSPI_TCR_CPHA_MASK		//配置发送寄存器,Transmit command register
					  |LPSPI_TCR_PRESCALE(2)	//设置PRESCALE为010,4分频
					  |LPSPI_TCR_PCS(0)			//?此项需要配置为与硬件一致的PCSn,此项目配置LPSPI0_PCS0(PTA26)
					  |LPSPI_TCR_FRAMESZ(15);   ///数据长度16位 Transmit cmd: PCS0, 16 bits, prescale func'l clk by 4, etc	*/
												/* CPOL=0: 时钟空闲状态为低电平							*/
												/* CPHA=1: 时钟下降沿有效	*/
												/* PRESCALE=2: Functional clock divided by 2**2 = 4 			*/
												/* PCS=1: Transfer using PCS1 									*/
												/* LSBF=0: Data is transfered MSB first 						*/
												/* BYSW=0: Byte swap disabled 									*/
												/* CONT, CONTC=0: Continuous transfer disabled 				*/
												/* RXMSK=0: Normal transfer: rx data stored in rx FIFO 		*/
												/* TXMSK=0: Normal transfer: data loaded from tx FIFO 			*/
												/* WIDTH=0: Single bit transfer 								*/
												/* FRAMESZ=15: # bits in frame = 15+1=16 						*/
	//CCR寄存器只在配置为主机模式时才使用，必须在LPSPI未使能时配置
	LPSPI0->CCR   = LPSPI_CCR_SCKPCS(4)		//配置最后一个SCK到PCS的延时为5个周期
					  |LPSPI_CCR_PCSSCK(4)		//配置PCS assertion到第一个SCK边沿的延迟时间为5个周期
					  |LPSPI_CCR_DBT(8)			//Delay between Transfers = 8+2 = 10
					  |LPSPI_CCR_SCKDIV(8);   	/* Clock dividers based on prescaled func'l clk of 100 nsec 	*/
												/* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec) 			*/
												/* PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) 				*/
												/* DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) 			*/
												/* SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) 	*/

	LPSPI0->FCR   = LPSPI_FCR_TXWATER(3);   	/* RXWATER=0: Rx flags set when Rx FIFO >0 //RX FIFO大于0时RX标志位将会置位	*/
											/* TXWATER=3: Tx flags set when Tx FIFO <= 3 	//TX FIFO小于3时Tx标志位将会置位*/

	LPSPI0->CR    = LPSPI_CR_MEN_MASK			//使能LPSPI0外设
					  |LPSPI_CR_DBGEN_MASK;   	/* Enable module for operation 			*/
												/* DBGEN=1: module enabled in debug mode 	*/
												/* DOZEN=0: module enabled in Doze mode 	*/
												/* RST=0: Master logic not reset 			*/
												/* MEN=1: Module is enabled 				*/

}

void LPSPI1_transmit_8bits (uint8_t send)
{
  while((LPSPI1->SR & LPSPI_SR_TDF_MASK)>>LPSPI_SR_TDF_SHIFT==0);
                                   /* Wait for Tx FIFO available 	*/
  LPSPI1->TDR = send;              /* Transmit data 				*/
  LPSPI1->SR |= LPSPI_SR_TDF_MASK; /* Clear TDF flag 				*/
}

uint8_t LPSPI1_receive_8bits (void)
{
  uint8_t recieve = 0;

  while((LPSPI1->SR & LPSPI_SR_RDF_MASK)>>LPSPI_SR_RDF_SHIFT==0);
                                   /* Wait at least one RxFIFO entry 	*/
  recieve= LPSPI1->RDR;            /* Read received data 				*/
  LPSPI1->SR |= LPSPI_SR_RDF_MASK; /* Clear RDF flag 					*/
  return recieve;                  /* Return received data 			*/
}

void LPSPI0_transmit_32bits (uint32_t send)
{
  while((LPSPI0->SR & LPSPI_SR_TDF_MASK)>>LPSPI_SR_TDF_SHIFT==0);
                                   /* Wait for Tx FIFO available 	*/
  LPSPI0->TDR = send;              /* Transmit data 				*/
  LPSPI0->SR |= LPSPI_SR_TDF_MASK; /* Clear TDF flag 				*/
}

uint32_t LPSPI0_receive_32bits (void)
{
  uint32_t recieve = 0;

  while((LPSPI0->SR & LPSPI_SR_RDF_MASK)>>LPSPI_SR_RDF_SHIFT==0);
                                   /* Wait at least one RxFIFO entry 	*/
  recieve= LPSPI0->RDR;            /* Read received data 				*/
  LPSPI0->SR |= LPSPI_SR_RDF_MASK; /* Clear RDF flag 					*/
  return recieve;                  /* Return received data 			*/
}

