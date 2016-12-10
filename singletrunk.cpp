#include "singletrunk.h"

using namespace std;

const double SingleTrunk::MAX = 1000000000;
const double SingleTrunk::MIN = 0;

double SingleTrunk::compute_para(int len, vector<double>& a, double &max_num, double &min_num)
{
	double avg = 0;
	for (int i = 0; i < len; i++)
	{
		avg += a[i];
		if (a[i] > max_num) max_num = a[i];
		if (a[i] < min_num) min_num = a[i];
	}
	avg = avg / len;
	return avg;
}

double SingleTrunk::sum(int num, vector<double>& a, double avg)
{
	double res = 0;
	for (int i = 0; i < num; i++)
	{
		res += fabs(a[i] - avg);
	}
	return res;
}

double SingleTrunk::STST(int num, vector<double>& x, vector<double>& y)
{
	double x_avg = 0;
	double x_max = MIN;
	double x_min = MAX;
	double y_avg = 0;
	double y_max = MIN;
	double y_min = MAX;

	x_avg = compute_para(num, x, x_max, x_min);
	y_avg = compute_para(num, y, y_max, y_min);
	//cout << "average: " << x_avg << " " << y_avg << endl ;
	//cout << "max: " << x_max << " " << y_max << endl ;
	//cout << "min: " << x_min << " " << y_min << endl ;

	double x_sum = sum(num, x, x_avg);
	double y_sum = sum(num, y, y_avg);

	//cout << "sum: " << x_sum << " " << y_sum << endl ;

	double Ln_x = y_max - y_min + x_sum;
	double Ln_y = x_max - x_min + y_sum;
	double ans = 0.5 * (Ln_x + Ln_y);
	//cout << Ln_x << " " << Ln_y << " " << ans << endl ;
	return ans;
}