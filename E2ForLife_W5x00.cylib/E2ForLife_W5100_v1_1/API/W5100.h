/**
 * \mainpage Interface Driver For the WIZnet W5100 Device
 * \section feature_sec Features
 * \par
 * \li Compatible with PSoC 3, 4, 5, and 5LP
 * \li SPI port independant
 * \li Supports Hardware TCP, UDP and ARP
 * \li Small FLASH footprint
 * \section intro_sec General Description
 * The W5100 interface driver provides a simple software driver for using the
 * WIZnet W5100 iEthernet controller with a PSoC project.  The driver can be
 * customized to support many system configurations, and allows for SPI port
 * sharing.  Both the SPIM and the SCB interfaces are supported to allow the
 * driver to support many hardware configurations of the application.
 * \section using_sec Using the W5100 Driver
 * \subsection sch_req_subsec Schematic Requirements
 * This driver is a software only driver, thus in order to effectively use
 * the functions provided to access the W5100, there must be a hadrware
 * interface defined in the schematics to access the device.  Once enterend
 * in the schematics, enter the instance name of the SPI component in to the
 * customizer parameters for the driver component.
 * \subsection using_subsec Using The Driver
 * When using the driver, simply start the driver with the Start() function
 * then open a socket using the protocol desired, and either start a server
 * to wait for connections or connect to a remote server.  The W5100 device
 * and the software driver handle the interfacing, management, and data
 * handling for the connections.
 * \section io_sec Input/Output Connections
 * There are no Input or Output connections to this component.
 * \section customizer_sec Component Parameters
 * \subsection comp_param_subsec Component Parameters
 * Drag a W5100 component on to your design and double-click to open the
 * component configuration dialog.
 * \image html Customizer.png
 * \subsection param_subsec Parameters
 * \subsubsection driver_parm_sub_sub Driver Configuration Parameters
 * This section contains parameters that modify the operation of the driver, or
 * provide settings for options of the driver implementation.
 * \arg \c CMD_TIMEOUT The number of missiseconds to wait for a W5100 Command to execute
 * \par
 * This parameter will allow you to set the ammount of time that the internal driver
 * fucntion used to execute socket commands within the W5100 device will wait for a
 * command to execute before declaring a timeout condition.
 * \arg \c INCLUDE_TCP Set to True to enable the TCP interface code
 * \par
 * a True/False parameter used to specify if the TCP protocol interface code will
 * included when compiling the driver software.  Set this to False when ot using
 * the TCP interface functions to save FLASH memory space. The default setting
 * is to include this interface code.
 * \arg \c INCLUDE_UDP Set to True to enable the UDP interface Code
 * \par
 * A True/False parameter used to specify if the UDP protocol interface code will
 * be compiled when building the library.  Set this to False if not using the UDP functions
 * and you wish to save some FLASH memory space.  the default setting for this
 * parameter is True.
 * \arg \c INIT_DELAY The number of milliseconds to wait for the W5100 PLL to Lock after a device reset or power on.
 * \par
 * Usually, this parameter will not need to be modified, however, it allows you to
 * configure the ammount of time that the driver will wait for the W5100 internal
 * PLL to achieve lock.  This might need to be adjusted if your power supply is noisy
 * or you are experiencing a high amount of clock jitter at power on.
 * \warning Adjusting this parameter may cause the W5100 to not respond on the Ethernet port. 
 * \arg \c TIMEOUT The number of milliseconds to wait before an operation declares a general timeout
 * \par
 * This parameter will allow you to adjust the number of milliseconds that an operation will wait
 * for an operation to complete before delaring a timeout condition.  This does not affect
 * every function.
 * \subsubsection config_param_sub_sub Network Configuration Parameters
 * The "configuration" parameters section contains the parameters for initializing
 * the default network configuration for use by the W5100.  These parameters can be
 * overridden within your application through the use of the API function calls.
 * \arg \c GATEWAY The IPv4 Address of the network gateway
 * \par
 * This parameter will allow you to specify the IP address of the ethernet gateway router.  This
 * value is a string specified in IPv4 format of \c www.xxx.yyy.zzz
 * \arg \c IP The IPv4 Address of the device
 * \par
 * The network address of the W5100 device.  This address is the configured address of the
 * controller after the API Start() call executes.  Setting this will change the fixed IP of the
 * system.
 * \arg \c MAC The hardware (MAC) address of the Ethernet Controller
 * \par
 * The MAC address contains the hardware address of the system. It is expressed as a 6 byte
 * comma delimited string containg the hardware address of the W5100.
 * \note If you're using the Arduino Ethernet shield, this is printed on the sticker on the
 * bottom of the board
 * \arg \c SUBNET_MASK The subnet mask used for Ethernet communications
 * \par
 * Modifying this parameter will change teh subnet that the MAC will use to communicate
 * over the network.  The default (and most common) subnet mask is \c 255.255.255.0 , meaning that
 * for a IP address of \c 192.168.1.100 the MAC can communicate directly with only other IP
 * addresses that match \c 192.168.1.xxx. Setting any mit in the subnet mask to a zero defines
 * that bit as a don't care for communicating.
 * \subsubsection hardware_config_parameters_sub_sub Hardware Configuration
 * This parameter section is used to define the interface parameters for associating component
 * instances with the driver, and for declaring design specific delays and configuration data.
 * \arg \c READ_WRITE_DELAY The number of milliseconds to wait for a read/write operation to complete
 * \par
 * This option allows for the configuration of the lag time between the SEND/RECEIVE command execution
 * and when the driver polls for the completion status of the transmission.  Under normal conditions,
 * it is inadvisable to modify this paramter, however, tweaking the delay time may allow for
 * enanced operation in some applications.
 * \arg \c SPI_INSTANCE The Instance Name of the SPI component
 * \par
 * Enter the component (instance) name of the SPI component that is used
 * to ommunicate with the W5100.  This SPI port should be configured to use
 * 8-bit data, MSB first transmission, and SPI mode 0.  The data rate is
 * depentant upon your board layout (EMI/Noise issues), and your processor
 * and bus clock speeds.
 * \note When using the SPIM or SPI mode SCB, this driver requires at least a 4-byte FIFO buffer
 * \note This component uses the internal SPI chip select generation to select the W5100.
 * \arg \c SS_NUM the slave select number used to connect to the W5100 (SCB Mode)
 * \par
 * When using the SCB component, this parameter specifies the slave select (SS) number
 * used to communicate with the W5100 device.  Valid values are from 0 to 3, values outside
 * of this range are assumed to be 0 and will use the SS1 pin.
 * \section api_sec Application Programming Iinterface
 * The functions of the Application Programming interface (API) provide the ability
 * to configure and operate the W5100 device using your software application.  The following
 * sections describe the driver API in detail.
 * \par
 * By default, PSoC Creator assigns the name \c W5100_1 to the first instance of the driver
 * component within your project.  You may rename the component to any unique name within
 * your project, provided it follows the syntax rules defined within PSoC Creator.  The name
 * of the instance becomes the prefix for each global identifier within the driver so that
 * no interface of the driver will interfere with your software project.  For simplicity, API
 * references within this document will use the instance name prefix of \t W5100.
 * \subsection api_func_subsec API Functions
 * \li W5100_Start() : Startup and initialize the device using the creator defaults
 * \li W5100_Init() : initialize device parameters and memory setup
 * \li W5100_ParseIP() : Parse a ASCII Text IPv4 address to an IPv4 Address.
 * \li W5100_SetIP() : re-assign the local IP address of the device
 * \li W5100_GetIP() : Read the current IP address of the device
 * \li W5100_SetMAC() : Re-assign the hardware address (MAC) of the device
 * \li W5100_GetMAC() : Retrieve the assigned Source hardware (MAC) address of the device
 * \li W5100_SocketOpen() : Open a socket using the specified protocol on the specified port
 * \li W5100_SocketClose() : Close a previously opened socket
 * \li W5100_SocketProcessConnections() : Process the socket connection to check for errors and remote closure
 * \li W5100_SocketEstablished() : Check the connection establishment status of the socket
 * \li W5100_SocketRxDataWaiting() : Retrieve the length of waiting Receive data
 * \li W5100_TcpOpen() : Open an port using the TCP protocol
 * \li W5100_TcpStartServer() : Start a server listening for connection on an open socket
 * \li W5100_TcpStartServerWait() : Start a TCP server listening for connections on the specified socket
 * \li W5100_TcpConnect() : Open a client connection to a specified IP and port
 * \li W5100_TcpConnected() : Return the connection status of the TCP socket
 * \li W5100_TcpDisconnect() : Terminate a connection with a remote client/server
 * \li W5100_TcpSend() : Transmit a byte packet using the built-in TCP
 * \li W5100_TcpReceive() : Receive a packet of data using the built-in TCP handler
 * \li W5100_TcpPrint() : Send a zero-terminated ASCII string using TCP
 * \li W5100_UdpOpen() : Open a Socket Port using the UDP protocol
 * \li W5100_UdpSend() : Transmit a byte packet using the built-in UDP
 * \li W5100_UdpReceive() : Receive a packet of data using the built-in p handler
 */
