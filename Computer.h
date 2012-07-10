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

  Computer(PriorityQueue<Event*>* events, unsigned position)
    : events_(events)
    , position_(position)
    , medium_busy_(false)
    , waiting_to_transmit_(false)
    , backoff_count_(0)
    , packet_queue_size_(0) {}

  void OnArrival();
  void OnMediumSensed();
  void OnMediumBusy();
  void OnMediumFree();

 private:
  PriorityQueue<Event*>* events_;
  unsigned position_;
  bool medium_busy_;
  unsigned waiting_to_transmit_;
  unsigned backoff_count_;
  unsigned packet_queue_size_;
};

#endif

