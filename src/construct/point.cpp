#include "point.hpp"

#include <cmath>

template <typename num_type1, typename num_type2>
float dist(point<num_type1> p1, point<num_type2> p2) {
	float x = p1.x - p2.x;
	float y = p1.y - p2.y;
	return std::sqrt(x * x + y * y);
}

template float dist(point<int>, point<int>);
template float dist(point<float>, point<int>);
template float dist(point<int>, point<float>);
template float dist(point<float>, point<float>);