#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <deque>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <cassert>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;
const ll inf = 1e16;

int dir[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} };

int N, M;
pair<int, int> finish;
char maze[105][105];
bool vis[105][105];
vector<pair<int, int> > st;
void dfs(int r, int c)
{
	//cout << r << ' ' << c << endl;
	st.push_back(make_pair(r, c));
	vis[r][c] = true;
	if(r == finish.first && c == finish.second)
	{
		for(int i = 0; i < st.size(); i++)
		{
			cout << st[i].first << ',' << st[i].second << '\n';
		}
		exit(0);
	}
	for(int i = 0; i < 4; i++)
	{
		int dr = dir[i][0], dc = dir[i][1];
		int r2 = r + dr, c2 = c + dc;
		if(0 <= r2 && r2 < N && 0 <= c2 && c2 < M && !vis[r2][c2] && maze[r2][c2] == '_')
			dfs(r2, c2);
	}
	st.pop_back();
}

int main()
{
	cin >> N >> M;
	for(int i = 0; i < N; i++)
		for(int j = 0; j < M; j++)
			cin >> maze[i][j];
	finish = make_pair(N - 2, M - 1);
	dfs(1, 0);
	return 0;
}
