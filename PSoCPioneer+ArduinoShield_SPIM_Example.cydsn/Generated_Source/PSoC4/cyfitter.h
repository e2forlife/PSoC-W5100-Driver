#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include <cydevice_trm.h>

/* ETH_CSN_1 */
#define ETH_CSN_1__0__DM__MASK 0x7000u
#define ETH_CSN_1__0__DM__SHIFT 12
#define ETH_CSN_1__0__DR CYREG_PRT3_DR
#define ETH_CSN_1__0__HSIOM CYREG_HSIOM_PORT_SEL3
#define ETH_CSN_1__0__HSIOM_MASK 0x000F0000u
#define ETH_CSN_1__0__HSIOM_SHIFT 16u
#define ETH_CSN_1__0__INTCFG CYREG_PRT3_INTCFG
#define ETH_CSN_1__0__INTSTAT CYREG_PRT3_INTSTAT
#define ETH_CSN_1__0__MASK 0x10u
#define ETH_CSN_1__0__OUT_SEL CYREG_UDB_PA3_CFG10
#define ETH_CSN_1__0__OUT_SEL_SHIFT 8u
#define ETH_CSN_1__0__OUT_SEL_VAL 1u
#define ETH_CSN_1__0__PA__CFG0 CYREG_UDB_PA3_CFG0
#define ETH_CSN_1__0__PA__CFG1 CYREG_UDB_PA3_CFG1
#define ETH_CSN_1__0__PA__CFG10 CYREG_UDB_PA3_CFG10
#define ETH_CSN_1__0__PA__CFG11 CYREG_UDB_PA3_CFG11
#define ETH_CSN_1__0__PA__CFG12 CYREG_UDB_PA3_CFG12
#define ETH_CSN_1__0__PA__CFG13 CYREG_UDB_PA3_CFG13
#define ETH_CSN_1__0__PA__CFG14 CYREG_UDB_PA3_CFG14
#define ETH_CSN_1__0__PA__CFG2 CYREG_UDB_PA3_CFG2
#define ETH_CSN_1__0__PA__CFG3 CYREG_UDB_PA3_CFG3
#define ETH_CSN_1__0__PA__CFG4 CYREG_UDB_PA3_CFG4
#define ETH_CSN_1__0__PA__CFG5 CYREG_UDB_PA3_CFG5
#define ETH_CSN_1__0__PA__CFG6 CYREG_UDB_PA3_CFG6
#define ETH_CSN_1__0__PA__CFG7 CYREG_UDB_PA3_CFG7
#define ETH_CSN_1__0__PA__CFG8 CYREG_UDB_PA3_CFG8
#define ETH_CSN_1__0__PA__CFG9 CYREG_UDB_PA3_CFG9
#define ETH_CSN_1__0__PC CYREG_PRT3_PC
#define ETH_CSN_1__0__PC2 CYREG_PRT3_PC2
#define ETH_CSN_1__0__PORT 3u
#define ETH_CSN_1__0__PS CYREG_PRT3_PS
#define ETH_CSN_1__0__SHIFT 4
#define ETH_CSN_1__DR CYREG_PRT3_DR
#define ETH_CSN_1__INTCFG CYREG_PRT3_INTCFG
#define ETH_CSN_1__INTSTAT CYREG_PRT3_INTSTAT
#define ETH_CSN_1__MASK 0x10u
#define ETH_CSN_1__PA__CFG0 CYREG_UDB_PA3_CFG0
#define ETH_CSN_1__PA__CFG1 CYREG_UDB_PA3_CFG1
#define ETH_CSN_1__PA__CFG10 CYREG_UDB_PA3_CFG10
#define ETH_CSN_1__PA__CFG11 CYREG_UDB_PA3_CFG11
#define ETH_CSN_1__PA__CFG12 CYREG_UDB_PA3_CFG12
#define ETH_CSN_1__PA__CFG13 CYREG_UDB_PA3_CFG13
#define ETH_CSN_1__PA__CFG14 CYREG_UDB_PA3_CFG14
#define ETH_CSN_1__PA__CFG2 CYREG_UDB_PA3_CFG2
#define ETH_CSN_1__PA__CFG3 CYREG_UDB_PA3_CFG3
#define ETH_CSN_1__PA__CFG4 CYREG_UDB_PA3_CFG4
#define ETH_CSN_1__PA__CFG5 CYREG_UDB_PA3_CFG5
#define ETH_CSN_1__PA__CFG6 CYREG_UDB_PA3_CFG6
#define ETH_CSN_1__PA__CFG7 CYREG_UDB_PA3_CFG7
#define ETH_CSN_1__PA__CFG8 CYREG_UDB_PA3_CFG8
#define ETH_CSN_1__PA__CFG9 CYREG_UDB_PA3_CFG9
#define ETH_CSN_1__PC CYREG_PRT3_PC
#define ETH_CSN_1__PC2 CYREG_PRT3_PC2
#define ETH_CSN_1__PORT 3u
#define ETH_CSN_1__PS CYREG_PRT3_PS
#define ETH_CSN_1__SHIFT 4

