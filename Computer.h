#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include <vector>

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
    SENSING,
    WAITING_TO_TRANSMIT,
    TRANSMITTING,
    BACKING_OFF,
  };

  Computer(PriorityQueue* events)
    : events_(events)
    , state_(IDLE)
    , medium_busy_(false)
    , backoff_count_(0)
    , packet_queue_size_(0)
    , last_jam_time_((unsigned long long)-1) {}

  unsigned long GetBackoff();

  void OnArrival();
  void OnMediumSensed();
  void OnMediumBusy();
  void OnMediumFree();
  void OnTransmittedFrame();
  void OnRaspberryJam();
  void OnBackoffDone();
  void OnPacketReceived();

 private:
  PriorityQueue* events_;
  State state_;
  bool medium_busy_;
  unsigned backoff_count_;
  unsigned packet_queue_size_;
  unsigned last_jam_time_;

  std::vector<Event*> cancellable_events_;

  void CancelEvents();
};

#endif

