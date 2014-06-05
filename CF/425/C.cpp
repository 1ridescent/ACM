#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <map>
#include <stack>
#include <set>
#include <cstdio>

using namespace std;

const int INF = 1000000000;

int N, M, S, E;
int A[100100], B[100100];

int dp[311][100100]; // [i][j] = iteration, best_index
map<int, int> states[311];
vector< pair<int, int> > temp;
vector< pair<int, int> > st;

set<int> posA[100100], posB[100100];

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M >> S >> E;
	for(int i = 1; i <= N; i++)
	{
		cin >> A[i];
		posA[A[i]].insert(i);
	}
	for(int i = 1; i <= M; i++)
	{
		cin >> B[i];
		posB[B[i]].insert(i);
	}

	states[0][0] = 0;
	int best = 0;
	for(int t = 1; t * E <= S; t++)
	{
		temp.clear();
		for(int a = 1; a <= N; a++)
		{
			if(states[t - 1].empty()) continue;
			if(states[t - 1].lower_bound(a) == states[t - 1].begin()) continue;
			int minb = (--states[t - 1].lower_bound(a))->second; // exclusive
			if(posB[A[a]].empty()) continue;
			if(posB[A[a]].upper_bound(minb) == posB[A[a]].end()) continue;
			int b = *(posB[A[a]].upper_bound(minb));

			temp.push_back(make_pair(a, b));
		}

		st.clear();
		for(int i = 0; i < temp.size(); i++)
		{
			if(st.empty() || temp[i].second < st.back().second) st.push_back(temp[i]);
			//printf("t=%d: a=%d b=%d\n", t, temp[i].first, temp[i].second);
			//while(!st.empty() && temp[i].second >= st.back().second) st.pop_back();
			//st.push_back(temp[i]);
		}
		for(int i = 0; i < st.size(); i++)
		{
			//printf("t=%d: a=%d b=%d\n", t, st[i].first, st[i].second);
			if(t * E + st[i].first + st[i].second <= S) best = max(best, t); // stop now?
			states[t][st[i].first] = st[i].second;
		}
	}
	cout << best << endl;
	return 0;
}
