#include "printer.h"
#include <iostream>
#include <iomanip>
using namespace std;

Printer::Printer( unsigned int players ){
	length = players+3;
	arr = new unsigned int[players+3];
	for(unsigned int i=0; i<length; i++){
		arr[i] = length;		//set a default value, which means empty
	}
}

Printer::~Printer(){
	delete [] arr;
}

void Printer::print( Kind kind, unsigned int state, unsigned int id, unsigned int player ){
	switch(state){
		case 1:
			//buffer is empty or not, if not then print&store, otherwise just store
			if(arr[player+3] == length) arr[player+3] = id;
			else{	
				//first step: print

				//the first column, Mashed
				bool isMashed = false;
				if(arr[0] != length){
					isMashed = true;
					cout<<setw(8)<<left<<arr[0];
				}
				else cout<<setw(8);

				//the second column, Fried
				if(arr[1] != length) cout<<setw(8)<<left<<arr[0];
				else cout<<setw(8);

				//the third column, Umpire
				if(isMashed) cout<<"M "<<setw(8)<<left<<arr[2];
				else cout<<"F "<<setw(8)<<left<<arr[2];

				bool isEven = true;
				for(unsigned int i=3; i<length; i++){
					
					if(arr[i] != length){	//not an empty column
						char symbol;
						//confirm the direction that the player is passing
						if(isEven){	//LRPlayer
							if(arr[i]-i == 1) symbol = 'l';	//pass to left
							else symbol = 'r';	//pass to right
						}
						else symbol = 'R';	//RMPlayer

						if(i+1 == length){	//the last column
							cout<<symbol<<" "<<arr[player]<<setw(1)<<left<<endl;
						}
						else{	//not the last column
							cout<<symbol<<" "<<arr[player]<<setw(5)<<left;
						}
					}

					else{	//an empty column
						if(i+1 == length) cout<<setw(4)<<endl;	//the last column
						else cout<<setw(8);		//not the last column
					}

					if(isEven) isEven = false;
					else isEven = true;
				}//for

				//second step: store
				delete [] arr;
				arr = new unsigned int[length];
				for(unsigned int i=0; i<length; i++){
					arr[i] = length;
				}
				arr[player] = id;
			}//else
			break;

		case 2:
			for(unsigned int i=0; i<length; i++){
				if(i<3) cout<<setw(8);
				else{
					if(i+1 == length){	//last column
						if(i-3 == player) cout<<"*"<<setw(3)<<left<<endl;
						else cout<<"..."<<setw(3)<<left<<endl;;
					}
					else{
						if(i-3 == player) cout<<"*"<<setw(7)<<left;
						else cout<<"..."<<setw(7)<<left;
					}					
				}
			}
			break;

		case 3:
			for(unsigned int i=0; i<length; i++){
				if(i==2) cout<<"W "<<player<<setw(5)<<left;
				else{
					if(i+1 == length) cout<<setw(4)<<endl;	//last column
					else cout<<setw(8);					
				}
			}
			break;
			
		case 4:
			arr[0] = id;
			break;

		case 5:
			arr[1] = id;
			break;

		case 6:
			arr[2] = id;
			break;

		default:	//state 0
			for(unsigned int i=0; i<length; i++){
				if(i==0) cout<<setw(8)<<left<<"M";
				else if(i==1) cout<<setw(8)<<left<<"F";
				else if(i==2) cout<<setw(8)<<left<<"U";
				else {
					if(i+1 == length) cout<<"P"<<setw(3)<<left<<i-3<<endl;
					else{
						cout<<"P"<<setw(7)<<left<<i-3;
					}
				}
			}
			for(unsigned int j=0; j<length; j++){
				if(j+1 == length) cout<<setw(4)<<left<<"==="<<endl;
				else cout<<setw(8)<<left<<"===";
			}
			break;
	}//switch
}//print
