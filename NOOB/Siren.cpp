/*
  Siren.cpp
*/

#include "Arduino.h"
#include "Siren.h"

Siren::Siren(int portId, int delay)
{
  pinMode(portId, OUTPUT);
  _portId = portId;
  _delay  = delay;
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
