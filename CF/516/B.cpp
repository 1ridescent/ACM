#include <bits/stdc++.h>

using namespace std;

int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

int N, M;
char B[2050][2050];


bool used[2050][2050];
bool good(int i, int j)
{
	if(used[i][j]) return false;
	if(B[i][j] != '.') return false;
	int cnt = 0;
	for(int k = 0; k < 4; k++)
		cnt += (B[i + dir[k][0]][j + dir[k][1]] == '.');
	return (cnt == 1);
}

vector<pair<int, int> > V;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	memset(B, '*', sizeof(B));
	for(int i = 10; i < N + 10; i++)
		for(int j = 10; j < M + 10; j++)
			cin >> B[i][j];
	for(int i = 10; i < N + 10; i++)
		for(int j = 10; j < M + 10; j++)
			if(good(i, j))
			{
				used[i][j] = true;
				V.push_back(make_pair(i, j));
			}
	while(!V.empty())
	{
		int i = V.back().first, j = V.back().second;
		V.pop_back();
		if(B[i][j] != '.') continue;
		if(B[i + 1][j] == '.')
		{
			B[i][j] = '^', B[i + 1][j] = 'v';
		}
		if(B[i - 1][j] == '.')
		{
			B[i][j] = 'v', B[i - 1][j] = '^';
		}
		if(B[i][j - 1] == '.')
			B[i][j] = '>', B[i][j - 1] = '<';
		if(B[i][j + 1] == '.')
			B[i][j] = '<', B[i][j + 1] = '>';
		for(int k = 0; k < 4; k++)
			for(int k2 = 0; k2 < 4; k2++)
			{
				int i2 = i + dir[k][0] + dir[k2][0];
				int j2 = j + dir[k][1] + dir[k2][1];
				if(good(i2, j2))
				{
					used[i2][j2] = true;
					V.push_back(make_pair(i2, j2));
				}
			}
	}
	for(int i = 10; i < N + 10; i++)
		for(int j = 10; j < M + 10; j++)
			if(B[i][j] == '.')
			{
				cout << "Not unique";
				return 0;
			}

	for(int i = 10; i < N + 10; i++)
	{
		for(int j = 10; j < M + 10; j++)
			cout << B[i][j];
		cout << '\n'; }
}
