/*
 * fs4500.c
 *
 *  Created on: 2023��8��30��
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

		  while(VREG_userread == 3908&&Vreg_userinit!=3840)//ż����SPIͨ�ų���,����ʱ����Ϊ3840�󣬻ᱣ��һ��ʱ�䣬���ڼ��������µ��޷��ԼĴ�����λ��
		  {

		  // 3. Power-On Reset, Init Main registers should be initialized
	      //  Bit 8 must be set to 0 if the number of 1 is odd
		  //  Bit 8 must be set to 1 if the number of 1 is even
		  FS65_SendCmdW_test(((0x0041<<9)|0x0100)|0x00); //INIT_VREG�޸�
		  Vreg_userinit = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_VREG_ADR);  //�����ã�д����ٶ�����
		  Vreg_userinit = FS65_ReadCmdR_test(0x00);
		  }

		  while(WU1_init!= 3904)//��ʼΪ3904
		  {
		  //��WAKE UP ������IO0  Wake-up on rising edge - or high level
		  //FS65_SendCmdW_test(((0x0042<<9)|0x0000)|0x40); //INIT_WU1�޸�
		  //WU1_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_WU1_ADR);	  //�����ã�д����ٶ�����
		  WU1_init = FS65_ReadCmdR_test(0x00);
		  }

		  while(WU2_init!=3840)//��ʼΪ3840
		  {
		  //FS65_SendCmdW_test(((0x0043<<9)|0x0000)|0x00); //INIT_WU2�޸�
		  //WU2_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_WU2_ADR);   //�����ã�д����ٶ�����
		  WU2_init = FS65_ReadCmdR_test(0x00);
		  }

		  while(INH_INIT!=3840)//��ʼΪ3846
		  {
		  FS65_SendCmdW_test(((0x0045<<9)|0x0000)|0x00);    //INH_INIT�޸�
		  INH_INIT = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_INH_INT_ADR);  //�����ã�д����ٶ�����
		  INH_INIT = FS65_ReadCmdR_test(0x00);
		  }

		  //4. Exit INIT_MAIN mode
		  while(INT_init!=3840)//��ʼΪ3840?
		  {
		  //FS65_SendCmdW_test(((0x0044<<9)|0x0100)|0x00);    //INT_INIT�޸�
		  //INT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_INT_ADR);  //�����ã�д����ٶ�����
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
		  //FS65_SendCmdW_test(((0x0061<<9)|0x0000)|0x60);    //F1SB_TIMING_INIT�޸�
		  //F1SB_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_FS1B_TIMING_ADR);  //�����ã�д����ٶ�����
		  F1SB_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(SUPERVISOR_init!=3840)//д��ò��δ�ɹ�
		  {
		  //FS65_SendCmdW_test(((0x0063<<9)|0x0100)|0x00);    //SUPERVISOR_INIT�޸�
		  //SUPERVISOR_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_SUPERVISOR_ADR);  //�����ã�д����ٶ�����
		  SUPERVISOR_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(FAULT_init!=3841)//д��ò��δ�ɹ�
		  {
		  //FS65_SendCmdW_test(((0x0064<<9)|0x0100)|0x10);    //FAULT_INIT�޸�
		  //FAULT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_FAULT_ADR);  //�����ã�д����ٶ�����
		  FAULT_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(FSSM_init!=3844)//��ʼΪ3844,Ӳ���а�IO2��IO3����Ϊ��safty input//д��ò��δ�ɹ�
		  {
			   // 0x4D,	//	INIT_FSSM: IO_23 is fail-safe
			   // 0x00,	//	INIT_FSSM: IO_23 not fail-safe
		  //FS65_SendCmdW_test(((0x0065<<9)|0x0100)|0x4D);   //FSSM_INIT�޸�
		  //FSSM_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_FSSM_ADR);  //�����ã�д����ٶ�����
		  FSSM_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(SFIMPACT_init!=3841)
		  {
		  //FS65_SendCmdW_test(((0x0066<<9)|0x0000)|0x10);    //SF_IMPACT__INIT�޸�
		  //SFIMPACT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_SF_IMPACT_ADR);  //�����ã�д����ٶ�����
		  SFIMPACT_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(WDWINDOW_init!=3843)//3843->3844д�벻�ɹ�����ʱʹ��Ĭ������
		  {
		  //FS65_SendCmdW_test(((0x0067<<9)|0x0100)|0x40);    //WD_WINDOW�޸�
			  //FS65_SendCmdW_test(((0x0067<<9)|0x0000)|0x00);
		  //WDWINDOW_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(WD_WINDOW_ADR);  //�����ã�д����ٶ�����
		  WDWINDOW_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(WDLFSR_init!=4018)//4018->3904д�벻�ɹ�
		  {
		  //FS65_SendCmdW_test(((0x0068<<9)|0x0000)|0xB2);    //WD_LFSR�޸�
		  //WDLFSR_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(WD_LFSR_ADR);  //�����ã�д����ٶ�����
		  WDLFSR_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(WDCNT_init!=3840)//д����ȡ����Ϊwdlfsr�ļĴ���ֵ��Ϊʲô���ˣ���д��δ�ɹ��й���
		  {
		  //FS65_SendCmdW_test(((0x006C<<9)|0x0100)|0x00);    //WD_CNT�޸�
		  //WDCNT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_WD_CNT_ADR);  //�����ã�д����ٶ�����
		  WDCNT_init = FS65_ReadCmdR_test(0x00);
		  delay_us(3);
		  }

		  while(VCORE_OVUV_IMPACT_init!=3854)//3854  д��ò��δ�ɹ�
		  {
		  //FS65_SendCmdW_test(((0x0071<<9)|0x0000)|0xE0);    //INIT_VCORE_OVUV_IMPACT�޸�
		  //VCORE_OVUV_IMPACT_init = FS65_ReadCmdR_test(0x00);
		  FS65_SendCmdR_test(INIT_VCORE_OVUV_IMPACT_ADR);  //�����ã�д����ٶ�����
		  VCORE_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  delay_us(3);
		  }

		  while(VCCA_OVUV_IMPACT_init!=3854)//3854  д��ò��δ�ɹ�
		  {
		  //FS65_SendCmdW_test(((0x0072<<9)|0x0000)|0xE0);    //INIT_VCCA_OVUV_IMPACT�޸�
		  //VCCA_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  FS65_SendCmdR_test(INIT_VCCA_OVUV_IMPACT_ADR);  //�����ã�д����ٶ�����
		  VCCA_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  delay_us(3);
		  }

		  while(VAUX_OVUV_IMPACT_init!=3854)//3854  д��ò��δ�ɹ�
		  {
		  //FS65_SendCmdW_test(((0x73<<9)|0x0000)|0xF0);    //INIT_VAUX_OVUV_IMPACT�޸�
		  //VAUX_OVUV_IMPACT_init = FS65_ReadCmdR_test();
		  FS65_SendCmdR_test(INIT_VAUX_OVUV_IMPACT_ADR);  //�����ã�д����ٶ�����
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
		  FS65_SendCmdW_test((0x62<<9)|0x40);    //BIST�޸�
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
				  FS65_SendCmdW_test((0x62<<9)|0x20);    //BIST�޸�
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
