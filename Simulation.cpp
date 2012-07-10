#include "Simulation.h"

#include <iostream>
#include <vector>

#include "Environment.h"
#include "Clock.h"
#include "Computer.h"
#include "Events.h"
#include "PriorityQueue.h"
#include "Router.h"

using std::vector;

unsigned long long Clock::time_ = 0;
static const unsigned NUM_EVENTS = 10000; // number of events before simulation ends

PriorityQueue events;
vector<Computer*> computers;

Simulation::Simulation() {
  Run();
  Router::GetInstance().PrintStatistics();
}

void Simulation::Run() {
  bool ended = false;
  Clock::SetTime(0);

  for (int i = 0; i < Environment::NUM_COMPS; i++) {
    computers.push_back(new Computer(&events));
    std::cerr << "Comp" << i << ": " << computers[i] << std::endl;
    events.Insert(new ArrivalEvent(computers[i]));
  }

  for (int i = 0; i < NUM_EVENTS; i++) {
    Event* event = events.Remove();
    Clock::SetTime(event->GetTime());
    event->HandleEvent();
    delete event;
  }

  for (int i = 0; i < Environment::NUM_COMPS; i++) {
    delete computers[i];
  }
}

