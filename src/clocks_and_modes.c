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

#include "device_registers.h"	/* include peripheral declarations S32K144 */
#include "clocks_and_modes.h"

void SOSC_init_8MHz(void)		//��VLPRģʽ
{
	/*!
	 * SOSC Initialization (8 MHz):
	 * ===================================================
	 */
	SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1)|		//VLPRģʽ�£�clock divider���ܷ�Ƶ
				   SCG_SOSCDIV_SOSCDIV2(1);  	/* SOSCDIV1 & SOSCDIV2 =1: divide by 1  	  //(����OSCʱ�ӷ�Ƶ)		*/
	SCG->SOSCCFG  =	SCG_SOSCCFG_RANGE(2)|		/* Range=2: Medium freq (SOSC betw 1MHz-8MHz) //(����OSCƵ�ʷ�Χ)	*/
					SCG_SOSCCFG_EREFS_MASK;		/* HGO=0:   Config xtal osc for low power 	  //(����OSC����ģʽ)	*/
  	  	  	  	  	  	  	  	  	  	  	  	/* EREFS=1: Input is external XTAL 			  //(����OSC�ڲ�������Ϊ�ο�Դ)*/
												//�����޸�
  while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); 	/* Ensure SOSCCSR unlocked 	//ͨ����ѯSOSCCSR��LK(Lock Register)λ�ж�SOSCCSR�Ĵ����Ƿ��д��					*/
  SCG->SOSCCSR = SCG_SOSCCSR_SOSCEN_MASK; 		/* LK=0:          SOSCCSR can be written 	  //����SOSCCSRΪ0x1,Ĭ�����ã�enable OSC			*/
												/* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled 		*/
												/* SOSCCM=0:      OSC CLK monitor disabled 			*/
												/* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
												/* SOSCLPEN=0:    Sys OSC disabled in VLP modes 		*/
												/* SOSCSTEN=0:    Sys OSC disabled in Stop modes 		*/
												/* SOSCEN=1:      Enable oscillator 		 		*/

while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));	/* Wait for sys OSC clk valid //ͨ����SOSCVLD�Ĵ��������жϣ���ʹ��OSC��xtal�����ﵽ4096�κ�SOSCVLD�ᱻ��1��˵��OSC�ѳɹ������������ʱ����Ч*/
}

void SPLL_init_160MHz(void)
{
	/*!
	 * SPLL Initialization (160 MHz):
	 * ===================================================
	 */
  //while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); 	/* Ensure SPLLCSR unlocked 	//ͨ����ѯSPLLCSR��LKλ�ж�SPLLCSR�Ƿ��д��			*/
  //SCG->SPLLCSR &= ~SCG_SPLLCSR_SPLLEN_MASK;  	/* SPLLEN=0: SPLL is disabled (default) //ȡ��SPLLʹ�� 	*/

  SCG->SPLLDIV |= 	SCG_SPLLDIV_SPLLDIV1(2)|	/* SPLLDIV1 divide by 2 //�����SPLLDIV1Ϊ0010 */
					SCG_SPLLDIV_SPLLDIV2(3);  	/* SPLLDIV2 divide by 4 //�����SPLLDIV2Ϊ0011*/

  //SCG->SPLLCFG = SCG_SPLLCFG_MULT(24);			/* PREDIV=0: Divide SOSC_CLK by 0+1=1 	 //����Ԥ��Ƶ000(��Ԥ����Ϊ1)	*/
  	  	  	  	  	  	  	  	  	  	  		/* MULT=24:  Multiply sys pll by 24+16=40 //����Multiply Factor��������Ϊ40	*/
										  		/* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz 	*/

  //while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); 	/* Ensure SPLLCSR unlocked 	//�ٴ�ȷ��SPLLCSR�ѽ���					*/
  //SCG->SPLLCSR |= SCG_SPLLCSR_SPLLEN_MASK; 		/* LK=0:        SPLLCSR can be written 			*/
                             	 	 	 		/* SPLLCMRE=0:  SPLL CLK monitor IRQ if enabled 	*/
                             	 	 	 	 	/* SPLLCM=0:    SPLL CLK monitor disabled 			*/
                             	 	 	 	 	/* SPLLSTEN=0:  SPLL disabled in Stop modes 		*/
                             	 	 	 	 	/* SPLLEN=1:    Enable SPLL 	//ʹ��SPLL					*/

  //while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid    //ͨ��SPLLVLDλȷ��SPLL��ʹ�ܣ������ʱ����Ч*/

  /*!
  	 * SIRC Initialization (8 MHz):
  	 * ===================================================
  	 */
  while(SCG->SIRCCSR & SCG_SIRCCSR_LK_MASK); 	/* Ensure SIRCCSR unlocked 	//ͨ����ѯSIRCCSR��LKλ�ж�SIRCCSR�Ƿ��д��			*/
  SCG->SIRCCSR &= ~SCG_SIRCCSR_SIRCEN_MASK;  	/* SIRCEN=0: SIRC is disabled (default) //ȡ��SIRCʹ�� 	*/

  SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV1(1)		/*��SIRC�����ڲ��ο�ʱ��DIV1��DIV2����Ϊ1��Ƶ*/
			   | SCG_SIRCDIV_SIRCDIV2(1);		//����SIRC_CLKΪ8MHz

  SCG->SIRCCFG = SCG_SIRCCFG_RANGE(1);			/* Slow IRC high range clock (8 MHz )	*/

  while(SCG->SIRCCSR & SCG_SIRCCSR_LK_MASK); 	/* Ensure SIRCCSR unlocked 	//�ٴ�ȷ��SIRCCSR�ѽ���					*/
  SCG->SIRCCSR |= SCG_SIRCCSR_SIRCEN_MASK; 		/* LK=0:        SIRCCSR can be written 			    */
                               	 	 	 		/* SIRCLPEN=0:  Slow IRC is disabled in VLP modes 	*/
                               	 	 	 	 	/* SIRCSTEN=0:  Slow IRC is disabled in supported Stop modes			*/
                               	 	 	 	 	/* SIRCEN=1:    Enable SIRC 						*/
  while(!(SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK)); /* Wait for SIRC valid    //ͨ��SIRCVLDλȷ��SIRC��ʹ�ܣ������ʱ����Ч*/
}