/* ETH_MISO_1 */
#define ETH_MISO_1__0__DM__MASK 0x38u
#define ETH_MISO_1__0__DM__SHIFT 3
#define ETH_MISO_1__0__DR CYREG_PRT3_DR
#define ETH_MISO_1__0__HSIOM CYREG_HSIOM_PORT_SEL3
#define ETH_MISO_1__0__HSIOM_MASK 0x000000F0u
#define ETH_MISO_1__0__HSIOM_SHIFT 4u
#define ETH_MISO_1__0__INTCFG CYREG_PRT3_INTCFG
#define ETH_MISO_1__0__INTSTAT CYREG_PRT3_INTSTAT
#define ETH_MISO_1__0__MASK 0x02u
#define ETH_MISO_1__0__PA__CFG0 CYREG_UDB_PA3_CFG0
#define ETH_MISO_1__0__PA__CFG1 CYREG_UDB_PA3_CFG1
#define ETH_MISO_1__0__PA__CFG10 CYREG_UDB_PA3_CFG10
#define ETH_MISO_1__0__PA__CFG11 CYREG_UDB_PA3_CFG11
#define ETH_MISO_1__0__PA__CFG12 CYREG_UDB_PA3_CFG12
#define ETH_MISO_1__0__PA__CFG13 CYREG_UDB_PA3_CFG13
#define ETH_MISO_1__0__PA__CFG14 CYREG_UDB_PA3_CFG14
#define ETH_MISO_1__0__PA__CFG2 CYREG_UDB_PA3_CFG2
#define ETH_MISO_1__0__PA__CFG3 CYREG_UDB_PA3_CFG3
#define ETH_MISO_1__0__PA__CFG4 CYREG_UDB_PA3_CFG4
#define ETH_MISO_1__0__PA__CFG5 CYREG_UDB_PA3_CFG5
#define ETH_MISO_1__0__PA__CFG6 CYREG_UDB_PA3_CFG6
#define ETH_MISO_1__0__PA__CFG7 CYREG_UDB_PA3_CFG7
#define ETH_MISO_1__0__PA__CFG8 CYREG_UDB_PA3_CFG8
#define ETH_MISO_1__0__PA__CFG9 CYREG_UDB_PA3_CFG9
#define ETH_MISO_1__0__PC CYREG_PRT3_PC
#define ETH_MISO_1__0__PC2 CYREG_PRT3_PC2
#define ETH_MISO_1__0__PORT 3u
#define ETH_MISO_1__0__PS CYREG_PRT3_PS
#define ETH_MISO_1__0__SHIFT 1
#define ETH_MISO_1__DR CYREG_PRT3_DR
#define ETH_MISO_1__INTCFG CYREG_PRT3_INTCFG
#define ETH_MISO_1__INTSTAT CYREG_PRT3_INTSTAT
#define ETH_MISO_1__MASK 0x02u
#define ETH_MISO_1__PA__CFG0 CYREG_UDB_PA3_CFG0
#define ETH_MISO_1__PA__CFG1 CYREG_UDB_PA3_CFG1
#define ETH_MISO_1__PA__CFG10 CYREG_UDB_PA3_CFG10
#define ETH_MISO_1__PA__CFG11 CYREG_UDB_PA3_CFG11
#define ETH_MISO_1__PA__CFG12 CYREG_UDB_PA3_CFG12
#define ETH_MISO_1__PA__CFG13 CYREG_UDB_PA3_CFG13
#define ETH_MISO_1__PA__CFG14 CYREG_UDB_PA3_CFG14
#define ETH_MISO_1__PA__CFG2 CYREG_UDB_PA3_CFG2
#define ETH_MISO_1__PA__CFG3 CYREG_UDB_PA3_CFG3
#define ETH_MISO_1__PA__CFG4 CYREG_UDB_PA3_CFG4
#define ETH_MISO_1__PA__CFG5 CYREG_UDB_PA3_CFG5
#define ETH_MISO_1__PA__CFG6 CYREG_UDB_PA3_CFG6
#define ETH_MISO_1__PA__CFG7 CYREG_UDB_PA3_CFG7
#define ETH_MISO_1__PA__CFG8 CYREG_UDB_PA3_CFG8
#define ETH_MISO_1__PA__CFG9 CYREG_UDB_PA3_CFG9
#define ETH_MISO_1__PC CYREG_PRT3_PC
#define ETH_MISO_1__PC2 CYREG_PRT3_PC2
#define ETH_MISO_1__PORT 3u
#define ETH_MISO_1__PS CYREG_PRT3_PS
#define ETH_MISO_1__SHIFT 1

