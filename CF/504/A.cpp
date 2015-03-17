#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int D[100005], S[100005];
vector<int> leaf;
int N;
vector<pair<int, int> > ans;

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		cin >> D[i] >> S[i];
		if(D[i] == 1) leaf.push_back(i);
	}
	while(!leaf.empty())
	{
		int u = leaf.back();
		int v = S[u];
		leaf.pop_back();
		if(D[u] != 1) continue;
		ans.push_back(make_pair(u, v));
		D[u]--;
		S[u] ^= v;
		D[v]--;
		S[v] ^= u;
		//cout << "d" << v << "=" << D[v] << endl;;
		if(D[v] == 1) leaf.push_back(v);
	}
	cout << ans.size() << '\n';
	for(int i = 0; i < ans.size(); i++)
		cout << ans[i].first << ' ' << ans[i].second << '\n';
}
