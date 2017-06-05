#include "lattice.h"
#include "dipole.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;
int main(){
	srand(time(NULL));
	const double k = 1.38E-23;
	int latSize = 32;
	Lattice myLattice(latSize,latSize); // create lattice of dipoles
	
	ofstream ten;
	ten.open("ten.text");

	double localE1=0; double localE2=0; double typeE1=0; double typeE2=0; double typeN1=0; double typeN2=0; double typeNb=0; // all energies
	double R=0; double P=0; int initDirection=0; int newDirection=0; int randX=0; int randX2=0; int randY=0;
	int randY2=0; int r=0; int type=0; int Ntype=0 ;int direction=0; int Ndirection=0;	
	
    	for(double T=5; T<6; T+=1){ 
			cout<< "T = " << T << endl;
			for(int i=0; i<100001; i++){
		
			//******************** PART 1 : FLIPPING ALIGNEMENT OF CENTRAL DIPOLE ******************************8
			
				randX = rand()%latSize; randY = rand()%latSize; 
				randX2 = rand()%latSize;  randY2 = rand()%latSize; 
				r = rand() % 4 ;
				Dipole* randomDipole = myLattice.GetDipole(randX, randY); // choose random dipole
				initDirection = randomDipole->GetDirection();   // get direction
				localE1 = myLattice.calcLocalEnergy(randX, randY);
			    randomDipole->randomFlip();
			    localE2 = myLattice.calcLocalEnergy(randX, randY);
			    newDirection = randomDipole->GetDirection();
			    randomDipole->SetDirection(initDirection);
				R = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); 	//random number between 0 and 1		
				if (localE2<localE1 || exp(-(localE2-localE1)/k/T) > R ){                  //  flip back if conditions met
					randomDipole->SetDirection(newDirection);
				}	
				
		//	*******************************  PART 2 OF SIMULATION : SWAPPING DIPOLES  ***************************************************** // 
			
				P = static_cast<float>(rand()) / static_cast<float>(RAND_MAX); 	//random number between 0 and 1	
							
				Dipole* rD1 = myLattice.GetDipole(randX2, randY2); // get random dipole
				typeE1 = myLattice.calcLocalEnergy(randX2, randY2);								
				type = rD1->GetType(); 
				direction = rD1->GetDirection();                // get energy, type and direction of central site
				Dipole* neighbour1;
				if(r==0){
					neighbour1 = myLattice.GetDipole(randX2+1,randY2);			// GET NEIGHBOUR RANDOMLY
					typeN1 = myLattice.calcLocalEnergy(randX2+1, randY2);
				}																
				if(r==1){
					neighbour1 = myLattice.GetDipole(randX2,randY2+1);
					typeN1 = myLattice.calcLocalEnergy(randX2, randY2+1);
				}		
				if(r==2){
					neighbour1 = myLattice.GetDipole(randX2,randY2-1);
					typeN1 = myLattice.calcLocalEnergy(randX2, randY2-1);
				}		
				if(r==3){
					neighbour1 = myLattice.GetDipole(randX2-1,randY2);
					typeN1 = myLattice.calcLocalEnergy(randX2-1, randY2);
				}													
					Ntype = neighbour1->GetType();  
					Ndirection = neighbour1->GetDirection();	   	
					                     					
					rD1->SetType(Ntype); rD1->SetDirection(Ndirection);
					neighbour1->SetType(type); neighbour1->SetDirection(direction);								          				
					typeE2 = myLattice.calcLocalEnergy(randX2,randY2);	
					
				if(r==0){															// GET ENERGY OF NEIGHBOURS SITE AFTER SWAP							
					typeN2 = myLattice.calcLocalEnergy(randX2+1, randY2);    
				}																
				if(r==1){				
					typeN2 = myLattice.calcLocalEnergy(randX2, randY2+1);
				}
				if(r==2){				
					typeN2 = myLattice.calcLocalEnergy(randX2, randY2-1);
				}	
				if(r==3){				
					typeN2 = myLattice.calcLocalEnergy(randX2-1, randY2);
				}																									
				rD1->SetType(type); rD1->SetDirection(direction);
				neighbour1->SetType(Ntype); neighbour1->SetDirection(Ndirection);		// flip back to 'original configuration'
			
				if (typeE2+typeN2<typeE1+typeN1 ||  exp(-(typeE2+typeN2-typeE1-typeN1)/k/T) > P ){    //  reverse to 'swapped config' if conditions met
					rD1->SetType(Ntype); rD1->SetDirection(Ndirection);								// always swap when T >> 1
				   	neighbour1->SetType(type); neighbour1->SetDirection(direction);	
				}
		       	if(i == 1000000){
					for(int m=0;m<latSize;m++){						// write matrix to file
						for(int n=0;n<latSize;n++){
							Dipole* site = myLattice.GetDipole(n,m);
							int x = site->GetDirection();
							if(x==0 || x==2){							
								ten<<"+";
							}	
							if(x==1 || x== 3){
								ten<<"-";
							}										
					   }
					   ten<<endl ;				
					}
					ten<<endl<<endl<<endl;					
				}
			}
		}
		        	
}
				




			
	
	
			
			

		
	
