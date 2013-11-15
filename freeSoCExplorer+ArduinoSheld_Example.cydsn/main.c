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
	char buffer[128];
	uint8 socket;
	uint16 length;
	int temp;
	
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	SPI0_Start();
	ETH0_Start();
	
//    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	
	
    for(;;)
    {
        /* Place your application code here. */
		socket = ETH0_TcpOpen( 23 );
		ETH0_TcpStartServer( socket );
		while ( !ETH0_TcpConnected( socket ) ) {
			/*
			 * While we are waiting for the client to attach
			 * to the server, flash some random colors on the
			 * LED to provide entertainment.
			 */
			/* wait for a connection, and delay the flashes */
			CyDelay(100);
		}
		/*
		 * Send the Logon welcom message to the client.
		 */
		ETH0_TcpPrint(socket,"Welcome to the freeSoC Explorer Board!\r\n");
		ETH0_TcpPrint(socket,"----------------------------------------------------------------------------\r\n\r\n");
		temp = 0;
		while( ETH0_SocketRxDataWaiting(socket) == 0) {
			ETH0_TcpPrint(socket, "Please Press a key: ");
			switch(temp) {
				case 0:
					ETH0_TcpPrint(socket, "\\ \r");
					break;
				case 1:
					ETH0_TcpPrint(socket, "|\r");
					break;
				case 2:
					ETH0_TcpPrint(socket, "/\r");
					break;
				case 3:
					ETH0_TcpPrint(socket, "-\r");
					break;
			}
			temp = (temp + 1) & 3;
			CyDelay(1);
		}
		ETH0_TcpPrint(socket,"\r\nThank You! :-) ");
		length = ETH0_TcpReceive(socket,(uint8*)&buffer[0],128);
		ETH0_TcpSend(socket,(uint8*)&buffer[0],length);
		
		ETH0_TcpDisconnect( socket );
		ETH0_SocketClose( socket );
		CyDelay(10);
    }
}

/* [] END OF FILE */
