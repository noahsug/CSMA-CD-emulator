#include "Router.h"

#include <assert.h>
#include "Clock.h"

using namespace std;

void Router::OnPacketGenerated(Computer* comp) {
  queue<unsigned long long> q = packetGeneratedTimes_[comp];
  q.push(Clock::GetTime());
}

void Router::OnPacketDropped(Computer* comp) {
  queue<unsigned long long> q = packetGeneratedTimes_[comp];
  assert(!q.empty());
  q.pop();
}

void Router::OnPacketTransmitted(Computer* comp) {
  queue<unsigned long long> q = packetGeneratedTimes_[comp];
  assert(!q.empty());
  packetsArrived_++;
  unsigned long long delay = Clock::GetTime() - q.front();
  q.pop();
  totalPacketDelay_ += delay;
}
