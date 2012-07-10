#include "Computer.h"

#include "Events.h"

using std::vector;

extern vector<Computer> computers;

void Computer::OnArrival() {
  packet_queue_size_++;
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
    Event* trans = new TransmittedFrameEvent(this);
    events_->Insert(trans);
    cancellable_events_.push_back(trans);

    for (unsigned i = 0; i < computers.size(); i++) {
      if (&computers[i] != this) {
        events_->Insert(new MediumBusyEvent(&computers[i]));
      }
    }
  }
}

void Computer::OnMediumBusy() {
  medium_busy_ = true;

  if (state_ == TRANSMITTING) {
    CancelEvents();
    for (unsigned i = 0; i < computers.size(); i++) {
      if (&computers[i] != this) {
        events_->Insert(new RaspberryJamEvent(&computers[i]));
      }
    }
    state_ = BACKING_OFF;
    events_->Insert(new BackoffDoneEvent(this));
  } else {
    Event* free = new MediumFreeEvent(this);
    events_->Insert(free);
    cancellable_events_.push_back(free);
  }
}

void Computer::OnMediumFree() {
  medium_busy_ = false;
  if (state_ == WAITING_TO_TRANSMIT) {
    state_ = SENSING;
    events_->Insert(new MediumSensedEvent(this));
  }
}

void Computer::OnTransmittedFrame() {
  //Router::FrameTransmitted();
  packet_queue_size_--;
  if (packet_queue_size_ > 0) {
    state_ = SENSING;
    events_->Insert(new MediumSensedEvent(this));
  } else {
    state_ = IDLE;
  }
}

void Computer::OnRaspberryJam() {
  if (state_ == TRANSMITTING) {
    CancelEvents();
    state_ = BACKING_OFF;
    events_->Insert(new BackoffDoneEvent(this));
  } else {
    medium_busy_ = true;
    Event* free = new MediumFreeEvent(this);
    events_->Insert(free);
    cancellable_events_.push_back(free);
  }
}

void Computer::OnBackoffDone() {
  state_ = SENSING;
  events_->Insert(new MediumSensedEvent(this));
}

void Computer::CancelEvents() {
  for (unsigned i = 0; i < cancellable_events_.size(); i++) {
    events_->Remove(cancellable_events_[i]);
  }
  cancellable_events_.clear();
}
