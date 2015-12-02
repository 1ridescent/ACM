#include <bits/stdc++.h>

using namespace std;

#define MAX 1005

const long long inf = 1e18;
long long zero[3] = { 0,0,0 };

struct NextHit
{
	long long n;
	long long a[MAX][MAX];
	void pre()
	{
		for(long long i = 0; i < MAX; i++)
			for(long long j = 0; j < MAX; j++)
				a[i][j] = inf;
		for(long long s = 0; s < MAX; s++)
			for(long long i = 0; i < MAX; i++)
			{
				long long t = (i * s) % n;
				a[s][t] = min(a[s][t], i);
			}
		//for(long long i = 0; i < n; i++)			for(long long j = 0; j < n;j ++)				prlong longf("%d %d : %d\n",i,j,a[i][j]);
	}
};

NextHit hit[3];
long long next_same(long long x1, long long v1, long long x2, long long v2, long long n)
{
	for(long long i = 0; i < 3; i++)
		if(hit[i].n == n)
		{
			long long time = hit[i].a[(v2 - v1 + 2000 * n) % n][(x1 - x2 + 2000 * n) % n];
			//prlong longf("query v=%d x=%d t=%d\n",v2-v1,x1-x2,time);
			return time;
		}
}


long long N[3];

void travel(long long* p, long long s, long long* v, long long* dest)
{
	for(long long i = 0; i < 3; i++)
		dest[i] = (p[i] + s * (2000 * N[i] + v[i])) % N[i];
}
long long next_collide(long long* p1, long long* v1, long long* p2, long long* v2)
{
	long long time[3], period[3];
	for(long long i = 0; i < 3; i++)
	{
		time[i] = next_same(p1[i], v1[i], p2[i], v2[i], N[i]);
		long long q1[3], q2[3];
		travel(p1, time[i], v1, p1);
		travel(p2, time[i], v2, p2);
		travel(p1, 1, v1, q1);
		travel(p2, 1, v2, q2);
		if(time[i] == inf) return inf;
		period[i] = 1 + next_same(q1[i], v1[i], q2[i], v2[i], N[i]);
//		prlong longf("%d: time=%d period=%d\n",i,time[i],period[i]);

		travel(zero, period[i], v1, v1);
		travel(zero, period[i], v2, v1);
	}

	return time[0] + period[0] * (time[1] + period[1] * time[2]);
}

void test()
{
	for(long long i = 0; i < 3; i++)
	{
		cin >> N[i];
		hit[i].n = N[i];
		hit[i].pre();
	}
	long long a[3], av[3], b[3], bv[3];
	for(long long i = 0; i < 3; i++) cin >> a[i];
	for(long long i = 0; i < 3; i++) cin >> av[i];
	for(long long i = 0; i < 3; i++) cin >> b[i];
	for(long long i = 0; i < 3; i++) cin >> bv[i];
	cout << next_collide(a, av, b, bv) << endl;
}


struct Planet
{
	long long mass;
	long long pos[3], vel[3];
	void travel(long long s)
	{
		for(long long i = 0; i < 3; i++)
			pos[i] = (pos[i] + s * (2000 * N[i] + vel[i])) % N[i];
	}
};
pair<long long, pair<long long, pair<long long, long long> > > to_pair(Planet& p)
{
	return make_pair(-p.mass, make_pair(p.pos[0], make_pair(p.pos[1], p.pos[2])));
}
bool cmp(Planet a, Planet b)
{
	return to_pair(a) < to_pair(b);
}

long long collide(Planet a, Planet b)
{
	long long p1[3], v1[3], p2[3], v2[3];
	for(long long i = 0; i < 3; i++) p1[i] = a.pos[i];
	for(long long i = 0; i < 3; i++) v1[i] = a.vel[i];
	for(long long i = 0; i < 3; i++) p2[i] = b.pos[i];
	for(long long i = 0; i < 3; i++) v2[i] = b.vel[i];
	return next_collide(p1, v1, p2, v2);
}

long long num;
Planet planets[105];
bool dead[105];

int main()
{
	//test();
	cin >> num;
	for(long long i = 0; i < 3; i++)
	{
		cin >> N[i];
		hit[i].n = N[i];
		hit[i].pre();
	}
	for(long long k = 0; k < num; k++)
	{
		cin >> planets[k].mass;
		for(long long i = 0; i < 3; i++)
		{
			cin >> planets[k].pos[i];
		}
		for(long long i = 0; i < 3; i++)
		{
			cin >> planets[k].vel[i];
		}
	}
	while(true)
	{
		long long best = inf, besti, bestj;
		for(long long i = 0; i < num; i++)
			for(long long j = i + 1; j < num; j++)
			{
				if(dead[i] || dead[j]) continue;
				long long t = collide(planets[i], planets[j]);
				//prlong longf("%d and %d collide at time %d\n",i,j,t);
				if(t < best) best = t, besti = i, bestj = j;
			}
		if(best == inf) break;
		for(long long i = 0; i < num; i++)
			if(!dead[i])
				planets[i].travel(best);
		for(long long i = 0; i < 3; i++)
		{
			long long num = (planets[besti].mass * planets[besti].vel[i] + planets[bestj].mass * planets[bestj].vel[i]);
			long long denom = (planets[besti].mass + planets[bestj].mass);
			planets[besti].vel[i] = (long long)((num) / denom); ;
		}
		planets[besti].mass += planets[bestj].mass;
		dead[bestj] = true;
	}
	vector<pair<long long, pair<long long, pair<long long, pair<long long, long long>>>>> ans;
	for(long long i = 0; i < num; i++)
		if(!dead[i])
		{
			ans.push_back(make_pair(-planets[i].mass, make_pair(planets[i].pos[0], make_pair(planets[i].pos[1], make_pair(planets[i].pos[2], i)))));
		}
	sort(ans.begin(), ans.end());
	cout << ans.size() << endl;
	for(long long j = 0; j < ans.size(); j++)
	{
		cout << 'P' << j << ": ";
		cout << -ans[j].first;
		long long t = ans[j].second.second.second.second;
		for(long long i = 0; i < 3; i++) cout << ' ' << planets[t].pos[i];
		for(long long i = 0; i < 3; i++) cout << ' ' << planets[t].vel[i];
		cout << endl;
	}
}
