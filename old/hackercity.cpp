#include <iostream>
#include <cstdio>

using namespace std;

int gcd(int a, int b)
{
	if(a == 0 || b == 0) return a+b;
	if(a > b) return gcd(a%b, b);
	return gcd(b%a, a);
}
const int MAX = 1234567;
pair<int, int> round(double x)
{
	double min_eps = MAX;
	pair<int, int> best;
	for(int i = 1; i < MAX; i++)
	{
		double kx = i*x;
		double eps = kx - (int)(kx+0.5);
		if(eps < 0) eps *= -1;
		if(eps < min_eps)
		{
			min_eps = eps;
			best = make_pair((int)(kx+0.5), i);
		}
	}
	int g = gcd(best.first, best.second);
	best.first /= g;
	best.second /= g;
	return best;
}

const double EPS = 1e-8;
int N;
int A[505][505];
double dist[505][505];

bool test(double mid)
{
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
	{
		if(i == j) dist[i][j] = 0;
		else dist[i][j] = A[i][j]-mid;
	}
	for(int k = 0; k < N; k++) for(int i = 0; i < N; i++) for(int j = 0; j < N; j++)
	{
		dist[i][j] = min(dist[i][j], dist[i][k]+dist[k][j]);
	}
	for(int i = 0; i < N; i++) if(dist[i][i] < 0) return true;
	return false;
}
int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) for(int j = 0; j < N; j++) scanf("%d", &A[i][j]);
	double low = 0, high = 501;
	while(low + EPS < high)
	{
		double mid = (low+high)/2;
		if(test(mid)) high = mid;
		else low = mid;
	}
	pair<int, int> ans = round(low);
	cout << ans.first << '/' << ans.second << endl;
	return 0;
}
