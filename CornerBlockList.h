#ifndef CORNERBLOCKLIST_H
#define CORNERBLOCKLIST_H

#include "Module.h"
#include "Node.h"
#include "Netlist.h"
class CornerBlockList {
private:
	int moduleNum;
	std::vector<NetList> NetLists;
	std::vector<Module> modules;
	std::vector<Edge*> HorEdges;
	std::vector<Edge*> VecEdges;
	std::vector<Node*> HorNodes;
	std::vector<Node*> VecNodes;
	std::vector<int> HorStack;
	std::vector<int> VecStack;
	Node *East, *South, *West, *North;
	std::vector<int> SList;
	std::vector<int> LList;
	std::vector<int> TList;
	double a;
	void calcLongPath(Node*, Node*);
	bool buildGraph();
public:
	void findNeibor();
	void placeModule();
	double Evaluate();
	CornerBlockList(std::vector<Module>&, double);
};

#endif