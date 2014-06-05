#include <iostream>

using namespace std;

int N, M;
int A[205][205];
int G[2][205][205];

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
		{
			cin >> A[i][j];
			if(i != j)
			{
				if(A[i][j] <= M / 2) G[0][i][j] = 1, G[1][i][j] = 7;
				else G[0][i][j] = 7, G[1][i][j] = 1;
			}
			else G[0][i][j] = G[1][i][j] = 0;
		}
	for(int t = 0; t <= 1; t++)
	{
		for(int k = 1; k <= N; k++)
			for(int i = 1; i <= N; i++)
				for(int j = 1; j <= N; j++)
					G[t][i][j] = min(G[t][i][j], G[t][i][k] + G[t][k][j]);
		bool check = true;
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
				if(G[t][i][j] > 3) check = false;
		if(check)
		{
			if(t == 0)
			{
				cout << M / 2 << endl;
				for(int i = 1; i <= M / 2; i++) cout << i << ' ';
			}
			else
			{
				cout << M - M / 2 << endl;
				for(int i = M / 2 + 1; i <= M; i++) cout << i << ' ';
			}
			return 0;
		}
	}
	return -1;
}
