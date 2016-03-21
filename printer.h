#ifndef PRINTER_H
#define PRINTER_H
/*
state = 0(default) means print the first line 
		which are objects' name
state = 1 means the player pass
state = 2 means the player loses
state = 3 means the player wins

state = 4 means Mashed potato called printer
		maxtick storing at id
state = 5 means Fried potato called printer
		maxtick storing at id
state = 6 means Umpire called printer
*/

class Printer {
	unsigned int length;
	unsigned int *arr;
  public:
    enum Kind { Mashed, Fried, Umpire, Player };
    Printer( unsigned int players );
    ~Printer();
    void print( Kind kind, unsigned int state, unsigned int id = 0, unsigned int player = 0 );
};

#endif
