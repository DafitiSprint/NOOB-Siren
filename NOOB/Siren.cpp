/*
  Siren.cpp
*/

#include "Arduino.h"
#include "Siren.h"

Siren::Siren(int portId, int delay, int repeat)
{
  pinMode(portId, OUTPUT);
  _portId = portId;
  _delay  = delay;
  _repeat = repeat;
}

void Siren::on() {
  digitalWrite(_portId, HIGH);
  delay(_delay);
}

void Siren::off() {
  digitalWrite(_portId, LOW);
  delay(_delay);
}

void Siren::setDelay(int delay) {
  _delay = delay;
}

void Siren::setRepeat(int repeat) {
  _repeat = repeat;
}

void Siren::blink() {
  for(int i=0; i<=_repeat; i++) {
    on();
    off();
  }
}
