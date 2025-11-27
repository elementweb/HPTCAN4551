#ifndef CLASS_HPTCAN4551_REGISTERS_H
#define CLASS_HPTCAN4551_REGISTERS_H

/**
 * ID and revision registers (0x0000-0x0008)
 */

#define HPTCAN4551_ADDR_DEV_ID1                                             0x0000
#define HPTCAN4551_USABLE_DEV_ID1                                           0xFFFFFFFF

#define HPTCAN4551_ADDR_DEV_ID2                                             0x0004
#define HPTCAN4551_USABLE_DEV_ID2                                           0xFFFFFFFF

#define HPTCAN4551_ADDR_DEV_SPIREV                                          0x0008
#define HPTCAN4551_USABLE_DEV_SPIREV                                        0xFF00FFFF

/**
 * Status Register (0x000C)
 */

#define HPTCAN4551_ADDR_STATUS                                              0x000C
#define HPTCAN4551_REG_PROTECTED_STATUS                                     false
#define HPTCAN4551_DEFAULT_STATUS                                           0x00000000
#define HPTCAN4551_USABLE_STATUS                                            0x3F3F003F

#define HPTCAN4551_MASK_STATUS_INT_READ_ERR                                 0x20000000 // 1 bit
#define HPTCAN4551_MASK_STATUS_INT_WRITE_ERR                                0x10000000 // 1 bit
#define HPTCAN4551_MASK_STATUS_INT_ERR_LOG_WRITE                            0x08000000 // 1 bit
#define HPTCAN4551_MASK_STATUS_READ_FIFO_UNDERFLOW                          0x04000000 // 1 bit
#define HPTCAN4551_MASK_STATUS_READ_FIFO_EMPTY                              0x02000000 // 1 bit
#define HPTCAN4551_MASK_STATUS_WRITE_FIFO_OVERFLOW                          0x01000000 // 1 bit
#define HPTCAN4551_MASK_STATUS_SPI_END_ERROR                                0x00200000 // 1 bit
#define HPTCAN4551_MASK_STATUS_INVALID_COMMAND                              0x00100000 // 1 bit
#define HPTCAN4551_MASK_STATUS_WRITE_OVERFLOW                               0x00080000 // 1 bit
#define HPTCAN4551_MASK_STATUS_WRITE_UNDERFLOW                              0x00040000 // 1 bit
#define HPTCAN4551_MASK_STATUS_READ_OVERFLOW                                0x00020000 // 1 bit
#define HPTCAN4551_MASK_STATUS_READ_UNDERFLOW                               0x00010000 // 1 bit
#define HPTCAN4551_MASK_STATUS_WRITE_FIFO_AVAILABLE                         0x00000020 // 1 bit
#define HPTCAN4551_MASK_STATUS_READ_FIFO_AVAILABLE                          0x00000010 // 1 bit
#define HPTCAN4551_MASK_STATUS_INTERNAL_ACCESS_ACTIVE                       0x00000008 // 1 bit
#define HPTCAN4551_MASK_STATUS_INTERNAL_ERR_INTERRUPT                       0x00000004 // 1 bit
#define HPTCAN4551_MASK_STATUS_SPI_ERR_INTERRUPT                            0x00000002 // 1 bit
#define HPTCAN4551_MASK_STATUS_INTERRUPT                                    0x00000001 // 1 bit

/**
 * Modes of Operation and Pin Configuration Registers (start @ 0x0800)
 */

#define HPTCAN4551_ADDR_OP                                                  0x0800
#define HPTCAN4551_REG_PROTECTED_OP                                         false
#define HPTCAN4551_DEFAULT_OP                                               0xC8000460
#define HPTCAN4551_USABLE_OP                                                0xC8E82FC7

#define HPTCAN4551_MASK_OP_WAKE_CONFIG                                      0xC0000000 // 2 bits
#define HPTCAN4551_MASK_OP_CLK_REF                                          0x08000000 // 1 bit
#define HPTCAN4551_MASK_OP_GPO2_CONFIG                                      0x00C00000 // 2 bits
#define HPTCAN4551_MASK_OP_TEST_MODE_EN                                     0x00200000 // 1 bit
#define HPTCAN4551_MASK_OP_NWKRQ_VOLTAGE                                    0x00080000 // 1 bit
#define HPTCAN4551_MASK_OP_FAIL_SAFE_EN                                     0x00002000 // 1 bit
#define HPTCAN4551_MASK_OP_GPO1_GPO_CONFIG                                  0x00000C00 // 2 bits
#define HPTCAN4551_MASK_OP_INH_DIS                                          0x00000200 // 1 bit
#define HPTCAN4551_MASK_OP_NWKRQ_CONFIG                                     0x00000100 // 1 bit
#define HPTCAN4551_MASK_OP_MODE_SEL                                         0x000000C0 // 2 bits
#define HPTCAN4551_MASK_OP_RSVD_WRITE                                       0x00000020 // 1 bit
#define HPTCAN4551_MASK_OP_DEVICE_RESET                                     0x00000004 // 1 bit
#define HPTCAN4551_MASK_OP_SWE_DIS                                          0x00000002 // 1 bit
#define HPTCAN4551_MASK_OP_TEST_MODE_CONFIG                                 0x00000001 // 1 bit

#define HPTCAN4551_VAL_OP_WAKE_CONFIG_DISABLED                              0b00
#define HPTCAN4551_VAL_OP_WAKE_CONFIG_RISING                                0b01
#define HPTCAN4551_VAL_OP_WAKE_CONFIG_FALLING                               0b10
#define HPTCAN4551_VAL_OP_WAKE_CONFIG_BIDIR                                 0b11 // default

#define HPTCAN4551_VAL_OP_CLK_REF_20M                                       0b0
#define HPTCAN4551_VAL_OP_CLK_REF_40M                                       0b1 // default

#define HPTCAN4551_VAL_OP_GPO2_CONFIG_NO_ACTION                             0b00 // default
#define HPTCAN4551_VAL_OP_GPO2_CONFIG_MCAN0_INT                             0b01
#define HPTCAN4551_VAL_OP_GPO2_CONFIG_INT_MIRROR                            0b11

#define HPTCAN4551_VAL_OP_TEST_MODE_EN_DISABLED                             0b0 // default
#define HPTCAN4551_VAL_OP_TEST_MODE_EN_ENABLED                              0b1

#define HPTCAN4551_VAL_OP_NWKRQ_VOLTAGE_INTERNAL                            0b0 // default
#define HPTCAN4551_VAL_OP_NWKRQ_VOLTAGE_VIO                                 0b1

#define HPTCAN4551_VAL_OP_FAIL_SAFE_EN_DISABLED                             0b0 // default
#define HPTCAN4551_VAL_OP_FAIL_SAFE_EN_ENABLED                              0b1

#define HPTCAN4551_VAL_OP_GPO1_GPO_CONFIG_SPI_FAULT                         0b00
#define HPTCAN4551_VAL_OP_GPO1_GPO_CONFIG_MCAN1_INT                         0b01 // default
#define HPTCAN4551_VAL_OP_GPO1_GPO_CONFIG_UV_THERMAL                        0b10

#define HPTCAN4551_VAL_OP_INH_DIS_ENALBED                                   0b0 // default
#define HPTCAN4551_VAL_OP_INH_DIS_DISABLED                                  0b1

#define HPTCAN4551_VAL_OP_NWKRQ_CONFIG_MIRROR_INH                           0b0 // default
#define HPTCAN4551_VAL_OP_NWKRQ_CONFIG_MIRROR_WAKE_REQ_INT                  0b1

#define HPTCAN4551_VAL_OP_MODE_SEL_SLEEP                                    0b00 
#define HPTCAN4551_VAL_OP_MODE_SEL_STANDBY                                  0b01 // default
#define HPTCAN4551_VAL_OP_MODE_SEL_NORMAL                                   0b10

#define HPTCAN4551_VAL_OP_DEVICE_RESET_KEEP_CURRENT                         0b0 // default
#define HPTCAN4551_VAL_OP_DEVICE_RESET_TO_DEFAULT                           0b1

#define HPTCAN4551_VAL_OP_SWE_DIS_ENABLED                                   0b0 // default
#define HPTCAN4551_VAL_OP_SWE_DIS_DISABLED                                  0b1

#define HPTCAN4551_VAL_OP_TEST_MODE_CONFIG_PHY                              0b0 // default
#define HPTCAN4551_VAL_OP_TEST_MODE_CONFIG_CAN                              0b0

/**
 * Timestamp Prescalar (0x0804)
 */

#define HPTCAN4551_ADDR_TIMESTAMP_PRESCALAR                                 0x0804
#define HPTCAN4551_REG_PROTECTED_TIMESTAMP_PRESCALAR                        false
#define HPTCAN4551_DEFAULT_TIMESTAMP_PRESCALAR                              0x00000002
#define HPTCAN4551_USABLE_TIMESTAMP_PRESCALAR                               0x000000FF

