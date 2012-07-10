#include "Computer.h"

#include "Events.h"

void Computer::OnArrival(unsigned long long time) {
  events_->Insert(new ArrivalEvent(time, this));
  events_->Insert(new MediumSensedEvent(time, this));
}

void Computer::OnMediumSensed(unsigned long long time) {
  if (medium_busy_) {
    //
  } else {
    // Send packet
  }
}

void Computer::OnMediumBusy(unsigned long long time) {
  medium_busy_ = true;
  events->Insert(new MediumFree(time + /*XXX*/));
}

void Computer::OnMediumFree(unsigned long long time) {
  medium_busy_ = false;
}

