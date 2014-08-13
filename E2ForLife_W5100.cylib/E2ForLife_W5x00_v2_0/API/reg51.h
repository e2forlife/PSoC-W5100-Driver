/**
 * \addtogroup w5x00
 * @{
 */
#if !defined(`$INSTANCE_NAME`_REG51_H)
	#define `$INSTANCE_NAME`_REG51_H
	
/*
 * Common REgister addresses used by the core.  REgisters that
 * are not being utilized by the drive havenot been defined
 */
#define `$INSTANCE_NAME`_REG_MODE             (0x0000)
#define `$INSTANCE_NAME`_REG_GAR              (0x0001)
#define `$INSTANCE_NAME`_REG_SUBR             (0x0005)
#define `$INSTANCE_NAME`_REG_SHAR             (0x0009)
#define `$INSTANCE_NAME`_REG_SIPR             (0x000F)
#define `$INSTNACE_NAME`_REG_RMSR             (0x001A)
#define `$INSTANCE_NAME`_REG_TXSR             (0x001B)

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
#define `$INSTANCE_NAME`_SOCK_PROTO           (0x0014)
#define `$INSTANCE_NAME`_SOCK_TOS             (0x0015)
#define `$INSTANCE_NAME`_SOCK_TTL             (0x0016)
#define `$INSTANCE_NAME`_SOCK_TXFSR           (0x0020)
#define `$INSTANCE_NAME`_SOCK_TXRD            (0x0022)
#define `$INSTANCE_NAME`_SOCK_TXWR            (0x0024)
#define `$INSTANCE_NAME`_SOCK_RXRSR           (0x0026)
#define `$INSTANCE_NAME`_SOCK_RXRD            (0x0028)
	
/* ------------------------------------------------------------------------ */
/* Memory Size Definitions */
#define `$INSTANCE_NAME`_MEM_0K          ( 0x00 ) /* Unused in W5100 */
#define `$INSTANCE_NAME`_MEM_1K          ( 0x00 )
#define `$INSTANCE_NAME`_MEM_2K          ( 0x01 )
#define `$INSTANCE_NAME`_MEM_4K          ( 0x02 )
#define `$INSTANCE_NAME`_MEM_8K          ( 0x03 )
#define `$INSTANCE_NAME`_MEM_16K         ( 0x00 )  /* Unused in W5100 */
	
#endif
/* [] END OF FILE */
/* @} */
