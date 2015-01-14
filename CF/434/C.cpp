#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <deque>
#include <map>
#include <set>

using namespace std;
typedef long long ll;
const ll mod = 1000000007;

int N, M, K;
deque<int> L, R;
deque<int> strings[205];
int string_vals[205];
map< deque<int>, int > strings_map; // to points
//deque<int> prefixes[MAX];
//map< deque<int>, int > prefix_map;
map< deque<int>, int > prefix_id;
int nextid = 0;
int next[205][22];
int points[205];

deque<int> empty; // empty
int emptyid;

void trim(deque<int>& D)
{
	while(/*!D.empty() && */!prefix_id.count(D)) D.pop_front();
}
int score(deque<int> D)
{
	int cnt = 0;
	while(!D.empty())
	{
		cnt += strings_map.count(D);
		D.pop_front();
	}
	return cnt;
}
void process()
{
	for(int t = 0; t < N; t++)
	{
		deque<int> D = strings[t];
		while(!D.empty())
		{
			prefix_id[D] = 0;
			D.pop_back();
		}
	}
	prefix_id[empty] = 0; // include empty
	for(map< deque<int>, int >::iterator it = prefix_id.begin(); it != prefix_id.end(); it++)
		it->second = nextid++;
	emptyid = prefix_id[empty];

	for(map< deque<int>, int >::iterator it = prefix_id.begin(); it != prefix_id.end(); it++)
	{
		int id = it->second;
		for(int m = 0; m < M; m++)
		{
			deque<int> D = it->first;
			D.push_back(m);
			trim(D);
			next[id][m] = prefix_id[D];
		}
	}
	for(map< deque<int>, int >::iterator it = prefix_id.begin(); it != prefix_id.end(); it++)
	{
		int id = it->second;
		points[id] = score(it->first);
	}
}

ll dp[205][2][205][505]; // [pos][top?][prefix][num]
ll get_num(deque<int>& end)
{
	memset(dp, 0, sizeof(dp));
	for(int i = 0; i < end.size(); i++)
	{
		if(i == 0)
		{
			for(int m = 1; m < end[0]; m++)
			{
				int id = next[emptyid][m];
				if(points[id] <= K) dp[0][0][id][points[id]] = 1;
			}
			int m = end[0];
			int id = next[emptyid][m];
			if(points[id] <= K) dp[0][1][id][points[id]] = 1;
		}
		else
		{
			for(int m = 1; m < M; m++) // start here
			{
				int id = next[emptyid][m];
				if(points[id] <= K) dp[i][0][id][points[id]] = 1;
			}
			for(int t = 0; t <= 1; t++)
			{
				if(t == 0)
				{
					for(int p = 0; p < nextid; p++)
						for(int m = 0; m < M; m++)
							for(int k = 0; k <= K; k++)
							{
								int id = next[p][m];
								if(k + points[id] <= K)
								{
									ll& val = dp[i][0][id][k + points[id]];
									val += dp[i - 1][0][p][k];
									val %= mod;
								}
							}
				}
				else
				{
					for(int p = 0; p < nextid; p++)
					{
						for(int m = 0; m < end[i]; m++) // don't keep top
							for(int k = 0; k <= K; k++)
							{
								int id = next[p][m];
								if(k + points[id] <= K)
								{
									ll& val = dp[i][0][id][k + points[id]];
									val += dp[i - 1][1][p][k];
									val %= mod;
								}
							}
						int m = end[i]; // keep top
						for(int k = 0; k <= K; k++)
						{
							int id = next[p][m];
							if(k + points[id] <= K)
							{
								ll& val = dp[i][1][id][k + points[id]];
								val += dp[i - 1][1][p][k];
								val %= mod;
							}
						}
					}
				}
			}
		}
	}

	ll total = 0;
	int i = end.size() - 1;
	for(int p = 0; p < nextid; p++)
		for(int k = 0; k <= K; k++)
			total = (total + dp[i][0][p][k]) % mod;
	return total;
}

void increment(deque<int>& D)
{
	for(int i = D.size() - 1; i >= 0; i--)
	{
		if(D[i] < M - 1)
		{
			D[i]++;
			return;
		}
		else
		{
			D[i] = 0;
		}
	}
	D.push_front(1);
}

int main()
{
	cin >> N >> M >> K;
	int len_L, len_R;
	cin >> len_L;
	for(int i = 0; i < len_L; i++)
	{
		int x;
		cin >> x;
		L.push_back(x);
	}
	cin >> len_R;
	for(int i = 0; i < len_R; i++)
	{
		int x;
		cin >> x;
		R.push_back(x);
	}

	for(int t = 0; t < N; t++)
	{
		int len;
		cin >> len;
		deque<int> D;
		for(int i = 0; i < len; i++)
		{
			int x;
			cin >> x;
			D.push_back(x);
		}
		int v;
		cin >> v;
		strings[t] = D;
		string_vals[t] = v;
		strings_map[D] = v;
	}

	process();

	increment(R);
	cout << (get_num(R) - get_num(L) + mod) % mod;
}
