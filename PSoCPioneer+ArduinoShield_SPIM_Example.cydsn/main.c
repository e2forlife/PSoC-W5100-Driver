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

char randomData[2000];

int main()
{
	char buffer[128];
	uint8 socket;
	uint16 length;
	int temp;
	
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	SPI0_Start();
	ETH_Start();

	/* Generate some random bytes to transmit to the Ethernet client */
	for (temp = 0; temp < 2000; ++temp)
	{
		randomData[temp] = (rand()&0x17) + 'A';
	}

//    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	
	
    for(;;)
    {
        /* Place your application code here. */
		socket = ETH_TcpOpen( 23 );
		ETH_TcpStartServer( socket );
		while ( !ETH_TcpConnected( socket ) ) {
			/*
			 * While we are waiting for the client to attach
			 * to the server, flash some random colors on the
			 * LED to provide entertainment.
			 */
			RED_Write( rand() & 0xFE);
			GREEN_Write( rand() & 0xFE);
			BLUE_Write( rand() & 0xFE) ;
			/* wait for a connection, and delay the flashes */
			CyDelay(100);
		}
		/*
		 * Send the Logon welcom message to the client.
		 */
		ETH_TcpPrint(socket,"Welcome to the PSoC4 Pioneer Board!\r\n");
		ETH_TcpPrint(socket,"----------------------------------------------------------------------------\r\n\r\n");
		temp = 0;
		while( ETH_SocketRxDataWaiting(socket) == 0) {
			ETH_TcpPrint(socket, "Please Press a key: ");
			switch(temp) {
				case 0:
					ETH_TcpPrint(socket, "\\ \r");
					break;
				case 1:
					ETH_TcpPrint(socket, "|\r");
					break;
				case 2:
					ETH_TcpPrint(socket, "/\r");
					break;
				case 3:
					ETH_TcpPrint(socket, "-\r");
					break;
			}
			temp = (temp + 1) & 3;
			CyDelay(1);
		}
		ETH_TcpPrint(socket,"\r\nThank You! :-) ");
		length = ETH_TcpReceive(socket,(uint8*)&buffer[0],128);
		ETH_TcpSend(socket,(uint8*)&buffer[0],length);

		/* pavloven test: TcpSend() of 2000 bytes */
		/* set I/O pin low for timing */
		SDCS_Write(0);
		/* Transmit 2000 bytes through the driver to the host */
		ETH_TcpSend(socket,(uint8*)&randomData[0], 2000);
		/* Set I/O pin high for measuring time */
		SDCS_Write(1);
		/* end test : measured time 46.82435 ms (Effective Data Rate: 341702 bps) */
		
		ETH_TcpDisconnect( socket );
		ETH_SocketClose( socket );
		CyDelay(10);
    }
}
/* [] END OF FILE */
