#include "Simulation.h"

#include <list>

#include "Events.h"

using std::list;

void Simulation::Simulation(unsigned number_computers, double arrival_time,
                            double lan_speed, int packet_length)
    : number_computers_(number_computers)
    , arrival_time_(arrival_time)
    , lan_speed_(lan_speed)
    , packet_length_(packet_length) {
  Run();
}

void Simulation::Run() {
  bool ended = false;
  unsigned long long clock = 0;

  list<Event*> events;
  vector<Computer> computers;
  for (int i = 0; i < number_computers_; i++) {
    //
  }

  while (!ended) {
    Event* event = events.pop_front();
  }
}

