#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll inf = 1e12;

ll N, M;
ll H[500005];
ll min_H[500005];
vector<ll> G[500005];

void make_tree(ll u, ll p)
{
	for(ll i = 0; i < G[u].size(); i++)
		if(G[u][i] == p)
		{
			G[u].erase(G[u].begin() + i);
			break;
		}
	for(ll i = 0; i < G[u].size(); i++)
	{
		//prllf("%d->%d\n", u, G[u][i]);
		make_tree(G[u][i], u);
	}
}

bool is_root[500005];
ll root[500005];

void find_roots(ll u, ll s, ll r)
{
	if(H[u] < s)
	{
		//prllf("root at %d\n", u);
		is_root[u] = true;
		r = u;
	}
	s = min(s, H[u]);
	min_H[u] = s;
	root[u] = r;
	//cout << u << ' ' << s << ' ' << H[u] << endl;
	for(ll i = 0; i < G[u].size(); i++)
		find_roots(G[u][i], s, r);
}

vector<pair<ll, ll> > accum;
priority_queue<pair<ll, ll> > Q;
void find_group(ll r)
{
	Q.push(make_pair(-inf, r));
	while(!Q.empty())
	{
		ll u = Q.top().second, h = -Q.top().first;
		Q.pop();
		//cout << "u=" << u << " h=" << h << endl;
		accum.push_back(make_pair(h, u));
		for(ll i = 0; i < G[u].size(); i++)
		{
			ll v = G[u][i];
			if(H[v] >= H[r])
				Q.push(make_pair(-min(H[v], h), v));
		}
	}
}

ll K;
ll miners[500005];
pair<ll, ll> heights[500005];

ll used[500005]; // height of miner in cave
set<pair<ll, ll> > pick;
vector<ll> bad;

vector<vector<pair<ll, ll> > > groups;

ll min_missed = inf;

bool test(ll D)
{
	for(ll g = 0; g < groups.size(); g++)
	{
		vector<pair<ll, ll> >& V = groups[g];
		ll r = V.back().second;
		if(H[r] > min_missed) continue;

		ll num_missed = bad.size();
		ll num_used = 0;
		for(ll i = 0; i < V.size(); i++)
		{
			ll v = V[i].second;
			if(used[v]) num_used++;
			else num_missed--;
		}
		if(num_used < num_missed) continue;

		assert(V.size() - (num_used - num_missed) == bad.size());
		bool good = true;
		//prllf("dist %d: try %d: ", D, r); for(ll i = num_used - num_missed; i < V.size(); i++) cout << min(V[i].first, H[r] + D) << ' '; cout << endl;
		for(ll i = num_used - num_missed; i < V.size(); i++)
		{
			ll h = min(V[i].first, H[r] + D);
			if(h < bad[i - (num_used - num_missed)]) good = false;
		}
		if(good)
		{
			//prllf("%d: good at %d\n", D, r);
			return true;
		}
	}
	return false;
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;
	for(ll i = 1; i <= N; i++)
		cin >> H[i];
	for(ll i = 1; i < N; i++)
	{
		ll u, v;
		cin >> u >> v;
		G[u].push_back(v);
		G[v].push_back(u);
	}
	cin >> K;
	for(ll i = 1; i <= K; i++)
		cin >> miners[i];

	make_tree(1, -1);
	find_roots(1, inf, -1);

	for(ll i = 1; i <= N; i++)
		heights[i] = make_pair(H[i], i);
	sort(heights + 1, heights + 1 + N);
	for(ll i = 1; i <= N; i++)
		if(is_root[heights[i].second])
		{
			find_group(heights[i].second);
			sort(accum.begin(), accum.end());
			groups.push_back(accum);
			accum.clear();
		}

	sort(miners + 1, miners + 1 + N);
	for(ll i = 1; i <= N; i++)
		pick.insert(make_pair(miners[i], i));

	for(ll g = 0; g < groups.size(); g++)
	{
		vector<pair<ll, ll> >& V = groups[g];
		ll r = V.back().second;
		ll h = H[r];
		//prllf("group at root %d of size %d\n", r, (ll)V.size());
		for(ll i = 0; i < V.size(); i++)
		{
			assert(!pick.empty());
			set<pair<ll, ll> >::iterator it = pick.upper_bound(make_pair(h + 1, -1));
			if(it == pick.begin())
			{
				min_missed = min(min_missed, h);
			}
			else
			{
				used[V[i].second] = true;
				it--;
				//prllf("v=%d h=%d m=%d\n", V[i].second, h, it->first);
				pick.erase(it);
			}
		}
	}
	for(set<pair<ll, ll> >::iterator it = pick.begin(); it != pick.end(); it++)
		bad.push_back(it->first);

	//cout << "bad: "; for(ll i = 0; i < bad.size(); i++) cout << bad[i] << ' '; cout << endl;

	ll low = -1, high = 2e9;
	while(low + 1 < high)
	{
		ll mid = (low + high) / 2;
		if(test(mid)) high = mid;
		else low = mid;
	}
	cout << (high == 2e9 ? -1 : high) << endl;
}
