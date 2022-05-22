#pragma once

class point {
public:
    int x, y;
    point(int x, int y): x(x), y(y) {}

    double dist(point p);

    friend bool operator==(const point& p1, const point& p2);

};