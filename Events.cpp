#include "Events.h"
#include "Environment.h"
#include "Computer.h"

#include <cmath>
#include <iostream>

#include "Clock.h"
#include "Random.h"

bool Event::operator<(const Event& e) {
  return time_ < e.time_;
}

bool Event::operator>(const Event& e) {
  return time_ > e.time_;
}

bool Event::operator<=(const Event& e) {
  return time_ <= e.time_;
}

bool Event::operator>=(const Event& e) {
  return time_ >= e.time_;
}

ArrivalEvent::ArrivalEvent(Computer* dest) {
  dest_ = dest;
  double rand = Random::GetDouble();
  time_ = Clock::GetTime() +
      (unsigned long long)((-1 / Environment::ARRIVAL_RATE) * log(1 - rand));
}

MediumSensedEvent::MediumSensedEvent(Computer* dest) {
  dest_ = dest;
  time_ = Clock::GetTime() + Computer::SENSE_MEDIUM_TIME;
}

MediumBusyEvent::MediumBusyEvent(Computer* dest) {
  dest_ = dest;
  time_ = Clock::GetTime() + 2*Environment::PROP_TIME;
}

MediumFreeEvent::MediumFreeEvent(Computer* dest) {
  dest_ = dest;
  time_ = Clock::GetTime() + Environment::PACKET_LENGTH;
}

TransmittedFrameEvent::TransmittedFrameEvent(Computer* dest) {
  dest_ = dest;
  time_ = Clock::GetTime() + Environment::PACKET_LENGTH;
}

RaspberryJamEvent::RaspberryJamEvent(Computer* dest) {
  dest_ = dest;
  time_ = Clock::GetTime() + 2*Environment::PROP_TIME;
}

BackoffDoneEvent::BackoffDoneEvent(Computer* dest) {
  dest_ = dest;
  unsigned long b = dest->GetBackoff();
  unsigned long val = (1 << b) - 1;
  unsigned long rand = Random::GetInt(val);
  time_ = Clock::GetTime() + Computer::TP * rand;
}

PacketReceivedEvent::PacketReceivedEvent(Computer* dest) {
  dest_ = dest;
  time_ = Clock::GetTime() + Environment::PROP_TIME;
}

