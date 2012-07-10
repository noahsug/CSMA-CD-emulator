#include "Simulation.h"

#include <vector>

#include "Environment.h"
#include "Clock.h"
#include "Computer.h"
#include "Events.h"
#include "PriorityQueue.h"

using std::vector;

unsigned long long Clock::time_ = 0;

vector<Computer> computers;

Simulation::Simulation() {
  Run();
}

void Simulation::Run() {
  bool ended = false;
  Clock::SetTime(0);

  PriorityQueue events;

  for (int i = 0; i < Environment::NUM_COMPS; i++) {
    computers.push_back(Computer(&events));
    events.Insert(new ArrivalEvent(&computers[i]));
  }

  for (int i = 0; i < 10; i++) {
    Event* event = events.Remove();
    event->HandleEvent();
    delete event;
  }
}

