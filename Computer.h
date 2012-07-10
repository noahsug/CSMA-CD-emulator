#include "Events.h"

class Computer {
 public:
  Computer(int distance): distanceFromRouter_(distance);

  void OnEvent(Event event);

 protected:
  unsigned int distanceFromRouter_;
};
