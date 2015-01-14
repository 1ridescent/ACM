#include <iostream>
#include <vector>
#include <map>
#include <cstring>

using namespace std;

typedef long long ll;

int N;
map<ll, int> id;
ll input[100005][3];

#define OFFSET 200000
vector<pair<int, int> > G[400005];

bool valid;
int color[400005];
void two_color(int u, int c)
{
	if(color[u] != 0)
	{
		if(color[u] != c) // conflict
			valid = false;
		return;
	}
	color[u] = c;
	for(int i = 0; i < G[u].size(); i++)
	{
		int v = G[u][i].first;
		two_color(v, c * G[u][i].second);
	}
}



int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> input[i][0] >> input[i][1];
		id[input[i][0]] = id[input[i][1]] = -1;
		int a, b;
		cin >> a >> b;
		input[i][2] = a * b;
	}

	int nextid = 0;
	for(map<ll, int>::iterator it = id.begin(); it != id.end(); it++)
		it->second = ++nextid;

	for(int i = 1; i <= N; i++)
	{
		input[i][0] = id[input[i][0]];
		input[i][1] = id[input[i][1]];
		input[i][1] += OFFSET;
	}

	int low = 1, high = N + 1;
	while(low + 1 < high)
	{
		int mid = (low + high) / 2;
		for(int i = 0; i < 400005; i++)
			G[i].clear();
		for(int i = 1; i <= mid; i++)
		{
			G[input[i][0]].push_back(make_pair(input[i][1], input[i][2]));
			G[input[i][1]].push_back(make_pair(input[i][0], input[i][2]));
		}
		memset(color, 0, sizeof(color));
		valid = true;
		for(int i = 0; i < 400005; i++)
		{
			if(!color[i]) two_color(i, 1);
		}
		if(valid) low = mid;
		else high = mid;
	}
	for(int i = 1; i <= low; i++) cout << "Yes\n";
	for(int i = low + 1; i <= N; i++) cout << "No\n";
}
