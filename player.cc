#include "player.h"
#include "PRNG.h"
#include "printer.h"
#include <vector>
#include <iostream>
using namespace std;

Player::Player( Printer &prt, unsigned int id, Players &players ):prt(prt),id(id),players(players){
	cerr<<"id "<<id<<endl;
}

RNPlayer::RNPlayer( Printer &prt, unsigned int id, Players &players ):Player(prt,id,players){
	players[id]=this;
}

LRPlayer::LRPlayer( Printer &prt, unsigned int id, Players &players ):Player(prt,id,players){
	players[id]=this;
	direction = false;
}

unsigned int Player::getId(){
	return id;
}

void RNPlayer::toss( Potato &potato ){
	try{
		potato.countdown();
	}catch(Potato::Expire){	//player loses
		throw Lost(getId());
	}
	
	//pass to next player
	unsigned int next = prng(players.size()-1);
	cerr<<"Ran"<<endl;
	prt.print(Printer::Player,'R',getId(),players[next]->getId());
	players[next]->toss(potato);
}

void LRPlayer::toss( Potato &potato ){
	try{
		potato.countdown();
	}catch(Potato::Expire){	//player loses
		throw Lost(getId());
	}

	//pass to next player
	unsigned int next;		//next player's position
	unsigned int position;	//current player's position
	unsigned int size = players.size();	//the size of container
	for(unsigned int i=0; i<size; i++){
		if(players[i]->getId() == getId()){
			position = i;
			break;
		}
	}

	if(!direction){		//to left
		if(position == size-1) next = 0;
		else next = position+1;
		direction = true;
		prt.print(Printer::Player,'l',getId(),players[next]->getId());
	}
	else{			//to right
		if(position == 0) next = size-1;
		else next = position-1;
		direction = false;
		prt.print(Printer::Player,'r',getId(),players[next]->getId());
	}	
	players[next]->toss(potato);
}
