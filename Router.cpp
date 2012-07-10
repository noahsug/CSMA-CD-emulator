#include "Router.h"

#include <cassert>
#include <iostream>

#include "Clock.h"

using namespace std;

Router Router::instance_;

void Router::OnPacketGenerated(Computer* comp) {
  std::cerr << "OnPacketGenerated: " << comp << std::endl;
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  q.push(Clock::GetTime());
}

void Router::OnPacketDropped(Computer* comp) {
  std::cerr << "OnPacketDropped: " << comp << std::endl;
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  assert(!q.empty());
  q.pop();
}

void Router::OnPacketTransmitted(Computer* comp) {
  std::cerr << "OnPacketTransmitted: " << comp << std::endl;
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  assert(!q.empty());
  packetsArrived_++;
  unsigned long long delay = Clock::GetTime() - q.front();
  q.pop();
  totalPacketDelay_ += delay;
}
