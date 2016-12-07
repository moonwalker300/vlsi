#include "CornerBlockList.h"
#include <cmath>
#include <ctime>

using namespace std;

CornerBlockList::CornerBlockList(std::vector<Module>& modules, double a) {
	srand(time(0));
	this->modules = modules;
	this->a = a;
	moduleNum = modules.size();
	for (int i = 0; i < moduleNum; i++)
		SList.push_back(i);
	for (int i = 0; i < moduleNum; i++) {
		HorEdges.push_back(new Edge());
		VecEdges.push_back(new Edge());
		HorNodes.push_back(new Node());
		VecNodes.push_back(new Node());
	}
	for (int i = 0; i < moduleNum - 1; i++)
		LList.push_back(0);
	for (int i = 0; i < moduleNum - 1; i++)
		TList.push_back(0);
	East = new Node();
	South = new Node();
	West = new Node();
	North = new Node();
}

void CornerBlockList::findNeibor() {
	int randNum = rand() % 6;
	if (randNum == 0) { //exchange SList
		int x, y;
		while (1) {
			x = rand() % moduleNum;
			y = rand() % moduleNum;
			if (x != y)
				break;
		}
		int tmp = SList[x];
		SList[x] = SList[y];
		SList[y] = tmp;
	}
	else if (randNum == 1) { //LList 0 <-> 1
		int x = rand() % moduleNum;
		LList[x] = 1 - LList[x];
	}
	else if (randNum = 2) { //TList Add 1 or Delete 1
		if (rand() % 2 == 0) { //Add 1 
			int Limit = TList.size();
			int p = rand() % Limit;
			TList.insert(TList.begin() + p, 1);
			//Illegal back
			if (Evaluate() < 0)
				TList.erase(TList.begin() + p);
		}
		else { //Delete 1
			vector<int> tmp;
			for (int i = 0; i < TList.size(); i++)
				if (TList[i] == 1)
					tmp.push_back(i);
			int p = tmp[rand() % tmp.size()];
			TList.erase(TList.begin() + p);
			//Illegal back
			if (Evaluate() < 0)
				TList.insert(TList.begin() + p, 1);
		}
	}
	else if (randNum == 3) { //Rotate
		int x = rand() % moduleNum;
		modules[x].rotateClockWise();
	}
	else if (randNum == 4) { //Reflect
		int x = rand() % moduleNum;
		modules[x].reflect();
	}
	else if (randNum == 5) { //ChangeRatio
		int x = rand() % moduleNum;
		modules[x].changeRatio();
	}
}

bool CornerBlockList::buildGraph() {
	for (int i = 0; i < moduleNum; i++) {
		HorEdges[i]->len = modules[i].getW();
		VecEdges[i]->len = modules[i].getH();
	}

	HorEdges[SList[0]]->head = West;
	HorEdges[SList[0]]->tail = East;
	VecEdges[SList[0]]->head = South;
	VecEdges[SList[0]]->tail = North;
	HorStack.clear();
	VecStack.clear();
	HorStack.push_back(SList[0]);
	VecStack.push_back(SList[0]);

	int HorNodePt = 0;
	int VecNodePt = 0;
	int pt = 0;
	for (int i = 0; i < moduleNum - 1; i++) {
		int num = 0;
		while (TList[pt] == 1) {
			pt++;
			num++;
		}
		num++;
		pt++;
		if (LList[i] == 0) {
			if (HorStack.size() < num)
				return false;
			int tmp = HorStack.size() - num;
			for (int j = tmp; j < tmp + num; j++)
				VecEdges[HorStack[j]]->tail = VecNodes[VecNodePt];
			VecNodes[VecNodePt]->clear();
			VecNodes[VecNodePt]->edges.push_back(VecEdges[SList[i + 1]]);
			VecEdges[SList[i + 1]]->head = VecNodes[VecNodePt];
			VecEdges[SList[i + 1]]->tail = North;
			VecNodePt++;
			int rem = HorStack[tmp];
			HorStack.erase(HorStack.begin() + tmp, HorStack.end());
			HorStack.push_back(SList[i + 1]);

			HorEdges[SList[i + 1]]->head = HorEdges[rem]->head;
			HorEdges[SList[i + 1]]->tail = East;
			VecStack.push_back(SList[i + 1]);
		}
		else {
			if (VecStack.size() < num)
				return false;
			int tmp = VecStack.size() - num;
			for (int j = tmp; j < tmp + num; j++)
				HorEdges[VecStack[j]]->tail = HorNodes[HorNodePt];
			HorNodes[HorNodePt]->clear();
			HorNodes[HorNodePt]->edges.push_back(HorEdges[SList[i + 1]]);
			HorEdges[SList[i + 1]]->head = HorNodes[HorNodePt];
			HorEdges[SList[i + 1]]->tail = East;
			HorNodePt++;
			int rem = VecStack[tmp];
			VecStack.erase(VecStack.begin() + tmp, VecStack.end());
			VecStack.push_back(SList[i + 1]);

			VecEdges[SList[i + 1]]->head = VecEdges[rem]->head;
			VecEdges[SList[i + 1]]->tail = East;
			HorStack.push_back(SList[i + 1]);
		}
	}
	return true;
}

