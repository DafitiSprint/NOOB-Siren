/*
  Siren.h
*/

#ifndef Siren_h
#define Siren_h

#include "Arduino.h"

class Siren
{
  private:
  int _portId;
  int _delay;

  public:
  Siren(int portId, int delay = 1000);

  void on();
  void off();
  void setDelay(int delay);
};

#endif
