#ifndef __RANDOM_H__
#define __RANDOM_H__

namespace Random {
    void Seed(unsigned long);

    unsigned long GetInt();
    unsigned long GetInt(unsigned long max);
    double GetDouble();
};

#endif

