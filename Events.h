#ifndef __EVENT_H__
#define __EVENT_H__

#include "Computer.h"

class Event {
 public:
  Event() {}

  enum EventType {
    EVENT_ARRIVAL,
    EVENT_MEDIUM_IN_USE
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

class MediumInUseEvent : public Event {
 public:
  MediumInUseEvent(unsigned long long time, Computer* dest, Computer* source);
  virtual EventType GetEventType() { return EVENT_MEDIUM_IN_USE; }
  virtual void HandleEvent() { dest_->OnMediumInUse(time_); }
};

#endif
