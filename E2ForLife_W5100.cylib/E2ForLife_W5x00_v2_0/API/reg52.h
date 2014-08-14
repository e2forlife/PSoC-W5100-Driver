/**
 * \addtogroup w5x00
 * @{
 */
#if (`$PART_FAMILY` == 2)
#if !defined(`$INSTANCE_NAME`_REG52_H)
	#define `$INSTANCE_NAME`_REG52_H
	
/*
 * Common Register addresses used by the core.  REgisters that
 * are not being utilized by the drive havenot been defined
 */
#define `$INSTANCE_NAME`_REG_MODE             (0x0000)
#define `$INSTANCE_NAME`_REG_GAR              (0x0001)
#define `$INSTANCE_NAME`_REG_SUBR             (0x0005)
#define `$INSTANCE_NAME`_REG_SHAR             (0x0009)
#define `$INSTANCE_NAME`_REG_SIPR             (0x000F)

/* ------------------------------------------------------------------------ */
/* Interrupt Register and Interrupt mask register for future use */
#define `$INSTANCE_NAME`_REG_IR               (0x0015)
#define `$INSTANCE_NAME`_REG_IMR              (0x0016)
#define `$INSTANCE_NAME`_REG_IR2              (0x0034)
#define `$INSTANCE_NAME`_REG_IMR2             (0x0036)
/* ------------------------------------------------------------------------ */

/* Socket Register offset addresses */
#define `$INSTANCE_NAME`_SOCK_MR              (0x4000)
#define `$INSTANCE_NAME`_SOCK_CR              (0x4001)
#define `$INSTANCE_NAME`_SOCK_IR              (0x4002)
#define `$INSTANCE_NAME`_SOCK_SR              (0x4003)
#define `$INSTANCE_NAME`_SOCK_PORT            (0x4004)
#define `$INSTANCE_NAME`_SOCK_DHAR            (0x4006)
#define `$INSTANCE_NAME`_SOCK_DIPR            (0x400C)
#define `$INSTANCE_NAME`_SOCK_DPORT           (0x4010)
#define `$INSTANCE_NAME`_SOCK_PROTO           (0x4014)
#define `$INSTANCE_NAME`_SOCK_TOS             (0x4015)
#define `$INSTANCE_NAME`_SOCK_TTL             (0x4016)
#define `$INSTANCE_NAME`_SOCK_RXMEM           (0x401E)
#define `$INSTANCE_NAME`_SOCK_TXMEM           (0x401F)
#define `$INSTANCE_NAME`_SOCK_TXFSR           (0x4020)
#define `$INSTANCE_NAME`_SOCK_TXRD            (0x4022)
#define `$INSTANCE_NAME`_SOCK_TXWR            (0x4024)
#define `$INSTANCE_NAME`_SOCK_RXRSR           (0x4026)
#define `$INSTANCE_NAME`_SOCK_RXRD            (0x4028)
#define `$INSTANCE_NAME`_SOCK_RXWR            (0x402A)
#define `$INSTANCE_NAME`_SOCK_IMR             (0x402C)
#define `$INSTANCE_NAME`_SOCK_FRAG            (0x402D)

/* ------------------------------------------------------------------------ */
/* Memory Size Definitions */
#define `$INSTANCE_NAME`_MEM_0K          ( 0 )
#define `$INSTANCE_NAME`_MEM_1K          ( 1 )
#define `$INSTANCE_NAME`_MEM_2K          ( 2 )
#define `$INSTANCE_NAME`_MEM_4K          ( 4 )
#define `$INSTANCE_NAME`_MEM_8K          ( 8 )
#define `$INSTANCE_NAME`_MEM_16K         ( 16 )
	
#endif
/* [] END OF FILE */
#endif
/* @} */
