#ifndef UMPIRE_H
#define UMPIRE_H

class Umpire {
    // YOU ADD MEMBERS
  public:
    Umpire( Printer &prt, unsigned int maxticks, Player::Players &players );
    void start();
};

#endif
