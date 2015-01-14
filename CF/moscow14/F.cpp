#include <iostream>
#include <cmath>

using namespace std;

typedef pair<int, int> point;
#define x first
#define y second

#define SQ(x) ((x) * (x))
double dist(point a, point b)
{
	return sqrt(SQ(a.x - b.x) + SQ(a.y - b.y));
}

double time_to_hours(string S)
{
	double hours = (S[0] - '0') * 10 + (S[1] - '0');
	double mins = (S[3] - '0') * 10 + (S[4] - '0');
	return hours + mins / 60.0;
}

point A, B, C;
double D, V;
double W;

int main()
{
	cin >> A.x >> A.y >> B.x >> B.y >> C.x >> C.y;
	cin >> D >> V;
	D /= 60.0;
	string s, t;
	cin >> s >> t;
	cin >> W;
	double dmitry = time_to_hours(s) - 9.0 + time_to_hours(t);
	double alex = (dist(A, C) + dist(C, B)) / V + D;
	double petr = dist(A, B) / W;
	if(dist(A, C) + dist(C, B) - dist(A, B) < 1e-9) petr += D;
	if(dmitry < alex && dmitry < petr) cout << "Dmitry\n";
	else if(alex < dmitry && alex < petr) cout << "Alex\n";
	else if(petr < dmitry && petr < alex) cout << "Petr\n";
	else return -1;
}
