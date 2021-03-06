#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

int N, M;
ll K;
int A[505][505];
vector<int> goods, bads;
int remap[505];
double P[505][505];

typedef double matrix[105][105];
void mult(matrix A, matrix B, matrix C)
{
	matrix temp;
	memset(temp, 0, sizeof(temp));
	for(int i = 0; i < 105; i++)
		for(int j = 0; j < 105; j++)
			for(int k = 0; k < 105; k++)
				temp[i][j] += A[i][k] * B[k][j];
	memcpy(C, temp, sizeof(matrix));
}

matrix Q, R;
int V[505];

int main()
{
	cin >> N >> M >> K;
	for(int i = 1; i <= N; i++)
	{
		int x;
		cin >> x;
		if(x || i == 1) bads.push_back(i);
		else goods.push_back(i);
	}
	for(int i = 0; i < bads.size(); i++)
		remap[bads[i]] = i;
	for(int i = 0; i < goods.size(); i++)
		remap[goods[i]] = bads.size() + i;
	for(int i = 0; i < M; i++)
	{
		int u, v;
		cin >> u >> v;
		u = remap[u], v = remap[v];
		A[u][v]++;
		A[v][u]++;
	}
	for(int i = 0; i < N; i++)
	{
		double deg = 0;
		for(int j = 0; j < N; j++)
			deg += A[i][j];
		for(int j = 0; j < N; j++)
			P[i][j] += A[i][j] / deg;
	}
	//for(int i = 0; i < N; i++) { for(int j = 0; j < N; j++) cout << P[i][j] << ' '; cout << endl; }
	while(N > bads.size())
	{
		N--;
		for(int i = 0; i < N; i++)
			P[N][i] /= (1.0 - P[N][N]);
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				P[i][j] += P[i][N] * P[N][j];
		//for(int i = 0; i < N; i++) { for(int j = 0; j < N; j++) cout << P[i][j] << ' '; cout << endl; } cout << "-----\n";
	}
	//for(int i = 0; i < N; i++) { for(int j = 0; j < N; j++) cout << P[i][j] << ' '; cout << endl; }
	N--;
	for(int i = 1; i <= N; i++)
		P[0][i] /= (1.0 - P[0][0]);
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= N; j++)
			Q[i][j] = P[i][j] + P[i][0] * P[0][j];
	//for(int i = 1; i <= N; i++) { for(int j = 1; j <= N; j++) cout << Q[i][j] << ' '; cout << endl; }
	for(int i = 1; i <= N; i++)
		R[i][i] = 1;
	K -= 2;
	for(int b = 0; b <= 63; b++)
	{
		if(K & (1LL << b))
			mult(Q, R, R);
		mult(Q, Q, Q);
		//for(int i = 1; i <= N; i++) { for(int j = 1; j <= N; j++) cout << Q[i][j] << ' '; cout << endl; }
	}
	//for(int i = 1; i <= N; i++) { for(int j = 1; j <= N; j++) cout << R[i][j] << ' '; cout << endl; }
	double total = 0;
	for(int i = 1; i <= N; i++)
		total += P[0][i] * R[i][N];
	cout << total << '\n';
}
