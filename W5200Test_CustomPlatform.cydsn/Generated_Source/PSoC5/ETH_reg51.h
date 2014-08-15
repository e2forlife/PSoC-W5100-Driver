/**
 * \addtogroup w5x00
 * @{
 */
#if (2 == 1)
#if !defined(ETH_REG51_H)
	#define ETH_REG51_H
	
/*
 * Common REgister addresses used by the core.  REgisters that
 * are not being utilized by the drive havenot been defined
 */
#define ETH_REG_MODE             (0x0000)
#define ETH_REG_GAR              (0x0001)
#define ETH_REG_SUBR             (0x0005)
#define ETH_REG_SHAR             (0x0009)
#define ETH_REG_SIPR             (0x000F)
#define ETH_REG_RMSR             (0x001A)
#define ETH_REG_TXSR             (0x001B)

/* ------------------------------------------------------------------------ */
/* Interrupt Register and Interrupt mask register for future use */
#define ETH_REG_IR               (0x0015)
#define ETH_REG_IMR              (0x0016)
/* ------------------------------------------------------------------------ */

/* Socket Register offset addresses */
#define ETH_SOCK_MR              (0x0000)
#define ETH_SOCK_CR              (0x0001)
#define ETH_SOCK_IR              (0x0002)
#define ETH_SOCK_SR              (0x0003)
#define ETH_SOCK_PORT            (0x0004)
#define ETH_SOCK_DHAR            (0x0006)
#define ETH_SOCK_DIPR            (0x000C)
#define ETH_SOCK_DPORT           (0x0010)
#define ETH_SOCK_PROTO           (0x0014)
#define ETH_SOCK_TOS             (0x0015)
#define ETH_SOCK_TTL             (0x0016)
#define ETH_SOCK_TXFSR           (0x0020)
#define ETH_SOCK_TXRD            (0x0022)
#define ETH_SOCK_TXWR            (0x0024)
#define ETH_SOCK_RXRSR           (0x0026)
#define ETH_SOCK_RXRD            (0x0028)
	
/* ------------------------------------------------------------------------ */
/* Memory Size Definitions */
#define ETH_MEM_0K          ( 0x00 ) /* Unused in W5100 */
#define ETH_MEM_1K          ( 0x00 )
#define ETH_MEM_2K          ( 0x01 )
#define ETH_MEM_4K          ( 0x02 )
#define ETH_MEM_8K          ( 0x03 )
#define ETH_MEM_16K         ( 0x00 )  /* Unused in W5100 */
	
#endif
/* [] END OF FILE */
#endif
/* @} */
