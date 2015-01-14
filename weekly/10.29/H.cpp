#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Point
{
	double x, y;
	Point() { }
	Point(int x2, int y2) { x = x2, y = y2; }
	Point operator+(Point p)
	{
		return Point(x + p.x, y + p.y);
	}
	Point operator-(Point p)
	{
		return Point(x - p.x, y - p.y);
	}
	Point operator*(int s)
	{
		return Point(s * x, s * y);
	}
};

class Line
{
	double m, b;
	Line() { }
	Line(Point s, Point t)
	{
		m = (t.y - s.y) / (t.x - s.x);
		b = s.y - m * s.x;
	}
	bool operator<(Line l)
	{
		return m < l.m;
	}
};

int N;
Point P[2020];

int main()
{
	ios::sync_with_stdio(false);
	while(true)
	{
		cin >> N;
		for(int i = 0; i < N; i++) cin >> P[i].x >> P[i].y;
		for(int i = 0; i < N; i++)
		{
			for(int j = i + 1; j < N; j++)
			{

			}
		}
	}
}
