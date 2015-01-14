#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <vector>
#include <cstdio>

using namespace std;

int N, M;

char B[75][75];
bool vowel[75][75];

char state[75][75][75][75];
bool vis[75][75];

vector<pair<int, int> > G[75][75];

void dfs(int sr, int sc)
{
	char temp[75][75];
	vis[sr][sc] = true;
	//printf("visit %d %d\n", sr, sc);
	/*cout << "state:\n";
	for(int r = 1; r <= N; r++)
	{
		for(int c = 1; c <= M; c++) cout << B[r][c];
		cout << '\n';
	}
	cout << endl;*/
	memcpy(temp, B, sizeof(B));
	if(B[sr - 1][sc] == '^' && !vis[sr - 2][sc])
	{
		//printf("up\n");
		B[sr - 2][sc] = '.';
		B[sr - 1][sc] = 'v';
		B[sr][sc]     = '^';
		G[sr][sc].push_back(make_pair(sr - 2, sc));
		dfs(sr - 2, sc);
		memcpy(B, temp, sizeof(B));
	}
	if(B[sr + 1][sc] == 'v' && !vis[sr + 2][sc])
	{
		//printf("down\n");
		B[sr][sc]     = 'v';
		B[sr + 1][sc] = '^';
		B[sr + 2][sc] = '.';
		G[sr][sc].push_back(make_pair(sr + 2, sc));
		dfs(sr + 2, sc);
		memcpy(B, temp, sizeof(B));
	}
	if(B[sr][sc - 1] == '<' && !vis[sr][sc - 2])
	{
		//printf("left\n");
		B[sr][sc - 2] = '.';
		B[sr][sc - 1] = '>';
		B[sr][sc]     = '<';
		G[sr][sc].push_back(make_pair(sr, sc - 2));
		dfs(sr, sc - 2);
		memcpy(B, temp, sizeof(B));
	}
	if(B[sr][sc + 1] == '>' && !vis[sr][sc + 2])
	{
		//printf("right\n");
		B[sr][sc]     = '>';
		B[sr][sc + 1] = '<';
		B[sr][sc + 2] = '.';
		G[sr][sc].push_back(make_pair(sr, sc + 2));
		dfs(sr, sc + 2);
		memcpy(B, temp, sizeof(B));
	}
}

bool is_vowel(char c)
{
	return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

bool mark[75][75];
void mark_all(int sr, int sc)
{
	if(vowel[sr][sc]) mark[sr][sc] = true;
	for(int i = 0; i < G[sr][sc].size(); i++)
	{
		int tr = G[sr][sc][i].first, tc = G[sr][sc][i].second;
		mark_all(tr, tc);
		if(mark[tr][tc]) mark[sr][sc] = true;
	}
}

int steps = 0;
int max_depth = 0;
void go(int sr, int sc, int d)
{
	max_depth = max(max_depth, d);
	for(int i = 0; i < G[sr][sc].size(); i++)
	{
		int tr = G[sr][sc][i].first, tc = G[sr][sc][i].second;
		if(!mark[tr][tc]) continue;
		steps++;
		go(tr, tc, d + 1);
		steps++;
	}
}

int main()
{
	memset(B, 'x', sizeof(B));

	cin >> N >> M;

	memset(vowel, 0, sizeof(vowel));
	for(int r = 1; r <= N; r++)
		for(int c = 1; c <= M; c++)
		{
			char k;
			cin >> k;
			vowel[r][c] = is_vowel(k);
		}

	for(int r = 1; r <= N; r++)
	{
		for(int c = 1; c <= M; c++)
		{
			char k;
			cin >> k;
			if(k == '.') B[r][c] = '.';
			else if(k == '-')
			{
				if(B[r][c - 1] == '>') B[r][c] = '<';
				else B[r][c] = '>';
			}
			else if(k == '|')
			{
				if(B[r - 1][c] == 'v') B[r][c] = '^';
				else B[r][c] = 'v';
			}
		}
	}

	dfs(1, 1);

	for(int r = 1; r <= N; r++)
		for(int c = 1; c <= M; c++)
		{
			if(vowel[r][c] && !vis[r][c])
			{
				cout << "NIE\n";
				return 0;
			}
		}

	memset(mark, 0, sizeof(mark));

	mark_all(1, 1);

	go(1, 1, 0);

	cout << steps - max_depth << endl;
}
