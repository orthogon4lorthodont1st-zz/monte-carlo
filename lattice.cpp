#include "dipole.h"
#include "lattice.h"
#include <cmath>
#include <cstdlib>
#include<iostream>
Lattice::Lattice(const int xSize, const int ySize): xSize(xSize), ySize(ySize){
	dipoleArray =  new Dipole[xSize*ySize];	//store 1D array list
	for(int i=0; i<xSize; i++){
		for(int j=0; j<ySize; j++){
			//loop through the entire array and create dipoles
			dipoleArray[ i+j*xSize ] = Dipole();  // i + j*xSize to mimic 2D lattice form
			
		}
	}
}
Dipole * Lattice::GetDipole(int x, int y){ 

	return &dipoleArray[ ((x+xSize)%xSize) + ((y+xSize)%xSize)*xSize  ];	// modulo is for loop behaviour 
}
double Lattice::calcLocalEnergy( int x, int y){  

	double k = 1/(4*3.14158*8.85E-12);  	double p1=0; 	double p2 =0;		double r  = 1E-8; 	double energy = 0;
	double E = 1e150;	double pZero = 1e-27;	double pOne = 1e-29;
	

	Dipole* central = GetDipole(x,y);  // define central dipole in the lattice at position [x,y] given by the argument
													// take modulo because x,y can potentially  = -1 OR xSize for neighbour dipoles
													// modulo ensures neighbours are found correctly
													// for 0 <=  x,y < xSize modulo has no effect	
														
	Dipole* neighbour[4];
	neighbour[0] = GetDipole(x,y-1); 		//up = 0, right = 1, down = 2, left = 3
	neighbour[1] = GetDipole(x+1,y);
	neighbour[2] = GetDipole(x,y+1);
	neighbour[3] = GetDipole(x-1,y);
	int myDirection =  central->GetDirection() ;
	int type = central->GetType();
	if(type==0){p1 = pZero;	}	else{p1 = pOne;	}
	double Energy[4][4];
	double Energy2[4][4];
	
	for(int i=0; i<4; i++){
		int neighbourDirection =  neighbour[i]->GetDirection();
		int Ntype = neighbour[i]->GetType();
		if(Ntype==1){	p2 = pOne;	}	else{	p2 = pZero;	} 

			Energy[0][0] = -2*k*p1*p2/r/r/r -(p1+p2)*E;
			Energy[0][1] = -p1*E;
			Energy[0][2] = 2*k*p1*p2/r/r/r -(p1-p2)*E;
			Energy[0][3] = -p1*E;
			
			Energy[1][0] = -p2*E;
			Energy[1][1] = 2*k*p1*p2/3/r/r/r;
			Energy[1][2] = p2*E;
			Energy[1][3] = -2*k*p1*p2/3/r/r/r;
			
			Energy[2][0] = 2*k*p1*p2/r/r/r +(p1-p2)*E;
			Energy[2][1] = p1*E;
			Energy[2][2] = -2*k*p1*p2/r/r/r +(p1+p2)*E;
			Energy[2][3] = p1*E;
			
			Energy[3][0] = -p2*E;
			Energy[3][1] = -2*k*p1*p2/3/r/r/r;
			Energy[3][2] = p2*E;
			Energy[3][3] = 2*k*p1*p2/3/r/r/r;
			
	   
			Energy2[0][1] = -p1*E;
			Energy2[0][2] = -2*k*p1*p2/3/r/r/r -(p1-p2)*E;
			Energy2[0][3] = -p1*E;
			
			Energy2[1][0] = -p2*E;
			Energy2[1][1] = -2*k*p1*p2/r/r/r;
			Energy2[1][2] = p2*E;
			Energy2[1][3] = 2*k*p1*p2/r/r/r;
			
			Energy2[2][0] = -2*k*p1*p2/3/r/r/r +(p1-p2)*E;
			Energy2[2][1] = p1*E;
			Energy2[2][2] = 2*k*p1*p2/3/r/r/r +(p1+p2)*E;
			Energy2[2][3] = p1*E;
			
			Energy2[3][0] = -p2*E;
			Energy2[3][1] = 2*k*p1*p2/r/r/r;
			Energy2[3][2] = p2*E;
			Energy2[3][3] = -2*k*p1*p2/r/r/r;
			
			if(i==0 || i==2){ 
				energy += Energy[myDirection][neighbourDirection];	
			}		
			else if(i==1 || i==3){  	 		
				energy += Energy2[myDirection][neighbourDirection];			
			}		
	}
	  return energy;
	  
}
		
