#include <bits/stdc++.h>
#include <point.h>
using namespace std;

// Convex Hull, runs in O(n) for sorted list
// pts must be vector of at least 3 points
// SORTED with pair sort
// Returns: points of convex hull in ccw order
vector<point> convex_hull(const vector<point>& pts) {
	const int& n = pts.size();

	vector<point> hull = { pts[0], pts[1] };

	for(int i=2; i<n; i++) {
		while(hull.size() > 1 and cross(pts[i] - hull[hull.size()-2], hull.back() - hull[hull.size()-2]) < 0)
			hull.pop_back();
		hull.push_back(pts[i]);
	}

	int lhsize = hull.size();
	hull.push_back(pts[n-2]);

	for(int i=n-3; i>=0; i--) {
		while(hull.size() > 1 and cross(pts[i] - hull[hull.size()-2], hull.back() - hull[hull.size()-2]) < 0)
			hull.pop_back();
		hull.push_back(pts[i]);
	}
	hull.pop_back();

	return hull;
}


