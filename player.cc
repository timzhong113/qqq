#include "player.h"
#include "PRNG.h"
#include "printer.h"
#include <vector>
#include <iostream>
using namespace std;

Player::Player( Printer &prt, unsigned int id, Players &players ):prt(prt),id(id),lost(Lost(id)),players(players){
	//cout<<"lalala"<<endl;
	players.push_back(this);
}

RNPlayer::RNPlayer( Printer &prt, unsigned int id, Players &players ):Player(prt,id,players){}

LRPlayer::LRPlayer( Printer &prt, unsigned int id, Players &players ):Player(prt,id,players){}

unsigned int Player::getId(){
	return id;
}
unsigned int RNPlayer::getId(){
	return id;
}

unsigned int LRPlayer::getId(){
	return id;
}

void RNPlayer::toss( Potato &potato ){
	try{
		potato.countdown();
	}catch(Potato::Expire){	//player loses
		throw lost;
	}
	
	//pass to next player
	uint32_t size = (uint32_t)players.size();
	unsigned int next = (unsigned int)prng(size-1);
	prt.print(Printer::Player,1,players[next]->getId(),getId());
	players[next]->toss(potato);
}

void LRPlayer::toss( Potato &potato ){
	try{
		potato.countdown();
	}catch(Potato::Expire){	//player loses
		throw lost;
	}

	//pass to next player
	uint32_t num = prng(1);
	unsigned int next;		//next player's position
	unsigned int position;	//current player's position
	unsigned int size = players.size();	//the size of container
	for(unsigned int i=0; i<size; i++){
		if(players[i]->getId() == getId()){
			position = i;
			break;
		}
	}
	if(num==0){		//left
		if(position == size-1) next = 0;
		else next = position+1;
	}
	else{
		if(position == 0) next = size-1;
		else next = position-1;
	}

	prt.print(Printer::Player,1,players[next]->getId(),getId());
	players[next]->toss(potato);
}
