#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1e17;

int N;
ll W[1005], H[1005];

ll process(int h)
{
	vector<ll> save;
	int cnt = 0;
	ll width = 0;
	for(int i = 0; i < N; i++)
	{
		if(W[i] > h && H[i] > h) return inf;
		else if(W[i] <= h && H[i] > h) // lie down
		{
			width += H[i];
			cnt++;
		}
		else if(W[i] > h && H[i] <= h) // upright
			width += W[i];
		else
		{
			width += W[i];
			if(W[i] > H[i])
				save.push_back(H[i] - W[i]);
		}
	}
	if(cnt > N / 2) return inf;
	sort(save.begin(), save.end());
	for(int i = 0; i < save.size() && i < (N / 2 - cnt); i++)
		width += save[i];
	return width * h;
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> W[i] >> H[i];
	ll best = inf;
	for(int h = 1; h <= 1005; h++) best = min(best, process(h));
	cout << best;
}