/* ETH_MOSI_1 */
#define ETH_MOSI_1__0__DM__MASK 0x07u
#define ETH_MOSI_1__0__DM__SHIFT 0
#define ETH_MOSI_1__0__DR CYREG_PRT3_DR
#define ETH_MOSI_1__0__HSIOM CYREG_HSIOM_PORT_SEL3
#define ETH_MOSI_1__0__HSIOM_MASK 0x0000000Fu
#define ETH_MOSI_1__0__HSIOM_SHIFT 0u
#define ETH_MOSI_1__0__INTCFG CYREG_PRT3_INTCFG
#define ETH_MOSI_1__0__INTSTAT CYREG_PRT3_INTSTAT
#define ETH_MOSI_1__0__MASK 0x01u
#define ETH_MOSI_1__0__OUT_SEL CYREG_UDB_PA3_CFG10
#define ETH_MOSI_1__0__OUT_SEL_SHIFT 0u
#define ETH_MOSI_1__0__OUT_SEL_VAL 1u
#define ETH_MOSI_1__0__PA__CFG0 CYREG_UDB_PA3_CFG0
#define ETH_MOSI_1__0__PA__CFG1 CYREG_UDB_PA3_CFG1
#define ETH_MOSI_1__0__PA__CFG10 CYREG_UDB_PA3_CFG10
#define ETH_MOSI_1__0__PA__CFG11 CYREG_UDB_PA3_CFG11
#define ETH_MOSI_1__0__PA__CFG12 CYREG_UDB_PA3_CFG12
#define ETH_MOSI_1__0__PA__CFG13 CYREG_UDB_PA3_CFG13
#define ETH_MOSI_1__0__PA__CFG14 CYREG_UDB_PA3_CFG14
#define ETH_MOSI_1__0__PA__CFG2 CYREG_UDB_PA3_CFG2
#define ETH_MOSI_1__0__PA__CFG3 CYREG_UDB_PA3_CFG3
#define ETH_MOSI_1__0__PA__CFG4 CYREG_UDB_PA3_CFG4
#define ETH_MOSI_1__0__PA__CFG5 CYREG_UDB_PA3_CFG5
#define ETH_MOSI_1__0__PA__CFG6 CYREG_UDB_PA3_CFG6
#define ETH_MOSI_1__0__PA__CFG7 CYREG_UDB_PA3_CFG7
#define ETH_MOSI_1__0__PA__CFG8 CYREG_UDB_PA3_CFG8
#define ETH_MOSI_1__0__PA__CFG9 CYREG_UDB_PA3_CFG9
#define ETH_MOSI_1__0__PC CYREG_PRT3_PC
#define ETH_MOSI_1__0__PC2 CYREG_PRT3_PC2
#define ETH_MOSI_1__0__PORT 3u
#define ETH_MOSI_1__0__PS CYREG_PRT3_PS
#define ETH_MOSI_1__0__SHIFT 0
#define ETH_MOSI_1__DR CYREG_PRT3_DR
#define ETH_MOSI_1__INTCFG CYREG_PRT3_INTCFG
#define ETH_MOSI_1__INTSTAT CYREG_PRT3_INTSTAT
#define ETH_MOSI_1__MASK 0x01u
#define ETH_MOSI_1__PA__CFG0 CYREG_UDB_PA3_CFG0
#define ETH_MOSI_1__PA__CFG1 CYREG_UDB_PA3_CFG1
#define ETH_MOSI_1__PA__CFG10 CYREG_UDB_PA3_CFG10
#define ETH_MOSI_1__PA__CFG11 CYREG_UDB_PA3_CFG11
#define ETH_MOSI_1__PA__CFG12 CYREG_UDB_PA3_CFG12
#define ETH_MOSI_1__PA__CFG13 CYREG_UDB_PA3_CFG13
#define ETH_MOSI_1__PA__CFG14 CYREG_UDB_PA3_CFG14
#define ETH_MOSI_1__PA__CFG2 CYREG_UDB_PA3_CFG2
#define ETH_MOSI_1__PA__CFG3 CYREG_UDB_PA3_CFG3
#define ETH_MOSI_1__PA__CFG4 CYREG_UDB_PA3_CFG4
#define ETH_MOSI_1__PA__CFG5 CYREG_UDB_PA3_CFG5
#define ETH_MOSI_1__PA__CFG6 CYREG_UDB_PA3_CFG6
#define ETH_MOSI_1__PA__CFG7 CYREG_UDB_PA3_CFG7
#define ETH_MOSI_1__PA__CFG8 CYREG_UDB_PA3_CFG8
#define ETH_MOSI_1__PA__CFG9 CYREG_UDB_PA3_CFG9
#define ETH_MOSI_1__PC CYREG_PRT3_PC
#define ETH_MOSI_1__PC2 CYREG_PRT3_PC2
#define ETH_MOSI_1__PORT 3u
#define ETH_MOSI_1__PS CYREG_PRT3_PS
#define ETH_MOSI_1__SHIFT 0

