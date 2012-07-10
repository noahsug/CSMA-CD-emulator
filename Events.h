class Event {
 public:
  Event();

  enum EventType {
    EVENT_ARRIVAL;
  };

  virtual unsigned long long GetEventTime() { return time_; }
  virtual EventType GetEventType() = 0;

 protected:
  unsigned long long time_;
};

class ArrivalEvent : public Event {
 public:
  ArrivalEvent(unsigned long long clock);
  virtual EventType GetEventType() { return EVENT_ARRIVAL; }
};

