#include <iostream>
#include <cmath>
#include <cstdio>


using namespace std;

typedef pair<double, double> point;
#define x first
#define y second

const double inf = 1e15;

point S, T;
int N;
point C[111];

#define SQ(x) ((x) * (x))
double dist(point a, point b)
{
	return sqrt(SQ(a.x - b.x) + SQ(a.y - b.y));
}

double D[111][111];

int main()
{
	cin >> S.x >> S.y >> T.x >> T.y;

	cin >> N;
	for(int i = 1; i <= N; i++) cin >> C[i].x >> C[i].y;

	for(int i = 0; i <= N + 1; i++)
		for(int j = 0; j <= N + 1; j++)
		{
			if(i == j) D[i][j] = 0;
			else
			{
				if(i == 0 && j == N + 1 || i == N + 1 && j == 0)
				{
					D[i][j] = dist(S, T) / 5;
				}
				else if(i == 0)
				{
					D[i][j] = dist(S, C[j]) / 5;
				}
				else if(i == N + 1)
				{
					D[i][j] = dist(T, C[j]) / 5;
				}
				else if(j == 0)
				{
					D[i][j] = abs(dist(C[i], S) - 50) / 5 + 2;
				}
				else if(j == N + 1)
				{
					D[i][j] = abs(dist(C[i], T) - 50) / 5 + 2;
				}
				else
				{
					D[i][j] = abs(dist(C[i], C[j]) - 50) / 5 + 2;
				}
			}
		}

	for(int k = 0; k <= N + 1; k++)
		for(int i = 0; i <= N + 1; i++)
			for(int j = 0; j <= N + 1; j++)
				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

	printf("%.9f\n", D[0][N + 1]);
}
