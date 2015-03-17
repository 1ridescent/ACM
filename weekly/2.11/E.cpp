#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

struct Segment
{
	ll x1, y1, x2, y2;
	bool operator<(Segment const& t0) const
	{
		Segment s;
		Segment t = t0;
		s.x1 = x1, s.y1 = y1, s.x2 = x2, s.y2 = y2;
		bool flip = false;
		if(s.x1 > t.x1)
		{
			swap(s, t);
			flip = true;
		}
		ll ux = s.x1 - t.x1, uy = s.y1 - t.y1;
		ll vx = s.x2 - t.x1, vy = s.y2 - t.y1;
		return flip ^ (ux * vy - vx * uy > 0);
	}
};

set<ll> X;
map<ll, vector<Segment> > I, D;
set<Segment> S;
void print()
{
	for(set<Segment>::iterator it = S.begin(); it != S.end(); it++)
		cout << it->x1 << ' ' << it->y1 << ' ' << it->x2 << ' ' << it->y2 << "   ";
	cout << endl;
}

int N;

int main()
{
	//Segment s, t; cin >> s.x1 >> s.y1 >> s.x2 >> s.y2 >> t.x1 >> t.y1 >> t.x2 >> t.y2; cout << (s < t);
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		Segment s;
		cin >> s.x1 >> s.y1 >> s.x2 >> s.y2;
		I[s.x1].push_back(s);
		D[s.x2].push_back(s);
		X.insert(s.x1);
		X.insert(s.x2);
	}
	int cnt = 0;
	set<Segment>::iterator cur;
	for(set<ll>::iterator it0 = X.begin(); it0 != X.end(); it0++)
	{
		ll x = *it0;
		if(x == 0)
		{
			for(int i = 0; i < I[0].size(); i++)
			{
				Segment s = I[0][i];
				S.insert(s);
				if(s.y1 == 0) // first
				{
					cnt++;
					cur = S.find(s);
				}
			}
		}
		else
		{
			for(int i = 0; i < I[x].size(); i++)
			{
				Segment s = I[x][i];
				S.insert(s);
			}
			bool found = false;
			Segment f;
			for(int i = 0; i < D[x].size(); i++)
			{
				Segment s = D[x][i];
				if(s.x1 == cur->x1 && s.y1 == cur->y1)
				{
					found = true;
					f = s;
				}
				S.erase(s);
			}
			if(found)
			{
				set<Segment>::iterator it = S.lower_bound(f);
				if(it == S.begin())
				{
					cout << cnt << endl;
					return 0;
				}
				it--;
				//cout << "new is at " << it->x1 << ' ' << it->y1 << ' ' << it->x2 << ' ' << it->y2 << endl;
				cnt++;
				cur = it;
			}
		}
		//cout << " at " << cur->x1 << ' ' << cur->y1 << endl; print();
	}
	assert(false);
}
