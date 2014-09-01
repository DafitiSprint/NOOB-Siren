/*
  Websocket.h
*/

#ifndef Websocket_h
#define Websocket_h

#include "Arduino.h"
#include <Ethernet.h>
#include <WSClient.h>

class Websocket
{
  private:
  EthernetClient _client;
  bool _isConnected;
  char *_host;
  char *_path;
  int _port;
  WSClient _wsClient;

  public:
  Websocket(EthernetClient client, char *host, char *path = "/", int port = 80);
  void connect();
  bool isConnected();
  char* getData();

};

#endif
