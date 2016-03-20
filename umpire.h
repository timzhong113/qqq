#ifndef UMPIRE_H
#define UMPIRE_H
#include "player.h"
#include "printer.h"
#include "potato.h"

class Umpire {
    Printer prt;
    unsigned int maxticks;
    Player::Players players;
  public:
    Umpire( Printer &prt, unsigned int maxticks, Player::Players &players );
    void start();
};

#endif
