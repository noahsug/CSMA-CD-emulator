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

ArrivalEvent::ArrivalEvent(unsigned long long time, Computer* dest, double arrival_rate) {
  dest_ = dest;
  double rand = Random::GetDouble();
  time_ = time + (unsigned long long)((-1 / arrival_rate) * log(1 - rand));
}

MediumBusyEvent::MediumBusyEvent(unsigned long long time, Computer* dest, Computer* source) {
  dest_ = dest;
  time_ = 5; // TODO this will not always be 5 :O
}
