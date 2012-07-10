#include <cstdio>
#include <iostream>

#include "Events.h"
#include "Environment.h"
#include "Simulation.h"

using std::cerr;

int main(int argc, char** argv) {
  if (argc != 5) {
    cerr << "Usage: " << argv[0] << " N A W L\n";
    return -1;
  }

  Environment::NUM_COMPS = atoi(argv[1]);
  Environment::LAN_SPEED = atof(argv[3]);
  Environment::PACKET_LENGTH = atoi(argv[4]);

  Environment::ARRIVAL_RATE = (Environment::LAN_SPEED * 1000000) * atof(argv[2]);
  Environment::PROP_TIME = (unsigned) 150 * Environment::LAN_SPEED;

  Simulation();
}

