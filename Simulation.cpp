#include "Simulation.h"

#include <vector>

#include "Environment.h"
#include "Clock.h"
#include "Computer.h"
#include "Events.h"
#include "PriorityQueue.h"
#include "Router.h"

using std::vector;

unsigned long long Clock::time_ = 0;
static const unsigned NUM_EVENTS = 10; // number of events before simulation ends

vector<Computer> computers;

Simulation::Simulation() {
  Run();
  Router::GetInstance().PrintStatistics();
}

void Simulation::Run() {
  bool ended = false;
  Clock::SetTime(0);

  PriorityQueue events;

  for (int i = 0; i < Environment::NUM_COMPS; i++) {
    computers.push_back(Computer(&events));
    events.Insert(new ArrivalEvent(&computers[i]));
  }

  for (int i = 0; i < NUM_EVENTS; i++) {
    Event* event = events.Remove();
    Clock::SetTime(event->GetTime());
    event->HandleEvent();
    delete event;
  }
}

