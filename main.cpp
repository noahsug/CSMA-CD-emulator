#include <cstdio>
#include <iostream>

#include "Simulation.h"

using std::cerr;

int main(int argc, char** argv) {
  double arrival_rate = 0;
  double lan_speed = 0;
  int packet_length = 0;

  if (argc != 4) {
    cerr << "Usage: ./" << argv[0] << " A W L\n";
    return -1;
  }

  arrival_rate = atof(argv[1]);
  lan_speed = atof(argv[2]);
  packet_length = atoi(argv[3]);

  Simulation(arrival_rate, lan_speed, packet_length);
}

