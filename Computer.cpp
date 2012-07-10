#include "Computer.h"

#include "Clock.h"
#include "Environment.h"
#include "Events.h"

using std::vector;

extern vector<Computer> computers;

void Computer::OnArrival() {
  //Router::OnPacketGenerated(this);
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
    last_jam_time_ = (unsigned long long)-1;
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
    last_jam_time_ = Clock::GetTime();
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
  Event* rec = new PacketReceivedEvent(this);
  events_->Insert(rec);
  cancellable_events_.push_back(rec);

  packet_queue_size_--;
  if (packet_queue_size_ > 0) {
    state_ = SENSING;
    events_->Insert(new MediumSensedEvent(this));
  } else {
    state_ = IDLE;
  }
}

void Computer::OnRaspberryJam() {
  last_jam_time_ = Clock::GetTime();
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

void Computer::OnPacketReceived() {
  if (last_jam_time_ - Environment::PROP_TIME < Clock::GetTime()) {
    //Router::OnPacketDropped(this);
  } else {
    //Router::OnPacketTransmitted(this);
  }
}

void Computer::CancelEvents() {
  for (unsigned i = 0; i < cancellable_events_.size(); i++) {
    events_->Remove(cancellable_events_[i]);
  }
  cancellable_events_.clear();
}

unsigned long Computer::GetBackoff() {
  unsigned long ret = backoff_count_;
  backoff_count_ = (backoff_count_ + 1) % Computer::KMAX;
  return ret;
}

