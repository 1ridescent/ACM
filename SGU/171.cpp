#include <iostream>
#include <map>
#include <algorithm>

using namespace std;

typedef long long ll;

int N = 0, K;
ll M[105], Q[105];
struct student
{
	int p, w, id;
};
bool cmp(student a, student b)
{
	return a.w > b.w;
}
student S[16016];
int Z[16016];

map<pair<ll, int>, int> pool;

int main()
{
	cin >> K;
	for(int i = 1; i <= K; i++)
	{
		cin >> M[i];
		N += M[i];
	}
	for(int i = 1; i <= K; i++) cin >> Q[i];
	for(int i = 1; i <= K; i++)
	{
		if(Q[i] > 0) pool[make_pair(Q[i], i)] = M[i];
	}

	for(int i = 1; i <= N; i++)
	{
		S[i].id = i;
		cin >> S[i].p;
	}
	for(int i = 1; i <= N; i++) cin >> S[i].w;

	sort(S + 1, S + 1 + N, cmp);

	for(int i = 1; i <= N; i++)
	{
		map<pair<ll, int>, int>::iterator it = pool.lower_bound(make_pair(S[i].p, -1));
		if(it == pool.begin())
		{
			it = pool.end();
			it--;
		}
		else
		{
			it--;
		}
		//cout << S[i].id << " -> " << it->first.first << ' ' << it->first.second << endl;
		Z[S[i].id] = it->first.second;
		it->second--;
		if(it->second == 0) pool.erase(it);
	}

	for(int i = 1; i <= N; i++) cout << Z[i] << ' ';
}
