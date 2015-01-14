#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>

using namespace std;

int N, L;
int X[100005], B[100005];
double F[1005][1005];

double dist[1005];
int last[1005];
int ans[1005];

int main()
{
	cin >> N >> L;
	X[0] = 0;
	for(int i = 1; i <= N; i++)
		cin >> X[i] >> B[i];
	for(int r = 1; r <= N; r++)
		for(int l = 0; l < r; l++)
		{
				F[l][r] = sqrt(abs(X[r] - X[l] - L));
		}
	double low = 0, high = 1000;
	while(low + 1e-8 < high)
	{
		double mid = (low + high) / 2;
		for(int i = 1; i <= N; i++)
			dist[i] = 1e15;
		dist[0] = 0;
		for(int r = 1; r <= N; r++)
		{
			for(int l = 0; l < r; l++)
				//if(F[l][r] != -1)
				{
					double d = dist[l] + F[l][r] - mid * B[r];
					if(d < dist[r])
					{
						dist[r] = d;
						last[r] = l;
					}
				}
		}
		if(dist[N] < 0)
		{
			high = mid;
			memcpy(ans, last, sizeof(last));
		}
		else
			low = mid;
	}
	vector<int> out;
	for(int i = N; i != 0; i = ans[i])
		out.push_back(i);
	for(int i = out.size() - 1; i >= 0; i--)
		cout << out[i] << ' ';
}
