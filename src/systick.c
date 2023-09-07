/*
 * systick.c
 *
 *  Created on: 2023��8��25��
 *      Author: fnadmin
 */


#include "device_registers.h"	  /* include peripheral declaration*/

static uint32_t fac_us;
void s32_systick_init(void)
{
	S32_SysTick->CSR = S32_SysTick_CSR_ENABLE(0);
	fac_us = 80000000 / 1000000;
	S32_SysTick->RVR = 0xFFFFFFul; //��װ�ؼĴ���
	S32_SysTick->CVR = 0ul; //��ǰ����
	S32_SysTick->CSR = 0u; //���ƼĴ���
	//S32_SysTick_CSR_TICKINT��λ��Ϊ1һ��Ҫ�����жϷ�����
	S32_SysTick->CSR |= S32_SysTick_CSR_TICKINT(1u)|S32_SysTick_CSR_ENABLE(1)|S32_SysTick_CSR_CLKSOURCE(1u);
}

void delay_us(uint32_t nus)
{
	uint32_t ticks;
	uint32_t told,tnow,tcnt=0;
	uint32_t reload=S32_SysTick->RVR;				//LOAD��ֵ
	ticks=nus*fac_us; 						//��Ҫ�Ľ�����
	told= S32_SysTick->CVR ;      				//�ս���ʱ�ļ�����ֵ
	while(1)
	{
		tnow= S32_SysTick->CVR ;
		if(tnow!=told)
		{
			if(tnow<told)tcnt+=told-tnow;	//����ע��һ��SYSTICK��һ���ݼ��ļ������Ϳ�����.
			else tcnt+=reload-tnow+told;
			told=tnow;
			if(tcnt>=ticks)break;			//ʱ�䳬��/����Ҫ�ӳٵ�ʱ��,���˳�.
		}
	};
}
void delay_ms(uint32_t nms)
{
	uint32_t i;
	for(i=0;i<nms;i++) delay_us(1000);
}