/* ETH_SCLK_1 */
#define ETH_SCLK_1__0__DM__MASK 0x1C0000u
#define ETH_SCLK_1__0__DM__SHIFT 18
#define ETH_SCLK_1__0__DR CYREG_PRT0_DR
#define ETH_SCLK_1__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define ETH_SCLK_1__0__HSIOM_MASK 0x0F000000u
#define ETH_SCLK_1__0__HSIOM_SHIFT 24u
#define ETH_SCLK_1__0__INTCFG CYREG_PRT0_INTCFG
#define ETH_SCLK_1__0__INTSTAT CYREG_PRT0_INTSTAT
#define ETH_SCLK_1__0__MASK 0x40u
#define ETH_SCLK_1__0__OUT_SEL CYREG_UDB_PA0_CFG10
#define ETH_SCLK_1__0__OUT_SEL_SHIFT 12u
#define ETH_SCLK_1__0__OUT_SEL_VAL 1u
#define ETH_SCLK_1__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define ETH_SCLK_1__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define ETH_SCLK_1__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define ETH_SCLK_1__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define ETH_SCLK_1__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define ETH_SCLK_1__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define ETH_SCLK_1__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define ETH_SCLK_1__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define ETH_SCLK_1__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define ETH_SCLK_1__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define ETH_SCLK_1__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define ETH_SCLK_1__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define ETH_SCLK_1__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define ETH_SCLK_1__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define ETH_SCLK_1__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define ETH_SCLK_1__0__PC CYREG_PRT0_PC
#define ETH_SCLK_1__0__PC2 CYREG_PRT0_PC2
#define ETH_SCLK_1__0__PORT 0u
#define ETH_SCLK_1__0__PS CYREG_PRT0_PS
#define ETH_SCLK_1__0__SHIFT 6
#define ETH_SCLK_1__DR CYREG_PRT0_DR
#define ETH_SCLK_1__INTCFG CYREG_PRT0_INTCFG
#define ETH_SCLK_1__INTSTAT CYREG_PRT0_INTSTAT
#define ETH_SCLK_1__MASK 0x40u
#define ETH_SCLK_1__PA__CFG0 CYREG_UDB_PA0_CFG0
#define ETH_SCLK_1__PA__CFG1 CYREG_UDB_PA0_CFG1
#define ETH_SCLK_1__PA__CFG10 CYREG_UDB_PA0_CFG10
#define ETH_SCLK_1__PA__CFG11 CYREG_UDB_PA0_CFG11
#define ETH_SCLK_1__PA__CFG12 CYREG_UDB_PA0_CFG12
#define ETH_SCLK_1__PA__CFG13 CYREG_UDB_PA0_CFG13
#define ETH_SCLK_1__PA__CFG14 CYREG_UDB_PA0_CFG14
#define ETH_SCLK_1__PA__CFG2 CYREG_UDB_PA0_CFG2
#define ETH_SCLK_1__PA__CFG3 CYREG_UDB_PA0_CFG3
#define ETH_SCLK_1__PA__CFG4 CYREG_UDB_PA0_CFG4
#define ETH_SCLK_1__PA__CFG5 CYREG_UDB_PA0_CFG5
#define ETH_SCLK_1__PA__CFG6 CYREG_UDB_PA0_CFG6
#define ETH_SCLK_1__PA__CFG7 CYREG_UDB_PA0_CFG7
#define ETH_SCLK_1__PA__CFG8 CYREG_UDB_PA0_CFG8
#define ETH_SCLK_1__PA__CFG9 CYREG_UDB_PA0_CFG9
#define ETH_SCLK_1__PC CYREG_PRT0_PC
#define ETH_SCLK_1__PC2 CYREG_PRT0_PC2
#define ETH_SCLK_1__PORT 0u
#define ETH_SCLK_1__PS CYREG_PRT0_PS
#define ETH_SCLK_1__SHIFT 6

/* RED */
#define RED__0__DM__MASK 0x1C0000u
#define RED__0__DM__SHIFT 18
#define RED__0__DR CYREG_PRT1_DR
#define RED__0__HSIOM CYREG_HSIOM_PORT_SEL1
#define RED__0__HSIOM_MASK 0x0F000000u
#define RED__0__HSIOM_SHIFT 24u
#define RED__0__INTCFG CYREG_PRT1_INTCFG
#define RED__0__INTSTAT CYREG_PRT1_INTSTAT
#define RED__0__MASK 0x40u
#define RED__0__PA__CFG0 CYREG_UDB_PA1_CFG0
#define RED__0__PA__CFG1 CYREG_UDB_PA1_CFG1
#define RED__0__PA__CFG10 CYREG_UDB_PA1_CFG10
#define RED__0__PA__CFG11 CYREG_UDB_PA1_CFG11
#define RED__0__PA__CFG12 CYREG_UDB_PA1_CFG12
#define RED__0__PA__CFG13 CYREG_UDB_PA1_CFG13
#define RED__0__PA__CFG14 CYREG_UDB_PA1_CFG14
#define RED__0__PA__CFG2 CYREG_UDB_PA1_CFG2
#define RED__0__PA__CFG3 CYREG_UDB_PA1_CFG3
#define RED__0__PA__CFG4 CYREG_UDB_PA1_CFG4
#define RED__0__PA__CFG5 CYREG_UDB_PA1_CFG5
#define RED__0__PA__CFG6 CYREG_UDB_PA1_CFG6
#define RED__0__PA__CFG7 CYREG_UDB_PA1_CFG7
#define RED__0__PA__CFG8 CYREG_UDB_PA1_CFG8
#define RED__0__PA__CFG9 CYREG_UDB_PA1_CFG9
#define RED__0__PC CYREG_PRT1_PC
#define RED__0__PC2 CYREG_PRT1_PC2
#define RED__0__PORT 1u
#define RED__0__PS CYREG_PRT1_PS
#define RED__0__SHIFT 6
#define RED__DR CYREG_PRT1_DR
#define RED__INTCFG CYREG_PRT1_INTCFG
#define RED__INTSTAT CYREG_PRT1_INTSTAT
#define RED__MASK 0x40u
#define RED__PA__CFG0 CYREG_UDB_PA1_CFG0
#define RED__PA__CFG1 CYREG_UDB_PA1_CFG1
#define RED__PA__CFG10 CYREG_UDB_PA1_CFG10
#define RED__PA__CFG11 CYREG_UDB_PA1_CFG11
#define RED__PA__CFG12 CYREG_UDB_PA1_CFG12
#define RED__PA__CFG13 CYREG_UDB_PA1_CFG13
#define RED__PA__CFG14 CYREG_UDB_PA1_CFG14
#define RED__PA__CFG2 CYREG_UDB_PA1_CFG2
#define RED__PA__CFG3 CYREG_UDB_PA1_CFG3
#define RED__PA__CFG4 CYREG_UDB_PA1_CFG4
#define RED__PA__CFG5 CYREG_UDB_PA1_CFG5
#define RED__PA__CFG6 CYREG_UDB_PA1_CFG6
#define RED__PA__CFG7 CYREG_UDB_PA1_CFG7
#define RED__PA__CFG8 CYREG_UDB_PA1_CFG8
#define RED__PA__CFG9 CYREG_UDB_PA1_CFG9
#define RED__PC CYREG_PRT1_PC
#define RED__PC2 CYREG_PRT1_PC2
#define RED__PORT 1u
#define RED__PS CYREG_PRT1_PS
#define RED__SHIFT 6

