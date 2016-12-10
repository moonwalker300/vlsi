#ifndef SA_H
#define SA_H

#include "CornerBlockList.h"

class SA {
private:
	double initialTemp;
	double decTemp;
	double incTurn;
	double stopTemp;
	int cof;
public:
	CornerBlockList result;
	SA(double, double, double, double, int);
	void Calculate(CornerBlockList&);
};

#endif