#define HPTCAN4551_MASK_TIMESTAMP_PRESCALAR                                 0x000000FF // 8 bits

/**
 * Test Register and Scratch Pad (0x0808)
 */

#define HPTCAN4551_ADDR_TEST_SCRATCHPAD                                     0x0808
#define HPTCAN4551_REG_PROTECTED_TEST_SCRATCHPAD                            false
#define HPTCAN4551_DEFAULT_TEST_SCRATCHPAD                                  0x00000000
#define HPTCAN4551_USABLE_TEST_SCRATCHPAD                                   0xFFFFFFFF

#define HPTCAN4551_MASK_TEST_RW_1                                           0xFF000000 // 8 bits
#define HPTCAN4551_MASK_TEST_RW_2                                           0x00FF0000 // 8 bits
#define HPTCAN4551_MASK_SCRATCHPAD_1                                        0x0000FF00 // 8 bits
#define HPTCAN4551_MASK_SCRATCHPAD_2                                        0x000000FF // 8 bits

/**
 * Test Register (0x080C)
 */

#define HPTCAN4551_ADDR_TREG                                                0x080C
#define HPTCAN4551_REG_PROTECTED_TREG                                       false
#define HPTCAN4551_DEFAULT_TREG                                             0x00000000
#define HPTCAN4551_USABLE_TREG                                              0x003F1800

#define HPTCAN4551_MASK_TREG_ECC_ERR_FORCE_BIT_SEL                          0x003F0000 // 6 bits
#define HPTCAN4551_MASK_TREG_ECC_ERR_FORCE                                  0x00001000 // 1 bit
#define HPTCAN4551_MASK_TREG_ECC_ERR_CHECK                                  0x00000800 // 1 bit

#define HPTCAN4551_VAL_TREG_ECC_ERR_FORCE_NONE                              0b0 // default
#define HPTCAN4551_VAL_TREG_ECC_ERR_FORCE_SINGLE_BIT                        0b1

#define HPTCAN4551_VAL_TREG_ECC_ERR_CHECK_NO_ERROR                          0b0 // default
#define HPTCAN4551_VAL_TREG_ECC_ERR_CHECK_DETECTED                          0b1

/**
 * Interrupts (0x0820)
 */

#define HPTCAN4551_ADDR_IR                                                  0x0820
#define HPTCAN4551_REG_PROTECTED_IR                                         false
#define HPTCAN4551_DEFAULT_IR                                               0x00100000
#define HPTCAN4551_USABLE_IR                                                0x8059E5EB

#define HPTCAN4551_MASK_IR_CANBUSNOM                                        0x80000000 // 1 bit
#define HPTCAN4551_MASK_IR_SMS                                              0x00800000 // 1 bit
#define HPTCAN4551_MASK_IR_UVSUP                                            0x00400000 // 1 bit
#define HPTCAN4551_MASK_IR_PWRON                                            0x00100000 // 1 bit
#define HPTCAN4551_MASK_IR_TSD                                              0x00080000 // 1 bit
#define HPTCAN4551_MASK_IR_ECC_ERR                                          0x00010000 // 1 bit
#define HPTCAN4551_MASK_IR_CANINT                                           0x00008000 // 1 bit
#define HPTCAN4551_MASK_IR_LWU                                              0x00004000 // 1 bit
#define HPTCAN4551_MASK_IR_WKERR                                            0x00002000 // 1 bit
#define HPTCAN4551_MASK_IR_CANSLNT                                          0x00000400 // 1 bit
#define HPTCAN4551_MASK_IR_CANDOM                                           0x00000100 // 1 bit
#define HPTCAN4551_MASK_IR_GLOBALERR                                        0x00000080 // 1 bit
#define HPTCAN4551_MASK_IR_WKRQ                                             0x00000040 // 1 bit
#define HPTCAN4551_MASK_IR_CANERR                                           0x00000020 // 1 bit
#define HPTCAN4551_MASK_IR_SPIERR                                           0x00000008 // 1 bit
#define HPTCAN4551_MASK_IR_M_CAN_INT                                        0x00000002 // 1 bit
#define HPTCAN4551_MASK_IR_VTWD                                             0x00000001 // 1 bit

/**
 * MCAN Interrupts (0x0824)
 */

#define HPTCAN4551_ADDR_MIR                                                 0x0824
#define HPTCAN4551_REG_PROTECTED_MIR                                        false
#define HPTCAN4551_DEFAULT_MIR                                              0x00000000
#define HPTCAN4551_USABLE_MIR                                               0x3FFFFFFF

#define HPTCAN4551_MASK_MIR_ARA                                             0x20000000 // 1 bit
#define HPTCAN4551_MASK_MIR_PED                                             0x10000000 // 1 bit
#define HPTCAN4551_MASK_MIR_PEA                                             0x08000000 // 1 bit
#define HPTCAN4551_MASK_MIR_WDI                                             0x04000000 // 1 bit
#define HPTCAN4551_MASK_MIR_BO                                              0x02000000 // 1 bit
#define HPTCAN4551_MASK_MIR_EW                                              0x01000000 // 1 bit
#define HPTCAN4551_MASK_MIR_EP                                              0x00800000 // 1 bit
#define HPTCAN4551_MASK_MIR_ELO                                             0x00400000 // 1 bit
#define HPTCAN4551_MASK_MIR_BEU                                             0x00200000 // 1 bit
#define HPTCAN4551_MASK_MIR_BEC                                             0x00100000 // 1 bit
#define HPTCAN4551_MASK_MIR_DRX                                             0x00080000 // 1 bit
#define HPTCAN4551_MASK_MIR_TOO                                             0x00040000 // 1 bit
#define HPTCAN4551_MASK_MIR_MRAF                                            0x00020000 // 1 bit
#define HPTCAN4551_MASK_MIR_TSW                                             0x00010000 // 1 bit
#define HPTCAN4551_MASK_MIR_TEFL                                            0x00008000 // 1 bit
#define HPTCAN4551_MASK_MIR_TEFF                                            0x00004000 // 1 bit
#define HPTCAN4551_MASK_MIR_TEFW                                            0x00002000 // 1 bit
#define HPTCAN4551_MASK_MIR_TEFN                                            0x00001000 // 1 bit
#define HPTCAN4551_MASK_MIR_TFE                                             0x00000800 // 1 bit
#define HPTCAN4551_MASK_MIR_TCF                                             0x00000400 // 1 bit
#define HPTCAN4551_MASK_MIR_TC                                              0x00000200 // 1 bit
#define HPTCAN4551_MASK_MIR_HPM                                             0x00000100 // 1 bit
#define HPTCAN4551_MASK_MIR_RF1L                                            0x00000080 // 1 bit
#define HPTCAN4551_MASK_MIR_RF1F                                            0x00000040 // 1 bit
#define HPTCAN4551_MASK_MIR_RF1W                                            0x00000020 // 1 bit
#define HPTCAN4551_MASK_MIR_RF1N                                            0x00000010 // 1 bit
#define HPTCAN4551_MASK_MIR_RF0L                                            0x00000008 // 1 bit
#define HPTCAN4551_MASK_MIR_RF0F                                            0x00000004 // 1 bit
#define HPTCAN4551_MASK_MIR_RF0W                                            0x00000002 // 1 bit
#define HPTCAN4551_MASK_MIR_RF0N                                            0x00000001 // 1 bit

/**
 * Interrupt Enables (0x0830)
 */

#define HPTCAN4551_ADDR_IE                                                  0x0830
#define HPTCAN4551_REG_PROTECTED_IE                                         false
#define HPTCAN4551_DEFAULT_IE                                               0xFFFFFFFF
#define HPTCAN4551_USABLE_IE                                                0x00493A00

#define HPTCAN4551_MASK_IE_UVSUP                                            0x00400000 // 1 bit
#define HPTCAN4551_MASK_IE_TSD                                              0x00080000 // 1 bit
#define HPTCAN4551_MASK_IE_ECCERR                                           0x00010000 // 1 bit
#define HPTCAN4551_MASK_IE_CANINT                                           0x00008000 // 1 bit
#define HPTCAN4551_MASK_IE_LWU                                              0x00004000 // 1 bit
#define HPTCAN4551_MASK_IE_CANSLNT                                          0x00000400 // 1 bit
#define HPTCAN4551_MASK_IE_CANDOM                                           0x00000100 // 1 bit

/**
 * Core Release Register (CREL @ 0x1000)
 */

#define HPTCAN4551_ADDR_FD_CREL                                             0x1000
#define HPTCAN4551_REG_PROTECTED_FD_CREL                                    false
#define HPTCAN4551_USABLE_FD_CREL                                           0xFFFFFFFF