/**
 * \defgroup w5100 W5100 Chip Interface Driver
 * @{
 */

/**
 * \file W5100.h 
 * Interface driver definitions and prototypes
 * \author Chuck Erhardt (chuck@e2forlife.com)
 * \version `$CY_MAJOR_VERSION`.`$CY_MINOR_VERSION`
 * \date 04-NOV-2013
 * 
 */

#if !defined(`$INSTANCE_NAME`_H)
#define `$INSTANCE_NAME`_H

#define `$INSTANCE_NAME`_READ_OP         ( 0x0F )
#define `$INSTANCE_NAME`_WRITE_OP        ( 0xF0 )

#define `$INSTANCE_NAME`_IPADDRESS(x1,x2,x3,x4)   ( (uint32)(x1&0x000000FF) + (uint32)((x2<<8)&0x0000FF00) + (uint32)((x3<<16)&0x00FF0000) + ((uint32)(x4<<24)&0xFF000000 ))

#define `$INSTANCE_NAME`_PROTO_TCP        ( 1 )
#define `$INSTANCE_NAME`_PROTO_UDP        ( 2 )
#define `$INSTANCE_NAME`_PROTO_IP         ( 3 )
#define `$INSTANCE_NAME`_PROTO_MAC        ( 4 )

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
void `$INSTANCE_NAME`_Start( void );

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
 * \note this function is usuallt called from `$INSTANCE_NAME`_Start()
 * \sa `$INSTANCE_NAME`_Start()
 */