/* BLUE */
#define BLUE__0__DM__MASK 0xE00u
#define BLUE__0__DM__SHIFT 9
#define BLUE__0__DR CYREG_PRT0_DR
#define BLUE__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define BLUE__0__HSIOM_MASK 0x0000F000u
#define BLUE__0__HSIOM_SHIFT 12u
#define BLUE__0__INTCFG CYREG_PRT0_INTCFG
#define BLUE__0__INTSTAT CYREG_PRT0_INTSTAT
#define BLUE__0__MASK 0x08u
#define BLUE__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define BLUE__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define BLUE__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define BLUE__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define BLUE__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define BLUE__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define BLUE__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define BLUE__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define BLUE__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define BLUE__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define BLUE__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define BLUE__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define BLUE__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define BLUE__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define BLUE__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define BLUE__0__PC CYREG_PRT0_PC
#define BLUE__0__PC2 CYREG_PRT0_PC2
#define BLUE__0__PORT 0u
#define BLUE__0__PS CYREG_PRT0_PS
#define BLUE__0__SHIFT 3
#define BLUE__DR CYREG_PRT0_DR
#define BLUE__INTCFG CYREG_PRT0_INTCFG
#define BLUE__INTSTAT CYREG_PRT0_INTSTAT
#define BLUE__MASK 0x08u
#define BLUE__PA__CFG0 CYREG_UDB_PA0_CFG0
#define BLUE__PA__CFG1 CYREG_UDB_PA0_CFG1
#define BLUE__PA__CFG10 CYREG_UDB_PA0_CFG10
#define BLUE__PA__CFG11 CYREG_UDB_PA0_CFG11
#define BLUE__PA__CFG12 CYREG_UDB_PA0_CFG12
#define BLUE__PA__CFG13 CYREG_UDB_PA0_CFG13
#define BLUE__PA__CFG14 CYREG_UDB_PA0_CFG14
#define BLUE__PA__CFG2 CYREG_UDB_PA0_CFG2
#define BLUE__PA__CFG3 CYREG_UDB_PA0_CFG3
#define BLUE__PA__CFG4 CYREG_UDB_PA0_CFG4
#define BLUE__PA__CFG5 CYREG_UDB_PA0_CFG5
#define BLUE__PA__CFG6 CYREG_UDB_PA0_CFG6
#define BLUE__PA__CFG7 CYREG_UDB_PA0_CFG7
#define BLUE__PA__CFG8 CYREG_UDB_PA0_CFG8
#define BLUE__PA__CFG9 CYREG_UDB_PA0_CFG9
#define BLUE__PC CYREG_PRT0_PC
#define BLUE__PC2 CYREG_PRT0_PC2
#define BLUE__PORT 0u
#define BLUE__PS CYREG_PRT0_PS
#define BLUE__SHIFT 3

/* SDCS */
#define SDCS__0__DM__MASK 0x07u
#define SDCS__0__DM__SHIFT 0
#define SDCS__0__DR CYREG_PRT0_DR
#define SDCS__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define SDCS__0__HSIOM_MASK 0x0000000Fu
#define SDCS__0__HSIOM_SHIFT 0u
#define SDCS__0__INTCFG CYREG_PRT0_INTCFG
#define SDCS__0__INTSTAT CYREG_PRT0_INTSTAT
#define SDCS__0__MASK 0x01u
#define SDCS__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define SDCS__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define SDCS__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define SDCS__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define SDCS__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define SDCS__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define SDCS__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define SDCS__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define SDCS__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define SDCS__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define SDCS__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define SDCS__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define SDCS__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define SDCS__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define SDCS__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define SDCS__0__PC CYREG_PRT0_PC
#define SDCS__0__PC2 CYREG_PRT0_PC2
#define SDCS__0__PORT 0u
#define SDCS__0__PS CYREG_PRT0_PS
#define SDCS__0__SHIFT 0
#define SDCS__DR CYREG_PRT0_DR
#define SDCS__INTCFG CYREG_PRT0_INTCFG
#define SDCS__INTSTAT CYREG_PRT0_INTSTAT
#define SDCS__MASK 0x01u
#define SDCS__PA__CFG0 CYREG_UDB_PA0_CFG0
#define SDCS__PA__CFG1 CYREG_UDB_PA0_CFG1
#define SDCS__PA__CFG10 CYREG_UDB_PA0_CFG10
#define SDCS__PA__CFG11 CYREG_UDB_PA0_CFG11
#define SDCS__PA__CFG12 CYREG_UDB_PA0_CFG12
#define SDCS__PA__CFG13 CYREG_UDB_PA0_CFG13
#define SDCS__PA__CFG14 CYREG_UDB_PA0_CFG14
#define SDCS__PA__CFG2 CYREG_UDB_PA0_CFG2
#define SDCS__PA__CFG3 CYREG_UDB_PA0_CFG3
#define SDCS__PA__CFG4 CYREG_UDB_PA0_CFG4
#define SDCS__PA__CFG5 CYREG_UDB_PA0_CFG5
#define SDCS__PA__CFG6 CYREG_UDB_PA0_CFG6
#define SDCS__PA__CFG7 CYREG_UDB_PA0_CFG7
#define SDCS__PA__CFG8 CYREG_UDB_PA0_CFG8
#define SDCS__PA__CFG9 CYREG_UDB_PA0_CFG9
#define SDCS__PC CYREG_PRT0_PC
#define SDCS__PC2 CYREG_PRT0_PC2
#define SDCS__PORT 0u
#define SDCS__PS CYREG_PRT0_PS
#define SDCS__SHIFT 0

