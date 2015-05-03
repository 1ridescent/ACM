#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>
#include <cassert>
#include <ctime>

using namespace std;

int N, K;
pair<int, int> A[100005];

vector<pair<int, int> > X; // (x, breed)

vector<int> cur[9];
map<vector<int>, set<int> > occ[9];

int main()
{
	cin >> N >> K;
	for(int i = 0; i < N; i++)
	{
		cin >> A[i].first >> A[i].second;
		A[i].second--;
	}
	sort(A, A + N);
	for(int i = 1; i <= 8; i++) cur[i] = vector<int>(i, 0);
	X.push_back(make_pair(-1, -1));
	int best = -1;
	for(int t = 0; t < N; t++)
	{
		int x = A[t].first, b = A[t].second;
		bool found = false;
		for(int i = 0; i < X.size(); i++)
			if(X[i].second == b)
			{
				X[i].first = x;
				found = true;
			}
		if(!found) X.push_back(make_pair(x, b));
		sort(X.begin(), X.end());
		for(int i = X.size() - K; i >= 1; i--) // [8 7 6 5 4 3 2 1]
		{
			vector<int> v;
			for(int j = i; j < X.size(); j++)
				v.push_back(X[j]);
			int f = X.size() - i;
			int l = X[i - 1].first + 1, r = X[i].first;
			if(!occ[f].count(cur[f])) continue;
			set<int>& S = occ[f][cur[f]];
			set<int>::iterator it = S.lower_bound(l);
			printf("f=%d l=%d r=%d *it=%d x=%d\n",f,l,r,*it,x);
			if(*it <= r) best = max(best, x - *it);
		}
		for(int f = 1; f <= 8; f++)
		{
			for(int i = 0; i < i; i++) cur[f][i]--;
			cur[f][b] += f;
			cout << "x=" << x << " f=" << f << " inserting "; for(int i = 0; i < cur[f].size(); i++) cout << cur[f][i] << ' '; cout << endl;
			occ[f][cur[f]].insert(x);
		}
	}
	cout << best << endl;
}
