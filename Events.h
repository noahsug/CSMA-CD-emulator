#ifndef __EVENT_H__
#define __EVENT_H__

#include "Computer.h"

class Event {
 public:
  Event() {}
  
  enum EventType {
    EVENT_ARRIVAL, // frame arrived at comp
    EVENT_MEDIUM_BUSY, // medium is now in use at a certain comp
    EVENT_MEDIUM_SENSED, // medium sensing over
    EVENT_MEDIUM_FREE, // medium is now free
    EVENT_TRANSMITTED_FRAME, // frame successfully transmitted
    EVENT_JAM, // jamming event arrived at comp
    EVENT_BACKOFF_DONE // backoff finished
  };

  virtual unsigned long long GetTime() { return time_; }
  virtual EventType GetType() = 0;
  virtual void HandleEvent() = 0;

  bool operator<(const Event&);
  bool operator>(const Event&);
  bool operator<=(const Event&);
  bool operator>=(const Event&);

 protected:
  Computer* dest_;
  unsigned long long time_;
};

class ArrivalEvent : public Event {
 public:
  ArrivalEvent(Computer* dest);
  virtual EventType GetType() { return EVENT_ARRIVAL; }
  virtual void HandleEvent() { dest_->OnArrival(); }
};

class MediumSensedEvent : public Event {
 public:
  MediumSensedEvent(Computer* dest);
  virtual EventType GetType() { return EVENT_MEDIUM_SENSED; }
  virtual void HandleEvent() { dest_->OnMediumSensed(); }
};

class MediumBusyEvent : public Event {
 public:
  MediumBusyEvent(Computer* dest);
  virtual EventType GetType() { return EVENT_MEDIUM_BUSY; }
  virtual void HandleEvent() { dest_->OnMediumBusy(); }
};

class MediumFreeEvent : public Event {
 public:
  MediumFreeEvent(Computer* dest);
  virtual EventType GetType() { return EVENT_MEDIUM_FREE; }
  virtual void HandleEvent() { dest_->OnMediumFree(); }
};

class TransmittedFrameEvent : public Event {
 public:
  TransmittedFrameEvent(Computer* dest);
  virtual EventType GetType() { return EVENT_TRANSMITTED_FRAME; }
  virtual void HandleEvent() { dest_->OnTransmittedFrame(); }
};

class RaspberryJamEvent : public Event {
 public:
  RaspberryJamEvent(Computer* dest);
  virtual EventType GetType() { return EVENT_JAM; }
  virtual void HandleEvent() { dest_->OnRaspberryJam(); }
};

class BackoffDoneEvent : public Event {
 public:
  BackoffDoneEvent(Computer* dest);
  virtual EventType GetType() { return EVENT_BACKOFF_DONE; }
  virtual void HandleEvent() { dest_->OnBackoffDone(); }
};

#endif
