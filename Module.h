#ifndef MODULE_H
#define MODULE_H
#include <vector>
#include "Point.h"
class Module {
private:
	bool ifReflect;
	int Rotate; // 0 degree, 90 degree, 180 degree, 270 degree 
	double Area;
	std::vector<double> HWRatio;
	int ratioRank;
	double LLX, LLY;
public:
	double getH();
	double getW();
	double getLeftLowerX();
	double getLeftLowerY();
	void setLeftLowerX(double x);
	void setLeftLowerY(double y);
	Point getTerminal(int seq);
	void changeRatio();
	void reflect();
	void rotateClockWise();
	Point terminalMove(int seq);
};

#endif