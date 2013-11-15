/**
 * \defgroup w5100 W5100 Chip Interface Driver
 * @{
 */

#if !defined(ETH0_H)
#define ETH0_H

#define ETH0_READ_OP         ( 0x0F )
#define ETH0_WRITE_OP        ( 0xF0 )

#define ETH0_IPADDRESS(x1,x2,x3,x4)   ( (uint32)(x1&0x000000FF) + (uint32)((x2<<8)&0x0000FF00) + (uint32)((x3<<16)&0x00FF0000) + ((uint32)(x4<<24)&0xFF000000 ))

#define ETH0_PROTO_TCP        ( 1 )
#define ETH0_PROTO_UDP        ( 2 )
#define ETH0_PROTO_IP         ( 3 )
#define ETH0_PROTO_MAC        ( 4 )

/* ------------------------------------------------------------------------ */
/**
 * \brief Startup and initialize the device using the creator defaults
 *
 * This function will initialize and startup the Ethernet device chip
 * using the default parameters supplied in the configuration window
 * of Creator.  This is usually the main method for initializing the device
 *
 * This function requires that the SPI interface is initialized, however
 * it will attempt to discover if the initialization has been completed
 * and initialize the interface if it has not yet been setup.  It is
 * highly recommended that your application initialize the SPI interface
 * directly rather than depend on this, since every SPI implementation
 * may be different and your port might not be corectly initialized.
 */
void ETH0_Start( void );

/**
 * \brief initialize device parameters and memory setup
 * \param *mac pointer to a 6-byte buffer holding the device MAC address
 * \param ip the IP address to which the device will be set
 * \param subnet the Subnet mask to be used for the device ( usually 255.255.255.0)
 * \param gateway the IPv4 address of the network gateway
 *
 * This function will reset the device, and wait for the internal PLL to
 * lock, then initialize the device registers to allow for correct operation
 * in your application.  It currently assumes that there will be a 2K buffer
 * for both transmit and receive for each of the 4 sockets available.
 *
 * \note this function is usuallt called from ETH0_Start()
 * \sa ETH0_Start()
 */
void ETH0_Init(uint8* mac, uint32 ip, uint32 subnet, uint32 gateway);

/**
 * \brief Parse a ASCII Text IPv4 address to an IPv4 Address.
 * \param ipString ASCII z-String containing the IP address to parse
 * \returns the parsed IP address
 *
 * this function will parse an ASCII String IP address in to a 32-bit IP
 * address used by the device.  If the address string contains an error, 
 * this function will return an IP address of 255.255.255.255, or 0xFFFFFFFF
 * to indicate that an error has been detected.
 */
uint32 ETH0_ParseIP( const char* ipString );

/**
 * \brief re-assign the local IP address of the device
 * \param ip the new IP address to assign to the device
 * \return 0 IP Address was not valid
 * \return 0xFF IP address was assigned to the device
 *
 * This function will re-assign the IP address of the ethernet device to the
 * specified address.  If the address to be assigned is invalid, a zero (0)
 * is returned from the function to indicatate a BAD IP wa sspecified. Otherwise,
 * 255 is returned.
 */
uint8 ETH0_SetIP( uint32 ip );

/**
 * \brief Read the current IP address of the device
 * \returns the IP address read from the device
 *
 * This function reads and returns the contents of the Source IP register
 * of the W5100 device.
 */
uint32 ETH0_GetIP( void );

/**
 * \brief Re-assign the hardware address (MAC) of the device
 * \param *mac pointer to the 6-byte array holding the MAC address
 *
 * This function will store the contents of the specified MAC address to the
 * source Hardware Address register (MAC address) for the W5100 device.
 */
void ETH0_SetMAC( uint8* mac );

/**
 * \brief Retrieve the assigned Source hardware (MAC) address of the device
 * \param *mac pointer to the 6-byte array to hold the read value.
 *
 * This function will read the assigned MAC address and store it within the
 * specified array.
 */
void ETH0_GetMAC( uint8* mac );

/**
 * \brief Open a socket using the specified protocol on the specified port
 * \param Protocol the protocol identification for the socket
 * \param flags Socket flags (currently not used)
 * \returns The socket number (0-3) or 0xFF when not available
 *
 * This function will allocate and initiailze a socket from the socket table
 * and return the socket number which was opened.  If there are no sockets
 * available, or there is an error opening the socket, a value of 0xFF will
 * be returned.
 * \sa ETH0_PROTO_TCP
 * \sa ETH0_PROTO_UDP
 * \sa ETH0_PROTO_IP
 * \sa ETH0_PROTO_MAC
 */
uint8 ETH0_SocketOpen( uint8 Protocol, uint16 port, uint8 flags );

/**
 * \brief Close a previously opened socket
 * \param socket the Socket number (0 - 3) to close
 *
 * This fucntion will close (and disconnect) an open socket, and flush
 * the allocation record from memory.  If an invlaid socket is specified,
 * the function will ignore the request.  Closing an alread closed socket
 * has no effect.
 */
void ETH0_SocketClose( uint8 socket );

