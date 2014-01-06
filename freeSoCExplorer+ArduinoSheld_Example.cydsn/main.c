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
/**
 * Notes:
 * 1) Test executed using a FreeSoC Eplorer board wired to use the Arduino Ethernet shield
 * 2) Modified design clock from 48 MHz PLL out to 64 PLL and added a 2000 byte speed test
 *    to end of the code to further compare data rates and issues as reported on the PSoC
 *    community forum by Pavloven.
 * =======================================================================================
 * From: Pavloven (16-DEC-2013)
 * Hi, ChuckE! I tried to send 2000 bytes in your example PSoC-W5100-Driver-master using the
 * TcpSend (...) For PSoC4 it took 38 ms For PSoC5LP it took 15 ms at PLL = 64MHz For PSoC5
 * it took 18 ms at PLL = 64MHz and had to include High Speed ​​Mode otherwise - does not go out
 * from while (! ETH0_TcpConnected (socket)) For PSoC3 - did not work: the compiler does not
 * like the word inline ((((
 * ========================================================================================
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
	ETH0_Start();
	
	/* Generate some random bytes to transmit to the Ethernet client */
	for (temp = 0; temp < 2000; ++temp)
	{
		randomData[temp] = (rand()&0x17) + 'A';
	}

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
		
		/* pavloven test: TcpSend() of 2000 bytes */
		/* set I/O pin low for timing */
		SDCS_Write(0);
		/* Transmit 2000 bytes through the driver to the host */
		ETH0_TcpSend(socket,(uint8*)&randomData[0], 2000);
		/* Set I/O pin high for measuring time */
		SDCS_Write(1);
		/* end test : measured time TBD ms (Effective Data Rate: TBD bps) */
		
		ETH0_TcpDisconnect( socket );
		ETH0_SocketClose( socket );
		CyDelay(10);
    }
}

/* [] END OF FILE */
