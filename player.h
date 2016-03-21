#ifndef PLAYER_H
#define PLAYER_H
#include <vector>
#include "potato.h"
#include "PRNG.h"
using namespace std;

extern PRNG prng;

class Printer;

class Player {
  protected:
    Printer &prt;
    unsigned int id;
  public:
    typedef vector<Player> Players;             // container type of your choice
    Players players;
    struct Lost {                    // raise after timer expires
        const unsigned int *id;
        Lost( const unsigned int *id ): id(id){}
    };
    Player( Printer &prt, unsigned int id, Players &players );
    virtual ~Player();
    virtual unsigned int getId();       //get next player's index in players
    virtual void toss( Potato &potato ) = 0; // must be defined in derived class
};

class RNPlayer : public Player {
  public:
    RNPlayer( Printer &prt, unsigned int id, Players &players );
    void toss( Potato &potato );
    virtual ~RNPlayer();
};

class LRPlayer : public Player {
  public:
    LRPlayer( Printer &prt, unsigned int id, Players &players );
    void toss( Potato &potato );
    virtual ~LRPlayer();
};

#endif
