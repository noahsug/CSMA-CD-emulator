#ifndef __CLOCK_H__
#define __CLOCK_H__

class Clock {
 public:
  static unsigned long long GetTime() { return time_; }
  static void SetTime(unsigned long long time) { time_ = time; }

 private:
  static unsigned long long time_;
};

#endif