void `$INSTANCE_NAME`_Init(uint8* mac, uint32 ip, uint32 subnet, uint32 gateway);

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
uint32 `$INSTANCE_NAME`_ParseIP( const char* ipString );

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
uint8 `$INSTANCE_NAME`_SetIP( uint32 ip );

/**
 * \brief Read the current IP address of the device
 * \returns the IP address read from the device
 *
 * This function reads and returns the contents of the Source IP register
 * of the W5100 device.
 */
uint32 `$INSTANCE_NAME`_GetIP( void );

/**
 * \brief Re-assign the hardware address (MAC) of the device
 * \param *mac pointer to the 6-byte array holding the MAC address
 *
 * This function will store the contents of the specified MAC address to the
 * source Hardware Address register (MAC address) for the W5100 device.
 */
void `$INSTANCE_NAME`_SetMAC( uint8* mac );

/**
 * \brief Retrieve the assigned Source hardware (MAC) address of the device
 * \param *mac pointer to the 6-byte array to hold the read value.
 *
 * This function will read the assigned MAC address and store it within the
 * specified array.
 */
void `$INSTANCE_NAME`_GetMAC( uint8* mac );

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
 * \sa `$INSTANCE_NAME`_PROTO_TCP
 * \sa `$INSTANCE_NAME`_PROTO_UDP
 * \sa `$INSTANCE_NAME`_PROTO_IP
 * \sa `$INSTANCE_NAME`_PROTO_MAC
 */