/**
 * \brief Process the socket connection to check for errors and remote closure
 * \param socket the socket number to be checked
 * \returns the socket status
 *
 * This fucntion will process the opened socket to look for socket closure
 * errors, and other aspects which would require the software to reset
 * the socket.  Upon detection of the issue, the socket will be closed, and
 * need to be re-opened from the software applicatoin.  If there are no
 * status detected which require action, nothing is executed.
 */
uint8 ETH0_SocketProcessConnections( uint8 socket );

/**
 * \brief Check the connection establishment status of the socket
 * \param socket the socket to be checked.
 * \return TRUE the socket is established
 * \return FALSE the socket has not yet been established
 *
 * This fucntion will read the socket status and return the state of the
 * socket establishment.
 */
inline uint8 ETH0_SocketEstablished( uint8 socket );

/**
 * \brief Retrieve the length of waiting Receive data
 * \param socket the socket which will be polled for waiting receive data
 * \returns the length of waiting data in the receive buffer.
 *
 * This function will read the waiting data length from the Receive buffer
 * and return the read length of waiting data.
 */
uint16 ETH0_SocketRxDataWaiting( uint8 socket );

/**
 * \brief Open an port using the TCP protocol
 * \param port the port on which the TCP socket will be openend
 * \returns The socket number that was opened (0-3) or 0xFF on error
 *
 * This function will open and initialize a socket using the W5100 buit-in
 * TCP protocol, and return the socket number for the opened TCP socket.
 * When there are no sockets available, or there is an error opening the
 * socket, 0xFF is returned.
 * \sa ETH0_SocketOpen()
 * \sa ETH0_SocketClose()
 */
uint8 ETH0_TcpOpen(uint16 port);

/**
 * \brief Start a server listening for connection on an open socket
 * \param socket The socket on which listening will occur.
 *
 * This function will execute the socket command to begin listening for
 * connections on the specified socket.  If the socket specified is not
 * a valid socket nothing will occur.  After starting the listen operation,
 * this function will return (NON-BLOCKING).
 * \sa _TcpOpen()
 * \sa ETH0_SocketClose()
 */
void ETH0_TcpStartServer( uint8 socket );

/**
 * \brief Start a TCP server listening for connections on the specified socket
 * \param socket the socket on which listening will occcur
 *
 * This function will start a valid socket listening for TCP connections
 * by executing the listen command on the specified socket.  If the socket
 * is invalid, no action is taken.  After the socket server is started,
 * this function will wait until a connection has been made to a cliet
 * before continuing.
 * 
 * \note This function is a blocking call, and will wait until a connection has been established.
 * \sa ETH0_TcpStartServer()
 * \sa ETH0_TcpOPen();
 * \sa ETH0_SocketClose()
 */
void ETH0_TcpStartServerWait( uint8 socket );

/**
 * \brief Open a client connection to a specified IP and port
 * \param socket the socket used to open the connection
 * \param ip the IPv4 address of the server to which a connection will be made
 * \param port the port number of the server
 *
 * This function will attempt to open a connection between a W5100 device
 * socket, and a remote server using TCP.  This function will wait for the
 * timeout specified in the component paramters within Creator for the
 * connection to be made before terminating the wait.
 *
 * \note This function will block for a specified wait period
 * \sa ETH0_SocketClose()
 * \sa ETH0_TcpOpen()
 * \sa ETH0_TcpStartServer()
 * \sa ETH0_TcpStartServerWait()
 * \sa ETH0_TcpConnected()
 * \sa ETH0_TcpDisconnect()
 */
void ETH0_TcpConnect( uint8 socket, uint32 ip, uint16 port );

/**
 * \brief Return the connection status of the TCP socket
 * \param socket the socket on which connection status will be polled
 * \return TRUE When the socket is connected and valid
 * \return FALSE when the socket is not connected, waiting, or invalid
 *
 * This function will check the establishment status of the specified socket,
 * and return the state.
 * \sa ETH0_TcpConnect()
 * \sa ETH0_TcpStartServer()
 */
inline uint8 ETH0_TcpConnected( uint8 socket );

/**
 * \brief Terminate a connection with a remote client/server
 * \param socket The socket on which the connection will be terminated
 *
 * This function will issue the disconnect function to initiate a connection
 * termination between the W5100 socket and the remote client/server.
 * \sa ETH0_TcpConnect()
 * \sa ETH0_TcpStartServer()
 * \sa ETH0_TcpStartServerWait()
 */
inline void ETH0_TcpDisconnect( uint8 socket );

/**
 * \brief Transmit a byte packet using the built-in TCP
 * \param socket the socket on which the transmission will occur
 * \param *buffer the packet data to be transmitted
 * \param len the length of the data packet to be transmitted
 * \returns the number of bytes transmitted via TCP
 *
 * this function will copy the specified packet buffer to the W5100 Transmitter
 * buffer, then execute the commands to transmit the data packet using the
 * built-in TCP handlers.  Upon completion of the operation, this function
 * will return the number of bytes transmitted.
 * 
 * When called, this function will verify that a socket connection has
 * first been established and is opened with the correct socket protocol. Send
 * operations to sockets that contain a different protocol or are not yet
 * established are ignored and 0 is returned.
 * \sa ETH0_TcpOpen()
 * \sa ETH0_TcpConnect()
 * \sa ETH0_TcpStartServer()
 * \sa ETH0_TcpStartServerWait()
 * \sa ETH0_TcpPrint()
 * \sa ETH0_TcpReceive()
 */
