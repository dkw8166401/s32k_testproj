/*
 * bq79616.h
 *
 *  Created on: 2023年8月28日
 *      Author: fnadmin
 */

#ifndef BQ79616_H_
#define BQ79616_H_

#define BQ79616_ADR_dev1 	1
#define BQ79616_ADR_dev2 	2
#define BQ79616_ADR_dev3 	3

/************************寄存器宏定义************************/
//分A、B两种，使用前先确认用的是A样还是B样
/**@name    寄存器地址值
* @{
*/
#define S_DIR0_ADDR_OTP			0x00
#define S_DIR1_ADDR_OTP			0x01
#define S_DEV_CONF				0x02
#define S_ACTIVE_CELL			0x03
//新增和变化
#define S_OTP_SPARE15			0x04
#define S_BBVC_POSN1			0x05
#define S_BBVC_POSN2			0x06

#define S_ADC_CONF1				0x07
#define S_ADC_CONF2				0x08
#define S_OV_THRESH				0x09
#define S_UV_THRESH				0x0A
#define S_OTUT_THRESH			0x0B
#define S_UV_DISABLE1			0x0C
#define S_UV_DISABLE2			0x0D

#define S_GPIO_CONF1			0x0E
#define S_GPIO_CONF2			0x0F
#define S_GPIO_CONF3			0x10
#define S_GPIO_CONF4			0x11
#define S_OTP_SPARE14			0x12
#define S_OTP_SPARE13			0x13
#define S_OTP_SPARE12			0x14
#define S_OTP_SPARE11			0x15

#define S_FAULT_MSK1			0x16
#define S_FAULT_MSK2			0x17
#define S_PWR_TRANSIT_CONF		0x18
#define S_COMM_TIMEOUT_CONF		0x19
#define S_TX_HOLD_OFF			0x1A
#define S_MAIN_ADC_CAL1			0x1B
#define S_MAIN_ADC_CAL2			0x1C
#define S_AUX_ADC_CAL1			0x1D
#define S_AUX_ADC_CAL2			0x1E
#define S_OTP_RSVD1F			0x1F
#define S_OTP_RSVD20			0x20

#define S_CUST_MISC1			0x21
#define S_CUST_MISC2			0x22
#define S_CUST_MISC3			0x23
#define S_CUST_MISC4			0x24
#define S_CUST_MISC5			0x25
#define S_CUST_MISC6			0x26
#define S_CUST_MISC7			0x27
#define S_CUST_MISC8			0x28
#define S_STACK_RESPONSE		0x29
#define S_BBP_LOC				0x2A

#define S_OTP_RSVD2B			0x2B
#define S_OTP_SPARE10			0x2C
#define S_OTP_SPARE9			0x2D
#define S_OTP_SPARE8			0x2E
#define S_OTP_SPARE7			0x2F
#define S_OTP_SPARE6			0x30
#define S_OTP_SPARE5			0x31
#define S_OTP_SPARE4			0x32
#define S_OTP_SPARE3			0x33
#define S_OTP_SPARE2			0x34
#define S_OTP_SPARE1			0x35
#define S_CUST_CRC_HI			0x36
#define S_CUST_CRC_LO			0x37

#define S_OTP_PROG_UNLOCK1A		0x300
#define S_OTP_PROG_UNLOCK1B		0x301
#define S_OTP_PROG_UNLOCK1C		0x302
#define S_OTP_PROG_UNLOCK1D		0x303

#define S_DIR0_ADDR				0x306
#define S_DIR1_ADDR				0x307
#define S_COMM_CTRL				0x308
#define S_CONTROL1				0x309
#define S_CONTROL2				0x30A
#define S_OTP_PROG_CTRL			0x30B

#define S_ADC_CTRL1				0x30D
#define S_ADC_CTRL2				0x30E
#define S_ADC_CTRL3				0x30F

