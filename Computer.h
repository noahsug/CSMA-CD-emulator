#ifndef __COMPUTER_H__
#define __COMPUTER_H__

#include "Events.h"

class Computer {
 public:
  Computer(int distance): distance_from_router_(distance) {}

  void OnEvent(Event* event);

 protected:
  unsigned int distance_from_router_;
};

#endif

