#ifndef RELAY_H
#define RELAY_H
#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <StandardCplusplus.h>
#include <serstream>
#include <vector>
#include <iterator>
class Relay {
  public:
    enum Status {
      OFF = HIGH,
      ON = LOW
    };
    Relay(uint8_t);
    Status getStatus();
    void setStatus(Status);
    void toggle(const Status);
    unsigned long getCounter();
    uint8_t getPin();
    static void applyToAll(std::vector<Relay> &, Status);
    static unsigned int getNumberOf(std::vector<Relay> &, Status);
    static void applyTo(std::vector<Relay> &, Status, int number);
    static unsigned long getAllCounter(std::vector<Relay> &);
  private:
    unsigned long counter = 0;
    uint8_t pin;
    Status status;
    void setPin(uint8_t);
};
#endif