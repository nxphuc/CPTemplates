#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <bitset>
using namespace std;
const double eps = 1e-9;

inline int diff(double lhs, double rhs){
	if (lhs - eps < rhs && rhs < lhs + eps)
		return 0;
	return (lhs < rhs) ? -1 : 1;
}

struct Point{
	double x, y;
	Point(){}
	Point(double x_, double y_): x(x_), y(y_) {}
};

int ccw(const Point &a, const Point &b, const Point &c){
	return diff(a.x * b.y + b.x *c.y + c.x * a.y - a.y * b.x - b.y * c.x - c.y * a.x, 0.0);
}

inline double dist2(const Point &a, const Point &b){
	double dx = a.x - b.x;
	double dy = a.y - b.y;
	return (dx * dx + dy * dy);
}

struct PointSorter{
	Point origin;
	PointSorter(const vector<Point> &Points){
		origin = Points[0];
		for (int i = 1; i < Points.size(); i++){
			int det = diff(origin.x, Points[i].x);
			if (det > 0)
				origin = Points[i];
			else
				if (det == 0 && diff(origin.y, Points[i].y) > 0)
					origin = Points[i];		
		}
	}
	
	bool operator()(const Point &a, const Point &b){
		if (diff(b.x, origin.x) == 0 && diff(b.y, origin.y) == 0)
			return false;
		if (diff(a.x, origin.x) == 0 && diff(a.y, origin.y) == 0)
			return true;
		int det = ccw(origin, a, b);
		if (det == 0)
			return dist2(a, origin) < dist2(b, origin);
		return det < 0;
	}
};

vector <Point> convex_hull(vector <Point> Points){
	if (Points.size() < 4)
		return Points;
	PointSorter cmp(Points);
	sort(Points.begin(), Points.end(), cmp);
	
	vector <Point> ans;
	
	ans.push_back(Points[0]);
	ans.push_back(Points[1]);
	for (int i = 2; i < Points.size(); i++){
		while (ans.size() > 1 && ccw(ans[ans.size() - 2], ans[ans.size() - 1], Points[i]) >= 0)
			ans.pop_back();
		ans.push_back(Points[i]);
	}
	return ans;
}

int main(){
	int t, n;
	vector <Point> a, ans;
	Point tmp;
	

	scanf("%d", &n);
	for (int i = 0; i < n; i++){
		scanf("%lf %lf", &tmp.x, &tmp.y);
		a.push_back(tmp);
	}
	
	ans = convex_hull(a);
	
	for(int i = 0; i < ans.size(); i++){
		printf("%.2lf %.2lf\n", ans[i].x, ans[i].y);
	}

	return 0;
}
