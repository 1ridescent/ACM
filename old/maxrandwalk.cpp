#include <cstdio>

using namespace std;

double P[1010][1010]; // [steps][max overhead]

int main()
{
	int T;
	scanf("%d", &T);
	while(T--)
	{
		int C, N;
		double L, R;
		scanf("%d %d %lf %lf", &C, &N, &L, &R);
		P[0][0] = 1;
		for(int x = 1; x < 1010; x++) P[0][x] = 0;
		for(int t = 1; t <= N; t++)
		{
			for(int x = 0; x <= N; x++)
			{
				P[t][x] = (1-L-R)*P[t-1][x] + L*P[t-1][x-1] + R*P[t-1][x+1];
				if(x == 0) P[t][x] += R*P[t-1][0];
			}
		}
		double E = N * (L*-1 + R*1);
		for(int x = 0; x <= N; x++) E += P[N][x] * x;
		printf("%d %.4f\n", C, E);
	}
	return 0;
}