uint8 `$INSTANCE_NAME`_SocketOpen( uint8 Protocol, uint16 port, uint8 flags );

/**
 * \brief Close a previously opened socket
 * \param socket the Socket number (0 - 3) to close
 *
 * This fucntion will close (and disconnect) an open socket, and flush
 * the allocation record from memory.  If an invlaid socket is specified,
 * the function will ignore the request.  Closing an alread closed socket
 * has no effect.
 */
void `$INSTANCE_NAME`_SocketClose( uint8 socket );

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
uint8 `$INSTANCE_NAME`_SocketProcessConnections( uint8 socket );

/**
 * \brief Check the connection establishment status of the socket
 * \param socket the socket to be checked.
 * \retval TRUE the socket is established
 * \retval FALSE the socket has not yet been established
 *
 * This fucntion will read the socket status and return the state of the
 * socket establishment.
 */
uint8 `$INSTANCE_NAME`_SocketEstablished( uint8 socket );

/**
 * \brief Retrieve the length of waiting Receive data
 * \param socket the socket which will be polled for waiting receive data
 * \returns the length of waiting data in the receive buffer.
 *
 * This function will read the waiting data length from the Receive buffer
 * and return the read length of waiting data.
 */
uint16 `$INSTANCE_NAME`_SocketRxDataWaiting( uint8 socket );

#if (`$INCLUDE_TCP`)
	
/**
 * \brief Open an port using the TCP protocol
 * \param port the port on which the TCP socket will be openend
 * \returns The socket number that was opened (0-3) or 0xFF on error
 *
 * This function will open and initialize a socket using the W5100 buit-in
 * TCP protocol, and return the socket number for the opened TCP socket.
 * When there are no sockets available, or there is an error opening the
 * socket, 0xFF is returned.
 * \sa `$INSTANCE_NAME`_SocketOpen()
 * \sa `$INSTANCE_NAME`_SocketClose()
 */
uint8 `$INSTANCE_NAME`_TcpOpen(uint16 port);

/**
 * \brief Start a server listening for connection on an open socket
 * \param socket The socket on which listening will occur.
 *
 * This function will execute the socket command to begin listening for
 * connections on the specified socket.  If the socket specified is not
 * a valid socket nothing will occur.  After starting the listen operation,
 * this function will return (NON-BLOCKING).
 * \sa `$INSTANCE_MAME`_TcpOpen()
 * \sa `$INSTANCE_NAME`_SocketClose()
 */
void `$INSTANCE_NAME`_TcpStartServer( uint8 socket );

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
 * \sa `$INSTANCE_NAME`_TcpStartServer()
 * \sa `$INSTANCE_NAME`_TcpOPen();
 * \sa `$INSTANCE_NAME`_SocketClose()
 */
void `$INSTANCE_NAME`_TcpStartServerWait( uint8 socket );

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
 * \sa `$INSTANCE_NAME`_SocketClose()
 * \sa `$INSTANCE_NAME`_TcpOpen()
 * \sa `$INSTANCE_NAME`_TcpStartServer()
 * \sa `$INSTANCE_NAME`_TcpStartServerWait()
 * \sa `$INSTANCE_NAME`_TcpConnected()
 * \sa `$INSTANCE_NAME`_TcpDisconnect()
 */
void `$INSTANCE_NAME`_TcpConnect( uint8 socket, uint32 ip, uint16 port );

/**
 * \brief Return the connection status of the TCP socket
 * \param socket the socket on which connection status will be polled
 * \retval TRUE When the socket is connected and valid
 * \retval FALSE when the socket is not connected, waiting, or invalid
 *
 * This function will check the establishment status of the specified socket,
 * and return the state.
 * \sa `$INSTANCE_NAME`_TcpConnect()
 * \sa `$INSTANCE_NAME`_TcpStartServer()
 */
