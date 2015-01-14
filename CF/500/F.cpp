#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int N, C, P;
vector<pair<int, int> > enter[50005];
vector<pair<int, int> > exit[50005];
vector<pair<int, int> > Q[50005];

int Left[10005][4005], Right[4005];
int ans[20005];

int main()
{
	cin >> N >> P;
	for(int i = 0; i < N; i++)
	{
		int c, h, t;
		cin >> c >> h >> t;
		enter[t].push_back(make_pair(c, h));
		exit[t + P - 1].push_back(make_pair(c, h));
	}
	int M;
	cin >> M;
	for(int i = 0; i < M; i++)
	{
		int t, b;
		cin >> t >> b;
		Q[t].push_back(make_pair(b, i));
	}
	for(int s = 0; s <= 20005; s += (P + 1))
	{
		for(int j = 0; j <= 4000; j++)
			Left[P + 1][j] = 0;
		for(int i = P; i >= 1; i--)
		{
			int t = s + i;
			for(int j = 0; j <= 4000; j++)
				Left[i][j] = Left[i + 1][j];
			for(int ii = 0; ii < exit[t].size(); ii++)
			{
				int c = exit[t][ii].first, h = exit[t][ii].second;
				for(int j = 4000 - c; j >= 0; j--)
					Left[i][j + c] = max(Left[i][j + c], Left[i][j] + h);
			}
		}
		for(int j = 0; j <= 4000; j++)
			Right[j] = 0;
		for(int i = 1; i <= P + 1; i++)
		{
			int t = s + i;
			if(i > 1)
			{
				for(int ii = 0; ii < enter[t].size(); ii++)
				{
					int c = enter[t][ii].first, h = enter[t][ii].second;
					for(int j = 4000 - c; j >= 0; j--)
						Right[j + c] = max(Right[j + c], Right[j] + h);
				}
			}
			for(int qi = 0; qi < Q[t].size(); qi++)
			{
				//cout << "qi = " << qi << " size = " << Q[t].size() << endl;
				int b = Q[t][qi].first, id = Q[t][qi].second;
				ans[id] = 0;
				for(int j = 0; j <= b; j++)
					ans[id] = max(ans[id], Left[i][j] + Right[b - j]);
			}
		}
	}
	for(int i = 0; i < M; i++)
		cout << ans[i] << '\n';
}
