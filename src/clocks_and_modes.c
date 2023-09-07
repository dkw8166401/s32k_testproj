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

void SOSC_init_8MHz(void)		//改VLPR模式
{
	/*!
	 * SOSC Initialization (8 MHz):
	 * ===================================================
	 */
	SCG->SOSCDIV = SCG_SOSCDIV_SOSCDIV1(1)|		//VLPR模式下，clock divider不能分频
				   SCG_SOSCDIV_SOSCDIV2(1);  	/* SOSCDIV1 & SOSCDIV2 =1: divide by 1  	  //(设置OSC时钟分频)		*/
	SCG->SOSCCFG  =	SCG_SOSCCFG_RANGE(2)|		/* Range=2: Medium freq (SOSC betw 1MHz-8MHz) //(设置OSC频率范围)	*/
					SCG_SOSCCFG_EREFS_MASK;		/* HGO=0:   Config xtal osc for low power 	  //(配置OSC功率模式)	*/
  	  	  	  	  	  	  	  	  	  	  	  	/* EREFS=1: Input is external XTAL 			  //(设置OSC内部晶振作为参考源)*/
												//无需修改
  while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); 	/* Ensure SOSCCSR unlocked 	//通过查询SOSCCSR的LK(Lock Register)位判断SOSCCSR寄存室是否可写入					*/
  SCG->SOSCCSR = SCG_SOSCCSR_SOSCEN_MASK; 		/* LK=0:          SOSCCSR can be written 	  //配置SOSCCSR为0x1,默认设置，enable OSC			*/
												/* SOSCCMRE=0:    OSC CLK monitor IRQ if enabled 		*/
												/* SOSCCM=0:      OSC CLK monitor disabled 			*/
												/* SOSCERCLKEN=0: Sys OSC 3V ERCLK output clk disabled */
												/* SOSCLPEN=0:    Sys OSC disabled in VLP modes 		*/
												/* SOSCSTEN=0:    Sys OSC disabled in Stop modes 		*/
												/* SOSCEN=1:      Enable oscillator 		 		*/

while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK));	/* Wait for sys OSC clk valid //通过对SOSCVLD寄存器进行判断，当使能OSC后，xtal次数达到4096次后，SOSCVLD会被置1，说明OSC已成功开启，且输出时钟有效*/
}

void SPLL_init_160MHz(void)
{
	/*!
	 * SPLL Initialization (160 MHz):
	 * ===================================================
	 */
  //while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); 	/* Ensure SPLLCSR unlocked 	//通过查询SPLLCSR的LK位判断SPLLCSR是否可写入			*/
  //SCG->SPLLCSR &= ~SCG_SPLLCSR_SPLLEN_MASK;  	/* SPLLEN=0: SPLL is disabled (default) //取消SPLL使能 	*/

  SCG->SPLLDIV |= 	SCG_SPLLDIV_SPLLDIV1(2)|	/* SPLLDIV1 divide by 2 //运算后SPLLDIV1为0010 */
					SCG_SPLLDIV_SPLLDIV2(3);  	/* SPLLDIV2 divide by 4 //运算后SPLLDIV2为0011*/

  //SCG->SPLLCFG = SCG_SPLLCFG_MULT(24);			/* PREDIV=0: Divide SOSC_CLK by 0+1=1 	 //配置预分频000(即预分配为1)	*/
  	  	  	  	  	  	  	  	  	  	  		/* MULT=24:  Multiply sys pll by 24+16=40 //配置Multiply Factor乘数因子为40	*/
										  		/* SPLL_CLK = 8MHz / 1 * 40 / 2 = 160 MHz 	*/

  //while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); 	/* Ensure SPLLCSR unlocked 	//再次确认SPLLCSR已解锁					*/
  //SCG->SPLLCSR |= SCG_SPLLCSR_SPLLEN_MASK; 		/* LK=0:        SPLLCSR can be written 			*/
                             	 	 	 		/* SPLLCMRE=0:  SPLL CLK monitor IRQ if enabled 	*/
                             	 	 	 	 	/* SPLLCM=0:    SPLL CLK monitor disabled 			*/
                             	 	 	 	 	/* SPLLSTEN=0:  SPLL disabled in Stop modes 		*/
                             	 	 	 	 	/* SPLLEN=1:    Enable SPLL 	//使能SPLL					*/

  //while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid    //通过SPLLVLD位确认SPLL已使能，且输出时钟有效*/

  /*!
  	 * SIRC Initialization (8 MHz):
  	 * ===================================================
  	 */
  while(SCG->SIRCCSR & SCG_SIRCCSR_LK_MASK); 	/* Ensure SIRCCSR unlocked 	//通过查询SIRCCSR的LK位判断SIRCCSR是否可写入			*/
  SCG->SIRCCSR &= ~SCG_SIRCCSR_SIRCEN_MASK;  	/* SIRCEN=0: SIRC is disabled (default) //取消SIRC使能 	*/

  SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV1(1)		/*将SIRC慢速内部参考时钟DIV1和DIV2设置为1分频*/
			   | SCG_SIRCDIV_SIRCDIV2(1);		//配置SIRC_CLK为8MHz

  SCG->SIRCCFG = SCG_SIRCCFG_RANGE(1);			/* Slow IRC high range clock (8 MHz )	*/

  while(SCG->SIRCCSR & SCG_SIRCCSR_LK_MASK); 	/* Ensure SIRCCSR unlocked 	//再次确认SIRCCSR已解锁					*/
  SCG->SIRCCSR |= SCG_SIRCCSR_SIRCEN_MASK; 		/* LK=0:        SIRCCSR can be written 			    */
                               	 	 	 		/* SIRCLPEN=0:  Slow IRC is disabled in VLP modes 	*/
                               	 	 	 	 	/* SIRCSTEN=0:  Slow IRC is disabled in supported Stop modes			*/
                               	 	 	 	 	/* SIRCEN=1:    Enable SIRC 						*/
  while(!(SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK)); /* Wait for SIRC valid    //通过SIRCVLD位确认SIRC已使能，且输出时钟有效*/
}

