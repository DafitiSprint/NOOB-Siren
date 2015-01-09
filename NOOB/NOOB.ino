#include "Arduino.h"
#include <Ethernet.h>
#include <SPI.h>
#include <WSClient.h>
#include "Siren.h"
#include "Websocket.h"

EthernetClient client;

Siren *siren;
Websocket *websocket;

char *host = "0.0.0.0";
int port = 80;
int pin = 6;
int refreshConnection = 150;
int count = 0;

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x78 };

void setup()
{
  Serial.begin(9600);
  Serial.println("START");
  
  Ethernet.begin(mac); // initialize ethernet
  Serial.print("Ethernet Connected - IP: ");
  Serial.println(Ethernet.localIP()); // printout IP address for debug purposes
  delay(300); // this is arduino baby ;-)
    
  siren = new Siren(pin);
  websocket = new Websocket(client, host, "/?type=siren", port);
}

void loop()
{
  if (!websocket->isConnected()) {
    Serial.println("Websocket is not Connected");
    _websocketConnect();
    return;
  }
//  Serial.println("Connected");
  count = count + 1;
//  Serial.println(count);

  String data = websocket->getData();
  if (data.length() > 0) {
     Serial.println("Message Received");
     Serial.println(data);
     int div = data.indexOf('-');
     siren->setDelay(data.substring(0, div).toInt());
     Serial.println(data.substring(0, div).toInt());
     siren->setRepeat(data.substring(div + 1, data.length()).toInt());
     Serial.println(data.substring(div + 1, data.length()).toInt());
     siren->blink();
     count = 0;
  } else if (count >= refreshConnection) {
    //Disconect to refresh connection
    Serial.println("Disconecting from server");
    websocket->disconnect();
    count = 0;
    delay(3000);  // wait to fully let the client disconnect
  }
  
  delay(3000);  // wait to fully let the client disconnect
}

void _websocketConnect()
{
  Serial.println("Connecting Websocket");
  websocket->connect();
}
