#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int N, M;
char B[55][55];

vector<pair<int, int> > res;

int main()
{
	memset(B, '#', sizeof(B));
	cin >> N >> M;
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
			cin >> B[i][j];
	for(int i = 1; i <= N; i++)
		for(int j = 1; j <= M; j++)
		{
			bool r = false;
			if(B[i - 1][j] == '#' && B[i][j] == '.' && B[i + 1][j] == '.' && B[i + 2][j] == '.') r = true;
			if(B[i][j - 1] == '#' && B[i][j] == '.' && B[i][j + 1] == '.' && B[i][j + 2] == '.') r = true;
			if(r) res.push_back(make_pair(i, j));
		}
	cout << res.size() << '\n';
	for(int i = 0; i < res.size(); i++)
		printf("%d %d\n", res[i].first, res[i].second);
}
