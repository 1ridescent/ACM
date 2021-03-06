#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
typedef long double ld;

int K, M, N;
int init[100005];
int data[100005][3];
pair<int, int> eql[100005];
vector<pair<int, int> > add[100005];
vector<pair<ld, int> > mul;
vector<int> ans;

int main()
{
	cin >> K >> N >> M;
	for(int i = 1; i <= K; i++) cin >> init[i];
	for(int i = 1; i <= N; i++)
	{
		int t, k, v;
		cin >> t >> k >> v;
		data[i][0] = t, data[i][1] = k, data[i][2] = v;
		if(t == 1)
			eql[k] = max(eql[k], make_pair(v, i));
		else if(t == 2)
			add[k].push_back(make_pair(v, i));
		else
			mul.push_back(make_pair(v, i));
	}
	for(int k = 1; k <= K; k++)
		if(eql[k].first > init[k])
			add[k].push_back(make_pair(eql[k].first - init[k], eql[k].second));
	for(int k = 1; k <= K; k++)
	{
		sort(add[k].begin(), add[k].end());
		ll cur = init[k];
		for(int j = add[k].size() - 1; j >= 0; j--)
		{
			int v = add[k][j].first, i = add[k][j].second;
			mul.push_back(make_pair((ld)(cur + v) / cur, i));
			//cout << mul.back().first << ' ' << mul.back().second << endl;
			cur += v;
		}
	}
	sort(mul.begin(), mul.end());
	for(int i = mul.size() - 1; i >= 0 && ans.size() < M; i--)
	{
		if(mul[i].first <= 1) break;
		ans.push_back(mul[i].second);
	}
	cout << ans.size() << '\n';
	for(int t = 1; t <= 3; t++)
		for(int i = 0; i < ans.size(); i++)
			if(data[ans[i]][0] == t)
				cout << ans[i] << ' ';
}
