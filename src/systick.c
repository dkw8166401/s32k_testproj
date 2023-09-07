/*
 * systick.c
 *
 *  Created on: 2023年8月25日
 *      Author: fnadmin
 */


#include "device_registers.h"	  /* include peripheral declaration*/

static uint32_t fac_us;
void s32_systick_init(void)
{
	S32_SysTick->CSR = S32_SysTick_CSR_ENABLE(0);
	fac_us = 80000000 / 1000000;
	S32_SysTick->RVR = 0xFFFFFFul; //重装载寄存器
	S32_SysTick->CVR = 0ul; //当前计数
	S32_SysTick->CSR = 0u; //控制寄存器
	//S32_SysTick_CSR_TICKINT此位设为1一定要建立中断服务函数
	S32_SysTick->CSR |= S32_SysTick_CSR_TICKINT(1u)|S32_SysTick_CSR_ENABLE(1)|S32_SysTick_CSR_CLKSOURCE(1u);
}

void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=S32_SysTick->RVR;				//LOAD的值
	ticks=nus*fac_us; 						//需要的节拍数
	told= S32_SysTick->CVR ;      				//刚进入时的计数器值
	while(1)
	{
		tnow= S32_SysTick->CVR ;
		if(tnow!=told)
		{
			if(tnow<told)tcnt+=told-tnow;	//这里注意一下SYSTICK是一个递减的计数器就可以了.
			else tcnt+=reload-tnow+told;
			told=tnow;
			if(tcnt>=ticks)break;			//时间超过/等于要延迟的时间,则退出.
		}
	};
}
void delay_ms(uint32_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}
