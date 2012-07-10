#include "Computer.h"

#include "Events.h"

void Computer::OnArrival() {
  events_->Insert(new ArrivalEvent(this));
  events_->Insert(new MediumSensedEvent(this));
}

void Computer::OnMediumSensed() {
  if (medium_busy_) {
    waiting_to_transmit_ = true;
  } else {
    // Send packet
  }
}

void Computer::OnMediumBusy() {
  medium_busy_ = true;
  events_->Insert(new MediumFreeEvent(this));
}

void Computer::OnMediumFree() {
  medium_busy_ = false;
  if (waiting_to_transmit_) {
    waiting_to_transmit_ = false;
    events_->Insert(new MediumSensedEvent(this));
  }
}

