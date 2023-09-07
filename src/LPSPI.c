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
	PCC->PCCn[PCC_LPSPI1_INDEX] = 0;          		/* Disable clocks to modify PCS ( default) //��ʼ��LSPI1����Χʱ�ӿ�����ȫ0	*/
	PCC->PCCn[PCC_LPSPI1_INDEX] = PCC_PCCn_PR_MASK	/* (default) Peripheral is present.		//����LSPI1Ϊ����״̬	*/
								 |PCC_PCCn_CGC_MASK	/* Enable PCS=SIRC_DIV2 (4 MHz func'l clock) //����������ʱ��Դ����ʹ��	*/
								 |PCC_PCCn_PCS(2);	//��3λ����������ʱ��Դ��ѡ��,��������ѡ��ͬ��ʱ��Դ ����������������������(clock option 2---SIRCDIV2_CLK)����CGC=0ʱ�ſ�����
	/*!
	 * LPSPI1 Initialization:						//��LPSPI1�Ĵ������г�ʼ��
	 * ===================================================
	 */
  LPSPI1->CR    = 0x00000000;   			/* Disable module for configuration  //��CR�Ĵ���ȫ0���ã�ȡ��LSPI1��ʹ�ܣ��Ա�����		*/
  LPSPI1->IER   = 0x00000000;   			/* Interrupts not used 		//��ֹʹ���ж�				*/
  LPSPI1->DER   = 0x00000000;   			/* DMA not used 			//��ֹʹ��DMA					*/
  LPSPI1->CFGR0 = 0x00000000;   			/* Defaults: 				//Ĭ��CFGR0����					*/
                                			/* RDM0=0: rec'd data to FIFO as normal //�����յ������ݴ���FIFO��		*/
                                			/* CIRFIFO=0; Circular FIFO is disabled //��ֹFIFO�ػ�����		*/
                                			/* HRSEL, HRPOL, HREN=0: Host request disabled  //��ֹHost Request*/

  LPSPI1->CFGR1 = LPSPI_CFGR1_MASTER_MASK;  /* Configurations: master mode		//����LPSPI δʹ��ʱ����						*/
											/* PCSCFG=0: PCS[3:2] are enabled 	//����Ϊ����ģʽ������Ĭ������							*/
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
		  	  	 |LPSPI_TCR_PRESCALE(2)		//���÷��ͼĴ���,Transmit command register
				 |LPSPI_TCR_PCS(1)			//����PRESCALEΪ010,4��Ƶ
		         |LPSPI_TCR_FRAMESZ(7); 	//?������Ҫ����Ϊ��Ӳ��һ�µ�PCSn,����Ŀ����LPSPI1_PCS1(��79600������CS�źţ�PTA6)
				    ///���ݳ���8λ Transmit cmd: PCS1, 8 bits, prescale func'l clk by 4, etc	*/
											/* CPOL=0��ΪCPOL=0: SCK inactive state is lowʱ�ӿ���ʱΪ�͵�ƽ 							*/
											/* CPHA=0��Ϊcpha=0: ʱ�ӵڶ����仯����Ч	*/
											/* PRESCALE=2: Functional clock divided by 2**2 = 4 			*/
											/* PCS=1: Transfer using PCS1 									*/
											/* LSBF=0: Data is transfered MSB first 						*/
											/* BYSW=0: Byte swap disabled 									*/
											/* CONT, CONTC=0: Continuous transfer disabled 				*/
											/* RXMSK=0: Normal transfer: rx data stored in rx FIFO 		*/
											/* TXMSK=0: Normal transfer: data loaded from tx FIFO 			*/
											/* WIDTH=0: Single bit transfer 								*/
											/* FRAMESZ=15: # bits in frame = 15+1=16 						*/
  //CCR�Ĵ���ֻ������Ϊ����ģʽʱ��ʹ�ã�������LPSPIδʹ��ʱ����
  LPSPI1->CCR   = LPSPI_CCR_SCKPCS(4)		//�������һ��SCK��PCS����ʱΪ5������
				  |LPSPI_CCR_PCSSCK(4)		//����PCS assertion����һ��SCK���ص��ӳ�ʱ��Ϊ5������
				  |LPSPI_CCR_DBT(8)			//Delay between Transfers = 8+2 = 10
				  |LPSPI_CCR_SCKDIV(8);   	/* Clock dividers based on prescaled func'l clk of 100 nsec 	*/
											/* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec) 			*/
											/* PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) 				*/
											/* DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) 			*/
											/* SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) 	*/

  LPSPI1->FCR   = LPSPI_FCR_TXWATER(3);   	/* RXWATER=0: Rx flags set when Rx FIFO >0 //RX FIFO����0ʱRX��־λ������λ	*/
                                			/* TXWATER=3: Tx flags set when Tx FIFO <= 3 	//TX FIFOС��3ʱTx��־λ������λ*/

  LPSPI1->CR    = LPSPI_CR_MEN_MASK			//ʹ��LPSPI1����
		  	  	  |LPSPI_CR_DBGEN_MASK;   	/* Enable module for operation 			*/
											/* DBGEN=1: module enabled in debug mode 	*/
											/* DOZEN=0: module enabled in Doze mode 	*/
											/* RST=0: Master logic not reset 			*/
											/* MEN=1: Module is enabled 				*/

	/*!
	 * LPSPI0 Clocking:
	 * ===================================================
	 */
	PCC->PCCn[PCC_LPSPI0_INDEX] = 0;          		/* Disable clocks to modify PCS ( default) //��ʼ��LSPI1����Χʱ�ӿ�����ȫ0	*/
	PCC->PCCn[PCC_LPSPI0_INDEX] = PCC_PCCn_PR_MASK	/* (default) Peripheral is present.		//����LSPI1Ϊ����״̬	*/
								 |PCC_PCCn_CGC_MASK	/* Enable PCS=SIRC_DIV2 (4 MHz func'l clock) //����������ʱ��Դ����ʹ��	*/
								 |PCC_PCCn_PCS(2);	//��3λ����������ʱ��Դ��ѡ��,��������ѡ��ͬ��ʱ��Դ ����������������������(clock option 2---SIRCDIV2_CLK)����CGC=0ʱ�ſ�����
	/*!
	 * LPSPI0 Initialization:						//��LPSPI1�Ĵ������г�ʼ��
	 * ===================================================
	 */
	LPSPI0->CR    = 0x00000000;   			/* Disable module for configuration  //��CR�Ĵ���ȫ0���ã�ȡ��LSPI1��ʹ�ܣ��Ա�����		*/
	LPSPI0->IER   = 0x00000000;   			/* Interrupts not used 		//��ֹʹ���ж�				*/
	LPSPI0->DER   = 0x00000000;   			/* DMA not used 			//��ֹʹ��DMA					*/
	LPSPI0->CFGR0 = 0x00000000;   			/* Defaults: 				//Ĭ��CFGR0����					*/
											/* RDM0=0: rec'd data to FIFO as normal //�����յ������ݴ���FIFO��		*/
											/* CIRFIFO=0; Circular FIFO is disabled //��ֹFIFO�ػ�����		*/
											/* HRSEL, HRPOL, HREN=0: Host request disabled  //��ֹHost Request*/

	LPSPI0->CFGR1 = LPSPI_CFGR1_MASTER_MASK;  /* Configurations: master mode		//����LPSPI δʹ��ʱ����						*/
												/* PCSCFG=0: PCS[3:2] are enabled 	//����Ϊ����ģʽ������Ĭ������							*/
												/* OUTCFG=0: Output data retains last value when CS negated	*/
												/* PINCFG=0: SIN is input, SOUT is output 						*/
												/* MATCFG=0: Match disabled 									*/
												/* PCSPOL=0: PCS is active low 								*/
												/* NOSTALL=0: Stall if Tx FIFO empty or Rx FIFO full 			*/
												/* AUTOPCS=0: does not apply for master mode 					*/
												/* SAMPLE=0: input data sampled on SCK edge 					*/
												/* MASTER=1: Master mode 										*/

	LPSPI0->TCR   = LPSPI_TCR_CPHA_MASK		//���÷��ͼĴ���,Transmit command register
					  |LPSPI_TCR_PRESCALE(2)	//����PRESCALEΪ010,4��Ƶ
					  |LPSPI_TCR_PCS(0)			//?������Ҫ����Ϊ��Ӳ��һ�µ�PCSn,����Ŀ����LPSPI0_PCS0(PTA26)
					  |LPSPI_TCR_FRAMESZ(15);   ///���ݳ���16λ Transmit cmd: PCS0, 16 bits, prescale func'l clk by 4, etc	*/
												/* CPOL=0: ʱ�ӿ���״̬Ϊ�͵�ƽ							*/
												/* CPHA=1: ʱ���½�����Ч	*/
												/* PRESCALE=2: Functional clock divided by 2**2 = 4 			*/
												/* PCS=1: Transfer using PCS1 									*/
												/* LSBF=0: Data is transfered MSB first 						*/
												/* BYSW=0: Byte swap disabled 									*/
												/* CONT, CONTC=0: Continuous transfer disabled 				*/
												/* RXMSK=0: Normal transfer: rx data stored in rx FIFO 		*/
												/* TXMSK=0: Normal transfer: data loaded from tx FIFO 			*/
												/* WIDTH=0: Single bit transfer 								*/
												/* FRAMESZ=15: # bits in frame = 15+1=16 						*/
	//CCR�Ĵ���ֻ������Ϊ����ģʽʱ��ʹ�ã�������LPSPIδʹ��ʱ����
	LPSPI0->CCR   = LPSPI_CCR_SCKPCS(4)		//�������һ��SCK��PCS����ʱΪ5������
					  |LPSPI_CCR_PCSSCK(4)		//����PCS assertion����һ��SCK���ص��ӳ�ʱ��Ϊ5������
					  |LPSPI_CCR_DBT(8)			//Delay between Transfers = 8+2 = 10
					  |LPSPI_CCR_SCKDIV(8);   	/* Clock dividers based on prescaled func'l clk of 100 nsec 	*/
												/* SCKPCS=4: SCK to PCS delay = 4+1 = 5 (500 nsec) 			*/
												/* PCSSCK=4: PCS to SCK delay = 9+1 = 10 (1 usec) 				*/
												/* DBT=8: Delay between Transfers = 8+2 = 10 (1 usec) 			*/
												/* SCKDIV=8: SCK divider =8+2 = 10 (1 usec: 1 MHz baud rate) 	*/

	LPSPI0->FCR   = LPSPI_FCR_TXWATER(3);   	/* RXWATER=0: Rx flags set when Rx FIFO >0 //RX FIFO����0ʱRX��־λ������λ	*/
											/* TXWATER=3: Tx flags set when Tx FIFO <= 3 	//TX FIFOС��3ʱTx��־λ������λ*/

	LPSPI0->CR    = LPSPI_CR_MEN_MASK			//ʹ��LPSPI0����
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

