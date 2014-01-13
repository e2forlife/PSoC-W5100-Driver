/* =========  for ChuckE   ================*/
#include <project.h>
#include <stdio.h>   /* sprintf() */

int main()
{
uint8 socket;
uint8 length = 0;	
char OutputString[255];
char buffer[2000];
uint8 test = 0;	
//____________________________	
SPI0_Start();
ETH0_Start();
	
	socket = ETH0_TcpOpen( 23 );
	ETH0_TcpStartServer( socket );

for(;;)
    {
	while ( !ETH0_TcpConnected( socket ) ) {CyDelay(100);}	/* wait for a connection, and delay the flashes */	
	
	while( ETH0_SocketRxDataWaiting(socket) == 0) 
			{	ETH0_TcpPrint(socket,"\r RxDataWaiting = 0");	CyDelay(500);}		// if no data i read    ETH0_SocketRxDataWaiting(socket) = 0 
	
	test =ETH0_SocketRxDataWaiting(socket);						// number of bytes received
	
	length = ETH0_TcpReceive(socket,(uint8*)&buffer[0],test);	// pick up data from V5100
	CyDelay(10);												// Suppose that W5100 is  lazy  I hope that the W5100 realized that I got data
	test =ETH0_SocketRxDataWaiting(socket);						// I would like to see here zero
	// When I install a flag = 1, in W5100.c   as here      str. 1394    `$INSTANCE_NAME`_ProcessRxData( socket, 0, buffer, RxSize, 1); 
	// the function ETH0_SocketRxDataWaiting(socket) will work correctly (return 0)

	sprintf(OutputString,"  <--I read %d bytes, then read RxDataWaiting = %d \r ",length, test);
	ETH0_TcpPrint(socket,OutputString);	
	
	CyDelay(500);
	//ETH0_TcpDisconnect( socket );
	//ETH0_SocketClose( socket );
	}
}

/* [] END OF FILE */
