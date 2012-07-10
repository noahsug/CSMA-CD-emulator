#ifndef __SIMULATION_H__
#define __SIMULATION_H__

class Simulation {
 public:
  Simulation(unsigned, double, double, int);

 private:
  void Run();

	unsigned number_computers_;
	double arrival_time_;
	double lan_speed_;
	int packet_length_;
};

#endif