#define S_CB_CELL16_CTRL		0x318
#define S_CB_CELL15_CTRL		0x319
#define S_CB_CELL14_CTRL		0x31A
#define S_CB_CELL13_CTRL		0x31B
#define S_CB_CELL12_CTRL		0x31C
#define S_CB_CELL11_CTRL		0x31D
#define S_CB_CELL10_CTRL		0x31E
#define S_CB_CELL9_CTRL			0x31F
#define S_CB_CELL8_CTRL			0x320
#define S_CB_CELL7_CTRL			0x321
#define S_CB_CELL6_CTRL			0x322
#define S_CB_CELL5_CTRL			0x323
#define S_CB_CELL4_CTRL			0x324
#define S_CB_CELL3_CTRL			0x324
#define S_CB_CELL2_CTRL			0x326
#define S_CB_CELL1_CTRL			0x327

#define S_VMB_DONE_THRESH		0x328
#define S_MB_TIMER_CTRL			0x329
#define S_VCB_DONE_THRESH		0x32A
#define S_OTCB_THRESH			0x32B
#define S_OVUV_CTRL				0x32C
#define S_OTUT_CTRL				0x32D
#define S_BAL_CTRL1				0x32E
#define S_BAL_CTRL2				0x32F
#define S_BAL_CTRL3				0x330

#define S_FAULT_RST1			0x331
#define S_FAULT_RST2			0x332
#define S_DIAG_OTP_CTRL			0x335
#define S_DIAG_COMM_CTRL		0x336
#define S_DIAG_PWR_CTRL			0x337
#define S_DIAG_CBFET_CTRL1		0x338
#define S_DIAG_CBFET_CTRL2		0x339
#define S_DIAG_COMP_CTRL1		0x33A
#define S_DIAG_COMP_CTRL2		0x33B
#define S_DIAG_COMP_CTRL3		0x33C
#define S_DIAG_COMP_CTRL4		0x33D
#define S_DIAG_PROT_CTRL		0x33E

#define S_OTP_ECC_DATAIN1		0x343
#define S_OTP_ECC_DATAIN2		0x344
#define S_OTP_ECC_DATAIN3		0x345
#define S_OTP_ECC_DATAIN4		0x346
#define S_OTP_ECC_DATAIN5		0x347
#define S_OTP_ECC_DATAIN6		0x348
#define S_OTP_ECC_DATAIN7		0x349
#define S_OTP_ECC_DATAIN8		0x34A
#define S_OTP_ECC_DATAIN9		0x34B
#define S_OTP_ECC_TEST			0x34C
#define S_SPI_CONF				0x34D
#define S_SPI_TX3				0x34E
#define S_SPI_TX2				0x34F
#define S_SPI_TX1				0x350
//
#define S_SPI_EXE				0x351

#define S_OTP_PROG_UNLOCK2A		0x352
#define S_OTP_PROG_UNLOCK2B		0x353
#define S_OTP_PROG_UNLOCK2C		0x354
#define S_OTP_PROG_UNLOCK2D		0x355

#define S_DEBUG_CTRL_UNLOCK		0x700
#define S_DEBUG_COMM_CTRL1		0x701
#define S_DEBUG_COMM_CTRL2		0x702

#define S_PARTID				0x500
#define S_DIE_ID1				0x501
#define S_DIE_ID2				0x502
#define S_DIE_ID3				0x503
#define S_DIE_ID4				0x504
#define S_DIE_ID5				0x505
#define S_DIE_ID6				0x506
#define S_DIE_ID7				0x507
#define S_DIE_ID8				0x508
#define S_DIE_ID9				0x509

#define S_CUST_CRC_RSLT_HI		0x50C
#define S_CUST_CRC_RSLT_LO		0x50D
#define S_OTP_ECC_DATAOUT1		0x510
#define S_OTP_ECC_DATAOUT2		0x511
#define S_OTP_ECC_DATAOUT3		0x512
#define S_OTP_ECC_DATAOUT4		0x513
#define S_OTP_ECC_DATAOUT5		0x514
#define S_OTP_ECC_DATAOUT6		0x515
#define S_OTP_ECC_DATAOUT7		0x516
#define S_OTP_ECC_DATAOUT8		0x517
#define S_OTP_ECC_DATAOUT9		0x518

