#ifndef NODE_H
#define NODE_H
#include <vector>
#include "Edge.h"
class Edge;
class Node {
public:
	double dist;
	int inDegree;
	std::vector<Edge*> edges;
	Node() { dist = 0; }
	void clear() { edges.clear(); }
};

#endif