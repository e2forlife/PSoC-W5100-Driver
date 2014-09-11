/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include <project.h>

int main()
{
	uint8 socket;
	
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	SPI_Start();
	ETH_Start();
	
    /* CyGlobalIntEnable; */ /* Uncomment this line to enable global interrupts. */
    for(;;)
    {
		socket = ETH_TcpOpen( 23 );
		ETH_TcpStartServerWait( socket );
		
		ETH_TcpPrint(socket,"Hello from PSoC 5LP and W5500!\r\n\r\n");
		CyDelay(10);
		ETH_TcpDisconnect( socket );
		CyDelay(100);
		ETH_SocketClose( socket );
    }
}

/* [] END OF FILE */
