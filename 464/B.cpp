#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

typedef long long ll;
const ll inf = 1e17;

ll P[8][3];
ll Q[8][3];
ll S[8];
int I[3];
int J[3];
bool good()
{
	memcpy(Q, P, sizeof(P));
	for(int i = 7; i >= 0; i--)
		for(int j = 0; j < 3; j++)
			Q[i][j] -= Q[0][j];
	ll side = inf;
	ll diag = -inf;
	for(int i = 1; i < 8; i++)
	{
		S[i] = Q[i][0] * Q[i][0] + Q[i][1] * Q[i][1] + Q[i][2] * Q[i][2];
		if(S[i] < side) side = S[i];
		if(S[i] > diag) diag = S[i];
	}
	//cout << "1 " << side << ' ' << diag << endl;;
	int di = -1;
	int nexti = 0;
	for(int i = 0; i < 8; i++)
	{
		if(S[i] == diag)
		{
			di = i;
			continue;
		}
		if(S[i] == side)
		{
			if(nexti == 3) return false;
			I[nexti++] = i;
		}
	}
	if(nexti != 3) return false;
	//cout << "2\n";
	for(int i = 0; i < 3; i++)
		for(int j = i + 1; j < 3; j++)
			if(Q[I[i]][0] * Q[I[j]][0] + Q[I[i]][1] * Q[I[j]][1] + Q[I[i]][2] * Q[I[j]][2] != 0)
				return false;
	//cout << "2.5\n";
	for(int i = 0; i < 8; i++)
		for(int j = i + 1; j < 8; j++)
			if(Q[i][0] == Q[j][0] && Q[i][1] == Q[j][1] && Q[i][2] == Q[j][2])
				return false;
	//cout << "3\n";
	int cnt[3] = {0, 0, 0};
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 8; j++)
			for(int k = 0; k < 8; k++)
				if(Q[j][0] - Q[k][0] == Q[I[i]][0] &&
						Q[j][1] - Q[k][1] == Q[I[i]][1] &&
						Q[j][2] - Q[k][2] == Q[I[i]][2])
					cnt[i]++;
	return (cnt[0] == 4 && cnt[1] == 4 && cnt[2] == 4);
}


void dfs(int i)
{
	if(i == 8)
	{
		if(good())
		{
			cout << "YES\n";
			for(i = 0; i < 8; i++)
			{
				for(int j = 0; j < 3; j++)
					cout << P[i][j] << ' ';
				cout << '\n';
			}
			exit(0);
		}
		return;
	}
	ll t[3];
	t[0] = P[i][0], t[1] = P[i][1], t[2] = P[i][2];
	P[i][0] = t[0], P[i][1] = t[1], P[i][2] = t[2];
	dfs(i + 1);
	P[i][0] = t[0], P[i][1] = t[2], P[i][2] = t[1];
	dfs(i + 1);
	P[i][0] = t[1], P[i][1] = t[0], P[i][2] = t[2];
	dfs(i + 1);
	P[i][0] = t[1], P[i][1] = t[2], P[i][2] = t[0];
	dfs(i + 1);
	P[i][0] = t[2], P[i][1] = t[0], P[i][2] = t[1];
	dfs(i + 1);
	P[i][0] = t[2], P[i][1] = t[1], P[i][2] = t[0];
	dfs(i + 1);
}

int main()
{
	for(int i = 0; i < 8; i++)
		for(int j = 0; j < 3; j++)
			cin >> P[i][j];
	//if(good()) cout << "YES\n";
	dfs(0);
	cout << "NO\n";
}
