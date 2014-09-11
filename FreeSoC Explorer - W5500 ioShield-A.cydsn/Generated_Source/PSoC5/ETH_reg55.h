/**
 * \addtogroup w5x00
 * @{
 */
#if (5 == 5)
#if !defined(ETH_REG55_H)
	#define ETH_REG55_H
	
/*
 * Common Register addresses used by the core.  Registers that
 * are not being utilized by the driver have not been defined
 */
#define ETH_REG_MODE             (0x0000)
#define ETH_REG_GAR              (0x0001)
#define ETH_REG_SUBR             (0x0005)
#define ETH_REG_SHAR             (0x0009)
#define ETH_REG_SIPR             (0x000F)

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
#define ETH_SOCK_TOS             (0x0015)
#define ETH_SOCK_TTL             (0x0016)
#define ETH_SOCK_RXMEM           (0x001E)
#define ETH_SOCK_TXMEM           (0x001F)
#define ETH_SOCK_TXFSR           (0x0020)
#define ETH_SOCK_TXRD            (0x0022)
#define ETH_SOCK_TXWR            (0x0024)
#define ETH_SOCK_RXRSR           (0x0026)
#define ETH_SOCK_RXRD            (0x0028)
#define ETH_SOCK_RXWR            (0x002A)
#define ETH_SOCK_IMR             (0x002C)
#define ETH_SOCK_FRAG            (0x002D)

/* ------------------------------------------------------------------------ */
/* Memory Size Definitions */
#define ETH_MEM_0K          ( 0 )
#define ETH_MEM_1K          ( 1 )
#define ETH_MEM_2K          ( 2 )
#define ETH_MEM_4K          ( 4 )
#define ETH_MEM_8K          ( 8 )
#define ETH_MEM_16K         ( 16 )
	
#endif
/* [] END OF FILE */
#endif
/* @} */
