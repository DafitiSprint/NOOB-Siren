/*
  Websocket.cpp
*/

#include "Arduino.h"
#include "Websocket.h"
#include <Ethernet.h>
#include <SPI.h>
#include <WSClient.h>

Websocket::Websocket(EthernetClient client, char *host, char *path, int port)
{
  _client = client;
  _host   = host;
  _path   = path;
  _port   = port;
  _isConnected = false;

  _wsClient.path = path;
  _wsClient.host = "echo.websocket.org";
}

void Websocket::connect()
{
  Serial.println("Connecting to Host");
  if (!_client.connect(_host, _port)) {
    Serial.println("Gone wrong =/");
    _isConnected = false;
    return;
  }
  Serial.println("Done");

  Serial.println("Sending Handshake");
  if (!_wsClient.handshake(_client)) {
    Serial.println("Gone wrong =/");
    _isConnected = false;
    return;
  }
  Serial.println("Done");

  _isConnected = true;
}

void Websocket::disconnect()
{
  _isConnected = false;
  _wsClient.disconnect();
  Serial.println("Disconected");
}

bool Websocket::isConnected()
{
  if (_client.connected() && _isConnected) {
    return true;
  }
  
  if (_isConnected) {
    disconnect();
  }

  return false;
}

char* Websocket::getData()
{
  return _wsClient.getData();
}

void Websocket::sendData(char *str)
{
  _wsClient.sendData(str);
}
