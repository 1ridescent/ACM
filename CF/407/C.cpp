#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define MOD(x) (((x) + mod) % mod)

ll choose[200005][105];
void pre()
{
	memset(choose, 0, sizeof(choose));
	choose[0][0] = 1;
	for(int n = 1; n <= 200000; n++)
	{
		choose[n][0] = 1;
		for(int k = 1; k <= 100; k++) choose[n][k] = MOD(choose[n - 1][k - 1] + choose[n - 1][k]);
	}
}

int N, M;
ll S[100005];
ll D[105][100005];

int main()
{
	pre();
	ios::sync_with_stdio(false);

	cin >> N >> M;
	for(int i = 1; i <= N; i++) cin >> S[i];

	memset(D, 0, sizeof(D));
	for(int m = 0; m < M; m++)
	{
		int L, R, K;
		cin >> L >> R >> K;
		D[100 - K][L] = MOD(D[100 - K][L] + 1);
		for(int k = 0; k <= K; k++)
		{
			D[100 - K + k][R + 1] = MOD(D[100 - K + k][R + 1] - choose[R - L + k][k]);
		}
	}

	/*for(int k = 95; k <= 100; k++)
	{
		cout << (k == 100 ? "" : " ") << k << ": ";
		for(int i = 1; i <= N; i++) cout << D[k][i] << ' ';
		cout << endl;
	}*/

	for(int k = 0; k <= 100; k++)
		for(int i = 1; i <= N; i++)
		{
			D[k][i] = MOD(D[k][i] + (k == 0 ? 0 : D[k - 1][i]) + (i == 1 ? 0 : D[k][i - 1]));
		}

	for(int i = 1; i <= N; i++) cout << MOD(S[i] + D[100][i]) << ' ';
}
