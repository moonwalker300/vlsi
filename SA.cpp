#include "SA.h"
#include <iostream>
#include <cstdlib>
using namespace std;
SA::SA(double initialTemp, double decTemp, double stopTemp, double incTurn, int cof) {
	this->initialTemp = initialTemp;
	this->decTemp = decTemp;
	this->stopTemp = stopTemp;
	this->incTurn = incTurn;
	this->cof = cof;
}

void SA::Calculate(CornerBlockList& cbl) {
	result.copyModel(cbl);
	result.copySolution(cbl);
	CornerBlockList tmp;
	tmp.copyModel(cbl);
	int n = result.getModuleNum();
	double bestArea, bestWireLen;
	double nowArea, nowWireLen;
	double bestFunc = result.Evaluate(bestArea, bestWireLen);
	double nowFunc;
	double temp = initialTemp;
	double turns = cof * n;
	while (temp > stopTemp) {
		int turnNum = int(turns);
		cout << temp << " " <<  turnNum << " " << bestFunc << endl;
		bool flag = false;
		for (int i = 0; i < turnNum; i++) {
			tmp.copySolution(result);
			tmp.findNeibor();
			nowFunc = tmp.Evaluate(nowArea, nowWireLen);
			double p = (rand() % 10000) * 1.0 / 10000;
			if ((nowFunc < bestFunc) || (p < exp((bestFunc / nowFunc - 1) * 5000 / temp))) {
				if (nowFunc < bestFunc)
					flag = true;
				result.copySolution(tmp);
				bestFunc = nowFunc;
				bestArea = nowArea;
				bestWireLen = nowWireLen;
			}
		}
		if (!flag)
			break;
		
		temp *= decTemp;
		turns *= incTurn;
	}
	result.Evaluate(nowArea, nowWireLen);
}