#define HPTCAN4551_MASK_FD_CREL_REL                                         0xF0000000 // 4 bits
#define HPTCAN4551_MASK_FD_CREL_STEP                                        0x0F000000 // 4 bits
#define HPTCAN4551_MASK_FD_CREL_SUBSTEP                                     0x00F00000 // 4 bits
#define HPTCAN4551_MASK_FD_CREL_YEAR                                        0x000F0000 // 4 bits
#define HPTCAN4551_MASK_FD_CREL_MONTH                                       0x0000FF00 // 8 bits
#define HPTCAN4551_MASK_FD_CREL_DAY                                         0x000000FF // 8 bits

/**
 * Endian Register (ENDN @ 0x1004)
 */

#define HPTCAN4551_ADDR_FD_ENDN                                             0x1004
#define HPTCAN4551_REG_PROTECTED_FD_ENDN                                    false
#define HPTCAN4551_DEFAULT_FD_ENDN                                          0x87654321
#define HPTCAN4551_USABLE_FD_ENDN                                           0xFFFFFFFF

#define HPTCAN4551_MASK_FD_ENDN_ETV1                                        0xFF000000 // 8 bits
#define HPTCAN4551_MASK_FD_ENDN_ETV2                                        0x00FF0000 // 8 bits
#define HPTCAN4551_MASK_FD_ENDN_ETV3                                        0x0000FF00 // 8 bits
#define HPTCAN4551_MASK_FD_ENDN_ETV4                                        0x000000FF // 8 bits

/**
 * Customer Register (CUST @ 0x1008)
 */

#define HPTCAN4551_ADDR_FD_CUST                                             0x1008
#define HPTCAN4551_REG_PROTECTED_FD_CUST                                    false
#define HPTCAN4551_DEFAULT_FD_CUST                                          0x00000000
#define HPTCAN4551_USABLE_FD_CUST                                           0x00000000

/**
 * Data Bit Timing & Prescaler (DBTP @ 0x100C)
 */

#define HPTCAN4551_ADDR_FD_DBTP                                             0x100C
#define HPTCAN4551_REG_PROTECTED_FD_DBTP                                    true
#define HPTCAN4551_DEFAULT_FD_DBTP                                          0x00000A33
#define HPTCAN4551_USABLE_FD_DBTP                                           0x009F1FFF

#define HPTCAN4551_MASK_FD_DBTP_TDC                                         0x00800000 // 1 bit
#define HPTCAN4551_MASK_FD_DBTP_DBRP                                        0x001F0000 // 5 bits
#define HPTCAN4551_MASK_FD_DBTP_DTSEG1                                      0x00001F00 // 5 bits
#define HPTCAN4551_MASK_FD_DBTP_DTSEG2                                      0x000000F0 // 4 bits
#define HPTCAN4551_MASK_FD_DBTP_DSJW                                        0x0000000F // 4 bits

#define HPTCAN4551_VAL_FD_DBTP_TDC_DISABLED                                 0b0 // default
#define HPTCAN4551_VAL_FD_DBTP_TDC_ENABLED                                  0b1

/**
 * Test Register (TEST @ 0x1010)
 */

#define HPTCAN4551_ADDR_FD_TEST                                             0x1010
#define HPTCAN4551_REG_PROTECTED_FD_TEST                                    true
#define HPTCAN4551_DEFAULT_FD_TEST                                          0x00000000
#define HPTCAN4551_USABLE_FD_TEST                                           0x000000F0

#define HPTCAN4551_MASK_FD_TEST_RX                                          0x00000080 // 1 bit
#define HPTCAN4551_MASK_FD_TEST_TX                                          0x00000060 // 2 bits
#define HPTCAN4551_MASK_FD_TEST_LBCK                                        0x00000010 // 1 bit

#define HPTCAN4551_VAL_FD_TEST_RX_DOMINANT                                  0b0
#define HPTCAN4551_VAL_FD_TEST_RX_RECESIVE                                  0b1

#define HPTCAN4551_VAL_FD_TEST_TX_RESET                                     0b00 // default
#define HPTCAN4551_VAL_FD_TEST_TX_SAMPLE                                    0b01
#define HPTCAN4551_VAL_FD_TEST_TX_DOMINANT                                  0b10
#define HPTCAN4551_VAL_FD_TEST_TX_RECESIVE                                  0b11

#define HPTCAN4551_VAL_FD_TEST_LBCK_DISALBED                                0b0 // default
#define HPTCAN4551_VAL_FD_TEST_LBCK_ENABLED                                 0b1

/**
 * RAM Watchdog (RWD @ 0x1014)
 */

#define HPTCAN4551_ADDR_FD_RWD                                              0x1014
#define HPTCAN4551_REG_PROTECTED_FD_RWD                                     true
#define HPTCAN4551_DEFAULT_FD_RWD                                           0x00000000
#define HPTCAN4551_USABLE_FD_RWD                                            0x0000FFFF

#define HPTCAN4551_MASK_FD_RWD_WDV                                          0x0000FF00 // 8 bits
#define HPTCAN4551_MASK_FD_RWD_WDC                                          0x000000FF // 8 bits

/**
 * CC Control Register (CCCR @ 0x1018)
 */

#define HPTCAN4551_ADDR_FD_CCCR                                             0x1018
#define HPTCAN4551_REG_PROTECTED_FD_CCCR                                    true
#define HPTCAN4551_DEFAULT_FD_CCCR                                          0x00000019
#define HPTCAN4551_USABLE_FD_CCCR                                           0x0000F3FF

#define HPTCAN4551_MASK_FD_CCCR_NISO                                        0x00008000 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_TXP                                         0x00004000 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_EFBI                                        0x00002000 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_PXHD                                        0x00001000 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_BRSE                                        0x00000200 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_FDOE                                        0x00000100 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_TEST                                        0x00000080 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_DAR                                         0x00000040 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_MON                                         0x00000020 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_CSR                                         0x00000010 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_CSA                                         0x00000008 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_ASM                                         0x00000004 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_CCE                                         0x00000002 // 1 bit
#define HPTCAN4551_MASK_FD_CCCR_INIT                                        0x00000001 // 1 bit

#define HPTCAN4551_VAL_FD_CCCR_NISO_ISO                                     0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_NISO_BOSCH                                   0b1

#define HPTCAN4551_VAL_FD_CCCR_TXP_DISABLED                                 0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_TXP_ENABLED                                  0b1

#define HPTCAN4551_VAL_FD_CCCR_EFBI_DISABLED                                0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_EFBI_CONSECUTIVE                             0b1

#define HPTCAN4551_VAL_FD_CCCR_PXHD_ENABLED                                 0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_PXHD_DISABLED                                0b1

#define HPTCAN4551_VAL_FD_CCCR_BRSE_DISABLED                                0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_BRSE_ENABLED                                 0b1

#define HPTCAN4551_VAL_FD_CCCR_FDOE_DISABLED                                0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_FDOE_ENABLED                                 0b1

#define HPTCAN4551_VAL_FD_CCCR_TEST_DISABLED                                0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_TEST_ENABLED                                 0b1

#define HPTCAN4551_VAL_FD_CCCR_DAR_ENABLED                                  0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_DAR_DISABLED                                 0b1

#define HPTCAN4551_VAL_FD_CCCR_MON_DISABLED                                 0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_MON_ENABLED                                  0b1

#define HPTCAN4551_VAL_FD_CCCR_CSR_NONE                                     0b0
#define HPTCAN4551_VAL_FD_CCCR_CSR_REQUESTED                                0b1 // default

#define HPTCAN4551_VAL_FD_CCCR_CSA_REQUESTED                                0b0
#define HPTCAN4551_VAL_FD_CCCR_CSA_PWR_DOWN                                 0b1 // default

#define HPTCAN4551_VAL_FD_CCCR_ASM_NORMAL                                   0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_ASM_RESTRICTED                               0b1

#define HPTCAN4551_VAL_FD_CCCR_CCE_FORBIDDEN                                0b0 // default
#define HPTCAN4551_VAL_FD_CCCR_CCE_PERMITTED                                0b1

#define HPTCAN4551_VAL_FD_CCCR_INIT_NORMAL                                  0b0
#define HPTCAN4551_VAL_FD_CCCR_INIT_STARTED                                 0b1 // default

/**
 * Nominal Bit Timing & Prescaler Register (NBTP @ 0x101C)
 */

#define HPTCAN4551_ADDR_FD_NBTP                                             0x101C
#define HPTCAN4551_REG_PROTECTED_FD_NBTP                                    true
#define HPTCAN4551_DEFAULT_FD_NBTP                                          0x06000A03
#define HPTCAN4551_USABLE_FD_NBTP                                           0xFFFFFF7F

