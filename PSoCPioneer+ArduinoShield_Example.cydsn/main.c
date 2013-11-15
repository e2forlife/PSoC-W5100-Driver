/**
 * \file Arduino Ethernet shield Example
 * \author Chuck Erhardt (chuck@e2forlife.com)
 * 
 * This is a real simple example project to connect the
 * PSoC4 Pioneer board to the Arduino Ethernet shield board.
 *
 * Copyright notice:
 *
 *
 * Dscaimer: 
 * This software is provided as-is for demonstration and
 * educational purposes only.  No warranty is expressed or
 * implied; The sole responsibility of the verification
 * on your platform is your own.
 */
#include <project.h>
#include <stdio.h>   /* sprintf() */
#include <string.h>  /* for STRLEN() */
#include <stdlib.h>  /* for RAND() */

int main()
{
	char buffer[128];
	uint8 socket;
	uint16 length;
	int temp;
	uint8 red;
	uint8 green;
	uint8 blue;
	
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
	SPI0_Start();
	ETH0_Start();
	LED0_Start();
	LED1_Start();
	
//    CyGlobalIntEnable; /* Uncomment this line to enable global interrupts. */
	
	/*
	 * initialize the local variables to produce a
	 * (somewhat) random default color for the LED
	 */
	red = rand()&0xFF;
	green = rand() % 0xFF;
	blue = rand() % 0xFF;
	
	/*
	 * Set the RGB LED color by writing the 2 PRiSM
	 * components to set the LED brightness
	 */
	LED0_WritePulse0( red );
	LED0_WritePulse1( green );
	LED1_WritePulse0( blue );
	
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
			red = rand() % 0xFF;
			green = rand() % 0xFF;
			blue = rand() % 0xFF;
			LED0_WritePulse0( red );
			LED0_WritePulse1( green );
			LED1_WritePulse0( blue );
			/* wait for a connection, and delay the flashes */
			CyDelay(100);
		}
		/*
		 * Send the Logon welcom message to the client.
		 */
		ETH0_TcpPrint(socket,"Welcome to the PSoC4 Pioneer Board!\r\n");
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
