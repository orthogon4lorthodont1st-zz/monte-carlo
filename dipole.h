#ifndef dipole
#define dipole



class Dipole{
	private: 
	int direction;      // 0=up   1=right   2=down   3=left
	int type;			// type 0 is dipole polystyrene , type 1 is dipole PVME
	
	public:
		Dipole();
		void randomFlip();
		void swapDipole();
		void SetDirection(int);
		void SetType(int);
		int GetDirection();
		int GetType();
};



#endif