#define HPTCAN4551_MASK_FD_NBTP_NSJW                                        0xFE000000 // 7 bits
#define HPTCAN4551_MASK_FD_NBTP_NBRP                                        0x01FF0000 // 9 bits
#define HPTCAN4551_MASK_FD_NBTP_NTSEG1                                      0x0000FF00 // 8 bits
#define HPTCAN4551_MASK_FD_NBTP_NTSEG2                                      0x0000007F // 7 bits

/**
 * Timestamp Counter Configuration (TSCC @ 0x1020)
 */

#define HPTCAN4551_ADDR_FD_TSCC                                             0x1020
#define HPTCAN4551_REG_PROTECTED_FD_TSCC                                    true
#define HPTCAN4551_DEFAULT_FD_TSCC                                          0x00000000
#define HPTCAN4551_USABLE_FD_TSCC                                           0x000F0003

#define HPTCAN4551_MASK_FD_TSCC_TCP                                         0x000F0000 // 4 bits
#define HPTCAN4551_MASK_FD_TSCC_TSS                                         0x00000003 // 2 bits

#define HPTCAN4551_VAL_FD_TSCC_TSS_DISABLED                                 0b00 // default
#define HPTCAN4551_VAL_FD_TSCC_TSS_INCR                                     0b01
#define HPTCAN4551_VAL_FD_TSCC_TSS_EXTERNAL_TS                              0b10

/**
 * Timestamp Counter Value (TSCV @ 0x1024)
 */

#define HPTCAN4551_ADDR_FD_TSCV                                             0x1024
#define HPTCAN4551_REG_PROTECTED_FD_TSCV                                    false
#define HPTCAN4551_DEFAULT_FD_TSCV                                          0x00000000
#define HPTCAN4551_USABLE_FD_TSCV                                           0x0000FFFF

#define HPTCAN4551_MASK_FD_TSCV_TSC                                         0x0000FFFF // 16 bits

/**
 * Timeout Counter Configuration (TOCC @ 0x1028)
 */

#define HPTCAN4551_ADDR_FD_TOCC                                             0x1028
#define HPTCAN4551_REG_PROTECTED_FD_TOCC                                    true
#define HPTCAN4551_DEFAULT_FD_TOCC                                          0xFFFF0000
#define HPTCAN4551_USABLE_FD_TOCC                                           0xFFFF0007

#define HPTCAN4551_MASK_FD_TOCC_TOP                                         0xFFFF0000
#define HPTCAN4551_MASK_FD_TOCC_TOS                                         0x00000006 // 2 bits
#define HPTCAN4551_MASK_FD_TOCC_ETOC                                        0x00000001 // 1 bit

#define HPTCAN4551_VAL_FD_TOCC_TOS_CONTINUOUS                               0b00 // default
#define HPTCAN4551_VAL_FD_TOCC_TOS_TX_FIFO                                  0b01
#define HPTCAN4551_VAL_FD_TOCC_TOS_RX_FIFO0                                 0b10
#define HPTCAN4551_VAL_FD_TOCC_TOS_RX_FIFO1                                 0b11

#define HPTCAN4551_VAL_FD_TOCC_ETOC_DISABLED                                0b0 // default
#define HPTCAN4551_VAL_FD_TOCC_ETOC_ENABLED                                 0b1

/**
 * Timeout Counter Value (TOCV @ 0x102C)
 */

#define HPTCAN4551_ADDR_FD_TOCV                                             0x102C
#define HPTCAN4551_REG_PROTECTED_FD_TOCV                                    false
#define HPTCAN4551_DEFAULT_FD_TOCV                                          0x0000FFFF
#define HPTCAN4551_USABLE_FD_TOCV                                           0x0000FFFF

#define HPTCAN4551_MASK_FD_TOCV_TOC                                         0x0000FFFF // 16 bits

/**
 * Error Counter Register (ECR @ 0x1040)
 */

#define HPTCAN4551_ADDR_FD_ECR                                              0x1040
#define HPTCAN4551_REG_PROTECTED_FD_ECR                                     false
#define HPTCAN4551_DEFAULT_FD_ECR                                           0x00000000
#define HPTCAN4551_USABLE_FD_ECR                                            0x00FFFFFF

#define HPTCAN4551_MASK_FD_ECR_CEL                                          0x00FF0000 // 8 bits
#define HPTCAN4551_MASK_FD_ECR_RP                                           0x00008000 // 1 bit
#define HPTCAN4551_MASK_FD_ECR_REC                                          0x00007F00 // 7 bits
#define HPTCAN4551_MASK_FD_ECR_TEC                                          0x000000FF // 8 bits

/**
 * Protocol Status Register (PSR @ 0x1044)
 */

#define HPTCAN4551_ADDR_FD_PSR                                              0x1044
#define HPTCAN4551_REG_PROTECTED_FD_PSR                                     false
#define HPTCAN4551_DEFAULT_FD_PSR                                           0x00000707
#define HPTCAN4551_USABLE_FD_PSR                                            0x007F7FFF

#define HPTCAN4551_MASK_FD_PSR_TDCV                                         0x007F0000 // 7 bits
#define HPTCAN4551_MASK_FD_PSR_PXE                                          0x00004000 // 1 bit
#define HPTCAN4551_MASK_FD_PSR_RFDF                                         0x00002000 // 1 bit
#define HPTCAN4551_MASK_FD_PSR_RBRS                                         0x00001000 // 1 bit
#define HPTCAN4551_MASK_FD_PSR_RESI                                         0x00000800 // 1 bit
#define HPTCAN4551_MASK_FD_PSR_DLEC                                         0x00000700 // 3 bits
#define HPTCAN4551_MASK_FD_PSR_BO                                           0x00000080 // 1 bit
#define HPTCAN4551_MASK_FD_PSR_EW                                           0x00000040 // 1 bit
#define HPTCAN4551_MASK_FD_PSR_EP                                           0x00000020 // 1 bit
#define HPTCAN4551_MASK_FD_PSR_ACT                                          0x00000018 // 2 bits
#define HPTCAN4551_MASK_FD_PSR_LEC                                          0x00000007 // 3 bits

#define HPTCAN4551_VAL_FD_PSR_ACT_SYNC                                      0b00 // default
#define HPTCAN4551_VAL_FD_PSR_ACT_IDLE                                      0b01
#define HPTCAN4551_VAL_FD_PSR_ACT_RECEIVER                                  0b10
#define HPTCAN4551_VAL_FD_PSR_ACT_TRANSMITTER                               0b11

/**
 * Transmitter Delay Compensation Register (TDCR @ 0x1048)
 */

#define HPTCAN4551_ADDR_FD_TDCR                                             0x1048
#define HPTCAN4551_REG_PROTECTED_FD_TDCR                                    true
#define HPTCAN4551_DEFAULT_FD_TDCR                                          0x00000000
#define HPTCAN4551_USABLE_FD_TDCR                                           0x00007F7F

#define HPTCAN4551_MASK_FD_TDCR_TDCO                                        0x00007F00 // 7 bits
#define HPTCAN4551_MASK_FD_TDCR_TDCF                                        0x0000007F // 7 bits

/**
 * Interrupt Register (IR @ 0x1050)
 */

#define HPTCAN4551_ADDR_FD_IR                                               0x1050
#define HPTCAN4551_REG_PROTECTED_FD_IR                                      false
#define HPTCAN4551_DEFAULT_FD_IR                                            0x00000000
#define HPTCAN4551_USABLE_FD_IR                                             0x3FFFFFFF

#define HPTCAN4551_MASK_FD_IR_ARA                                           0x20000000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_PED                                           0x10000000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_PEA                                           0x08000000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_WDI                                           0x04000000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_BO                                            0x02000000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_EW                                            0x01000000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_EP                                            0x00800000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_ELO                                           0x00400000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_BEU                                           0x00200000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_BEC                                           0x00100000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_DRX                                           0x00080000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TOO                                           0x00040000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_MRF                                           0x00020000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TSW                                           0x00010000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TEFL                                          0x00008000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TEFF                                          0x00004000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TEFW                                          0x00002000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TEFN                                          0x00001000 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TFE                                           0x00000800 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TCF                                           0x00000400 // 1 bit
#define HPTCAN4551_MASK_FD_IR_TC                                            0x00000200 // 1 bit
#define HPTCAN4551_MASK_FD_IR_HPM                                           0x00000100 // 1 bit
#define HPTCAN4551_MASK_FD_IR_RF1L                                          0x00000080 // 1 bit
#define HPTCAN4551_MASK_FD_IR_RF1F                                          0x00000040 // 1 bit
#define HPTCAN4551_MASK_FD_IR_RF1W                                          0x00000020 // 1 bit
#define HPTCAN4551_MASK_FD_IR_RF1N                                          0x00000010 // 1 bit
#define HPTCAN4551_MASK_FD_IR_RF0L                                          0x00000008 // 1 bit
#define HPTCAN4551_MASK_FD_IR_RF0F                                          0x00000004 // 1 bit
#define HPTCAN4551_MASK_FD_IR_RF0W                                          0x00000002 // 1 bit
#define HPTCAN4551_MASK_FD_IR_RF0N                                          0x00000001 // 1 bit

