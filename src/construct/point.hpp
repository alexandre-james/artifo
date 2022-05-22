#pragma once

template <typename num_type>
class point {
public:
    num_type x, y;
    point(num_type x, num_type y): x(x), y(y) {}
};

template <typename num_type1, typename num_type2>
float dist(point<num_type1> p1, point<num_type2> p2);