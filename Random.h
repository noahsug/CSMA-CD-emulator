#ifndef __RANDOM_H__
#define __RANDOM_H__

namespace Random {
    void Seed(unsigned long);

    unsigned long GetInt();
    double GetDouble();
};

#endif

