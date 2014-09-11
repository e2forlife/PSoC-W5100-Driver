/**
 * \addtogroup w5x00
 * @{
 */
#if (`$PART_FAMILY` == 5)
#if !defined(`$INSTANCE_NAME`_REG55_H)
	#define `$INSTANCE_NAME`_REG55_H
	
/*
 * Common Register addresses used by the core.  Registers that
 * are not being utilized by the driver have not been defined
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
/* ------------------------------------------------------------------------ */

/* Socket Register offset addresses */
#define `$INSTANCE_NAME`_SOCK_MR              (0x0000)
#define `$INSTANCE_NAME`_SOCK_CR              (0x0001)
#define `$INSTANCE_NAME`_SOCK_IR              (0x0002)
#define `$INSTANCE_NAME`_SOCK_SR              (0x0003)
#define `$INSTANCE_NAME`_SOCK_PORT            (0x0004)
#define `$INSTANCE_NAME`_SOCK_DHAR            (0x0006)
#define `$INSTANCE_NAME`_SOCK_DIPR            (0x000C)
#define `$INSTANCE_NAME`_SOCK_DPORT           (0x0010)
#define `$INSTANCE_NAME`_SOCK_TOS             (0x0015)
#define `$INSTANCE_NAME`_SOCK_TTL             (0x0016)
#define `$INSTANCE_NAME`_SOCK_RXMEM           (0x001E)
#define `$INSTANCE_NAME`_SOCK_TXMEM           (0x001F)
#define `$INSTANCE_NAME`_SOCK_TXFSR           (0x0020)
#define `$INSTANCE_NAME`_SOCK_TXRD            (0x0022)
#define `$INSTANCE_NAME`_SOCK_TXWR            (0x0024)
#define `$INSTANCE_NAME`_SOCK_RXRSR           (0x0026)
#define `$INSTANCE_NAME`_SOCK_RXRD            (0x0028)
#define `$INSTANCE_NAME`_SOCK_RXWR            (0x002A)
#define `$INSTANCE_NAME`_SOCK_IMR             (0x002C)
#define `$INSTANCE_NAME`_SOCK_FRAG            (0x002D)

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
