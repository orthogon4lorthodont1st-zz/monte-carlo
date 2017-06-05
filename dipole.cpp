#include "dipole.h"
#include <cmath>
#include <stdlib.h>
#include <time.h>
Dipole::Dipole(){	//constrctor to make a dipole with completly random properties
	direction = rand()%4;
	type = rand()%2;
}


void Dipole::randomFlip(){ 
	direction = rand()%4;  // flip to a new random direction
}

void Dipole::SetDirection(int newDirection){
	direction = newDirection;
}

void Dipole::SetType(int newType){
	type = newType;	
}
void Dipole::swapDipole(){   
	if(type==0){              // swap type 
		type = 1;
	}else{
		type = 0;
	}
}

int Dipole::GetType(){          //return dipole type so lattice can use it
	return type;
}
int Dipole::GetDirection(){          //return dipole direction, allows lattice class to access this property for energy calculations
	return direction;
}
