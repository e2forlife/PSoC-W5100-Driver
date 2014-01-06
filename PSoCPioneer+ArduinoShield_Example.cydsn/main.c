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

char randomData[2000];

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
	SDCS_Write(1);
	
	/* Generate some random bytes to transmit to the Ethernet client */
	for (temp = 0; temp < 2000; ++temp)
	{
		randomData[temp] = (rand()&0x17) + 'A';
	}
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
			CyDelay(250);
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
		
		/* pavloven test: TcpSend() of 2000 bytes */
		/* set I/O pin low for timing */
		SDCS_Write(0);
		/* Transmit 2000 bytes through the driver to the host */
		ETH0_TcpSend(socket,(uint8*)&randomData[0], 2000);
		/* Set I/O pin high for measuring time */
		SDCS_Write(1);
		/* end test : measured time 30.20275 ms (Effective data rate: 529753 bps) */
		
		ETH0_TcpDisconnect( socket );
		ETH0_SocketClose( socket );
		CyDelay(10);
    }
}

/* [] END OF FILE */
