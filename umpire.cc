#include "umpire.h"
#include "printer.h"
#include <cstdlib>	//exit
#include <iostream>
using namespace std;

Umpire::Umpire( Printer &prt, unsigned int maxticks, Player::Players &players ):prt(prt),maxticks(maxticks),players(players){

}

void Umpire::start(){
	Mashed mashed(prt,maxticks);
	Fried fried(prt,maxticks);
	bool isEven = true;

	while(1){
		try{
			uint32_t size = (uint32_t)players.size()-1;
			uint32_t num = prng(size);
			unsigned int playerId = (unsigned int)num;
			if(isEven){
				prt.print(Printer::Umpire,'M',0,playerId);
			}
			else{
				prt.print(Printer::Umpire,'F',0,playerId);
			}
			unsigned int length = players.size();
			unsigned int position=0;
			for(unsigned int i=0; i<length; i++){
				if(players[i]->getId() == playerId){
					position = i;
					break;
				}
			}

			if(isEven){
				players[position]->toss(mashed);
			}
			else{
				players[position]->toss(fried);
			}
			
		}catch(Player::Lost lost){
			unsigned int length = players.size();
			unsigned int position;
			for(unsigned int i=0; i<length; i++){
				if(players[i]->getId() == lost.id){
					position = i;
					break;
				}
			}
			prt.print(Printer::Player,'*',lost.id);
			players.erase(players.begin()+position);
			if(players.size()==1){	//someone wins
				unsigned int winner = players[0]->getId();
				prt.print(Printer::Umpire,'W',winner);
				exit(0);
			}
			else{
				if(isEven){
					mashed.reset();
					isEven = false;
				}
				else{
					fried.reset();
					isEven = true;
				}
				continue;
			}
		}//try
	}//while
}
