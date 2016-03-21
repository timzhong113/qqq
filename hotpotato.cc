#include <iostream>
#include "PRNG.h"
#include <unistd.h> //getpid
#include <cstdlib>	//exit
#include "printer.h"
#include "player.h"
#include "umpire.h"
#include "string.h"
#include <stdlib.h>	//atoi

using namespace std;

PRNG prng;
extern PRNG prng;

int main( int argc, char *argv[] ){
	unsigned int nop, maxtick;
	uint32_t seed;

	try{
		switch(argc){
			case 1:		//all use default values
				nop = 5;
				maxtick = 10;
				seed = getpid();
				break;
				
			case 2:		//have 1 argument
				if((atoi(argv[1]) < 2) || (atoi(argv[1]) > 20)) throw ios_base::failure("Usage Error");
				nop = atoi(argv[1]);
				maxtick = 10;
				seed = getpid();
				break;

			case 3:		//have 2 arguments
				if((atoi(argv[1]) < 2) || (atoi(argv[1]) > 20)|| (atoi(argv[2]) < 2)) throw ios_base::failure("Usage Error");
				nop = atoi(argv[1]);
				maxtick = atoi(argv[2]);
				seed = getpid();
				break;

			case 4:		//have 3 arguments
				if((atoi(argv[1]) < 2) || (atoi(argv[1]) > 20)|| (atoi(argv[2]) < 2) || (atoi(argv[3]) < 1)) throw ios_base::failure("Usage Error");
				nop = atoi(argv[1]);
				maxtick = atoi(argv[2]);
				seed = atoi(argv[3]);
				break;

			default:	//more than 3 arguments, usage error occurs
				throw ios_base::failure("Usage Error");
				break;

		}
	}catch(ios_base::failure err){
		cerr<<"Usage: ./hotpotato [ P (number of players 2..20) ";
        cerr<<"[ M (maximum ticks for potato) 2..N) ";
        cerr<<"[ S (seed for random-number generator (1..N) ] ] ]"<<endl;
        exit(1);
	}//try

	//PRNG
	prng.seed(seed);

	//printer
	Printer printer(nop);

	//player
	Player::Players players(nop);
	bool isEven = true;
	for(unsigned int i=0; i<nop; i++){
		if(isEven){
			LRPlayer(printer, i, players);
			isEven = false;
		}
		else{
			RNPlayer(printer, i, players);
			isEven = true;
		}
		cerr<<"p: "<<players[i]->getId()<<endl;
		cerr<<"i "<<i<<endl;
	}
	cout<<"player 0: "<<players[0]->getId()<<endl;
	for(unsigned int i=0; i<nop; i++){
		cout<<"player id: "<<players[i]->getId()<<endl;
	}
	//umpire
	Umpire umpire(printer,maxtick,players);
	umpire.start();

}//main
