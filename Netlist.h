#ifndef NETLIST_H
#define NETLIST_H

#include <vector>

struct Net {
	int moduleSeq, cornerRank;
};

struct NetList {
	std::vector<Net> net;
};

#endif