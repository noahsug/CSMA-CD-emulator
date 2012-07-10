#include "Events.h"
#include "Computer.h"

#include <cmath>

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

double ArrivalEvent::ARRIAVL_RATE = 0;

ArrivalEvent::ArrivalEvent(unsigned long long time, Computer* dest) {
  dest_ = dest;
  double rand = Random::GetDouble();
  time_ = time + (unsigned long long)((-1 / ARRIAVL_RATE) * log(1 - rand));
}

MediumBusyEvent::MediumBusyEvent(unsigned long long time, Computer* dest, Computer* source) {
  dest_ = dest;
  time_ = 5; // TODO this will not always be 5 :O
}