void NormalRUNmode_80MHz (void)			//ȡ��SPLL��ʱ��Դѡ��ѡ��SIRC��Ϊʱ��Դ��������VCCR��CORE_CLK����Ϊ4MHz
{
/*!
 *  Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL:
 *  ====================================================
 *///SCG_RCCR�Ĵ���Ϊ�ں��ṩnormal RUNģʽ�µ�ϵͳʱ�ӿ��ƺ�ϵͳʱ�ӷ�Ƶ����
  //SCG->RCCR=SCG_RCCR_SCS(6)      /* Select PLL as clock source 	//ѡ��SPLL��ΪRUNģʽ�µ�ϵͳʱ��Դ							*/
  //  |SCG_RCCR_DIVCORE(0b01)      /* DIVCORE=1, div. by 2: Core clock = 160/2 MHz = 80 MHz 	//����DIVCOREλ����Ϊ2��Ƶ�����ں�ʱ��Ƶ��ΪSPLL_CLK/2 = 80MHz*/
  //  |SCG_RCCR_DIVBUS(0b01)       /* DIVBUS=1, div. by 2: bus clock = 40 MHz  //��DIVBUSλ����Ϊ2��Ƶ��������ʱ��Ƶ��ΪCORE_CLK/2 = 40MHz					*/
  //  |SCG_RCCR_DIVSLOW(0b10);     /* DIVSLOW=2, div. by 3: SCG slow, flash clock= 26 2/3 MHz //����DIVSLOWλ����Ϊ3��Ƶ����FLASHʱ��Ƶ��ΪCORE_CLK/2 = 26MHz	*/

  //while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}	/* Wait for sys clk src = SPLL //�ж�CSR�Ĵ����е�SCSλ�Ƿ�Ϊ0110,������6����֤��MCU�ѳɹ����õ�ʱ��ԴΪSPLLƵ��*/

	//SCG->RCCR=SCG_RCCR_SCS(2);

  /*!
   *  Change to very low power RUN mode with 8MHz SOSC, 8 MHz SIRC:
   *  ====================================================
   *///SCG_VCCR�Ĵ���Ϊ�ں��ṩvery low power RUNģʽ�µ�ϵͳʱ�ӿ��ƺ�ϵͳʱ�ӷ�Ƶ����
	SCG->VCCR=SCG_VCCR_SCS(2)      /* Select SIRC as clock source 	//ѡ��SIRC��ΪRUNģʽ�µ�ϵͳʱ��Դ							*/
	   |SCG_VCCR_DIVCORE(0b01)      /* DIVCORE=1, div. by 2: Core clock = 8/2 MHz = 4 MHz 	//����DIVCOREλ����Ϊ2��Ƶ�����ں�ʱ��Ƶ��Ϊʱ��Դ��һ�룺SIRC_CLK/2 = 4MHz*/
	   |SCG_VCCR_DIVBUS(0b00)       /* DIVBUS=0, div. by 1: bus clock = 4 MHz  //��DIVBUSλ����Ϊ1��Ƶ��������ʱ��Ƶ��ΪCORE_CLK/1 = 4MHz					*/
	   |SCG_VCCR_DIVSLOW(0b11);     /* DIVSLOW=3, div. by 4: SCG slow, flash clock= 4/4 MHz //����DIVSLOWλ����Ϊ4��Ƶ����FLASHʱ��Ƶ��ΪCORE_CLK/4 = 1MHz	*/


	while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 2) {}  /*Wait for sys clk src = SIRC //�ж�CSR�Ĵ����е�SCSλ�Ƿ�Ϊ0010,������2����֤��MCU�ѳɹ����õ�ʱ��ԴΪSIRCƵ��*/
}

