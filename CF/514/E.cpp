#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;

#define SIZE 105

ll mult(ll A[SIZE][SIZE], ll B[SIZE][SIZE], ll C[SIZE][SIZE])
{
	memset(C, 0, sizeof(C));
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
}
void identity(ll I[SIZE][SIZE])
{
	memset(I, 0, sizeof(I));
	for(int i = 0; i < SIZE;i ++) I[i][i] = 1;
}
ll power(ll A[SIZE][SIZE], ll C[SIZE][SIZE], int e)
{
	if(e == 0) identity(C);
	else
	{
		ll temp[SIZE][SIZE];
		memset(temp, 0, sizeof(temp));
		power(A, temp, e / 2);
		if(e % 2)
		{
			ll temp2[SIZE][SIZE];
			memset(temp2, 0, sizeof(temp2));
			mult(temp, temp, temp2);
			mult(temp2, A, C);
		}
		else mult(temp, temp, C);
	}
}
void print(ll A[SIZE][SIZE])
{
	for(int i = 0; i < SIZE; i++)
	{
		for(int j = 0; j < SIZE; j++) cout << A[i][j] << ' ';
		cout << endl;
	}
}

ll T[SIZE][SIZE];
ll T2[SIZE][SIZE];

int main()
{
	for(int i = 0; i < SIZE - 2; i++) T[i][i + 1] = 1;
	int N, X;
	cin >> N >> X;
	while(N--)
	{
		int d;
		cin >> d;
		T[SIZE - 2][SIZE - 1 - d]++;
		T[SIZE - 1][SIZE - 1 - d]++;
	}
	T[SIZE - 1][SIZE - 1] = 1;
	//print(T);
	power(T, T2, X);
	//print(T2);
	cout << (T2[SIZE - 1][SIZE - 2] + T2[SIZE - 1][SIZE - 1]) % mod;
}
