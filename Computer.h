#include "Events.h"

class Computer {
  static const int TP = 512;
  static const int KMAX = 10;
  static const int JAMMING_LENGTH = 48;
  static const int SENSE_MEDIUM_TIME = 96;

 public:
  Computer(int distance): distanceFromRouter_(distance);

  void OnEvent(Event event);

 protected:
  unsigned int distanceFromRouter_;
};
