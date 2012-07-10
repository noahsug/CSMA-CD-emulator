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

ArrivalEvent::ArrivalEvent(unsigned long long time, double arrival_rate) {
  double rand = Random::GetDouble();
  time_ = time + (unsigned long long)((-1 / arrival_rate) * log(1 - rand));
}

MediumInUseEvent::MediumInUseEvent(unsigned long long time, Computer* source) {
  time_ = 5; // TODO this will not always be 5 :O
}
