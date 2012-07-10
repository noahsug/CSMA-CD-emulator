#include "Events.h"

#include "Random.h"

ArrivalEvent::ArrivalEvent(unsigned long long clock) {
  double rand = Random::GetDouble();
  clock_ = clock + (-1 / arrival_rate) * log(1 - rand);
}

