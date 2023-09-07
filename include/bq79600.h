/*
 * bq79600.h
 *
 *  Created on: 2023年8月25日
 *      Author: fnadmin
 */

#ifndef BQ79600_H_
#define BQ79600_H_

#define   BQ79600_RDY          (PTB->PDIR&(1<<13))

/**@name    BQ79600读写指令
* @{
*/
#define Single_Device_Read             0x80    ///<单设备读取
#define Stack_Read                     0xA0    ///<菊花链读取
#define Broadcast_Read                 0xC0    ///<广播读取

#define Single_Device_Write            0x90    ///<单设备写
#define Stack_Write                    0xB0    ///<堆写
#define Broadcast_Write                0xD0    ///<广播写
#define Broadcast_Write_Reverse        0xE0    ///<广播写，有返回
/**@} */


/**@name    寄存器地址宏定义
* @{
*/
#define Z_DIR0_ADDR             0x306
#define Z_DIR1_ADDR             0x307
#define Z_CONTROL1              0x309
#define Z_CONTROL2              0x30A
#define Z_DIAG_CTRL             0x2000
#define Z_DEV_CONF1             0x2001
#define Z_DEV_CONF2             0x2002
#define Z_TX_HOLD_OFF           0x2003
#define Z_SLP_TIMEOUT           0x2004
#define Z_COMM_TIMEOUT          0x2005
#define Z_SPI_FIFO_UNLOCK       0x2010
#define Z_FAULT_MSK             0x2020
#define Z_FAULT_RST             0x2030
#define Z_FAULT_SUMMARY         0x2100
#define Z_FAULT_REG             0x2101
#define Z_FAULT_SYS             0x2102
#define Z_FAULT_PWR             0x2103
#define Z_FAULT_COMM1           0x2104
#define Z_FAULT_COMM2           0x2105
#define Z_DEV_DIAG_STAT         0x2110
#define Z_PARTID                0x2120
#define Z_DIE_ID1               0x2121
#define Z_DIE_ID2               0x2122
#define Z_DIE_ID3               0x2123
#define Z_DIE_ID4               0x2124
#define Z_DIE_ID5               0x2125
#define Z_DIE_ID6               0x2126
#define Z_DIE_ID7               0x2127
#define Z_DIE_ID8               0x2128
#define Z_DIE_ID9               0x2129
#define Z_DEBUG_CTRL_UNLOCK     0x2200
#define Z_DEBUG_COMM_CTRL       0x2201
#define Z_DEBUG_COMM_STAT       0x2300
#define Z_DEBUG_SPI_PHY         0x2301
#define Z_DEBUG_SPI_FRAME       0x2302
#define Z_DEBUG_UART_FRAME      0x2303
#define Z_DEBUG_COMH_PHY        0x2304
#define Z_DEBUG_COMH_FRAME      0x2305
#define Z_DEBUG_COML_PHY        0x2306
#define Z_DEBUG_COML_FRAME      0x2307
/**@} */

/**@name    地址的宏定义值
	* @{
	*/
#define BQ79600_ADR 	0

void BQ79600_Comm_Clear(void);///<总线清除
uint8_t BQ79600_Single_Read(uint8_t DEV_adr, uint16_t REG_adr, uint8_t DATA, uint8_t *readbuf);
uint8_t BQ79600_Single_Wr(uint8_t datanum, uint8_t devadr, uint16_t regadr, uint8_t *DATA);

//寄存器声明
typedef struct _Bq79600_Register_Group
{
    union
    {
        struct
        {
            uint8_t ADDRESS  : 6; //Follow steps in section Device Addressing?to config this register. A
            uint8_t RSVD     : 2;
        } Bit;
        uint8_t Byte;
    } DIR0_ADDR;

    union
    {
        struct
        {
        	uint8_t ADDRESS  : 6; //Follow steps in section Device Addressing?to config this register. A
            uint8_t RSVD     : 2;
        } Bit;
        uint8_t Byte;
    } DIR1_ADDR;

    union
    {
        struct
        {
        	uint8_t ADDR_WR          : 1; //Enable device to start auto-addressing
        	uint8_t SOFT_RESET       : 1; //Reset the digital to OTP default
        	uint8_t GOTO_SLEEP       : 1; //Transition device to SLEEP mode.
        	uint8_t GOTO_SHUTDOWN    : 1; //Transition device to SHUTDOWN mode
        	uint8_t SEND_SLPTOACT    : 1; //Send SLEEPtoWAKE tone up the stack
        	uint8_t SEND_WAKE        : 1; //Send WAKE tone up the stack
        	uint8_t SEND_SHUTDOWN    : 1; //Sends SHUTDOWN tone to next device up the stack
        	uint8_t DIR_SEL          : 1; //Select daisy chain comm direction. Not self-clear bit.
        } Bit;
        uint8_t Byte;
    } CONTROL1;

    union
    {
        struct
        {
        	uint8_t SPARE            : 1;
        	uint8_t SEND_HW_RESET    : 1; //Send HW_RESET tone up the stack
        	uint8_t RSVD             : 6;
        } Bit;
        uint8_t Byte;
    } CONTROL2;

    union
    {
        struct
        {
        	uint8_t INH_SET_GO           : 1; //This bits intentionally activates INH PMOS pull up, sets [INH] and [INH_STAT] to 1
        	uint8_t FLIP_TR_CRC          : 1; //Sends a purposely incorrect communication CRC by inverting all of the calculated CRC bits
        	uint8_t FLIP_FACT_CRC        : 1; //An enable bit to flip the factory CRC expected value. This is for factory CRC diagnostic.
        	uint8_t SPI_FIFO_DIAG_GO     : 1; //nitiate SPI FIFO diagnostic
        	uint8_t PWR_DIAG_GO          : 1; //Indicates a power supply BIST diagnostic is initiated, self-clear bit.
            uint8_t CONF_MON_GO          : 1; //Resample 2 registers setting
            uint8_t RSVD                 : 2;
        } Bit;
        uint8_t Byte;
    } DIAG_CTRL;

    union
    {
        struct
        {
        	uint8_t HB_TX_EN             : 1; //Enable HEARTBEAT transmitter when device is in SLEEP mode
        	uint8_t SEL_TX_TONE          : 1; //Select daisy chain transmits bq79606 tones or non bq7606 tones
        	uint8_t NFAULT_EN            : 1; //Enables the NFAULT function
        	uint8_t TWO_STOP_EN          : 1; //Enables two stop bits for the UART in case of severe oscillator error in both the host and device
        	uint8_t FCOMM_EN             : 1; //Enable the fault state detection through communication in ACTIVE mode
        	uint8_t TONE_RX_EN           : 1; //Enable the Tone receiver, depends on [DIR_SEL],  in VALIDATE
        	uint8_t SNIFDET_DIS          : 1; //Enable the Sniff detector on COM* port, this bit is latched into AVAOREF domain,
            //once latched in, this bit is still effective in SHUTDOWN
        	uint8_t SNIFDET_EN           : 1; //Enable the Sniff detector on COM* port, this bit is latched into AVAOREF domain,
            //once latched in, this bit is still effective in SHUTDOWN
        } Bit;
        uint8_t Byte;
    } DEV_CONF1;

    union
    {
        struct
        {
        	uint8_t INH_DIS       : 2; //Disable INH driver (PMOS pull up).
        	uint8_t RSVD          : 6;
        } Bit;
        uint8_t Byte;
    } DEV_CONF2;

}_Bq79600_RegisterGroup;

#endif /* BQ79600_H_ */
