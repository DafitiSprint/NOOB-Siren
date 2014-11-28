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
  int _repeat;

  public:
  Siren(int portId, int delay = 1000, int repeat = 1);

  void on();
  void off();
  void setDelay(int delay);
  void setRepeat(int repeat);
  void blink();
};

#endif
