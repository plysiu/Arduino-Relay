#include <Relay.h>
/**
 * @param int pin Pin designated for relay control.
 */
Relay::Relay(uint8_t relayPin) {
  this->setPin(relayPin);
  pinMode(this->getPin(), OUTPUT);
  this->toggle(Status::OFF);
};
/**
 * Returns current relay status.
 * @return Status
 */
Relay::Status Relay::getStatus() {
  return this->status;
};
void Relay::setStatus(Status status) {
  this->status = status;
}
/**
 * Toggle relay
 * @param Status
 * @return bool Returns true if toggle was switched
 */
void Relay::toggle(Status status) {
  if (this->getStatus() != status) {
    this->setStatus(status);
    this->counter++;
    digitalWrite(this->getPin(), this->getStatus());
    Serial.print("Relay Pin:");
    Serial.print(this->getPin());
    Serial.print(" Toggled:");
    Serial.println((Relay::Status::ON == this->getStatus() ? "ON" : "OFF"));
  }
};
/**
 * Returns how many times relay has been toggled.
 * @return long
 */
unsigned long Relay::getCounter() {
  return this->counter;
};
/**
 *
 */
uint8_t Relay::getPin() {
  return this->pin;
};
/**
 *
 */
void Relay::setPin(uint8_t pin) {
  this->pin = pin;
};
/**
 *
 */
void Relay::applyToAll(std::vector<Relay> & relays,   Status status) {
  Serial.print("Relay::applyToAll:");
  Serial.println(Status::ON == status ? "ON" : "OFF");
  for (std::vector<Relay>::iterator relay = relays.begin(); relay != relays.end(); ++relay) {
    relay->toggle(status);
  }
};

unsigned int Relay::getNumberOf(std::vector<Relay>& relays, Status status) {
  int sum = 0;
  for (std::vector<Relay>::iterator relay = relays.begin(); relay != relays.end(); ++relay) {
    if (relay->getStatus() == status) {
      sum++;
    }
  };
  return sum;
};

/**
 *
 */
void Relay::applyTo(std::vector<Relay> & relays, Status status, int number = 1) {
  if (number < 1) {
    number = 1;
  }
  Serial.print("Relay::applyTo(");
  Serial.print(number);
  Serial.print(", ");
  Serial.println(Status::ON == status ? "ON)" : "OFF)");

  for (std::vector<Relay>::iterator relay = relays.begin(); relay != relays.end(); ++relay) {
    if (Relay::getNumberOf(relays, status) != number) {

      if (Relay::getNumberOf(relays, status) < number) {
        relay->toggle(status);
      }
      else {
        relay->toggle(status == Status::ON ? Status::OFF : Status::ON);
      }
    }
  }
};

unsigned long Relay::getAllCounter(std::vector<Relay>& relays) {
  unsigned long sum = 0;
  for (std::vector<Relay>::iterator relay = relays.begin(); relay != relays.end(); ++relay) {
    sum += relay->getCounter();
  };
  return sum;
};