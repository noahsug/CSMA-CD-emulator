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

  enum State {
    IDLE,
    WAITING_TO_TRANSMIT,
    TRANSMITTING,
    BACKING_OFF,
  };

  Computer(PriorityQueue<Event*>* events, unsigned distance)
    : events_(events)
    , state_(STATE_IDLE)
    , distance_from_router_(distance)
    , medium_busy_(false)
    , backoff_count_(0)
    , packet_queue_size_(0) {}

  void OnArrival();
  void OnMediumSensed();
  void OnMediumBusy();
  void OnMediumFree();

 private:
  PriorityQueue<Event*>* events_;
  State state_;
  unsigned distance_from_router_;
  bool medium_busy_;
  unsigned backoff_count_;
  unsigned packet_queue_size_;
};

#endif

