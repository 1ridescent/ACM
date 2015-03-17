#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int N, M;
char B[2005][2005];
int U[2005][2005], D[2005][2005], L[2005][2005], R[2005][2005];

int dU[2005][2005], dD[2005][2005], dL[2005][2005], dR[2005][2005];

ll ones = 0;
ll twos = 0;
ll threes = 0;

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		scanf("%s", &(B[i][1]));
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			U[i][j] = (B[i][j] == '#' ? 0 : U[i - 1][j] + 1);
			L[i][j] = (B[i][j] == '#' ? 0 : L[i][j - 1] + 1);
		}
	for(int i = N; i >= 1; i--)
		for(int j = M; j >= 1; j--)
		{
			D[i][j] = (B[i][j] == '#' ? 0 : D[i + 1][j] + 1);
			R[i][j] = (B[i][j] == '#' ? 0 : R[i][j + 1] + 1);
		}
	for(int c = 2; c < M; c++)
		if(1 + D[1][c] == N + 1) ones++;
	for(int r = 2; r < N; r++)
		if(1 + R[r][1] == M + 1) ones++;
	for(int r = 2; r < N; r++)
		for(int c = 2; c < M; c++)
		{
			int v = 0;
			if(r + D[r][c] == N + 1) v++;
			if(r - U[r][c] == 0) v++;
			int h = 0;
			if(c + R[r][c] == M + 1) h++;
			if(c - L[r][c] == 0) h++;
			cout <<r<< ' '<<c<<' '<<v<<' '<<h<<endl;
			twos += v * h;
			dL[r][c - 1] += v, dR[r][c + 1] += v;
			dU[r - 1][c] += h, dD[r + 1][c] += h;
		}

	for(int r = 2; r < N; r++)
		for(int c = 2; c < M; c++)
	printf("%d %d: %d %d %d %d\n",r,c,dL[r][c],dR[r][c],dU[r][c],dD[r][c]);
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			if(B[i][j] == '#') dD[i][j] = dR[i][j] = 0;
			else dD[i][j] += dD[i - 1][j], dR[i][j] += dR[i][j - 1];
		}
	for(int i = N; i >= 1; i--)
		for(int j = M; j >= 1; j--)
		{
			if(B[i][j] == '#') dU[i][j] = dL[i][j] = 0;
			else dU[i][j] += dU[i + 1][j], dL[i][j] += dL[i][j + 1];
		}
	for(int r = 2; r < N; r++)
		for(int c = 2; c < M; c++)
		{
			int v = 0;
			if(r + D[r][c] == N + 1) v++;
			if(r - U[r][c] == 0) v++;
			printf("%d %d: %d %d %d %d\n",r,c,dL[r][c],dR[r][c],dU[r][c],dD[r][c]);
			threes += v * (dL[r][c] + dR[r][c]);
			int h = 0;
			if(c + R[r][c] == M + 1) h++;
			if(c - L[r][c] == 0) h++;
			threes += h * (dU[r][c] + dD[r][c]);
		}
	cout << ones << ' ' << twos << ' ' << threes << endl;
	cout << ones + twos + threes / 2 << endl;
}
