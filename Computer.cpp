#include "Computer.h"

#include "Events.h"

void Computer::OnArrival() {
  events_->Insert(new ArrivalEvent(this));
  if (state_ == IDLE) {
    events_->Insert(new MediumSensedEvent(this));
  }
}

void Computer::OnMediumSensed() {
  if (medium_busy_) {
    state_ = WAITING_TO_TRANSMIT;
  } else {
    state_ = TRANSMITTING;
  }
}

void Computer::OnMediumBusy() {
  medium_busy_ = true;

  if (state_ == TRANSMITTING) {
    // OSHIT. RASPBERRY JAM THYME.
  } else {
    events_->Insert(new MediumFreeEvent(this));
  }
}

void Computer::OnMediumFree() {
  medium_busy_ = false;
  if (state_ == WAITING_TO_TRANSMIT) {
    state_ = IDLE;
    events_->Insert(new MediumSensedEvent(this));
  }
}

