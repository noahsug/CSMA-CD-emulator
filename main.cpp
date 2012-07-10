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

  NUM_COMPS = atoi(argv[1]);
  ARRIVAL_RATE = atof(argv[2]);
  LAN_SPEED = atof(argv[3]);
  PACKET_LENGTH = atoi(argv[4]);
  PROP_TIME = 2000 / LAN_SPEED;

  Simulation();
}

