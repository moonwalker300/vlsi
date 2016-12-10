#ifndef EDGE_H
#define EDGE_H
#include "Node.h"
class Node;
class Edge {
public:
	Node* head;
	Node* tail;
	double len;
};

#endif