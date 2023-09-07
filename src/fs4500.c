/*
 * fs4500.c
 *
 *  Created on: 2023年8月30日
 *      Author: fnadmin
 */
#include "device_registers.h"	  /* include peripheral declarations */
#include "fs4500.h"	  /* include peripheral declarations */
#include "fs4500_driver.h"	  /* include peripheral declarations */

#include "LPSPI.h"	  /* include peripheral declarations */

void FS65_Init(void)
{
	FS65_SendCmdR(DEVICE_ID_ADR);

}

void FS65_SendCmdR_test(uint32_t REG_address)
{
	LPSPI0_transmit_32bits(REG_address << 9);
}

void FS65_SendCmdW_test(uint32_t REG_address)
{
	LPSPI0_transmit_32bits(REG_address);
}

uint32_t FS65_ReadCmdR_test()
{
	uint32_t buffer = 0;
	buffer = LPSPI0_receive_32bits();
	return buffer;
}

void fs4500_config()
{
	// 0. Get silicon version
		  while(fsdev_id != 3986)
		  {
			  FS65_SendCmdR_test(DEVICE_ID_ADR);
			  fsdev_id = FS65_ReadCmdR_test(0x00);
		  }

		  while(bist != 3849)
		  {
		  // 1.Check LBIST & ABIST1 completion
		  FS65_SendCmdR_test(BIST_ADR);
		  bist = FS65_ReadCmdR_test(0x00);
		  }

		  while(VREG_userread != 3908&&VREG_userread!=3840)
		  {
		  // 2. Get cause of SBC restart
		  FS65_SendCmdR_test(INIT_VREG_ADR);
		  VREG_userread = FS65_ReadCmdR_test(0x00);
		  }

		  while(VREG_userread == 3908&&Vreg_userinit!=3840)//偶尔会SPI通信出错,调试时配置为3840后，会保持一段时间，此期间重新上下电无法对寄存器复位？
		  {

		  // 3. Power-On Reset, Init Main registers should be initialized
	      //  Bit 8 must be set to 0 if the number of 1 is odd
		  //  Bit 8 must be set to 1 if the number of 1 is even
		  FS65_SendCmdW_test(((0x0041<<9)|0x0100)|0x00); //INIT_VREG修改
		  Vreg_userinit = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_VREG_ADR);  //测试用，写完后再读看看
		  Vreg_userinit = FS65_ReadCmdR_test(0x00);
		  }

		  while(WU1_init!= 3904)//初始为3904
		  {
		  //将WAKE UP 配置在IO0  Wake-up on rising edge - or high level
		  //FS65_SendCmdW_test(((0x0042<<9)|0x0000)|0x40); //INIT_WU1修改
		  //WU1_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_WU1_ADR);	  //测试用，写完后再读看看
		  WU1_init = FS65_ReadCmdR_test(0x00);
		  }

		  while(WU2_init!=3840)//初始为3840
		  {
		  //FS65_SendCmdW_test(((0x0043<<9)|0x0000)|0x00); //INIT_WU2修改
		  //WU2_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_WU2_ADR);   //测试用，写完后再读看看
		  WU2_init = FS65_ReadCmdR_test(0x00);
		  }

		  while(INH_INIT!=3840)//初始为3846
		  {
		  FS65_SendCmdW_test(((0x0045<<9)|0x0000)|0x00);    //INH_INIT修改
		  INH_INIT = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_INH_INT_ADR);  //测试用，写完后再读看看
		  INH_INIT = FS65_ReadCmdR_test(0x00);
		  }

		  //4. Exit INIT_MAIN mode
		  while(INT_init!=3840)//初始为3840?
		  {
		  //FS65_SendCmdW_test(((0x0044<<9)|0x0100)|0x00);    //INT_INIT修改
		  //INT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_INT_ADR);  //测试用，写完后再读看看
		  INT_init = FS65_ReadCmdR_test(0x00);
		  }

		  while(WUSOURCE_init!=3840)
		  {
		  FS65_SendCmdR_test(WU_SOURCE_ADR);  //Read and clear WU sources
		  WUSOURCE_init = FS65_ReadCmdR_test(0x00);
		  }

		  //5. Init FSSM registers
		  while(F1SB_init!= 3846)
		  {
		  //FS65_SendCmdW_test(((0x0061<<9)|0x0000)|0x60);    //F1SB_TIMING_INIT修改
		  //F1SB_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_FS1B_TIMING_ADR);  //测试用，写完后再读看看
		  F1SB_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(SUPERVISOR_init!=3840)//写入貌似未成功
		  {
		  //FS65_SendCmdW_test(((0x0063<<9)|0x0100)|0x00);    //SUPERVISOR_INIT修改
		  //SUPERVISOR_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_SUPERVISOR_ADR);  //测试用，写完后再读看看
		  SUPERVISOR_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(FAULT_init!=3841)//写入貌似未成功
		  {
		  //FS65_SendCmdW_test(((0x0064<<9)|0x0100)|0x10);    //FAULT_INIT修改
		  //FAULT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_FAULT_ADR);  //测试用，写完后再读看看
		  FAULT_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(FSSM_init!=3844)//初始为3844,硬件中把IO2和IO3设置为了safty input//写入貌似未成功
		  {
			   // 0x4D,	//	INIT_FSSM: IO_23 is fail-safe
			   // 0x00,	//	INIT_FSSM: IO_23 not fail-safe
		  //FS65_SendCmdW_test(((0x0065<<9)|0x0100)|0x4D);   //FSSM_INIT修改
		  //FSSM_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_FSSM_ADR);  //测试用，写完后再读看看
		  FSSM_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(SFIMPACT_init!=3841)
		  {
		  //FS65_SendCmdW_test(((0x0066<<9)|0x0000)|0x10);    //SF_IMPACT__INIT修改
		  //SFIMPACT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_SF_IMPACT_ADR);  //测试用，写完后再读看看
		  SFIMPACT_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(WDWINDOW_init!=3843)//3843->3844写入不成功，暂时使用默认配置
		  {
		  //FS65_SendCmdW_test(((0x0067<<9)|0x0100)|0x40);    //WD_WINDOW修改
			  //FS65_SendCmdW_test(((0x0067<<9)|0x0000)|0x00);
		  //WDWINDOW_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(WD_WINDOW_ADR);  //测试用，写完后再读看看
		  WDWINDOW_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(WDLFSR_init!=4018)//4018->3904写入不成功
		  {
		  //FS65_SendCmdW_test(((0x0068<<9)|0x0000)|0xB2);    //WD_LFSR修改
		  //WDLFSR_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(WD_LFSR_ADR);  //测试用，写完后再读看看
		  WDLFSR_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(WDCNT_init!=3840)//写入后读取到的为wdlfsr的寄存器值，为什么错开了？与写入未成功有关吗？
		  {
		  //FS65_SendCmdW_test(((0x006C<<9)|0x0100)|0x00);    //WD_CNT修改
		  //WDCNT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_WD_CNT_ADR);  //测试用，写完后再读看看
		  WDCNT_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(VCORE_OVUV_IMPACT_init!=3854)//3854  写入貌似未成功
		  {
		  //FS65_SendCmdW_test(((0x0071<<9)|0x0000)|0xE0);    //INIT_VCORE_OVUV_IMPACT修改
		  //VCORE_OVUV_IMPACT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_VCORE_OVUV_IMPACT_ADR);  //测试用，写完后再读看看
		  VCORE_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  delay_us(3);
		  }

		  while(VCCA_OVUV_IMPACT_init!=3854)//3854  写入貌似未成功
		  {
		  //FS65_SendCmdW_test(((0x0072<<9)|0x0000)|0xE0);    //INIT_VCCA_OVUV_IMPACT修改
		  //VCCA_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  FS65_SendCmdR_test(INIT_VCCA_OVUV_IMPACT_ADR);  //测试用，写完后再读看看
		  VCCA_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  delay_us(3);
		  }

		  while(VAUX_OVUV_IMPACT_init!=3854)//3854  写入貌似未成功
		  {
		  //FS65_SendCmdW_test(((0x73<<9)|0x0000)|0xF0);    //INIT_VAUX_OVUV_IMPACT修改
		  //VAUX_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  FS65_SendCmdR_test(INIT_VAUX_OVUV_IMPACT_ADR);  //测试用，写完后再读看看
		  VAUX_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  delay_us(3);
		  }

		  //5bis; Get current mode of operation
		 FS65_SendCmdR_test(MODE_ADR);
		 MODE_status = FS65_ReadCmdR_test();

		  // 5ter; Check HW configuration of Vaux/Vcca
		 FS65_SendCmdR_test(HW_CONFIG_ADR);
		 HWCONFG_init = FS65_ReadCmdR_test();

		 // 6. Read all Diag registers to clear all bits
		 FS65_SendCmdR_test(DIAG_VPRE_ADR);
		 DIAGVPRE_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_VCORE_ADR);
		 DIAGVCORE_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_VCCA_ADR);
		 DIAGVCCA_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_VAUX_ADR);
		 DIAGVAUX_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_VSUP_VCAN_ADR);
		 DIAGVSUPVCAN_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_CAN_FD_ADR);
		 DIAGCANFD_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_CAN_LIN_ADR);
		 DIAGCANLIN_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_SPI_ADR);
		 DIAGSPI_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_SF_IOS_ADR);
		 DIAGSFIOS_init = FS65_ReadCmdR_test();

		 FS65_SendCmdR_test(DIAG_SF_ERR_ADR);
		 DIAGSFERR_init = FS65_ReadCmdR_test();

		 // 7. Check if FS1b implemented
		 FS65_SendCmdR_test(DEVICE_ID_FS_ADR);
		 DEVICEIDFS_init = FS65_ReadCmdR_test();

		 if((DEVICEIDFS_init & 0x01)==1 )
		 {//FS1B is implemented, it should be zero at this stage
			 FS65_SendCmdR_test(RELEASE_FSxB_ADR);
			 FSxB_init = FS65_ReadCmdR_test();
			 if((FSxB_init>>2) & 0x01 == 1)
			 {
				 if(((DIAGSFIOS_init>>2)&0x03)>=2)
				 {
					 ;
				 }
				 else
				 {

					 FS65_SendCmdR_test(RELEASE_FSxB_ADR);
					 FSxB_init = FS65_ReadCmdR_test();

				 }
				 while ((DEVICEIDFS_init & 0x01)==1 );
			 }
		 }
		 //Run ABIST2_FS1B
		  FS65_SendCmdW_test((0x62<<9)|0x40);    //BIST修改
		  BIST_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(BIST_ADR);
		  BIST_init = FS65_ReadCmdR_test();
		  delay_us(200);

		  if ((BIST_init>>2)&0x01 != 1)
		  {
		  	   // Error during ABIST2, user action required
			  ;
		  }

		  // 8. BIST Vaux if necessary
		  /*	 FS65_SendCmdR_test(INIT_VAUX_OVUV_IMPACT_ADR);
			 INIT_VAUX_OVUV_IMPACT_init = FS65_ReadCmdR_test();
			 if((((INIT_VAUX_OVUV_IMPACT_init>>2)&0x03) != 0 )&&(INIT_VAUX_OVUV_IMPACT_init&0x03)!=0)
			 {
				 //Run ABIST2_VAUX
				  FS65_SendCmdW_test((0x62<<9)|0x20);    //BIST修改
				  FS65_SendCmdR_test(BIST_ADR);
				  BIST_init = FS65_ReadCmdR_test();
				  delay_us(200);
			 }
			 if ((BIST_init>>1)&0x01 != 1)
			 {
		    	;// Error during ABIST2 VAUX, user action required
			 }
		  */

		  //Configure non-init registers
		  FS65_SendCmdR_test(CAN_LIN_MODE_ADR);
		  canlin_mode = FS65_ReadCmdR_test();
}
