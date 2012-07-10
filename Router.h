#ifndef __ROUTER_H__
#define __ROUTER_H__

#include "Environment.h"
#include <map>
#include <queue>

class Computer;

// Calculates statistics about the system. Is not actually a router.
class Router {
  static Router instance_;

 public:
  static Router GetInstance() { return instance_; }
  void OnPacketDropped(Computer*);
  void OnPacketGenerated(Computer*);
  void OnPacketTransmitted(Computer*);
  void PrintStatistics();

 private:
  Router() {}
  std::map<Computer*, std::queue<unsigned long long> > packetGeneratedTimes_;
  unsigned long long packetsArrived_;
  unsigned long long totalPacketDelay_;
};

#endif
