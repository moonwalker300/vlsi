#ifndef POINT_H
#define POINT_H

struct Point {
	double x, y;
	Point(double xx, double yy) {
		x = xx;
		y = yy;
	}
};

struct Rectangle {
	Point LL, RU;
	Rectangle(Point L, Point R) {
		LL.x = L.x;
		LL.y = L.y;
		RU.x = R.x;
		RU.y = R.y;
	}
};

#endif