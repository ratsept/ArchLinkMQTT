#include "mbed.h"
#include "EthernetInterface.h"
#include "MQTTEthernet.h"
#include "MQTTClient.h"
#include "dht22.h"

void messageArrived(MQTT::MessageData &md)
{
    MQTT::Message &message = md.message;
 
    printf("Message ('%.*s') arrived: qos %d, retained %d, dup %d, packetid %d\r\n", message.payloadlen, (char *)message.payload, message.qos, message.retained, message.dup, message.id);
}

int main() {
    printf("ArcLink booting...\n\r");

    SPI spi(p25, p28, p29); // mosi, miso, sclk
    EthernetInterface eth(&spi, p24, p17); // spi, cs, reset
    DHT22 sens(p1);

    eth.init(); //Use DHCP
    printf("MAC:%s\n\r", eth.getMACAddress());
    if(eth.connect() == 0) {
        printf("IP Address is %s\n\r", eth.getIPAddress());
    } else {
        printf("Error while connecting.\n\r");
    }
    MQTTPacket_connectData data = MQTTPacket_connectData_initializer;
    data.MQTTVersion = 3;
    data.clientID.cstring = "ArchLink";
    data.username.cstring = "user";
    data.password.cstring = "pass";
    data.keepAliveInterval = 30;
    
    MQTTEthernet ipstack = MQTTEthernet();
    int rc = ipstack.connect("192.168.0.2",1883);
    printf("ipstack connect returned %d\n\r", rc);
    MQTT::Client<MQTTEthernet, Countdown> *client = new MQTT::Client<MQTTEthernet, Countdown>(ipstack);
    rc = client->connect(data);
    printf("mqtt connect returned %d\n\r", rc);
    
    if ((rc = client->subscribe("home/#", MQTT::QOS0, messageArrived)) != 0) {
        printf("rc from MQTT subscribe is %d\r\n", rc);
    } else {
        printf("rc from MQTT subscribe is %d\r\n", rc);
    }

    int index = 0;
    MQTT::Message message;
	char buf[64];
    while(1) {
        printf("Reading temperature and humidity\n\r");
        sens.sample();
        int temp = sens.getTemperature();
        int hum = sens.getHumidity();
		printf("Sending payload #%d\n\r", index++);
    	sprintf(buf,  "{\"DHT22\": {\"temperature\":%d, \"humidity\":%d}}", temp, hum);
    	message.qos = MQTT::QOS0;
    	message.retained = false;
    	message.dup = false;
    	message.payload = (void*)buf;
    	message.payloadlen = strlen(buf);
    	rc = client->publish("home/archlink/temperature", message);
        
		wait(1);    
    }
 
}
