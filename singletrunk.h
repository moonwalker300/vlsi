#ifndef SINGLETRUNK_H
#define SINGLETRUNK_H
#include <vector>

class SingleTrunk {
public:
	const static double MAX;
	const static double MIN;
	static double compute_para(int len, std::vector<double>& a, double &max_num, double &min_num);
	static double sum(int num, std::vector<double>& a, double avg);
	static double STST(int num, std::vector<double>& x, std::vector<double>& y);
};

#endif