#ifndef PLAYER_H
#define PLAYER_H

class Player {
    // YOU ADD MEMBERS
  public:
    typedef ... Players;             // container type of your choice
    struct Lost {                    // raise after timer expires
        // YOU ADD MEMBERS
    };
    Player( Printer &prt, unsigned int id, Players &players );
    virtual unsigned int getId();
    virtual void toss( Potato &potato ) = 0; // must be defined in derived class
};

class RNPlayer : public Player {
    // YOU ADD MEMBERS
  public:
    RNPlayer( Printer &prt, unsigned int id, Players &players );
    void toss( Potato &potato );
};

class LRPlayer : public Player {
    // YOU ADD MEMBERS
  public:
    LRPlayer( Printer &prt, unsigned int id, Players &players );
    void toss( Potato &potato );
};

#endif
