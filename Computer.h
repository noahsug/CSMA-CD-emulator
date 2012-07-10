#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "Events.h"

class Computer {
  static const int KMAX = 10;

  // values are in bit-times
  static const int TP = 512;
  static const int JAMMING_LENGTH = 48;
  static const int SENSE_MEDIUM_TIME = 96;
  static const int COMP_DISTANCE = 200;

 public:
  Computer(int distance): distance_from_router_(distance) {}

  void OnEvent(Event* event);

 protected:
  unsigned int distance_from_router_;
};

#endif

