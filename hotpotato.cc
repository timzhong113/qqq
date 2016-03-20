#include <iostream>
#include "PRNG.h"
#include <unistd.h> //getpid
#include <cstdlib>	//exit
#include "printer.h"

using namespace std;

int main( int argc, char *argv[] ){
	unsigned int nop, maxtick;
	uint32_t seed;

	try{
		switch(argc){
			case 1:		//all use default values
				nop = 5;
				maxtick = 10;
				seed = getpid();

			case 2:		//have 1 argument
				if(argv[1]<2 || argv[1]>20) throw ios_base::failure();
				nop = argv[1];
				maxtick = 10;
				seed = getpid();

			case 3:		//have 2 arguments
				if(argv[1]<2 || argv[1]>20 || argv[2]<2) throw ios_base::failure();
				nop = argv[1];
				maxtick = argv[2];
				seed = getpid();

			case 4:		//have 3 arguments
				if(argv[1]<2 || argv[1]>20 || argv[2]<2 || argv[3]<1) throw ios_base::failure();
				nop = argv[1];
				maxtick = argv[2];
				seed = argv[3];

			default:	//more than 3 arguments, usage error occurs
				throw ios_base::failure();
		}
	}catch(ios_base::failure){
		cerr<<"Usage: ./hotpotato [ P (number of players 2..20) ";
        cerr<<"[ M (maximum ticks for potato) 2..N) ";
        cerr<<"[ S (seed for random-number generator (1..N) ] ] ]"<<endl;
        exit(1);
	}//try

	//printer
	Printer printer(nop);

	//player
	vector<Player> players;
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
	}

	//potato

	//umpire

}//main