void CornerBlockList::calcLongPath(Node* start, Node* end) {
	start->dist = 0;
	end->dist = 0;

	vector<Node*> order;
	order.push_back(start);
	int head = 0, tail = 0;
	for (; head <= tail; head++) {
		Node* now = order[head];
		for (int i = 0; i < now->edges.size(); i++) {
			now->edges[i]->tail->inDegree;
			if (now->edges[i]->tail->inDegree == 0) {
				order.push_back(now->edges[i]->tail);
				tail++;
			}
		}
	}

	for (int i = 0; i <= tail; i++) {
		Node* now = order[i];
		for (int j = 0; j < now->edges.size(); j++)
			if (now->edges[j]->tail->dist < now->dist + now->edges[j]->len)
				now->edges[j]->tail->dist = now->dist + now->edges[j]->len;
	}

}

void CornerBlockList::placeModule() {
	int NetListNum = NetLists.size();
	vector<Point> lyx;
	vector<int> times;
	for (int i = 0; i < moduleNum; i++) {
		lyx.push_back(Point(0, 0));
		times.push_back(0);
	}
	for (int i = 0; i < NetListNum; i++) {
		int NetNum = NetLists[i].net.size();
		Point res(0, 0);
		for (int j = 0; j < NetNum; j++) {
			int mSeq = NetLists[i].net[j].moduleSeq;
			int cSeq = NetLists[i].net[j].cornerRank;
			double w = modules[mSeq].getW();
			double h = modules[mSeq].getH();
			Point LLP(HorEdges[mSeq]->head->dist, VecEdges[mSeq]->head->dist);
			Point RUP(HorEdges[mSeq]->head->dist - w, VecEdges[mSeq]->head->dist - h);
			Point move = modules[mSeq].terminalMove(cSeq);
			res.x += (LLP.x + RUP.x) / 2 + move.x;
			res.y += (LLP.y + RUP.y) / 2 + move.y;
		}
		res.x /= NetNum;
		res.y /= NetNum;
		for (int j = 0; j < NetNum; j++) {
			int mSeq = NetLists[i].net[j].moduleSeq;
			int cSeq = NetLists[i].net[j].cornerRank;
			Point move = modules[mSeq].terminalMove(cSeq);
			lyx[mSeq].x += (res.x - move.x);
			lyx[mSeq].y += (res.y - move.y);
			times[mSeq]++;
		}
	}

	for (int i = 0; i < moduleNum; i++) {
		double w = modules[i].getW();
		double h = modules[i].getH();
		Point LLP(HorEdges[i]->head->dist, VecEdges[i]->head->dist);
		Point RUP(HorEdges[i]->head->dist - w, VecEdges[i]->head->dist - h);
		lyx[i].x /= times[i];
		lyx[i].y /= times[i];
		
		double px, py;
		
		if (lyx[i].x < LLP.x)
			px = LLP.x;
		else if (lyx[i].x > RUP.x)
			px = RUP.x;
		else
			px = lyx[i].x;

		if (lyx[i].y < LLP.y)
			py = LLP.y;
		else if (lyx[i].y > RUP.y)
			py = RUP.y;
		else
			py = lyx[i].y;
		
		modules[i].setLeftLowerX(px);
		modules[i].setLeftLowerY(py);
	}
}

double CornerBlockList::Evaluate() {
	bool f = buildGraph();
	if (!f)
		return -1;
	for (int i = 0; i < moduleNum; i++) {
		HorNodes[i]->dist = 0;
		HorNodes[i]->inDegree = 0;
		VecNodes[i]->dist = 0;
		VecNodes[i]->inDegree = 0;
	}

	East->inDegree = 0;
	South->inDegree = 0;
	West->inDegree = 0;
	North->inDegree = 0;
	for (int i = 0; i < moduleNum; i++) {
		VecEdges[i]->tail->inDegree++;
		HorEdges[i]->tail->inDegree++;
	}

	calcLongPath(West, East);
	calcLongPath(South, North);
	 
	double area = East->dist * North->dist;

	placeModule();
}