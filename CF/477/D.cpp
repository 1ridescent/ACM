#include <iostream>
#include <cstring>

using namespace std;

typedef long long ll;
#define MOD(x) (((x) + 1000000007000LL) % 1000000007)
const ll inf = 1e15;

string S0;
int S[5050];
int N;

int len[5050][5050];

ll num[5050][5050]; // [r][l]: total num with last print [l,r]
ll best[5050][5050]; // [r][l]: min # prints with last print [l,r]
bool poss[5050][5050];

ll val[5050];
bool end[5050];

bool try_same(int l, int r)
{
	int s = r - l + 1;
	int d = len[l - s][l];
	if(d >= s) return true;
	return S[l - s + d] < S[l + d];
}

ll to_binary(int l, int r)
{
	ll res = 0;
	for(int i = l; i <= r; i++)
	{
		res *= 2;
		res += S[i];
		res = MOD(res);
	}
	return res;
}

int main()
{
	cin >> S0;

	int init_i = 0;
	while(S0[init_i] == '0')
	{
		init_i++;
		if(init_i == S0.size())
		{
			//cout << "asdf";
			cout << 1 << endl << S0.size() << endl;
			return 0;
		}
	}

	S0 = S0.substr(init_i);
	N = S0.size();

	for(int i = 0; i < N; i++) S[i + 1] = S0[i] - '0';

	memset(len, 0, sizeof(len));
	for(int i = N; i >= 1; i--)
		for(int j = N; j >= 1; j--)
		{
			if(S[i] != S[j]) len[i][j] = 0;
			else len[i][j] = len[i + 1][j + 1] + 1;
		}

	for(int r = 1; r <= N; r++)
	{
		for(int l = 1; l <= r; l++) // add [l, r]
		{
			if(S[l] == 0)
			{
				num[r][l] = 0;
				best[r][l] = inf;
				poss[r][l] = false;
				continue;
			}
			if(l == 1)
			{
				num[r][l] = 1;
				best[r][l] = 1;
				poss[r][l] = true;
				continue;
			}

			int s = r - l + 1;
			int start;
			if(l - s < 1)
				start = 1;
			else
			{
				start = l - s;
				if(!try_same(l, r)) start++;
			}

			num[r][l] = num[l - 1][start];
			best[r][l] = 1 + best[l - 1][start];
			poss[r][l] = poss[l - 1][start];
		}

		if(r == N)
		{
			for(int i = 1; i <= N; i++)
			{
				val[i] = best[N][i];
				end[i] = poss[N][i];
			}
		}

		for(int l = r - 1; l >= 1; l--)
		{
			num[r][l] = MOD(num[r][l] + num[r][l + 1]);
			best[r][l] = min(best[r][l], best[r][l + 1]);
			poss[r][l] |= poss[r][l + 1];
		}
	}

	cout << num[N][1] << endl;

	bool small = false;
	for(int i = max(1, N - 16); i <= N; i++)
		if(end[i])
			small = true;

	ll ans = inf;
	if(small)
	{
		for(int i = max(1, N - 16); i <= N; i++)
			if(end[i])
				ans = min(ans, val[i] + to_binary(i, N));
	}
	else
	{
		for(int i = N; i >= 1; i--)
		{
			if(end[i])
			{
				ans = val[i] + to_binary(i, N);
				break;
			}
		}
	}
	cout << MOD(ans + init_i) << endl;

}