void NormalRUNmode_80MHz (void)			//取消SPLL的时钟源选择，选择SIRC作为时钟源，并配置VCCR将CORE_CLK设置为4MHz
{
/*!
 *  Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL:
 *  ====================================================
 *///SCG_RCCR寄存器为内核提供normal RUN模式下的系统时钟控制和系统时钟分频控制
  //SCG->RCCR=SCG_RCCR_SCS(6)      /* Select PLL as clock source 	//选择SPLL作为RUN模式下的系统时钟源							*/
  //  |SCG_RCCR_DIVCORE(0b01)      /* DIVCORE=1, div. by 2: Core clock = 160/2 MHz = 80 MHz 	//设置DIVCORE位设置为2分频，即内核时钟频率为SPLL_CLK/2 = 80MHz*/
  //  |SCG_RCCR_DIVBUS(0b01)       /* DIVBUS=1, div. by 2: bus clock = 40 MHz  //将DIVBUS位设置为2分频，即总线时钟频率为CORE_CLK/2 = 40MHz					*/
  //  |SCG_RCCR_DIVSLOW(0b10);     /* DIVSLOW=2, div. by 3: SCG slow, flash clock= 26 2/3 MHz //设置DIVSLOW位设置为3分频，即FLASH时钟频率为CORE_CLK/2 = 26MHz	*/

  //while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}	/* Wait for sys clk src = SPLL //判断CSR寄存器中的SCS位是否为0110,若返回6，则证明MCU已成功配置的时钟源为SPLL频率*/

	//SCG->RCCR=SCG_RCCR_SCS(2);

  /*!
   *  Change to very low power RUN mode with 8MHz SOSC, 8 MHz SIRC:
   *  ====================================================
   *///SCG_VCCR寄存器为内核提供very low power RUN模式下的系统时钟控制和系统时钟分频控制
	SCG->VCCR=SCG_VCCR_SCS(2)      /* Select SIRC as clock source 	//选择SIRC作为RUN模式下的系统时钟源							*/
	   |SCG_VCCR_DIVCORE(0b01)      /* DIVCORE=1, div. by 2: Core clock = 8/2 MHz = 4 MHz 	//设置DIVCORE位设置为2分频，即内核时钟频率为时钟源的一半：SIRC_CLK/2 = 4MHz*/
	   |SCG_VCCR_DIVBUS(0b00)       /* DIVBUS=0, div. by 1: bus clock = 4 MHz  //将DIVBUS位设置为1分频，即总线时钟频率为CORE_CLK/1 = 4MHz					*/
	   |SCG_VCCR_DIVSLOW(0b11);     /* DIVSLOW=3, div. by 4: SCG slow, flash clock= 4/4 MHz //设置DIVSLOW位设置为4分频，即FLASH时钟频率为CORE_CLK/4 = 1MHz	*/


	while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 2) {}  /*Wait for sys clk src = SIRC //判断CSR寄存器中的SCS位是否为0010,若返回2，则证明MCU已成功配置的时钟源为SIRC频率*/
}