/* SPI0_BSPIM */
#define SPI0_BSPIM_BitCounter__CONTROL_AUX_CTL_REG CYREG_UDB_W8_ACTL_03
#define SPI0_BSPIM_BitCounter__CONTROL_REG CYREG_UDB_W8_CTL_03
#define SPI0_BSPIM_BitCounter__CONTROL_ST_REG CYREG_UDB_CAT16_CTL_ST_03
#define SPI0_BSPIM_BitCounter__COUNT_REG CYREG_UDB_W8_CTL_03
#define SPI0_BSPIM_BitCounter__COUNT_ST_REG CYREG_UDB_CAT16_CTL_ST_03
#define SPI0_BSPIM_BitCounter__MASK_CTL_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_03
#define SPI0_BSPIM_BitCounter__PER_CTL_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_03
#define SPI0_BSPIM_BitCounter__PERIOD_REG CYREG_UDB_W8_MSK_03
#define SPI0_BSPIM_BitCounter_ST__MASK_REG CYREG_UDB_W8_MSK_03
#define SPI0_BSPIM_BitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_03
#define SPI0_BSPIM_BitCounter_ST__PER_ST_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_03
#define SPI0_BSPIM_BitCounter_ST__STATUS_AUX_CTL_REG CYREG_UDB_W8_ACTL_03
#define SPI0_BSPIM_BitCounter_ST__STATUS_CNT_REG CYREG_UDB_CAT16_CTL_ST_03
#define SPI0_BSPIM_BitCounter_ST__STATUS_CONTROL_REG CYREG_UDB_CAT16_CTL_ST_03
#define SPI0_BSPIM_BitCounter_ST__STATUS_REG CYREG_UDB_W8_ST_03
#define SPI0_BSPIM_RxStsReg__16BIT_STATUS_AUX_CTL_REG CYREG_UDB_W16_ACTL_00
#define SPI0_BSPIM_RxStsReg__16BIT_STATUS_REG CYREG_UDB_W16_ST_00
#define SPI0_BSPIM_RxStsReg__32BIT_MASK_REG CYREG_UDB_W32_MSK_00
#define SPI0_BSPIM_RxStsReg__32BIT_STATUS_AUX_CTL_REG CYREG_UDB_W32_ACTL_00
#define SPI0_BSPIM_RxStsReg__32BIT_STATUS_REG CYREG_UDB_W32_ST_00
#define SPI0_BSPIM_RxStsReg__4__MASK 0x10u
#define SPI0_BSPIM_RxStsReg__4__POS 4
#define SPI0_BSPIM_RxStsReg__5__MASK 0x20u
#define SPI0_BSPIM_RxStsReg__5__POS 5
#define SPI0_BSPIM_RxStsReg__6__MASK 0x40u
#define SPI0_BSPIM_RxStsReg__6__POS 6
#define SPI0_BSPIM_RxStsReg__MASK 0x70u
#define SPI0_BSPIM_RxStsReg__MASK_REG CYREG_UDB_W8_MSK_00
#define SPI0_BSPIM_RxStsReg__MASK_ST_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define SPI0_BSPIM_RxStsReg__PER_ST_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define SPI0_BSPIM_RxStsReg__STATUS_AUX_CTL_REG CYREG_UDB_W8_ACTL_00
#define SPI0_BSPIM_RxStsReg__STATUS_CNT_REG CYREG_UDB_CAT16_CTL_ST_00
#define SPI0_BSPIM_RxStsReg__STATUS_CONTROL_REG CYREG_UDB_CAT16_CTL_ST_00
#define SPI0_BSPIM_RxStsReg__STATUS_REG CYREG_UDB_W8_ST_00
#define SPI0_BSPIM_sR8_Dp_u0__A0_A1_REG CYREG_UDB_CAT16_A_03
#define SPI0_BSPIM_sR8_Dp_u0__A0_REG CYREG_UDB_W8_A0_03
#define SPI0_BSPIM_sR8_Dp_u0__A1_REG CYREG_UDB_W8_A1_03
#define SPI0_BSPIM_sR8_Dp_u0__D0_D1_REG CYREG_UDB_CAT16_D_03
#define SPI0_BSPIM_sR8_Dp_u0__D0_REG CYREG_UDB_W8_D0_03
#define SPI0_BSPIM_sR8_Dp_u0__D1_REG CYREG_UDB_W8_D1_03
#define SPI0_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG CYREG_UDB_W8_ACTL_03
#define SPI0_BSPIM_sR8_Dp_u0__F0_F1_REG CYREG_UDB_CAT16_F_03
#define SPI0_BSPIM_sR8_Dp_u0__F0_REG CYREG_UDB_W8_F0_03
#define SPI0_BSPIM_sR8_Dp_u0__F1_REG CYREG_UDB_W8_F1_03
#define SPI0_BSPIM_sR8_Dp_u0__MSK_DP_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_03
#define SPI0_BSPIM_sR8_Dp_u0__PER_DP_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_03
#define SPI0_BSPIM_TxStsReg__0__MASK 0x01u
#define SPI0_BSPIM_TxStsReg__0__POS 0
#define SPI0_BSPIM_TxStsReg__1__MASK 0x02u
#define SPI0_BSPIM_TxStsReg__1__POS 1
#define SPI0_BSPIM_TxStsReg__16BIT_STATUS_AUX_CTL_REG CYREG_UDB_W16_ACTL_01
#define SPI0_BSPIM_TxStsReg__16BIT_STATUS_REG CYREG_UDB_W16_ST_01
#define SPI0_BSPIM_TxStsReg__2__MASK 0x04u
#define SPI0_BSPIM_TxStsReg__2__POS 2
#define SPI0_BSPIM_TxStsReg__3__MASK 0x08u
#define SPI0_BSPIM_TxStsReg__3__POS 3
#define SPI0_BSPIM_TxStsReg__4__MASK 0x10u
#define SPI0_BSPIM_TxStsReg__4__POS 4
#define SPI0_BSPIM_TxStsReg__MASK 0x1Fu
#define SPI0_BSPIM_TxStsReg__MASK_REG CYREG_UDB_W8_MSK_01
#define SPI0_BSPIM_TxStsReg__STATUS_AUX_CTL_REG CYREG_UDB_W8_ACTL_01
#define SPI0_BSPIM_TxStsReg__STATUS_REG CYREG_UDB_W8_ST_01

