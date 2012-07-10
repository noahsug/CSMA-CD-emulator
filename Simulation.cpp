#include "Simulation.h"

#include <vector>

#include "Computer.h"
#include "Events.h"
#include "PriorityQueue.h"

using std::vector;

Simulation::Simulation(unsigned number_computers, double lan_speed, int packet_length)
    : number_computers_(number_computers)
    , lan_speed_(lan_speed)
    , packet_length_(packet_length) {
  Run();
}

void Simulation::Run() {
  bool ended = false;
  unsigned long long clock = 0;

  PriorityQueue<Event*> events;
  vector<Computer> computers;

  for (int i = 0; i < number_computers_; i++) {
    computers.push_back(Computer(&events, Computer::COMP_DISTANCE * (i + 1)));
    events.Insert(new ArrivalEvent(clock, &computers[i]));
  }

  for (int i = 0; i < 10; i++) {
    Event* event = events.Remove();
    event->HandleEvent();
    delete event;
  }
}

