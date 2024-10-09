#include <bits/stdc++.h>
using namespace std;
using ll=long long;

template<typename T>
struct Point {
	T x,y;

	Point() = default;
	Point(T x, T y) : x(x), y(y) {}

	bool operator<(const Point& o) const {
		if(x == o.x) return y<o.y;
		return x<o.x;
	}

	// Point operator
	Point operator+(const Point& o) const {
		return Point(x+o.x, y+o.y);
	}

	Point operator-(const Point& o) const {
		return Point(x-o.x, y-o.y);
	}
};

template<typename T>
T dot(const Point<T>& a, const Point<T>& b) {
	return a.x*b.x + a.y*b.y;
}

template<typename T>
T cross(const Point<T>& a, const Point<T>& b) {
	return a.x*b.y - a.y*b.x;
}

using point = Point<ll>;

