#include <bits/stdc++.h>

using namespace std;

int N;

int A[505][505];
void row_add(int from, int to)
{
	for(int i = 1; i <= N + 1; i++)
		A[to][i] ^= A[from][i];
}
int rref()
{
	int r = 1;
	for(int c = 1; c <= N; c++)
	{
		if(!A[r][c])
		{
			for(int i = r + 1; i <= N; i++)
				if(A[i][c])
				{
					row_add(i, r);
					break;
				}
		}
		if(!A[r][c]) continue;
		for(int i = r + 1; i <= N; i++)
			if(A[i][c])
				row_add(r, i);
		r++;
	}
	return r;
}
void print()
{
	for(int i = 1; i <= N; i++)
	{
		for(int j = 1; j <= N; j++) cout << A[i][j] << ' ';
		cout << "| " << A[i][N + 1] << endl;
	}
}

int res[505];

int main()
{
	int M;
	cin >> N >> M;
	while(M--)
	{
		int a, b;
		cin >> a >> b;
		A[a][b] ^= 1;
		A[b][a] ^= 1;
		A[a][a] ^= 1;
		A[b][b] ^= 1;
		A[a][N + 1] ^= 1;
		A[b][N + 1] ^= 1;
	}
	//print();
	int rank = rref();
	//print();
	for(int i = rank + 1; i <= N; i++)
		if(A[i][N + 1])
		{
			cout << "IMPOSSIBLE\n";
			return 0;
		}
	for(int i = rank; i >= 1; i--)
	{
		for(int j = 1; j <= N; j++)
			if(A[i][j])
			{
				res[j] = A[i][N + 1];
				for(int k = j + 1; k <= N; k++)
					if(A[i][k])
						res[j] ^= res[k];
				break;
			}
	}
	for(int i = 1; i <= N; i++) cout << (res[i] ? 'A' : 'B');
	cout << endl;
}
