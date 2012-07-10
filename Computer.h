#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "PriorityQueue.h"

class Event;

class Computer {
 public:
  static const unsigned KMAX = 10;

  // values are in bit-times
  static const unsigned TP = 512;
  static const unsigned JAMMING_LENGTH = 48;
  static const unsigned SENSE_MEDIUM_TIME = 96;
  static const unsigned COMP_DISTANCE = 200;

  Computer(PriorityQueue<Event*>* events, unsigned distance)
    : events_(events)
    , distance_from_router_(distance)
    , medium_busy_(false) {}

  void OnArrival(unsigned long long time);
  void OnMediumInUse(unsigned long long time);
  void OnMediumBusy(unsigned long long time);
  void OnMediumFree(unsigned long long time);

 private:
  PriorityQueue<Event*>* events_;
  unsigned distance_from_router_;
  bool medium_busy_;
};

#endif

