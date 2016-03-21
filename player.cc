#include "player.h"
#include "PRNG.h"
#include "printer.h"
#include <vector>

Player::Player( Printer &prt, unsigned int id, Players &players ):prt(prt),id(id),lost(Lost(id)){
	players.push_back(this);
}

RNPlayer::RNPlayer( Printer &prt, unsigned int id, Players &players ):Player(prt,id,players){}

LRPlayer::LRPlayer( Printer &prt, unsigned int id, Players &players ):Player(prt,id,players){}

unsigned int Player::getId(){
	return id;
}

void RNPlayer::toss( Potato &potato ){
	try{
		potato.countdown();
	}catch(Potato::Expire){	//player loses
		throw lost;
	}
	
	//pass to next player
	uint32_t size = (uint32_t)players.size()-1;
	unsigned int nextId = (unsigned int)prng(size);
	prt.print(Printer::Player,1,players[nextId]->getId(),id);
	players[nextId]->toss(potato);
}

void LRPlayer::toss( Potato &potato ){
	try{
		potato.countdown();
	}catch(Potato::Expire){	//player loses
		throw lost;
	}

	//pass to next player
	uint32_t num = prng(1);
	unsigned int nextId;
	if(num == 0){	//left
		unsigned int size = players.size();
		if(players[size-1]->getId()==id){
			nextId = 0;//players[0].id;
		}
		else{
			unsigned int index;
			for(unsigned int i=0; i<size; i++){
				if(players[i]->getId()==id){
					index = i;
					break;
				}
			}
			nextId = index+1;//players[index+1].id;
		}
	}
	else{	//right
		unsigned int size = players.size();
		if(players[0]->getId()==id){
			nextId = size-1;//players[size-1].id;
		}
		else{
			unsigned int index;
			for(unsigned int i=0; i<size; i++){
				if(players[i]->getId()==id){
					index = i;
					break;
				}
			}
			nextId = index-1;//players[index-1].id;
		}
	}

	prt.print(Printer::Player,1,players[nextId]->getId(),id);
	players[nextId]->toss(potato);
}
