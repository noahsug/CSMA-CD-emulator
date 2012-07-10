#ifndef __EVENT_H__
#define __EVENT_H__

#include "Computer.h"

class Event {
 public:
  Event() {}

  enum EventType {
    EVENT_ARRIVAL, // packet arrived at comp
    EVENT_MEDIUM_BUSY, // medium is now in use at a certain comp
    EVENT_RECEIVED, // packet received by router
    EVENT_MEDIUM_SENSED, // medium free for the entire time
    EVENT_MEDIUM_FREE
  };

  virtual unsigned long long GetEventTime() { return time_; }
  virtual EventType GetEventType() = 0;
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
  ArrivalEvent(unsigned long long time, Computer* dest);
  virtual EventType GetEventType() { return EVENT_ARRIVAL; }
  virtual void HandleEvent() { dest_->OnArrival(time_); }

  static double ARRIAVL_RATE;
};

class MediumBusyEvent : public Event {
 public:
  MediumBusyEvent(unsigned long long time, Computer* dest, Computer* source);
  virtual EventType GetEventType() { return EVENT_MEDIUM_BUSY; }
  virtual void HandleEvent() { dest_->OnMediumInUse(time_); }
};

#endif
