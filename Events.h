#ifndef __EVENT_H__
#define __EVENT_H__

class Computer;

class Event {
 public:
  Event() {}

  enum EventType {
    EVENT_ARRIVAL,
    EVENT_MEDIUM_IN_USE
  };

  virtual unsigned long long GetEventTime() { return time_; }
  virtual EventType GetEventType() = 0;

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
  ArrivalEvent(unsigned long long time, Computer* dest, double arrival_rate);
  virtual EventType GetEventType() { return EVENT_ARRIVAL; }
};

class MediumInUseEvent : public Event {
 public:
  MediumInUseEvent(unsigned long long time, Computer* dest, Computer* source);
  virtual EventType GetEventType() { return EVENT_MEDIUM_IN_USE; }
};

#endif