/* SPI0_IntClock */
#define SPI0_IntClock__DIVIDER_MASK 0x0000FFFFu
#define SPI0_IntClock__ENABLE CYREG_CLK_DIVIDER_A00
#define SPI0_IntClock__ENABLE_MASK 0x80000000u
#define SPI0_IntClock__MASK 0x80000000u
#define SPI0_IntClock__REGISTER CYREG_CLK_DIVIDER_A00

/* SSCR */
#define SSCR_Sync_ctrl_reg__0__MASK 0x01u
#define SSCR_Sync_ctrl_reg__0__POS 0
#define SSCR_Sync_ctrl_reg__16BIT_CONTROL_AUX_CTL_REG CYREG_UDB_W16_ACTL_00
#define SSCR_Sync_ctrl_reg__16BIT_CONTROL_CONTROL_REG CYREG_UDB_W16_CTL_00
#define SSCR_Sync_ctrl_reg__16BIT_CONTROL_COUNT_REG CYREG_UDB_W16_CTL_00
#define SSCR_Sync_ctrl_reg__16BIT_COUNT_CONTROL_REG CYREG_UDB_W16_CTL_00
#define SSCR_Sync_ctrl_reg__16BIT_COUNT_COUNT_REG CYREG_UDB_W16_CTL_00
#define SSCR_Sync_ctrl_reg__16BIT_MASK_MASK_REG CYREG_UDB_W16_MSK_00
#define SSCR_Sync_ctrl_reg__16BIT_MASK_PERIOD_REG CYREG_UDB_W16_MSK_00
#define SSCR_Sync_ctrl_reg__16BIT_PERIOD_MASK_REG CYREG_UDB_W16_MSK_00
#define SSCR_Sync_ctrl_reg__16BIT_PERIOD_PERIOD_REG CYREG_UDB_W16_MSK_00
#define SSCR_Sync_ctrl_reg__32BIT_CONTROL_AUX_CTL_REG CYREG_UDB_W32_ACTL_00
#define SSCR_Sync_ctrl_reg__32BIT_CONTROL_REG CYREG_UDB_W32_CTL_00
#define SSCR_Sync_ctrl_reg__32BIT_COUNT_REG CYREG_UDB_W32_CTL_00
#define SSCR_Sync_ctrl_reg__32BIT_PERIOD_REG CYREG_UDB_W32_MSK_00
#define SSCR_Sync_ctrl_reg__CONTROL_AUX_CTL_REG CYREG_UDB_W8_ACTL_00
#define SSCR_Sync_ctrl_reg__CONTROL_REG CYREG_UDB_W8_CTL_00
#define SSCR_Sync_ctrl_reg__CONTROL_ST_REG CYREG_UDB_CAT16_CTL_ST_00
#define SSCR_Sync_ctrl_reg__COUNT_REG CYREG_UDB_W8_CTL_00
#define SSCR_Sync_ctrl_reg__COUNT_ST_REG CYREG_UDB_CAT16_CTL_ST_00
#define SSCR_Sync_ctrl_reg__MASK 0x01u
#define SSCR_Sync_ctrl_reg__MASK_CTL_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define SSCR_Sync_ctrl_reg__PER_CTL_AUX_CTL_REG CYREG_UDB_CAT16_ACTL_MSK_00
#define SSCR_Sync_ctrl_reg__PERIOD_REG CYREG_UDB_W8_MSK_00