#define S_OTP_PROG_STAT			0x519
#define S_OTP_CUST1_STAT		0x51A
#define S_OTP_CUST2_STAT		0x51B

#define S_SPI_RX3				0x520
#define S_SPI_RX2				0x521
#define S_SPI_RX1				0x522
#define S_DIAG_STAT				0x526
#define S_ADC_STAT1				0x527
#define S_ADC_STAT2				0x528
#define S_GPIO_STAT				0x52A
#define S_BAL_STAT				0x52B
#define S_DEV_STAT				0x52C
#define S_FAULT_SUMMARY			0x52D
#define S_FAULT_COMM1			0x530
#define S_FAULT_COMM2			0x531
#define S_FAULT_COMM3			0x532

#define S_FAULT_OTP				0x535
#define S_FAULT_SYS				0x536
#define S_FAULT_PROT1			0x53A
#define S_FAULT_PROT2			0x53B
#define S_FAULT_OV1				0x53C
#define S_FAULT_OV2				0x53D
#define S_FAULT_UV1				0x53E
#define S_FAULT_UV2				0x53F

#define S_FAULT_OT				0x540
#define S_FAULT_UT				0x541
#define S_FAULT_COMP_GPIO		0x543
#define S_FAULT_COMP_VCCB1		0x545
#define S_FAULT_COMP_VCCB2		0x546
#define S_FAULT_COMP_VCOW1		0x548
#define S_FAULT_COMP_VCOW2		0x549
#define S_FAULT_COMP_CBOW1		0x54B
#define S_FAULT_COMP_CBOW2		0x54C
#define S_FAULT_COMP_CBFET1		0x54E
#define S_FAULT_COMP_CBFET2		0x54F

#define S_FAULT_COMP_MISC		0x550
#define S_FAULT_PWR1			0x552
#define S_FAULT_PWR2			0x553
#define S_FAULT_PWR3			0x554
#define S_CB_COMPLETE1			0x556
#define S_CB_COMPLETE2			0x557

#define S_VCELL16_HI			0x568
#define S_VCELL16_LO			0x569
#define S_VCELL15_HI			0x56A
#define S_VCELL15_LO			0x56B
#define S_VCELL14_HI			0x56C
#define S_VCELL14_LO			0x56D
#define S_VCELL13_HI			0x56E
#define S_VCELL13_LO			0x56F
#define S_VCELL12_HI			0x570
#define S_VCELL12_LO			0x571
#define S_VCELL11_HI			0x572
#define S_VCELL11_LO			0x573
#define S_VCELL10_HI			0x574
#define S_VCELL10_LO			0x575
#define S_VCELL9_HI				0x576
#define S_VCELL9_LO				0x577
#define S_VCELL8_HI				0x578
#define S_VCELL8_LO				0x579
#define S_VCELL7_HI				0x57A
#define S_VCELL7_LO				0x57B
#define S_VCELL6_HI				0x57C
#define S_VCELL6_LO				0x57D
#define S_VCELL5_HI				0x57E
#define S_VCELL5_LO				0x57F
#define S_VCELL4_HI				0x580
#define S_VCELL4_LO				0x581
#define S_VCELL3_HI				0x582
#define S_VCELL3_LO				0x583
#define S_VCELL2_HI				0x584
#define S_VCELL2_LO				0x585
#define S_VCELL1_HI				0x586
#define S_VCELL1_LO				0x587


#define S_BUSBAR_HI				0x588
#define S_BUSBAR_LO				0x589
#define S_TSREF_HI				0x58C
#define S_TSREF_LO				0x58D

