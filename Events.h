class Event {
 public:
  Event();

  enum EventType {
    EVENT_ARRIVAL;
  };

  virtual unsigned long long GetEventTime() = 0;
  virtual EventType GetEventType() = 0;
};

class ArrivalEvent : public Event {
 public:
  ArrivalEvent(unsigned long long clock);
  virtual unsigned long long GetEventTime() { return time_; }
  virtual EventType GetEventType() { return EVENT_ARRIVAL; }

 private:
  unsigned long long clock_;
};