/**
 * Interrupt Enable (IE @ 0x1054)
 */

#define HPTCAN4551_ADDR_FD_IE                                               0x1054
#define HPTCAN4551_REG_PROTECTED_FD_IE                                      false
#define HPTCAN4551_DEFAULT_FD_IE                                            0x00000000
#define HPTCAN4551_USABLE_FD_IE                                             0x3FFFFFFF

#define HPTCAN4551_MASK_FD_IE_ARAE                                          0x20000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_PEDE                                          0x10000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_PEAE                                          0x08000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_WDIE                                          0x04000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_BOE                                           0x02000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_EWE                                           0x01000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_EPE                                           0x00800000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_ELOE                                          0x00400000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_BEUE                                          0x00200000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_BECE                                          0x00100000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_DRXE                                          0x00080000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TOOE                                          0x00040000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_MRFE                                          0x00020000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TSWE                                          0x00010000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TEFLE                                         0x00008000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TEFFE                                         0x00004000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TEFWE                                         0x00002000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TEFNE                                         0x00001000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TFEE                                          0x00000800 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TCFE                                          0x00000400 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TCE                                           0x00000200 // 1 bit
#define HPTCAN4551_MASK_FD_IE_HPM                                           0x00000100 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF1LE                                         0x00000080 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF1FE                                         0x00000040 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF1WE                                         0x00000020 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF1NE                                         0x00000010 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF0LE                                         0x00000008 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF0FE                                         0x00000004 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF0WE                                         0x00000002 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF0NE                                         0x00000001 // 1 bit

/**
 * Interrupt Line Select (ILS @ 0x1058)
 */

#define HPTCAN4551_ADDR_FD_ILS                                              0x1058
#define HPTCAN4551_REG_PROTECTED_FD_ILS                                     false
#define HPTCAN4551_DEFAULT_FD_ILS                                           0x00000000
#define HPTCAN4551_USABLE_FD_ILS                                            0x3FFFFFFF

#define HPTCAN4551_MASK_FD_IE_ARAL                                          0x20000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_PEDL                                          0x10000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_PEAL                                          0x08000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_WDIL                                          0x04000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_BOL                                           0x02000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_EWL                                           0x01000000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_EPL                                           0x00800000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_ELOL                                          0x00400000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_BEUL                                          0x00200000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_BECL                                          0x00100000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_DRXL                                          0x00080000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TOOL                                          0x00040000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_MRFL                                          0x00020000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TSWL                                          0x00010000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TEFLL                                         0x00008000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TEFFL                                         0x00004000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TEFWL                                         0x00002000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TEFNL                                         0x00001000 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TFEL                                          0x00000800 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TCFL                                          0x00000400 // 1 bit
#define HPTCAN4551_MASK_FD_IE_TCL                                           0x00000200 // 1 bit
#define HPTCAN4551_MASK_FD_IE_HPML                                          0x00000100 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF1LL                                         0x00000080 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF1FL                                         0x00000040 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF1WL                                         0x00000020 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF1NL                                         0x00000010 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF0LL                                         0x00000008 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF0FL                                         0x00000004 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF0WL                                         0x00000002 // 1 bit
#define HPTCAN4551_MASK_FD_IE_RF0NL                                         0x00000001 // 1 bit

#define HPTCAN4551_VAL_FD_IE_ALL_MCAN0                                      HPTCAN4551_REGISTER_ALL_CLEAR // default
#define HPTCAN4551_VAL_FD_IE_ALL_MCAN1                                      HPTCAN4551_REGISTER_ALL_SET

/**
 * Interrupt Line Enable (ILE @ 0x105C)
 */

#define HPTCAN4551_ADDR_FD_ILE                                              0x105C
#define HPTCAN4551_REG_PROTECTED_FD_ILE                                     false
#define HPTCAN4551_DEFAULT_FD_ILE                                           0x00000000
#define HPTCAN4551_USABLE_FD_ILE                                            0x00000003

#define HPTCAN4551_MASK_FD_ILE_EINT1                                        0x00000002 // 1 bit
#define HPTCAN4551_MASK_FD_ILE_EINT0                                        0x00000001 // 1 bit

#define HPTCAN4551_VAL_FD_ILE_BOTH_DISABLED                                 0b00 // default
#define HPTCAN4551_VAL_FD_ILE_BOTH_ENABLED                                  0b11

/**
 * Global Filter Configuration (GFC @ 0x1080)
 */

#define HPTCAN4551_ADDR_FD_GFC                                              0x1080
#define HPTCAN4551_REG_PROTECTED_FD_GFC                                     true
#define HPTCAN4551_DEFAULT_FD_GFC                                           0x00000000
#define HPTCAN4551_USABLE_FD_GFC                                            0x0000003F

#define HPTCAN4551_MASK_FD_GFC_ANFS                                         0x00000030 // 2 bits
#define HPTCAN4551_MASK_FD_GFC_ANFE                                         0x0000000C // 2 bits
#define HPTCAN4551_MASK_FD_GFC_RRFS                                         0x00000002 // 1 bit
#define HPTCAN4551_MASK_FD_GFC_RRFE                                         0x00000001 // 1 bit

#define HPTCAN4551_VAL_FD_GFC_ANFS_ACCEPT_FIFO0                             0b00 // default
#define HPTCAN4551_VAL_FD_GFC_ANFS_ACCEPT_FIFO1                             0b01
#define HPTCAN4551_VAL_FD_GFC_ANFS_REJECT                                   0b10

#define HPTCAN4551_VAL_FD_GFC_ANFE_ACCEPT_FIFO0                             0b00 // default
#define HPTCAN4551_VAL_FD_GFC_ANFE_ACCEPT_FIFO1                             0b01
#define HPTCAN4551_VAL_FD_GFC_ANFE_REJECT                                   0b10

#define HPTCAN4551_VAL_FD_GFC_RRFS_FILTER                                   0b0 // default
#define HPTCAN4551_VAL_FD_GFC_RRFS_REJECT                                   0b1

#define HPTCAN4551_VAL_FD_GFC_RRFE_FILTER                                   0b0 // default
#define HPTCAN4551_VAL_FD_GFC_RRFE_REJECT                                   0b1

/**
 * Standard ID Filter Configuration (SIDFC @ 0x1084)
 */

#define HPTCAN4551_ADDR_FD_SIDFC                                            0x1084
#define HPTCAN4551_REG_PROTECTED_FD_SIDFC                                   true
#define HPTCAN4551_DEFAULT_FD_SIDFC                                         0x00000000
#define HPTCAN4551_USABLE_FD_SIDFC                                          0x00FFFFFF

#define HPTCAN4551_MASK_FD_SIDFC_LSS                                        0x00FF0000 // 8 bits
#define HPTCAN4551_MASK_FD_SIDFC_FLSSA                                      0x0000FFFF // 16 bits

/**
 * Extended ID Filter Configuration (XIDFC @ 0x1088)
 */

#define HPTCAN4551_ADDR_FD_XIDFC                                            0x1088
#define HPTCAN4551_REG_PROTECTED_FD_XIDFC                                   true
#define HPTCAN4551_DEFAULT_FD_XIDFC                                         0x00000000
#define HPTCAN4551_USABLE_FD_XIDFC                                          0x007FFFFF

#define HPTCAN4551_MASK_FD_XIDFC_LSE                                        0x007F0000 // 7 bits
#define HPTCAN4551_MASK_FD_XIDFC_FLESA                                      0x0000FFFF // 16 bits

/**
 * Extended ID and MASK 1FFF FFFF RP (XIDAM @ 0x1090)
 */

#define HPTCAN4551_ADDR_FD_XIDAM                                            0x1090
#define HPTCAN4551_REG_PROTECTED_FD_XIDAM                                   true
#define HPTCAN4551_DEFAULT_FD_XIDAM                                         0x1FFFFFFF
#define HPTCAN4551_USABLE_FD_XIDAM                                          0x3FFFFFFF

#define HPTCAN4551_MASK_FD_XIDAM_EIDM                                       0x3FFFFFFF // 30 bits

/**
 * High Priority Message Status (HPMS @ 0x1094)
 */

#define HPTCAN4551_ADDR_FD_HPMS                                             0x1094
#define HPTCAN4551_REG_PROTECTED_FD_HPMS                                    false
#define HPTCAN4551_DEFAULT_FD_HPMS                                          0x00000000
#define HPTCAN4551_USABLE_FD_HPMS                                           0x0000FFFF

#define HPTCAN4551_MASK_FD_HPMS_FLST                                        0x00008000 // 1 bit
#define HPTCAN4551_MASK_FD_HPMS_FIDX                                        0x00007F00 // 7 bits
#define HPTCAN4551_MASK_FD_HPMS_MSI                                         0x000000C0 // 2 bits
#define HPTCAN4551_MASK_FD_HPMS_BIDX                                        0x0000003F // 6 bits

