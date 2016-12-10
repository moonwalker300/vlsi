#include "BmpWriter.h"
#include "CornerBlockList.h"
#include "SA.h"
#include <iostream>
#include <fstream>

using namespace std;
const int imageWidth = 800;
const int imageHeight = 800;
const double a = 1.0;
const double initialTemp = 10000;
const double stopTemp = 0.1;
const double decTemp = 0.96;
const double incTurn = 1.02;
int main(int argc, char* argv[]) {
	if (argc != 3) {
		cout << "Illegal Format!" << endl;
		return 0;
	}
	BmpWriter bw(imageHeight, imageWidth, argv[2]);
	ifstream in(argv[1]);
	
	vector<Module> moduleList;
	int moduleNum;
	in >> moduleNum;
	for (int i = 0; i < moduleNum; i++) {
		Module tmp;
		double area;
		in >> area;
		tmp.setArea(area);
		int ratioNum;
		double ratio;
		in >> ratioNum;
		for (int j = 0; j < ratioNum; j++) {
			in >> ratio;
			tmp.addRatio(ratio);
		}
		moduleList.push_back(tmp);
	}

	vector<NetList> NetLists;
	int NetListNum;
	in >> NetListNum;
	for (int i = 0; i < NetListNum; i++) {
		NetList tmp;
		int NetNum, ms, cr;
		in >> NetNum;
		for (int j = 0; j < NetNum; j++) {
			in >> ms >> cr;
			Net net;
			net.moduleSeq = ms;
			net.cornerRank = cr;
			tmp.net.push_back(net);
		}
		NetLists.push_back(tmp);
	}
	CornerBlockList cbl(NetLists, moduleList, a);
	SA yx(initialTemp, decTemp, stopTemp, incTurn, 100);
	yx.Calculate(cbl);
	bw.print(yx.result);
	
	return 0;
}