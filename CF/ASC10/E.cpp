#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

typedef long long ll;

int M, N;
map<vector<int>, ll> num[33];

vector< vector<int> > hor;

void print(vector<int>& V)
{
	for(int i = 0; i < V.size(); i++) cout << V[i] << ' ';
	cout << endl;
}

int main()
{
	freopen("dominoes.in", "r", stdin); freopen("dominoes.out", "w", stdout);
	cin >> M >> N;

	{
		vector<int> v;
		hor.push_back(v);
	}
	for(int i1 = 0; i1 < M - 2; i1++)
	{
		{
			vector<int> v;
			v.push_back(i1);
			hor.push_back(v);
		}
		for(int i2 = i1 + 3; i2 < M - 2; i2++)
		{
			{
				vector<int> v;
				v.push_back(i1);
				v.push_back(i2);
				hor.push_back(v);
			}
			for(int i3 = i2 + 3; i3 < M - 2; i3++)
			{
				vector<int> v;
				v.push_back(i1);
				v.push_back(i2);
				v.push_back(i3);
				hor.push_back(v);
			}
		}
	}
	//sort(hor.begin(), hor.end());
	//for(int i = 0; i < hor.size(); i++) print(hor[i]);

	num[0][vector<int>(M, 0)] = 1;
	for(int n = 0; n < N; n++)
	{
		for(map<vector<int>, ll>::iterator it = num[n].begin(); it != num[n].end(); it++)
		{
			vector<int> mask = it->first;
			for(int h = 0; h < hor.size(); h++)
			{
				bool ok = true;
				for(int i = 0; i < hor[h].size(); i++)
				{
					if(mask[hor[h][i]] != 0) ok = false;
					if(mask[hor[h][i] + 1] != 0) ok = false;
					if(mask[hor[h][i] + 2] != 0) ok = false;
				}

				if(ok)
				{
					vector<int> next = mask;
					for(int i = 0; i < M; i++)
					{
						if(next[i] == 0) next[i] = 1;
						else if(next[i] == 1) next[i] = 2;
						else if(next[i] == 2) next[i] = 0;
					}
					for(int i = 0; i < hor[h].size(); i++)
					{
						next[hor[h][i]] = 0;
						next[hor[h][i] + 1] = 0;
						next[hor[h][i] + 2] = 0;
					}
					num[n + 1][next] += it->second;
				}
			}
		}
	}
	cout << num[N][vector<int>(M, 0)] << endl;
}
