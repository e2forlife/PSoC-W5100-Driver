/**
 * \addtogroup w5x00
 * @{
 */
#if (5 == 2)
#if !defined(ETH_REG52_H)
	#define ETH_REG52_H
	
/*
 * Common Register addresses used by the core.  REgisters that
 * are not being utilized by the drive havenot been defined
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
#define ETH_REG_IR2              (0x0034)
#define ETH_REG_IMR2             (0x0036)
/* ------------------------------------------------------------------------ */

/* Socket Register offset addresses */
#define ETH_SOCK_MR              (0x4000)
#define ETH_SOCK_CR              (0x4001)
#define ETH_SOCK_IR              (0x4002)
#define ETH_SOCK_SR              (0x4003)
#define ETH_SOCK_PORT            (0x4004)
#define ETH_SOCK_DHAR            (0x4006)
#define ETH_SOCK_DIPR            (0x400C)
#define ETH_SOCK_DPORT           (0x4010)
#define ETH_SOCK_PROTO           (0x4014)
#define ETH_SOCK_TOS             (0x4015)
#define ETH_SOCK_TTL             (0x4016)
#define ETH_SOCK_RXMEM           (0x401E)
#define ETH_SOCK_TXMEM           (0x401F)
#define ETH_SOCK_TXFSR           (0x4020)
#define ETH_SOCK_TXRD            (0x4022)
#define ETH_SOCK_TXWR            (0x4024)
#define ETH_SOCK_RXRSR           (0x4026)
#define ETH_SOCK_RXRD            (0x4028)
#define ETH_SOCK_RXWR            (0x402A)
#define ETH_SOCK_IMR             (0x402C)
#define ETH_SOCK_FRAG            (0x402D)

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
