#include "Module.h"
#include <cmath>

double Module::getH() {
	return sqrt(Area * HWRatio[ratioRank]);
}

double Module::getW() {
	return sqrt(Area / HWRatio[ratioRank]);
}

double Module::getLeftLowerX() {
	return LLX;
}

double Module::getLeftLowerY() {
	return LLY;
}

void Module::setLeftLowerX(double x) {
	LLX = x;
}

void Module::setLeftLowerY(double y) {
	LLY = y;
}

Point Module::getTerminal(int seq) {
	double h = sqrt(Area * HWRatio[ratioRank]);
	double w = sqrt(Area / HWRatio[ratioRank]);
	int s = (Rotate + seq) % 4;
	if (ifReflect)
		s = 3 - s;
	if (s == 0)
		return Point(LLX, LLY + h);
	else if (s == 1)
		return Point(LLX + w, LLY + h);
	else if (s == 2)
		return Point(LLX + w, LLY);
	else
		return Point(LLX, LLY);
}

Point Module::terminalMove(int seq) {
	double h = sqrt(Area * HWRatio[ratioRank]);
	double w = sqrt(Area / HWRatio[ratioRank]);
	int s = (Rotate + seq) % 4;
	if (ifReflect)
		s = 3 - s;
	if (s == 0)
		return Point(0, h);
	else if (s == 1)
		return Point(w, h);
	else if (s == 2)
		return Point(w, 0);
	else
		return Point(0, 0);
}
void Module::changeRatio() {
	ratioRank++;
	if (ratioRank == HWRatio.size())
		ratioRank = 0;
}

void Module::reflect() {
	ifReflect = !ifReflect;
}

void Module::rotateClockWise() {
	Rotate = (Rotate + 1) % 4;
}