#define HPTCAN4551_VAL_FD_HPMS_FLST_STANDARD                                0b0 // default
#define HPTCAN4551_VAL_FD_HPMS_FLST_EXTENDED                                0b1

#define HPTCAN4551_VAL_FD_HPMS_MSI_NO_FIFO                                  0b00 // default
#define HPTCAN4551_VAL_FD_HPMS_MSI_FIFO_MSG_LOST                            0b01
#define HPTCAN4551_VAL_FD_HPMS_MSI_MSG_STORED_FIFO0                         0b10
#define HPTCAN4551_VAL_FD_HPMS_MSI_MSG_STORED_FIFO1                         0b11

/**
 * New Data 1 (NDAT1 @ 0x1098)
 */

#define HPTCAN4551_ADDR_FD_NDAT1                                            0x1098
#define HPTCAN4551_REG_PROTECTED_FD_NDAT1                                   false
#define HPTCAN4551_DEFAULT_FD_NDAT1                                         0x00000000
#define HPTCAN4551_USABLE_FD_NDAT1                                          0xFFFFFFFF

#define HPTCAN4551_MASK_FD_NDAT1_ND                                         0xFFFFFFFF // 32 bits

/**
 * New Data 2 (NDAT2 @ 0x109C)
 */

#define HPTCAN4551_ADDR_FD_NDAT2                                            0x109C
#define HPTCAN4551_REG_PROTECTED_FD_NDAT2                                   false
#define HPTCAN4551_DEFAULT_FD_NDAT2                                         0x00000000
#define HPTCAN4551_USABLE_FD_NDAT2                                          0xFFFFFFFF

#define HPTCAN4551_MASK_FD_NDAT2_ND                                         0xFFFFFFFF // 32 bits

/**
 * Rx FIFO 0 Configuration (RXF0C @ 0x10A0)
 */

#define HPTCAN4551_ADDR_FD_RXF0C                                            0x10A0
#define HPTCAN4551_REG_PROTECTED_FD_RXF0C                                   true
#define HPTCAN4551_DEFAULT_FD_RXF0C                                         0x00000000
#define HPTCAN4551_USABLE_FD_RXF0C                                          0xFF7FFFFF

#define HPTCAN4551_MASK_FD_RXF0C_F0OM                                       0x80000000 // 1 bit
#define HPTCAN4551_MASK_FD_RXF0C_F0WM                                       0x7F000000 // 7 bits
#define HPTCAN4551_MASK_FD_RXF0C_F0S                                        0x007F0000 // 7 bits
#define HPTCAN4551_MASK_FD_RXF0C_F0SA                                       0x0000FFFF // 16 bits

#define HPTCAN4551_VAL_FD_RXF0C_F0OM_BLOCKING                               0b0 // default
#define HPTCAN4551_VAL_FD_RXF0C_F0OM_OVERWRITE                              0b1

/**
 * Rx FIFO 0 Status (RXF0S @ 0x10A4)
 */

#define HPTCAN4551_ADDR_FD_RXF0S                                            0x10A4
#define HPTCAN4551_REG_PROTECTED_FD_RXF0S                                   false
#define HPTCAN4551_DEFAULT_FD_RXF0S                                         0x00000000
#define HPTCAN4551_USABLE_FD_RXF0S                                          0x033F3F7F

#define HPTCAN4551_MASK_FD_RXF0S_RF0L                                       0x02000000 // 1 bit
#define HPTCAN4551_MASK_FD_RXF0S_F0F                                        0x01000000 // 1 bit
#define HPTCAN4551_MASK_FD_RXF0S_F0PI                                       0x003F0000 // 6 bits
#define HPTCAN4551_MASK_FD_RXF0S_F0GI                                       0x00003F00 // 6 bits
#define HPTCAN4551_MASK_FD_RXF0S_F0FL                                       0x0000007F // 7 bits

#define HPTCAN4551_VAL_FD_RXF0S_RF0L_NONE                                   0b0 // default
#define HPTCAN4551_VAL_FD_RXF0S_RF0L_LOST                                   0b1

#define HPTCAN4551_VAL_FD_RXF0S_F0F_NOT_FULL                                0b0 // default
#define HPTCAN4551_VAL_FD_RXF0S_F0F_FULL                                    0b1

/**
 * Rx FIFO 0 Acknowledge (RXF0A @ 0x10A8)
 */

#define HPTCAN4551_ADDR_FD_RXF0A                                            0x10A8
#define HPTCAN4551_REG_PROTECTED_FD_RXF0A                                   false
#define HPTCAN4551_DEFAULT_FD_RXF0A                                         0x00000000
#define HPTCAN4551_USABLE_FD_RXF0A                                          0x0000003F

#define HPTCAN4551_MASK_FD_RXF0A_F0AI                                       0x0000003F // 6 bits

/**
 * Rx Buffer Configuration (RXBC @ 0x10AC)
 */

#define HPTCAN4551_ADDR_FD_RXBC                                             0x10AC
#define HPTCAN4551_REG_PROTECTED_FD_RXBC                                    true
#define HPTCAN4551_DEFAULT_FD_RXBC                                          0x00000000
#define HPTCAN4551_USABLE_FD_RXBC                                           0x0000FFFF

#define HPTCAN4551_MASK_FD_RXBC_RBSA                                        0x0000FFFF // 16 bits

/**
 * Rx FIFO 1 Configuration (RXF1C @ 0x10B0)
 */

#define HPTCAN4551_ADDR_FD_RXF1C                                            0x10B0
#define HPTCAN4551_REG_PROTECTED_FD_RXF1C                                   true
#define HPTCAN4551_DEFAULT_FD_RXF1C                                         0x00000000
#define HPTCAN4551_USABLE_FD_RXF1C                                          0xFF7FFFFF

#define HPTCAN4551_MASK_FD_RXF1C_F1OM                                       0x80000000 // 1 bit
#define HPTCAN4551_MASK_FD_RXF1C_F1WM                                       0x7F000000 // 7 bits
#define HPTCAN4551_MASK_FD_RXF1C_F1S                                        0x007F0000 // 7 bits
#define HPTCAN4551_MASK_FD_RXF1C_F1SA                                       0x0000FFFF // 16 bits

#define HPTCAN4551_VAL_FD_RXF1C_F1OM_BLOCKING                               0b0 // default
#define HPTCAN4551_VAL_FD_RXF1C_F1OM_OVERWRITE                              0b1

/**
 * Rx FIFO 1 Status (RXF1S @ 0x10B4)
 */

#define HPTCAN4551_ADDR_FD_RXF1S                                            0x10B4
#define HPTCAN4551_REG_PROTECTED_FD_RXF1S                                   false
#define HPTCAN4551_DEFAULT_FD_RXF1S                                         0x00000000
#define HPTCAN4551_USABLE_FD_RXF1S                                          0xC33F3F7F

#define HPTCAN4551_MASK_FD_RXF1S_DMS                                        0xC0000000 // 2 bits
#define HPTCAN4551_MASK_FD_RXF1S_RF1L                                       0x02000000 // 1 bit
#define HPTCAN4551_MASK_FD_RXF1S_F1F                                        0x01000000 // 1 bit
#define HPTCAN4551_MASK_FD_RXF1S_F1PI                                       0x003F0000 // 6 bits
#define HPTCAN4551_MASK_FD_RXF1S_F1GI                                       0x00003F00 // 6 bits
#define HPTCAN4551_MASK_FD_RXF1S_F1FL                                       0x0000007F // 7 bits

#define HPTCAN4551_VAL_FD_RXF1S_RF1L_NONE                                   0b0 // default
#define HPTCAN4551_VAL_FD_RXF1S_RF1L_LOST                                   0b1

#define HPTCAN4551_VAL_FD_RXF1S_F1F_NOT_FULL                                0b0 // default
#define HPTCAN4551_VAL_FD_RXF1S_F1F_FULL                                    0b1

/**
 * Rx FIFO 1 Acknowledge (RXF1A @ 0x10B8)
 */

#define HPTCAN4551_ADDR_FD_RXF1A                                            0x10B8
#define HPTCAN4551_REG_PROTECTED_FD_RXF1A                                   false
#define HPTCAN4551_DEFAULT_FD_RXF1A                                         0x00000000
#define HPTCAN4551_USABLE_FD_RXF1A                                          0x0000003F

#define HPTCAN4551_MASK_FD_RXF1A_F1AI                                       0x0000003F // 6 bits

/**
 * Rx Buffer/FIFO Element Size Configuration (RXESC @ 0x10BC)
 */

