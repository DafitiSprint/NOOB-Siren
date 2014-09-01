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

byte mac[] = {
  0x90, 0xA2, 0xDA, 0x00, 0xF2, 0x78 };

int ethernetStatus = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("START");

  siren = new Siren(pin);
  websocket = new Websocket(client, host, "/", port);

  _ethernetConnect();

  Serial.println("Connecting...");
  websocket->connect();
}

void loop()
{
  if (!ethernetStatus || !client.available()) {
    Serial.println("Ethernet connection is offline");
    delay(5000);

    Serial.println("Trying to reconnect the ethernet");
    _ethernetConnect();
  }

  if (websocket->isConnected()) {
     Serial.println("Connected");

     String data = websocket->getData();

     if (data.length() > 0) {
       siren->setDelay(data.toInt());
       siren->on();
       siren->off();
     }

     return;
  }

  Serial.println("Connection failed");
  delay(5000);

  Serial.println("Trying to reconnect");
  delay(5000);

  websocket->connect();
  delay(5000);
}

void _ethernetConnect()
{
  Serial.println("Starting Ethernet");
  delay(5000);

  ethernetStatus = Ethernet.begin(mac);

  if (!ethernetStatus) {
    Serial.println("Was not possible to assign the IP");
    return;
  }

  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());
}
