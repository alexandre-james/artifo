#include "point.hpp"

#include <cmath>

bool operator==(const point& p1, const point& p2) {
	return p1.x == p2.x && p1.y == p2.y;
}

double point::dist(point p) {
	int x_gap = x - p.x;
	int y_gap = y - p.y;
	return std::sqrt(x_gap * x_gap + y_gap * y_gap);
}