uint8 `$INSTANCE_NAME`_TcpConnected( uint8 socket );

/**
 * \brief Terminate a connection with a remote client/server
 * \param socket The socket on which the connection will be terminated
 *
 * This function will issue the disconnect function to initiate a connection
 * termination between the W5100 socket and the remote client/server.
 * \sa `$INSTANCE_NAME`_TcpConnect()
 * \sa `$INSTANCE_NAME`_TcpStartServer()
 * \sa `$INSTANCE_NAME`_TcpStartServerWait()
 */
void `$INSTANCE_NAME`_TcpDisconnect( uint8 socket );

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
 * \sa `$INSTANCE_NAME`_TcpOpen()
 * \sa `$INSTANCE_NAME`_TcpConnect()
 * \sa `$INSTANCE_NAME`_TcpStartServer()
 * \sa `$INSTANCE_NAME`_TcpStartServerWait()
 * \sa `$INSTANCE_NAME`_TcpPrint()
 * \sa `$INSTANCE_NAME`_TcpReceive()
 */
uint16 `$INSTANCE_NAME`_TcpSend(uint8 socket, uint8* buffer, uint16 len);

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
 * \sa `$INSTANCE_NAME`_TcpOpen()
 * \sa `$INSTANCE_NAME`_TcpConnect()
 * \sa `$INSTANCE_NAME`_TcpStartServer()
 * \sa `$INSTANCE_NAME`_TcpStartServerWait()
 * \sa `$INSTANCE_NAME`_TcpPrint()
 * \sa `$INSTANCE_NAME`_TcpSend()
 */
uint16 `$INSTANCE_NAME`_TcpReceive( uint8 socket, uint8* buffer, uint16 length );

/**
 * \brief Send a zero-terminated ASCII string using TCP
 * \param socket the socket on which the print will occur
 * \param *str the ASCII-Z string to be sent
 *
 * this function is a shortcut to using the `$INSTANCE_NAME`_TcpSend()
 * to transmit a zero-terminated ASCII (ASCII-Z) string to a remote
 * client/server.
 * \sa `$INSTANCE_NAME`_TcpOpen()
 * \sa `$INSTANCE_NAME`_TcpConnect()
 * \sa `$INSTANCE_NAME`_TcpStartServer()
 * \sa `$INSTANCE_NAME`_TcpStartServerWait()
 * \sa `$INSTANCE_NAME`_TcpSend()
 * \sa `$INSTANCE_NAME`_TcpReceive()
 */
void `$INSTANCE_NAME`_TcpPrint( uint8 socket, const char* str );

#endif

#if (`$INCLUDE_UDP`)
/**
 * \brief Open an socket port using the UDP protocol
 * \param port the port on which the TCP socket will be openend
 * \returns The socket number that was opened (0-3) or 0xFF on error
 *
 * This function will open and initialize a socket using the W5100 buit-in
 * TCP protocol, and return the socket number for the opened TCP socket.
 * When there are no sockets available, or there is an error opening the
 * socket, 0xFF is returned.
 * \sa `$INSTANCE_NAME`_SocketOpen()
 * \sa `$INSTANCE_NAME`_SocketClose()
 */
uint8 `$INSTANCE_NAME`_UdpOpen(uint16 port);

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
 * \sa `$INSTANCE_NAME`_UdpReceive()
 */
uint16 `$INSTANCE_NAME`_UdpSend(uint8 socket, uint32 ip, uint16 port, uint8* buffer, uint16 length);

/**
 * \brief Receive a packet of data using the built-in UDP handler
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
 * \sa `$INSTANCE_NAME`_UdpSend()
 */
uint16 `$INSTANCE_NAME`_UdpReceive(uint8 socket, uint32 *ip, uint16 *port, uint8* buffer, uint16 length);

#endif

#endif

/* [] END OF FILE */
/** @} */
