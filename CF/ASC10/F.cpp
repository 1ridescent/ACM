#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

const double PI = acos(-1);
const double INF = 1e100;

int N;
double R, H;

#define SQ(x) ((x) * (x))
inline double normalize(double a)
{
	while(a <= 0) a += 2 * PI;
	while(a >= 2 * PI) a -= 2 * PI;
	return a;
}
/*inline double angledist(double a, double b)
{
	a = normalize(a);
	b = normalize(b);
	return min(abs(a - b), 2 * PI - abs(a - b));
}*/
double dist(double a, double b)
{
	double d = a - b;//angledist(a, b);
	if(d < 0) d *= -1;
	return sqrt(SQ(d * R) + SQ(H));
}

double best;
int assign[1010];
vector<double> V;
vector<double> divs;
void compute(vector< pair<double, int> > A, vector< pair<double, int> > B)
{
	V.clear();//vector<double> V;
	for(int i = 0; i < N; i++) V.push_back(normalize(A[i].first));
	for(int i = 0; i < N; i++) V.push_back(normalize(B[i].first));
	sort(V.begin(), V.end());
	divs.clear();//vector<double> divs;
	for(int i = 0; i < N - 1; i++) divs.push_back(0.5 * (V[i] + V[i + 1]));
	divs.push_back(normalize(0.5 * (V[N - 1] + (V[0] + 2 * PI))));

	best = INF;
	for(int di = 0; di < N; di++)
	{
		double div = divs[di];
		for(int i = 0; i < N; i++) A[i].first = normalize(A[i].first - div);
		for(int i = 0; i < N; i++) B[i].first = normalize(B[i].first - div);

		sort(A.begin(), A.end());
		sort(B.begin(), B.end());

		double cur = 0;
		for(int i = 0; i < N; i++)
		{
			cur += dist(A[i].first, B[i].first);
		}
		if(cur < best)
		{
			best = cur;
			for(int i = 0; i < N; i++) assign[A[i].second] = B[i].second;
		}

		for(int i = 0; i < N; i++) A[i].first = normalize(A[i].first + div);
		for(int i = 0; i < N; i++) B[i].first = normalize(B[i].first + div);
	}
}
vector< pair<double, int> > top, mid, bot;
int nexttop[1010];
int nextmid[1010];

int main()
{
	freopen("magic.in", "r", stdin); freopen("magic.out", "w", stdout);

	cin >> N >> R >> H;
	H /= 2;
	for(int i = 1; i <= N; i++)
	{
		double a;
		cin >> a;
		top.push_back( make_pair(normalize(a), i) );
	}
	for(int i = 1; i <= N; i++)
	{
		double a;
		cin >> a;
		mid.push_back( make_pair(normalize(a), i) );
	}
	for(int i = 1; i <= N; i++)
	{
		double a;
		cin >> a;
		bot.push_back( make_pair(normalize(a), i) );
	}

	double ans = 0;
	compute(top, mid);
	ans += best;
	for(int i = 1; i <= N; i++) nexttop[i] = assign[i];

	compute(mid, bot);
	ans += best;
	for(int i = 1; i <= N; i++) nextmid[i] = assign[i];

	printf("%.9f\n", ans);
	for(int i = 1; i <= N; i++) printf("%d %d %d\n", i, nexttop[i], nextmid[nexttop[i]]);
	return 0;
}
