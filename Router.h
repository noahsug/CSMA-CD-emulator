#ifndef __ROUTER_H__
#define __ROUTER_H__

// Calculates statistics about the system
class Router {
  static Router instance_;
  static Router GetInstance() { return instance_; }

 public:
  Router() {}

  void OnPacketGenerated();
  void OnPacketTransmitted();
};
#endif