/* GREEN */
#define GREEN__0__DM__MASK 0x1C0u
#define GREEN__0__DM__SHIFT 6
#define GREEN__0__DR CYREG_PRT0_DR
#define GREEN__0__HSIOM CYREG_HSIOM_PORT_SEL0
#define GREEN__0__HSIOM_MASK 0x00000F00u
#define GREEN__0__HSIOM_SHIFT 8u
#define GREEN__0__INTCFG CYREG_PRT0_INTCFG
#define GREEN__0__INTSTAT CYREG_PRT0_INTSTAT
#define GREEN__0__MASK 0x04u
#define GREEN__0__PA__CFG0 CYREG_UDB_PA0_CFG0
#define GREEN__0__PA__CFG1 CYREG_UDB_PA0_CFG1
#define GREEN__0__PA__CFG10 CYREG_UDB_PA0_CFG10
#define GREEN__0__PA__CFG11 CYREG_UDB_PA0_CFG11
#define GREEN__0__PA__CFG12 CYREG_UDB_PA0_CFG12
#define GREEN__0__PA__CFG13 CYREG_UDB_PA0_CFG13
#define GREEN__0__PA__CFG14 CYREG_UDB_PA0_CFG14
#define GREEN__0__PA__CFG2 CYREG_UDB_PA0_CFG2
#define GREEN__0__PA__CFG3 CYREG_UDB_PA0_CFG3
#define GREEN__0__PA__CFG4 CYREG_UDB_PA0_CFG4
#define GREEN__0__PA__CFG5 CYREG_UDB_PA0_CFG5
#define GREEN__0__PA__CFG6 CYREG_UDB_PA0_CFG6
#define GREEN__0__PA__CFG7 CYREG_UDB_PA0_CFG7
#define GREEN__0__PA__CFG8 CYREG_UDB_PA0_CFG8
#define GREEN__0__PA__CFG9 CYREG_UDB_PA0_CFG9
#define GREEN__0__PC CYREG_PRT0_PC
#define GREEN__0__PC2 CYREG_PRT0_PC2
#define GREEN__0__PORT 0u
#define GREEN__0__PS CYREG_PRT0_PS
#define GREEN__0__SHIFT 2
#define GREEN__DR CYREG_PRT0_DR
#define GREEN__INTCFG CYREG_PRT0_INTCFG
#define GREEN__INTSTAT CYREG_PRT0_INTSTAT
#define GREEN__MASK 0x04u
#define GREEN__PA__CFG0 CYREG_UDB_PA0_CFG0
#define GREEN__PA__CFG1 CYREG_UDB_PA0_CFG1
#define GREEN__PA__CFG10 CYREG_UDB_PA0_CFG10
#define GREEN__PA__CFG11 CYREG_UDB_PA0_CFG11
#define GREEN__PA__CFG12 CYREG_UDB_PA0_CFG12
#define GREEN__PA__CFG13 CYREG_UDB_PA0_CFG13
#define GREEN__PA__CFG14 CYREG_UDB_PA0_CFG14
#define GREEN__PA__CFG2 CYREG_UDB_PA0_CFG2
#define GREEN__PA__CFG3 CYREG_UDB_PA0_CFG3
#define GREEN__PA__CFG4 CYREG_UDB_PA0_CFG4
#define GREEN__PA__CFG5 CYREG_UDB_PA0_CFG5
#define GREEN__PA__CFG6 CYREG_UDB_PA0_CFG6
#define GREEN__PA__CFG7 CYREG_UDB_PA0_CFG7
#define GREEN__PA__CFG8 CYREG_UDB_PA0_CFG8
#define GREEN__PA__CFG9 CYREG_UDB_PA0_CFG9
#define GREEN__PC CYREG_PRT0_PC
#define GREEN__PC2 CYREG_PRT0_PC2
#define GREEN__PORT 0u
#define GREEN__PS CYREG_PRT0_PS
#define GREEN__SHIFT 2

/* Miscellaneous */
#define CYDEV_BCLK__HFCLK__HZ 24000000U
#define CYDEV_BCLK__HFCLK__KHZ 24000U
#define CYDEV_BCLK__HFCLK__MHZ 24U
#define CYDEV_BCLK__SYSCLK__HZ 24000000U
#define CYDEV_BCLK__SYSCLK__KHZ 24000U
#define CYDEV_BCLK__SYSCLK__MHZ 24U
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 4u
#define CYDEV_CHIP_DIE_PSOC4A 2u
#define CYDEV_CHIP_DIE_PSOC5LP 5u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC4
#define CYDEV_CHIP_JTAG_ID 0x04C81193u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 2u
#define CYDEV_CHIP_MEMBER_4D 3u
#define CYDEV_CHIP_MEMBER_5A 4u
#define CYDEV_CHIP_MEMBER_5B 5u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_4A
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4D_ES0 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_4A_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_READ_ACCELERATOR 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_PROTECT_KILL 4
#define CYDEV_DEBUG_PROTECT_OPEN 1
#define CYDEV_DEBUG_PROTECT CYDEV_DEBUG_PROTECT_OPEN
#define CYDEV_DEBUG_PROTECT_PROTECTED 2
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_HEAP_SIZE 0x0100
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_STACK_SIZE 0x0400
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 1
#define CYDEV_VDDA 3.3
#define CYDEV_VDDA_MV 3300
#define CYDEV_VDDD 3.3
#define CYDEV_VDDD_MV 3300
#define CYIPBLOCK_M0S8_CTBM_VERSION 0
#define CYIPBLOCK_m0s8cpuss_VERSION 0
#define CYIPBLOCK_m0s8csd_VERSION 0
#define CYIPBLOCK_m0s8gpio2_VERSION 0
#define CYIPBLOCK_m0s8hsiom4a_VERSION 0
#define CYIPBLOCK_m0s8lcd_VERSION 0
#define CYIPBLOCK_m0s8lpcomp_VERSION 0
#define CYIPBLOCK_m0s8pclk_VERSION 0
#define CYIPBLOCK_m0s8sar_VERSION 0
#define CYIPBLOCK_m0s8scb_VERSION 0
#define CYIPBLOCK_m0s8srssv2_VERSION 1
#define CYIPBLOCK_m0s8tcpwm_VERSION 0
#define CYIPBLOCK_m0s8udbif_VERSION 0
#define CYIPBLOCK_S8_GPIO_VERSION 2
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