#define HPTCAN4551_ADDR_FD_RXESC                                            0x10BC
#define HPTCAN4551_REG_PROTECTED_FD_RXESC                                   true
#define HPTCAN4551_DEFAULT_FD_RXESC                                         0x00000000
#define HPTCAN4551_USABLE_FD_RXESC                                          0x00000777

#define HPTCAN4551_MASK_FD_RXESC_RBDS                                       0x00000700 // 3 bits
#define HPTCAN4551_MASK_FD_RXESC_F1DS                                       0x00000070 // 3 bits
#define HPTCAN4551_MASK_FD_RXESC_F0DS                                       0x00000007 // 3 bits

#define HPTCAN4551_VAL_FD_RXESC_RBDS_8                                      0b000 // default
#define HPTCAN4551_VAL_FD_RXESC_RBDS_12                                     0b001
#define HPTCAN4551_VAL_FD_RXESC_RBDS_16                                     0b010
#define HPTCAN4551_VAL_FD_RXESC_RBDS_20                                     0b011
#define HPTCAN4551_VAL_FD_RXESC_RBDS_24                                     0b100
#define HPTCAN4551_VAL_FD_RXESC_RBDS_32                                     0b101
#define HPTCAN4551_VAL_FD_RXESC_RBDS_48                                     0b110
#define HPTCAN4551_VAL_FD_RXESC_RBDS_64                                     0b111

#define HPTCAN4551_VAL_FD_RXESC_F1DS_8                                      0b000 // default
#define HPTCAN4551_VAL_FD_RXESC_F1DS_12                                     0b001
#define HPTCAN4551_VAL_FD_RXESC_F1DS_16                                     0b010
#define HPTCAN4551_VAL_FD_RXESC_F1DS_20                                     0b011
#define HPTCAN4551_VAL_FD_RXESC_F1DS_24                                     0b100
#define HPTCAN4551_VAL_FD_RXESC_F1DS_32                                     0b101
#define HPTCAN4551_VAL_FD_RXESC_F1DS_48                                     0b110
#define HPTCAN4551_VAL_FD_RXESC_F1DS_64                                     0b111

#define HPTCAN4551_VAL_FD_RXESC_F0DS_8                                      0b000 // default
#define HPTCAN4551_VAL_FD_RXESC_F0DS_12                                     0b001
#define HPTCAN4551_VAL_FD_RXESC_F0DS_16                                     0b010
#define HPTCAN4551_VAL_FD_RXESC_F0DS_20                                     0b011
#define HPTCAN4551_VAL_FD_RXESC_F0DS_24                                     0b100
#define HPTCAN4551_VAL_FD_RXESC_F0DS_32                                     0b101
#define HPTCAN4551_VAL_FD_RXESC_F0DS_48                                     0b110
#define HPTCAN4551_VAL_FD_RXESC_F0DS_64                                     0b111

/**
 * Tx Buffer Configuration (TXBC @ 0x10C0)
 */

#define HPTCAN4551_ADDR_FD_TXBC                                             0x10C0
#define HPTCAN4551_REG_PROTECTED_FD_TXBC                                    true
#define HPTCAN4551_DEFAULT_FD_TXBC                                          0x00000000
#define HPTCAN4551_USABLE_FD_TXBC                                           0x7F3FFFFF

#define HPTCAN4551_MASK_FD_TXBC_TFQM                                        0x40000000 // 1 bit
#define HPTCAN4551_MASK_FD_TXBC_TFQS                                        0x3F000000 // 6 bits
#define HPTCAN4551_MASK_FD_TXBC_NDTB                                        0x003F0000 // 6 bits
#define HPTCAN4551_MASK_FD_TXBC_TBSA                                        0x0000FFFF // 16 bits

#define HPTCAN4551_VAL_FD_TXBC_TFQM_FIFO                                    0b0 // default
#define HPTCAN4551_VAL_FD_TXBC_TFQM_QUEUE                                   0b1

/**
 * Tx FIFO/Queue Status (TXFQS @ 0x10C4)
 */

#define HPTCAN4551_ADDR_FD_TXFQS                                            0x10C4
#define HPTCAN4551_REG_PROTECTED_FD_TXFQS                                   false
#define HPTCAN4551_DEFAULT_FD_TXFQS                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXFQS                                          0x003F1F3F

#define HPTCAN4551_MASK_FD_TXFQS_TFQF                                       0x00200000 // 1 bit
#define HPTCAN4551_MASK_FD_TXFQS_TFQPI                                      0x001F0000 // 5 bits
#define HPTCAN4551_MASK_FD_TXFQS_TFGI                                       0x00001F00 // 5 bits
#define HPTCAN4551_MASK_FD_TXFQS_TFFL                                       0x0000003F // 6 bits

#define HPTCAN4551_VAL_FD_TXFQS_TFQF_NOT_FULL                               0b0 // default
#define HPTCAN4551_VAL_FD_TXFQS_TFQF_FULL                                   0b1

/**
 * Tx Buffer Element Size Configuration (TXESC @ 0x10C8)
 */

#define HPTCAN4551_ADDR_FD_TXESC                                            0x10C8
#define HPTCAN4551_REG_PROTECTED_FD_TXESC                                   true
#define HPTCAN4551_DEFAULT_FD_TXESC                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXESC                                          0x00000007

#define HPTCAN4551_MASK_FD_TXESC_TBDS                                       0x00000007 // 3 bits

#define HPTCAN4551_VAL_FD_TXESC_TBDS_8                                      0b000 // default
#define HPTCAN4551_VAL_FD_TXESC_TBDS_12                                     0b001
#define HPTCAN4551_VAL_FD_TXESC_TBDS_16                                     0b010
#define HPTCAN4551_VAL_FD_TXESC_TBDS_20                                     0b011
#define HPTCAN4551_VAL_FD_TXESC_TBDS_24                                     0b100
#define HPTCAN4551_VAL_FD_TXESC_TBDS_32                                     0b101
#define HPTCAN4551_VAL_FD_TXESC_TBDS_48                                     0b110
#define HPTCAN4551_VAL_FD_TXESC_TBDS_64                                     0b111

/**
 * Tx Buffer Request Pending (TXBRP @ 0x10CC)
 */

#define HPTCAN4551_ADDR_FD_TXBRP                                            0x10CC
#define HPTCAN4551_REG_PROTECTED_FD_TXBRP                                   false
#define HPTCAN4551_DEFAULT_FD_TXBRP                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXBRP                                          0xFFFFFFFF

#define HPTCAN4551_MASK_FD_TXBRP_TRP                                        0xFFFFFFFF // 32 bits

/**
 * Tx Buffer Add Request (TXBAR @ 0x10D0)
 */

#define HPTCAN4551_ADDR_FD_TXBAR                                            0x10D0
#define HPTCAN4551_REG_PROTECTED_FD_TXBAR                                   false
#define HPTCAN4551_DEFAULT_FD_TXBAR                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXBAR                                          0xFFFFFFFF

#define HPTCAN4551_MASK_FD_TXBAR_AR                                         0xFFFFFFFF // 32 bits

/**
 * Tx Buffer Cancellation Request (TXBCR @ 0x10D4)
 */

#define HPTCAN4551_ADDR_FD_TXBCR                                            0x10D4
#define HPTCAN4551_REG_PROTECTED_FD_TXBCR                                   false
#define HPTCAN4551_DEFAULT_FD_TXBCR                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXBCR                                          0xFFFFFFFF

#define HPTCAN4551_MASK_FD_TXBCR_CR                                         0xFFFFFFFF // 32 bits

/**
 * Tx Buffer Transmission Occurred (TXBTO @ 0x10D8)
 */

#define HPTCAN4551_ADDR_FD_TXBTO                                            0x10D8
#define HPTCAN4551_REG_PROTECTED_FD_TXBTO                                   false
#define HPTCAN4551_DEFAULT_FD_TXBTO                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXBTO                                          0xFFFFFFFF

#define HPTCAN4551_MASK_FD_TXBTO_TO                                         0xFFFFFFFF // 32 bits

/**
 * Tx Buffer Cancellation Finished (TXBCF @ 0x10DC)
 */

#define HPTCAN4551_ADDR_FD_TXBCF                                            0x10DC
#define HPTCAN4551_REG_PROTECTED_FD_TXBCF                                   false
#define HPTCAN4551_DEFAULT_FD_TXBCF                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXBCF                                          0xFFFFFFFF

#define HPTCAN4551_MASK_FD_TXBCF_CF                                         0xFFFFFFFF // 32 bits

/**
 * Tx Buffer Transmission Interrupt Enable (TXBTIE @ 0x10E0)
 */

#define HPTCAN4551_ADDR_FD_TXBTIE                                           0x10E0
#define HPTCAN4551_REG_PROTECTED_FD_TXBTIE                                  false
#define HPTCAN4551_DEFAULT_FD_TXBTIE                                        0x00000000
#define HPTCAN4551_USABLE_FD_TXBTIE                                         0xFFFFFFFF

