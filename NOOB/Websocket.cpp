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

  _wsClient.path = path;
  _wsClient.host = host;
}

void Websocket::connect()
{
  if (!_client.connect(_host, _port)) {
    _isConnected = false;
    return;
  }

  if (!_wsClient.handshake(_client)) {
    _isConnected = false;
    return;
  }

  _isConnected = true;
}

bool Websocket::isConnected()
{
  if (_client.available() && _client.connected() && _isConnected) {
    return true;
  }

  _client.stop();

  return false;
}

char* Websocket::getData()
{
  return _wsClient.getData();
}
