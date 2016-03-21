#include <iostream>
#include "PRNG.h"
#include <unistd.h> //getpid
#include <cstdlib>	//exit
#include "printer.h"
#include "player.h"
#include "umpire.h"
#include "string.h"

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
				if(strcmp("2",argv[1])>0 || strcmp(argv[1],"20")>0) throw ios_base::failure("Usage Error");
				nop = (unsigned int)*argv[1];
				maxtick = 10;
				seed = getpid();
				break;

			case 3:		//have 2 arguments
				if(strcmp("2",argv[1])>0 || strcmp(argv[1],"20")>0 || strcmp("2",argv[2])>0 ) throw ios_base::failure("Usage Error");
				nop = (unsigned int)*argv[1];
				maxtick = (unsigned int)*argv[2];
				seed = getpid();
				break;

			case 4:		//have 3 arguments
				if(strcmp("2",argv[1])>0 || strcmp(argv[1],"20")>0 || strcmp("2",argv[2])>0 || strcmp("1",argv[3])>0) throw ios_base::failure("Usage Error");
				nop = (unsigned int)*argv[1];
				maxtick = (unsigned int)*argv[2];
				seed = (unsigned int)*argv[3];
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
	vector<Player *> players;
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

	//umpire
	Umpire umpire(printer,maxtick,players);
	umpire.start();

}//main
