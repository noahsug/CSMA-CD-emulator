#include <cstdio>
#include <iostream>

#include "Events.h"
#include "Simulation.h"

using std::cerr;

int main(int argc, char** argv) {
  if (argc != 5) {
    cerr << "Usage: " << argv[0] << " N A W L\n";
    return -1;
  }

  unsigned number_computers = atoi(argv[1]);
  double arrival_rate = atof(argv[2]);
  double lan_speed = atof(argv[3]);
  int packet_length = atoi(argv[4]);

  ArrivalEvent::ARRIAVL_RATE = arrival_rate;

  Simulation(number_computers, lan_speed, packet_length);
}

