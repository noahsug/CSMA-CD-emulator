#include "Computer.h"

#include <iostream>

#include "Clock.h"
#include "Debug.h"
#include "Environment.h"
#include "Events.h"
#include "Router.h"

using std::vector;

extern vector<Computer*> computers;

void Computer::OnArrival() {
  PRINT(this << ": " << Clock::GetTime() << ": OnArrival" << std::endl);

  Router::GetInstance().OnPacketGenerated(this);
  packet_queue_size_++;

  if (!Environment::GameOverMan) {
    events_->Insert(new ArrivalEvent(this));
  }

  if (state_ == IDLE) {
    state_ = SENSING;
    events_->Insert(new MediumSensedEvent(this));
  }
}

void Computer::OnMediumSensed() {
  PRINT(this << ": " << Clock::GetTime() << ": OnMediumSensed" << std::endl);

  if (medium_busy_) {
    state_ = WAITING_TO_TRANSMIT;
  } else {
    state_ = TRANSMITTING;
    last_jam_time_ = (unsigned long long)-1;
    Event* trans = new TransmittedFrameEvent(this);
    events_->Insert(trans);
    cancellable_events_.push_back(trans->GetId());

    for (unsigned i = 0; i < computers.size(); i++) {
      if (computers[i] != this) {
        events_->Insert(new MediumBusyEvent(computers[i]));
      }
    }
  }
}

void Computer::OnMediumBusy() {
  PRINT(this << ": " << Clock::GetTime() << ": OnMediumBusy" << std::endl);

  if (state_ == TRANSMITTING) {
    CancelEvents();
    for (unsigned i = 0; i < computers.size(); i++) {
      if (computers[i] != this) {
        events_->Insert(new RaspberryJamEvent(computers[i]));
      }
    }
    state_ = BACKING_OFF;
    medium_busy_ = false;
    events_->Insert(new BackoffDoneEvent(this));
    last_jam_time_ = Clock::GetTime();
  } else {
    medium_busy_ = true;
    Event* free = new MediumFreeEvent(this);
    events_->Insert(free);
    cancellable_events_.push_back(free->GetId());
  }
}

void Computer::OnMediumFree() {
  PRINT(this << ": " << Clock::GetTime() << ": OnMediumFree" << std::endl);
  medium_busy_ = false;
  if (state_ == WAITING_TO_TRANSMIT) {
    state_ = SENSING;
    events_->Insert(new MediumSensedEvent(this));
  }
}

void Computer::OnTransmittedFrame() {
  PRINT(this << ": " << Clock::GetTime() << ": OnTransmittedFrame" << std::endl);
  Event* rec = new PacketReceivedEvent(this);
  events_->Insert(rec);
  cancellable_events_.push_back(rec->GetId());

  packet_queue_size_--;
  if (packet_queue_size_ > 0) {
    state_ = SENSING;
    events_->Insert(new MediumSensedEvent(this));
  } else {
    state_ = IDLE;
  }
}

void Computer::OnRaspberryJam() {
  PRINT(this << ": " << Clock::GetTime() << ": OnRaspberryJam" << std::endl);
  last_jam_time_ = Clock::GetTime();
  if (state_ == TRANSMITTING) {
    CancelEvents();
    state_ = BACKING_OFF;
    events_->Insert(new BackoffDoneEvent(this));
  } else {
    medium_busy_ = true;
    Event* free = new MediumFreeEvent(this);
    events_->Insert(free);
    cancellable_events_.push_back(free->GetId());
  }
}

void Computer::OnBackoffDone() {
  PRINT(this << ": " << Clock::GetTime() << ": OnBackoffDone" << std::endl);
  state_ = SENSING;
  events_->Insert(new MediumSensedEvent(this));
}

void Computer::OnPacketReceived() {
  PRINT(this << ": " << Clock::GetTime() << ": OnPacketReceived" << std::endl);
  if (last_jam_time_ - Environment::PROP_TIME < Clock::GetTime()) {
    Router::GetInstance().OnPacketDropped(this);
  } else {
    Router::GetInstance().OnPacketTransmitted(this);
  }
}

void Computer::CancelEvents() {
  for (unsigned i = 0; i < cancellable_events_.size(); i++) {
    events_->Remove(cancellable_events_[i]);
  }
  cancellable_events_.clear();
}

unsigned long Computer::GetBackoff() {
  backoff_count_++;
  if (backoff_count_ > Computer::KMAX) {
    backoff_count_ = Computer::KMAX;
  }
  return backoff_count_;
}

