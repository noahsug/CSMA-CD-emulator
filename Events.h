class Event {
 public:
  Event() {}

  enum EventType {
    EVENT_ARRIVAL
  };

  virtual unsigned long long GetEventTime() { return time_; }
  virtual EventType GetEventType() = 0;

  bool operator<(const Event&);
  bool operator>(const Event&);
  bool operator<=(const Event&);
  bool operator>=(const Event&);

 protected:
  unsigned long long time_;
};

class ArrivalEvent : public Event {
 public:
  ArrivalEvent(unsigned long long time, double arrival_rate);
  virtual EventType GetEventType() { return EVENT_ARRIVAL; }
};

