#include "printer.h"
#include <iostream>
#include <iomanip>
using namespace std;

Printer::Printer( unsigned int players ){
	length = players+3;
	arr = new Buffer*[players+3];
	for(unsigned int i=0; i<length; i++){
		arr[i] = NULL;		//set default value
	}

	cout<<"M\t"<<"F\t"<<"U\t"<<"P0";

	for(unsigned int i=1; i<players; i++){
		cout<<"\tP"<<i;
	}
	cout<<endl;
	cout<<"===";
	for(unsigned int j=1; j<length; j++){
		cout<<"\t===";
	}
	cout<<endl;
}

Printer::~Printer(){
	for(unsigned int i=0; i<length; i++){
		delete arr[i];
	}
	delete [] arr;
}

void Printer::print( Kind kind, unsigned int state, unsigned int id, unsigned int player ){
	if((kind == 2)&&(state=='W')){
		cout<<"\t"<<"\t"<<"W "<<id<<"\t";
		for(unsigned int i=3; i<length; i++){
			cout<<"\t";
		}
		cout<<endl;
	}
	if(arr[kind+id]||state=='*'){	//print
		if(arr[0]) {
			cout<<arr[0]->state<<"\t";
			delete arr[0];
			arr[0] = NULL;
		}
		else cout<<"\t";
		if(arr[1]) {
			cout<<arr[1]->state<<"\t";
			delete arr[1];
			arr[1] = NULL;
		}
		else cout<<"\t";
		for(unsigned int i=2; i<length; i++){
			if(arr[i]) {
				cout<<(char)arr[i]->state<<" "<<arr[i]->player<<"\t";
				delete arr[i];
				arr[i] = NULL;
			}
			else cout<<"\t";
		}
		cout<<endl;
	}

	//store
	if(state!='*'){
		arr[kind+id] = new Buffer;
		arr[kind+id]->state = state;	
		arr[kind+id]->player = player;
	}
	else{
		cout<<"\t"<<"\t"<<"\t";
		for(unsigned int i=3; i<length; i++){
			if(i == kind+id) cout<<"*\t";
			else cout<<"...\t";
		}
		cout<<endl;
	}
}
