#ifndef lattice
#define lattice
#include "dipole.h"

class Lattice{

	private: 
	Dipole* dipoleArray;
	
	double E;	// pointing in +ve y axis V/m
	
	public:
		const int xSize;
		const int ySize;
		Lattice(const int, const int);
		Dipole* GetDipole(int x, int y);  //  return a dipole
		double calcLocalEnergy( int x, int y);
	
	
};



#endif


