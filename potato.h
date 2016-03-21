#ifndef POTATO_H
#define POTATO_H
#include "PRNG.h"
extern PRNG prng;
class Printer;

class Potato {
    Printer &prt;
  public:
    struct Expire {};                // raise when timer expires
    Potato( Printer &prt );
    virtual void reset() = 0;        // must be defined in derived class
    virtual void countdown();
};

class Mashed : public Potato {
    unsigned int maxticks;
    unsigned int ticks;     //current ticks, set up by reset()
  public:
    Mashed( Printer &prt, unsigned int maxTicks = 10 );
    void reset();
    void countdown();
};

class Fried : public Potato {
    unsigned int maxticks;
    unsigned int ticks;     //current ticks, set up by reset()
  public:
    Fried( Printer &prt, unsigned int maxTicks = 10 );
    void reset();
    void countdown();
};

#endif