#define S_GPIO1_HI				0x58E
#define S_GPIO1_LO				0x58F
#define S_GPIO2_HI				0x590
#define S_GPIO2_LO				0x591
#define S_GPIO3_HI				0x592
#define S_GPIO3_LO				0x593
#define S_GPIO4_HI				0x594
#define S_GPIO4_LO				0x595
#define S_GPIO5_HI				0x596
#define S_GPIO5_LO				0x597
#define S_GPIO6_HI				0x598
#define S_GPIO6_LO				0x599
#define S_GPIO7_HI				0x59A
#define S_GPIO7_LO				0x59B
#define S_GPIO8_HI				0x59C
#define S_GPIO8_LO				0x59D

#define S_DIETEMP1_HI			0x5AE
#define S_DIETEMP1_LO			0x5AF
#define S_DIETEMP2_HI			0x5B0
#define S_DIETEMP2_LO			0x5B1
#define S_AUX_CELL_HI			0x5B2
#define S_AUX_CELL_LO			0x5B3
#define S_AUX_GPIO_HI			0x5B4
#define S_AUX_GPIO_LO			0x5B5
#define S_AUX_BAT_HI			0x5B6
#define S_AUX_BAT_LO			0x5B7
#define S_AUX_REFL_HI			0x5B8
#define S_AUX_REFL_LO			0x5B9
#define S_AUX_VBG2_HI			0x5BA
#define S_AUX_VBG2_LO			0x5BB
#define S_AUX_VREF4P2_HI		0x5BC
#define S_AUX_VREF4P2_LO		0x5BD
#define S_AUX_AVAO_REF_HI		0x5BE
#define S_AUX_AVAO_REF_LO		0x5BF
#define S_AUX_AVDD_REF_HI		0x5C0
#define S_AUX_AVDD_REF_LO		0x5C1
#define S_AUX_OV_DACHI			0x5C2
#define S_AUX_OV_DAC_LO			0x5C3
#define S_AUX_UV_DAC_HI			0x5C4
#define S_AUX_UV_DAC_LO			0x5C5
#define S_AUX_OT_OTCB_DAC_HI	0x5C6
#define S_AUX_OT_OTCB_DAC_LO	0x5C7
#define S_AUX_UT_DAC_HI			0x5C8
#define S_AUX_UT_DAC_LO			0x5C9
#define S_AUX_VCBDONE_DAC_HI	0x5CA
#define S_AUX_VCBDONE_DAC_LO	0x5CB
#define S_AUX_VCM1_HI			0x5CC
#define S_AUX_VCM1_LO			0x5CD
#define S_VREF4P2_HI			0x5CE
#define S_VREF4P2_LO			0x5CF

#define S_RVEFH_HI				0x5D0
#define S_VREFH_LO				0x5D1
#define S_DIAG_MAIN_HI			0x5D2
#define S_DIAG_MAIN_LO			0x5D3
#define S_DIAG_AUX_HI			0x5D4
#define S_DIAG_AUX_LO			0x5D5

#define S_DEBUG_COMM_STAT		0x780
#define S_DEBUG_UART_RC			0x781
#define S_DEBUG_UARTR_RR		0x782
#define S_DEBUG_COMH_BIT		0x783
#define S_DEBUG_COMH_RC			0x784
#define S_DEBUG_COMH_RR_TR		0x785
#define S_DEBUG_COML_BIT		0x786
#define S_DEBUG_COML_RC			0x787
#define S_DEBUG_COML_RR_TR		0x788
#define S_DEBUG_UART_DISCARD	0x789
#define S_DEBUG_COMH_DISCARD	0x78A
#define S_DEBUG_COML_DISCARD	0x78B
#define S_DEBUG_UART_VALID_HI	0x78C
#define S_DEBUG_UART_VALID_LO	0x78D
#define S_DEBUG_COMH_VALID_HI	0x78E
#define S_DEBUG_COMH_VALID_LO	0x78F
#define S_DEBUG_COML_VALID_HI	0x790
#define S_DEBUG_COML_VALID_LO	0x791
#define S_DEBUG_OTP_SEC_BLK		0x7A0
#define S_DEBUG_OTP_DED_BLK		0x7A1
/**@} */

typedef struct _Bq_Register_Group
{

}_Bq79616_RegisterGroup;

#endif /* BQ79616_H_ */w