uint16 ETH0_TcpSend(uint8 socket, uint8* buffer, uint16 len);

/**
 * \brief Receive a packet of data using the built-in TCP handler
 * \param socket The socket on which the receive will occur
 * \param *buffer the buffer to hold the received data
 * \param length the Maximum amount of data to be received in to the buffer
 * \returns the length of data received and copied in to the receive buffer
 *
 * This function will check for available received data, then copy the data
 * from the internal W5100 buffer to the specified holding buffer for the
 * received data.  When there is more data waiting than available space
 * in the buffer (specified by the length paramer), this function will only
 * receive up to the maximum length specified.
 *
 * prior to receiving data, this function will verify that a valid
 * connection has been established, and that the configured protocol
 * is set to the internal TCP.  When not properly configured, this function
 * will return 0, otherwise, the number of bytes read from the W5100
 * receive buffer memory is returned.
 * \sa ETH0_TcpOpen()
 * \sa ETH0_TcpConnect()
 * \sa ETH0_TcpStartServer()
 * \sa ETH0_TcpStartServerWait()
 * \sa ETH0_TcpPrint()
 * \sa ETH0_TcpSend()
 */
uint16 ETH0_TcpReceive( uint8 socket, uint8* buffer, uint16 length );

/**
 * \brief Send a zero-terminated ASCII string using TCP
 * \param socket the socket on which the print will occur
 * \param *str the ASCII-Z string to be sent
 *
 * this function is a shortcut to using the ETH0_TcpSend()
 * to transmit a zero-terminated ASCII (ASCII-Z) string to a remote
 * client/server.
 * \sa ETH0_TcpOpen()
 * \sa ETH0_TcpConnect()
 * \sa ETH0_TcpStartServer()
 * \sa ETH0_TcpStartServerWait()
 * \sa ETH0_TcpSend()
 * \sa ETH0_TcpReceive()
 */
void ETH0_TcpPrint( uint8 socket, const char* str );

/**
 * \brief Open an port using the TCP protocol
 * \param port the port on which the TCP socket will be openend
 * \returns The socket number that was opened (0-3) or 0xFF on error
 *
 * This function will open and initialize a socket using the W5100 buit-in
 * TCP protocol, and return the socket number for the opened TCP socket.
 * When there are no sockets available, or there is an error opening the
 * socket, 0xFF is returned.
 * \sa ETH0_SocketOpen()
 * \sa ETH0_SocketClose()
 */
uint8 ETH0_UdpOpen(uint16 port);

/**
 * \brief Transmit a byte packet using the built-in UDP
 * \param socket the socket on which the transmission will occur
 * \param ip the IPv4 Address of the target
 * \param port the target port number for the transmission
 * \param *buffer the packet data to be transmitted
 * \param length the length of the data packet to be transmitted
 * \returns the number of bytes transmitted via TCP
 *
 * this function will copy the specified packet buffer to the W5100 Transmitter
 * buffer, then execute the commands to transmit the data packet using the
 * built-in UDP handlers.  Upon completion of the operation, this function
 * will return the number of bytes transmitted.
 * 
 * When called, this function will verify that a socket connection has
 * first been opened with the correct socket protocol. Send operations
 * to sockets that contain a different protocol are ignored and 0 is returned.
 * \sa ETH0_UdpReceive()
 */
uint16 ETH0_UdpSend(uint8 socket, uint32 ip, uint16 port, uint8* buffer, uint16 length);

/**
 * \brief Receive a packet of data using the built-in TCP handler
 * \param socket The socket on which the receive will occur
 * \param *ip buffer to hold the IPv4 address of the packet sender
 * \param *port biffer to hold the port number of the sender of the received packet.
 * \param *buffer the buffer to hold the received data
 * \param length the Maximum amount of data to be received in to the buffer
 * \returns the length of data received and copied in to the receive buffer
 *
 * This function will check for available received data, then copy the data
 * from the internal W5100 buffer to the specified holding buffer for the
 * received data.  When there is more data waiting than available space
 * in the buffer (specified by the length paramer), this function will only
 * receive up to the maximum length specified.
 *
 * prior to receiving data, this function will verify that the configured protocol
 * is set to the internal UDP.  When not properly configured, this function
 * will return 0, otherwise, the number of bytes read from the W5100
 * receive buffer memory is returned.
 * \sa ETH0_UdpSend()
 */
uint16 ETH0_UdpReceive(uint8 socket, uint32 *ip, uint16 *port, uint8* buffer, uint16 length);

#endif

/* [] END OF FILE */
/** @} */
