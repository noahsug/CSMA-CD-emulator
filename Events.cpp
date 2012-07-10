#include "Events.h"
#include "Environment.h"
#include "Computer.h"

#include <cmath>

#include "Clock.h"
#include "Random.h"

bool Event::operator<(const Event& e) {
  return time_ < e.time_;
}

bool Event::operator>(const Event& e) {
  return time_ > e.time_;
}

bool Event::operator<=(const Event& e) {
  return time_ <= e.time_;
}

bool Event::operator>=(const Event& e) {
  return time_ >= e.time_;
}

ArrivalEvent::ArrivalEvent(Computer* dest) {
  dest_ = dest;
  double rand = Random::GetDouble();
  time_ = Clock::GetTime() + (unsigned long long)((-1 / ARRIVAL_RATE) * log(1 - rand));
}

MediumSensedEvent::MediumSensedEvent(Computer* dest) {
  dest_ = dest;
  time_ = Clock::GetTime() + Computer::SENSE_MEDIUM_TIME;
}

MediumBusyEvent::MediumBusyEvent(Computer* dest, Computer* source) {
  dest_ = dest;
  time_ = Clock::GetTime() + 5; // TODO this will not always be 5 :O
}

MediumFreeEvent::MediumFreeEvent(Computer* dest) {
  dest_ = dest;
  time_ = Clock::GetTime() + 5; // TODO see above todo D:
}

