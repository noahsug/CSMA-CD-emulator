#include "Events.h"

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
  time_ = time + (-1 / arrival_rate) * log(1 - rand);
}