#define HPTCAN4551_MASK_FD_TXBTIE_TIE                                       0xFFFFFFFF // 32 bits

/**
 * Tx Buffer Cancellation Finished Interrupt Enable (TXBCIE @ 0x10E4)
 */

#define HPTCAN4551_ADDR_FD_TXBCIE                                           0x10E4
#define HPTCAN4551_REG_PROTECTED_FD_TXBCIE                                  false
#define HPTCAN4551_DEFAULT_FD_TXBCIE                                        0x00000000
#define HPTCAN4551_USABLE_FD_TXBCIE                                         0xFFFFFFFF

#define HPTCAN4551_MASK_FD_TXBCIE_CFIE                                      0xFFFFFFFF // 32 bits

/**
 * Tx Event FIFO Configuration (TXEFC @ 0x10F0)
 */

#define HPTCAN4551_ADDR_FD_TXEFC                                            0x10F0
#define HPTCAN4551_REG_PROTECTED_FD_TXEFC                                   true
#define HPTCAN4551_DEFAULT_FD_TXEFC                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXEFC                                          0x3F3FFFFF

#define HPTCAN4551_MASK_FD_TXEFC_EFWM                                       0x3F000000 // 6 bits
#define HPTCAN4551_MASK_FD_TXEFC_EFS                                        0x003F0000 // 6 bits
#define HPTCAN4551_MASK_FD_TXEFC_EFSA                                       0x0000FFFF // 16 bits

/**
 * Tx Event FIFO Status (TXEFS @ 0x10F4)
 */

#define HPTCAN4551_ADDR_FD_TXEFS                                            0x10F4
#define HPTCAN4551_REG_PROTECTED_FD_TXEFS                                   false
#define HPTCAN4551_DEFAULT_FD_TXEFS                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXEFS                                          0x031F1F3F

#define HPTCAN4551_MASK_FD_TXEFS_TEFL                                       0x02000000 // 1 bit
#define HPTCAN4551_MASK_FD_TXEFS_EFF                                        0x01000000 // 1 bit
#define HPTCAN4551_MASK_FD_TXEFS_EFPI                                       0x001F0000 // 5 bits
#define HPTCAN4551_MASK_FD_TXEFS_REFGI                                      0x00001F00 // 5 bits
#define HPTCAN4551_MASK_FD_TXEFS_EFFL                                       0x0000003F // 6 bits

#define HPTCAN4551_VAL_FD_TXEFS_TEFL_NOT_LOST                               0b0 // default
#define HPTCAN4551_VAL_FD_TXEFS_TEFL_LOST                                   0b1

#define HPTCAN4551_VAL_FD_TXEFS_EFF_NOT_FULL                                0b0 // default
#define HPTCAN4551_VAL_FD_TXEFS_EFF_FULL                                    0b1

/**
 * Tx Event FIFO Acknowledge (TXEFA @ 0x10F8)
 */

#define HPTCAN4551_ADDR_FD_TXEFA                                            0x10F8
#define HPTCAN4551_REG_PROTECTED_FD_TXEFA                                   false
#define HPTCAN4551_DEFAULT_FD_TXEFA                                         0x00000000
#define HPTCAN4551_USABLE_FD_TXEFA                                          0x0000001F

#define HPTCAN4551_MASK_FD_TXEFA_EFAI                                       0x0000001F // 5 bits

/**
 * MRAM
 */

#define HPTCAN4551_ADDR_MRAM                                                0x8000
#define HPTCAN4551_ADDR_MRAM_FIRST_WORD                                     HPTCAN4551_ADDR_MRAM
#define HPTCAN4551_ADDR_MRAM_LAST_WORD                                      0x87FC
#define HPTCAN4551_ADDR_MRAM_UPPER_BOUND                                    0x87FF
#define HPTCAN4551_SIZE_MRAM_BYTES                                          2048

/**
 * Standard ID Filter Element (SIDFE @ MRAM)
 */

#define HPTCAN4551_LENGTH_MRAM_SIDFE_BYTES                                  4
#define HPTCAN4551_LENGTH_MRAM_SIDFE_WORDS                                  1
#define HPTCAN4551_DEFAULT_MRAM_SIDFE                                       0x00000000
#define HPTCAN4551_USABLE_MRAM_SIDFE                                        0xFFFF87FF

#define HPTCAN4551_MASK_MRAM_SIDFE_SFT                                      0xC0000000 // 2 bits
#define HPTCAN4551_MASK_MRAM_SIDFE_SFEC                                     0x38000000 // 3 bits
#define HPTCAN4551_MASK_MRAM_SIDFE_SFID1                                    0x07FF0000 // 11 bits
#define HPTCAN4551_MASK_MRAM_SIDFE_SSYNC                                    0x00008000 // 1 bit
#define HPTCAN4551_MASK_MRAM_SIDFE_SFID2                                    0x000007FF // 11 bits

#define HPTCAN4551_MASK_STANDARD_ID                                         0x000007FF // 11 bits
#define HPTCAN4551_MASK_EXTENDED_ID                                         0x1FFFFFFF // 29 bits

/**
 * Extended ID Filter Element (XIDFE @ MRAM)
 */

#define HPTCAN4551_LENGTH_MRAM_XIDFE_BYTES                                  8
#define HPTCAN4551_LENGTH_MRAM_XIDFE_WORDS                                  2
#define HPTCAN4551_DEFAULT_MRAM_XIDFE_F0                                    0x00000000
#define HPTCAN4551_DEFAULT_MRAM_XIDFE_F1                                    0x00000000
#define HPTCAN4551_USABLE_MRAM_XIDFE_F0                                     0xFFFFFFFF
#define HPTCAN4551_USABLE_MRAM_XIDFE_F1                                     0xFFFFFFFF

#define HPTCAN4551_MASK_MRAM_XIDFE_F0_EFEC                                  0xE0000000 // 3 bits
#define HPTCAN4551_MASK_MRAM_XIDFE_F0_EFID1                                 0x1FFFFFFF // 29 bits

#define HPTCAN4551_MASK_MRAM_XIDFE_F1_EFT                                   0xC0000000 // 2 bit
#define HPTCAN4551_MASK_MRAM_XIDFE_F1_ESYNC                                 0x20000000 // 1 bit
#define HPTCAN4551_MASK_MRAM_XIDFE_F1_EFID2                                 0x1FFFFFFF // 29 bits

/**
 * RX buffer element
 */

#define HPTCAN4551_MASK_MRAM_RXB_R0_ESI                                     0x80000000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_R0_XTD                                     0x40000000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_R0_RTR                                     0x20000000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_R0_SID                                     0x1FFC0000 // 11 bits
#define HPTCAN4551_MASK_MRAM_RXB_R0_XID                                     0x1FFFFFFF // 29 bits

#define HPTCAN4551_MASK_MRAM_RXB_R1_ANMF                                    0x80000000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_R1_FIDX                                    0x7F000000 // 7 bits
#define HPTCAN4551_MASK_MRAM_RXB_R1_FDF                                     0x00200000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_R1_BRS                                     0x00100000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_R1_DLC                                     0x000F0000 // 4 bits
#define HPTCAN4551_MASK_MRAM_RXB_R1A_RXTS                                   0x0000FFFF // 16 bits
#define HPTCAN4551_MASK_MRAM_RXB_R1B_TSC                                    0x00000010 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_R1B_RXTSP                                  0x0000000F // 4 bits

/**
 * TX buffer element
 */

#define HPTCAN4551_MASK_MRAM_TXB_T0_ESI                                     0x80000000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_T0_XTD                                     0x40000000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_T0_RTR                                     0x20000000 // 1 bit
#define HPTCAN4551_MASK_MRAM_RXB_T0_ID                                      0x1FFFFFFF // 29 bits

#define HPTCAN4551_MASK_MRAM_RXB_T0_ID_SID                                  0x1FFC0000 // 11 bits
#define HPTCAN4551_MASK_MRAM_RXB_T0_ID_XID                                  0x1FFFFFFF // 29 bits

#define HPTCAN4551_MASK_MRAM_TXB_T1_MML                                     0xFF000000 // 8 bits
#define HPTCAN4551_MASK_MRAM_TXB_T1_EFC                                     0x00800000 // 1 bit
#define HPTCAN4551_MASK_MRAM_TXB_T1_TSCE                                    0x00400000 // 1 bit
#define HPTCAN4551_MASK_MRAM_TXB_T1_FDF                                     0x00200000 // 1 bit
#define HPTCAN4551_MASK_MRAM_TXB_T1_BRS                                     0x00100000 // 1 bit
#define HPTCAN4551_MASK_MRAM_TXB_T1_DLC                                     0x000F0000 // 4 bits
#define HPTCAN4551_MASK_MRAM_TXB_T1_MMH                                     0x0000FF00 // 8 bits

#endif // CLASS_HPTCAN4551_REGISTERS_H
