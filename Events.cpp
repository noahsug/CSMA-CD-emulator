#include "Events.h"

#include "Random.h"

ArrivalEvent::ArrivalEvent(unsigned long long time) {
  double rand = Random::GetDouble();
  time_ = time + (-1 / arrival_rate) * log(1 - rand);
}
