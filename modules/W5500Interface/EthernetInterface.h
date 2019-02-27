// EthernetInterface for W5500 2014/8/20

#pragma once
#include "wiznet.h"

using namespace W5500;

 /** Interface using Wiznet W5500 chip to connect to an IP-based network
 *
 */
class EthernetInterface: public WIZnet_Chip {
public:

    /**
    * Constructor
    *
    * \param mosi mbed pin to use for SPI
    * \param miso mbed pin to use for SPI
    * \param sclk mbed pin to use for SPI
    * \param cs chip select of the WIZnet_Chip
    * \param reset reset pin of the WIZnet_Chip
    */
    EthernetInterface(PinName mosi, PinName miso, PinName sclk, PinName cs, PinName reset);
    EthernetInterface(SPI* spi, PinName cs, PinName reset);

  /** Initialize the interface with DHCP w/o MAC address
  * Initialize the interface and configure it to use DHCP (no connection at this point).
  * \return 0 on success, a negative number on failure
  */
  int init(); //With DHCP
  /** Initialize the interface with DHCP.
  * Initialize the interface and configure it to use DHCP (no connection at this point).
  * \param mac the MAC address to use
  * \return 0 on success, a negative number on failure
  */
  int init(uint8_t * mac); //With DHCP

  /** Initialize the interface with a static IP address without MAC.
  * Initialize the interface and configure it with the following static configuration (no connection at this point).
  * \param ip the IP address to use
  * \param mask the IP address mask
  * \param gateway the gateway to use
  * \return 0 on success, a negative number on failure
  */

  int init(const char* ip, const char* mask, const char* gateway);
  /** Initialize the interface with a static IP address.
  * Initialize the interface and configure it with the following static configuration (no connection at this point).
  * \param mac the MAC address to use
  * \param ip the IP address to use
  * \param mask the IP address mask
  * \param gateway the gateway to use
  * \return 0 on success, a negative number on failure
  */
  int init(uint8_t * mac, const char* ip, const char* mask, const char* gateway);

  /** Connect
  * Bring the interface up, start DHCP if needed.
  * \return 0 on success, a negative number on failure
  */
  int connect();
  
  /** Disconnect
  * Bring the interface down
  * \return 0 on success, a negative number on failure
  */
  int disconnect();
  
  /** Get IP address
  *
  * @ returns ip address
  */
  char* getIPAddress();
  char* getNetworkMask();
  char* getGateway();
  char* getMACAddress();

  int IPrenew(int timeout_ms = 30*1000);
    
private:
    char ip_string[20];
    char mask_string[20];
    char gw_string[20];
    char mac_string[20];
    bool ip_set;
};

#include "TCPSocketConnection.h"
#include "TCPSocketServer.h"
#include "UDPSocket.h"
