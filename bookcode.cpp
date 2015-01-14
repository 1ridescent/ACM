/***** MIN-COST FLOW *****/

#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;
const int MAX = 1215;
const int INF = 1231231231;

vector<int> G[MAX];
int cap[MAX][MAX];
int cost[MAX][MAX];
int pi[MAX];
int dist[MAX];
int from[MAX];

int mcf(int src, int snk, int flow)
{
	for(int i = 0; i < MAX; i++)
		for(int j = 0; j < MAX; j++)
			if(cap[i][j])
				cost[j][i] = -cost[i][j];

	memset(pi, 0, sizeof(pi));

	int cst = 0;
	for(int f = 0; f < flow; )
	{
		for(int i = 0; i < MAX; i++) dist[i] = INF;
		memset(from, -1, sizeof(from));
		dist[src] = 0, from[src] = -2;
		priority_queue<pair<int, int> > q;
		q.push(make_pair(0, src));
		while(!q.empty())
		{
			pair<int, int> pr = q.top(); q.pop();
			int best = pr.second;
			if(abs(pr.first + dist[best]) > 0) continue;
			for(int vi = 0; vi < G[best].size(); vi++)
			{
				int i = G[best][vi];
				if(cap[best][i] && dist[best] + cost[best][i] + pi[best] - pi[i] < dist[i])
				{
					dist[i] = dist[best] + cost[best][i] + pi[best] - pi[i];
					from[i] = best;
					q.push(make_pair(-dist[i], i));
				}
			}
		}
		if(from[snk] == -1) return -1;
		for(int i = 0; i < MAX; i++) if(from[i] == -1) pi[i] += dist[i];

		int aug_f = flow - f;
		for(int v = snk; v != src; v = from[v])
			aug_f = min(aug_f, cap[from[v]][v]);

		for(int v = snk; v != src; v = from[v])
		{
			int u = from[v];
			cap[u][v] -= aug_f;
			cap[v][u] += aug_f;
			cst += aug_f * cost[u][v];
		}
		f += aug_f;
	}
	return cst;
}

void add_edge(int u, int v, int cp, int cst)
{
	G[u].push_back(v);
	G[v].push_back(u);
    cap[u][v] = cp;
    cap[v][u] = 0;
    cost[u][v] = cst;
}



/***** FFT WITH PRIMES *****/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll P = 2013265921; // 15*2^27+1
const ll ORDER = (1 << 27);
const ll ROOT = 440564289; // ORDER'th root of unity
const int MAX = (1 << 16);

ll omega[MAX];

ll power(ll b, ll e)
{
	ll res = 1;
	while(e > 0)
	{
		if(e % 2 == 1) res = (res * b) % P;
		b = (b * b) % P;
		e /= 2;
	}
	return res;
}

void fft(vector<ll> &A, int n, bool inverse = false)
{
	int N = (1 << n);
	ll root = power(ROOT, ORDER / N * (inverse ? (N - 1) : 1));
	omega[0] = 1;
	for(int i = 1; i < N; i++) omega[i] = (omega[i - 1] * root) % P;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < (1 << i); j++)
		{
			for(int k = 0; k < (1 << (n - i - 1)); k++)
			{
				int s = (j << (n - i)) + k;
				int t = s + (1 << (n - i - 1));
				ll w = omega[k << i];
				ll temp = A[s] + A[t];
				if(temp >= P) temp -= P;
				ll temp2 = A[s] - A[t] + P;
				A[t] = (w * temp2) % P;
				A[s] = temp;
			}
		}
	}
	for(int i = 0; i < N; i++)
	{
		int x = i, y = 0;
		for(int j = 0; j < n; j++)
		{
			y = y * 2 + x % 2;
			x /= 2;
		}
		if(i < y) swap(A[i], A[y]);
	}
	if(inverse)
	{
		ll inv = power(N, P - 2);
		for(int i = 0; i < N; i++) A[i] = (A[i] * inv) % P;
	}
}

vector<ll> conv(vector<ll> A, vector<ll> B)
{
	int N = A.size() + B.size();
	int n = 1;
	while((1 << n) < N) n++;
	while(A.size() < (1 << n)) A.push_back(0);
	while(B.size() < (1 << n)) B.push_back(0);
	fft(A, n);
	fft(B, n);
	for(int i = 0; i < (1 << n); i++) A[i] = (A[i] * B[i]) % P;
	fft(A, n, true);
	return A;
}

int main()
{
	vector<ll> A(8), B(8);
	for(int i = 0; i < 8; i++) cin >> A[i];
	for(int i = 0; i < 8; i++) cin >> B[i];
	A = conv(A, B);
	for(int i = 0; i < A.size(); i++) cout << A[i] << ' ';
	cout << endl;
}



/***** TREAP *****/

#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

const ll P = 2013265921; // 15*2^27+1
const ll ORDER = (1 << 27);
const ll ROOT = 440564289; // ORDER'th root of unity
const int MAX = (1 << 16);

ll omega[MAX];

ll power(ll b, ll e)
{
	ll res = 1;
	while(e > 0)
	{
		if(e % 2 == 1) res = (res * b) % P;
		b = (b * b) % P;
		e /= 2;
	}
	return res;
}

void fft(vector<ll> &A, int n, bool inverse = false)
{
	int N = (1 << n);
	ll root = power(ROOT, ORDER / N * (inverse ? (N - 1) : 1));
	omega[0] = 1;
	for(int i = 1; i < N; i++) omega[i] = (omega[i - 1] * root) % P;
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < (1 << i); j++)
		{
			for(int k = 0; k < (1 << (n - i - 1)); k++)
			{
				int s = (j << (n - i)) + k;
				int t = s + (1 << (n - i - 1));
				ll w = omega[k << i];
				ll temp = A[s] + A[t];
				if(temp >= P) temp -= P;
				ll temp2 = A[s] - A[t] + P;
				A[t] = (w * temp2) % P;
				A[s] = temp;
			}
		}
	}
	for(int i = 0; i < N; i++)
	{
		int x = i, y = 0;
		for(int j = 0; j < n; j++)
		{
			y = y * 2 + x % 2;
			x /= 2;
		}
		if(i < y) swap(A[i], A[y]);
	}
	if(inverse)
	{
		ll inv = power(N, P - 2);
		for(int i = 0; i < N; i++) A[i] = (A[i] * inv) % P;
	}
}

vector<ll> conv(vector<ll> A, vector<ll> B)
{
	int N = A.size() + B.size();
	int n = 1;
	while((1 << n) < N) n++;
	while(A.size() < (1 << n)) A.push_back(0);
	while(B.size() < (1 << n)) B.push_back(0);
	fft(A, n);
	fft(B, n);
	for(int i = 0; i < (1 << n); i++) A[i] = (A[i] * B[i]) % P;
	fft(A, n, true);
	return A;
}



/***** MAX-FLOW *****/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>

using namespace std;

const int MAX = 205;

int cap[MAX][MAX];

int from[MAX];
queue<int> Q;
int augment_path(int s, int t)
{
	memset(from, -1, sizeof(from));

	from[s] = s;
	Q.push(s);
	while(!Q.empty())
	{
		int u = Q.front();
		Q.pop();
		for(int v = 0; v < MAX; v++)
		{
			if(from[v] != -1) continue;
			if(cap[u][v] == 0) continue;
			from[v] = u;
			Q.push(v);
		}
	}
	if(from[t] == -1) return 0;

	int flow = cap[from[t]][t];
	for(int v = t; v != s; v = from[v])
	{
		int u = from[v];
		flow = min(flow, cap[u][v]);
	}

	for(int v = t; v != s; v = from[v])
	{
		int u = from[v];
		cap[u][v] -= flow;
		cap[v][u] += flow;
	}

	return flow;
}
int max_flow(int s, int t)
{
	int flow = 0;
	while(true)
	{
		int add = augment_path(s, t);
		if(add == 0) break;
		flow += add;
	}
	return flow;
}
void init()
{
	memset(cap, 0, sizeof(cap));
}
void add_edge(int u, int v, int c)
{
	cap[u][v] += c;
}



/***** SUFFIX ARRAY *****/

#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAX = (1 << 19);

int n1;
string S;
int sa1[MAX];
int rank1[MAX];
int height1[MAX];

int next[MAX];
int temp[MAX];
bool comp1(int a, int b)
{
  return S[a] < S[b];
}

void buildSA1()
{
  for(int i = 0; i < n1; i++)
    sa1[i] = i;
  sort(sa1, sa1 + n1, comp1);

  rank1[sa1[0]] = 0;
  for(int i = 0; i < n1-1; i++)
  {
    if(S[sa1[i]] == S[sa1[i+1]])
      rank1[sa1[i+1]] = rank1[sa1[i]];
    else
      rank1[sa1[i+1]] = i+1;
  }
  for(int len = 1; len < n1; len *= 2)
  {
    for(int i = 0; i < n1; i++)
      next[i] = i;
    for(int i = n1-len; i < n1; i++) // end have highest priority
      temp[next[rank1[i]]++] = i;
    for(int i = 0; i < n1; i++) // then, prioritize segments based on next seg
      if(sa1[i] >= len)
        temp[next[rank1[sa1[i]-len]]++] = sa1[i]-len;
    memcpy(sa1, temp, sizeof(temp)); // copy new orderings of segments into sa1
    temp[sa1[0]] = 0;
    for(int i = 0; i < n1-1; i++)
    {
      if(sa1[i] + len < n1 && sa1[i+1] + len < n1 && rank1[sa1[i]] == rank1[sa1[i+1]] && rank1[sa1[i]+len] == rank1[sa1[i+1]+len])
        temp[sa1[i+1]] = temp[sa1[i]]; // can't separate yet, so leave the same
      else
        temp[sa1[i+1]] = i+1;
    }
    memcpy(rank1, temp, sizeof(temp)); // copy new ranks into rank1
  }
}

int lcp1(int p1, int p2, int l)
{
  while(p1+l < n1 && p2+l < n1 && S[p1+l] == S[p2+l])
    l++;
  return l;
}

void calcHeight1()
{
  int pre = 0;
  for(int i = 0; i < n1; i++)
  {
    if(rank1[i] == 0)
      height1[0] = 0;
    else
    {
      pre = lcp1(sa1[rank1[i]-1], sa1[rank1[i]], max(pre-1, 0));
      height1[rank1[i]] = pre;
    }
  }
}


int seg[MAX * 2]; // segtree for height array

void seg_init()
{
  for(int i = 0; i < 2*MAX; i++)
    seg[i] = MAX;
  for(int i = 0; i < n1; i++)
    seg[MAX+i] = height1[i];
  for(int i = MAX-1; i >= 0; i--)
    seg[i] = min(seg[i*2], seg[i*2+1]);
}
int seg_lookup2(int l, int r, int p, int a, int b) // min in [l, r)
{
    //cout << l << ' ' << r << ' ' << p << ' ' << a << ' ' << b << endl;
    if(a >= r || b <= l)
        return MAX;
    if(l <= a && b <= r)
        return seg[p];
    int m = (a + b) / 2;
    return min(seg_lookup2(l, r, p * 2, a, m), seg_lookup2(l, r, p * 2 + 1, m, b));
}
int seg_lookup(int l, int r)
{
    return seg_lookup2(l, r, 1, 0, MAX);
}
int lcp(int i, int j)
{
  return seg_lookup(min(rank1[i], rank1[j])+1, max(rank1[i], rank1[j])+1);
}

void get_suffix_array()
{
  n1 = S.size();
  buildSA1();
  calcHeight1();
  //cout << "height array for string " << S << " is: ";  for(int i = 0; i < n1; i++) cout << height1[rank1[i]] << ' ';  cout << endl;
  seg_init();
}



/***** MANACHER'S ALGORITHM *****/

int pals[2*MAX-1]; // length of pal centered at s[i] is at [2*i]
void find_pals(const string& S)
{
	pals[0] = 1, pals[1] = 0;
	for(int d, i = 1; i+2 < 2 * S.size(); i += d)
	{
		int& p = pals[i];
		int left = (i-p-1)/2, right = (i+p+1)/2;
		while(0 <= left && right < S.size() && S[left] == S[right])
		{
			left--;
			right++;
			p += 2;
		}
		for(d = 1; pals[i-d] < p-d; d++)
			pals[i+d] = pals[i-d];
		pals[i+d] = p-d;
	}
	pals[2*(S.size()-1)] = 1;
}



/***** RANK SEGTREE *****/

#include <cstdio>
#include <cstring>

using namespace std;

const int MAX = (1 << 21);
const int OFFSET = (1 << 20);

struct RankSegTree
{
	int seg[2 * MAX];
	RankSegTree()
	{
		memset(seg, 0, sizeof(seg));
	}
	void insert(int v, int i)
	{
		for(i += MAX; i > 0; i /= 2) seg[i] += v;
	}
	int rank(int k)
	{
		int p;
		for(p = 1; p < MAX; )
		{
			//cout << 2*p << ' ' << seg[2*p] << endl;
			if(seg[2 * p] < k)
			{
				k -= seg[2 * p];
				p = 2 * p + 1;
			}
			else
			{
				p = 2 * p;
			}
		}
		return p - MAX;
	}
};




SEG TREE SINGLE INSERT, SEGMENT LOOKUP

const int MAX = 65536;

int seg[MAX * 2];

void insert(int v, int i) // insert at index i
{
    seg[MAX + i] = min(seg[MAX + i], v);
    int p = (MAX + i) / 2;
    while(p > 0)
    {
        seg[p] = min(seg[p * 2], seg[p * 2 + 1]);
        p /= 2;
    }
}

int lookup2(int l, int r, int p, int a, int b) // min in [l, r)
{
    //cout << l << ' ' << r << ' ' << p << ' ' << a << ' ' << b << endl;
    if(a >= r || b <= l)
        return INF + 13;
    if(l <= a && b <= r)
        return seg[p];
    int m = (a + b) / 2;
    return min(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
}

int lookup(int l, int r)
{
    return lookup2(l, r, 1, 0, MAX);
}




SEG TREE SEGMENT INSERT, SINGLE LOOKUP


const int VOID = -1;
const int MAX = 16;

int seg[2 * MAX];

void init()
{
    for(int i = 0; i < 2 * MAX; i++)
        seg[i] = VOID;
}

void insert2(int v, int l, int r, int p, int a, int b)
{
    if(a >= r || b <= l)
        return;
    if(l <= a && b <= r)
        seg[p] = v;
    else
    {
        if(seg[p] != VOID)
        {
            seg[p * 2] = seg[p]; // propagate
            seg[p * 2 + 1] = seg[p];
        }
        seg[p] = VOID;
        int m = (a + b) / 2;
        insert2(v, l, r, p * 2, a, m);
        insert2(v, l, r, p * 2 + 1, m, b);
    }
}

void insert(int v, int l, int r)
{
    insert2(v, l, r, 1, 0, MAX);
}

int lookup(int i)
{
    int res = VOID;
    for(int p = MAX + i; p > 0; p /= 2)
    {
        if(seg[p] != VOID)
            res = seg[p]; // look for last modified
    }
    return res;
}



SEG TREE SEGMENT INSERT, SEGMENT LOOKUP

struct node {
    ll val, sum, time, weight;
};
struct SegTree {
    int timestamp = 0;
    node seg[2 * MAX];
    void init() {
        for(int i = 0; i < MAX; i++) {
            seg[MAX + i].weight = ((i < segs.size()) ? (segs[i].second - segs[i].first + 1) : 0);
        }
        for(int i = MAX - 1; i > 0; i--) {
            seg[i].weight = seg[i * 2].weight + seg[i * 2 + 1].weight;
        }
        for(int i = 0; i < 2 * MAX; i++) {
            seg[i].val = 1;
            seg[i].sum = seg[i].weight * 1;
            seg[i].time = timestamp;
        }
        timestamp++;
    }
    void propagate_up(int p) {
        if(p < MAX) {
            seg[p].sum = seg[p * 2].sum + seg[p * 2 + 1].sum;
        }
    }
    void propagate_down(int p) {
        if(p < MAX) {
            for(int q = p * 2; q <= p * 2 + 1; q++) {
                if(seg[q].time < seg[p].time) {
                    seg[q].val = seg[p].val;
                    seg[q].sum = seg[q].weight * seg[q].val;
                    seg[q].time = seg[p].time;
                }
            }
        }
    }
    void insert2(int v, int l, int r, int p, int a, int b) {
        if(a >= r || b <= l) return;
        if(l <= a && b <= r) {
            seg[p].val = v;
            seg[p].sum = seg[p].weight * v;
            seg[p].time = timestamp;
            return;
        }
        propagate_down(p);
        int m = (a + b) / 2;
        insert2(v, l, r, p * 2, a, m);
        insert2(v, l, r, p * 2 + 1, m, b);
        propagate_up(p);
    }
    void insert(int v, int l, int r) {
        insert2(v, l, r + 1, 1, 0, MAX);
        timestamp++;
    }
    ll lookup2(int l, int r, int p, int a, int b) {
        if(a >= r || b <= l) return 0;
        if(l <= a && b <= r) return seg[p].sum;
        propagate_down(p);
        int m = (a + b) / 2;
        return lookup2(l, r, p * 2, a, m) + lookup2(l, r, p * 2 + 1, m, b);
    }
    ll lookup(int l, int r) {
        return lookup2(l, r + 1, 1, 0, MAX);
    }
};



2D GEO, CONVEX HULL

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

const double EPS = 1e-8;

class Point
{
public:
    double x, y;
    Point() { }
    Point(double x, double y)
    {
        this->x = x, this->y = y;
    }
    Point operator+(Point q)
    {
        return Point(x + q.x, y + q.y);
    }
    Point operator-(Point q)
    {
        return Point(x - q.x, y - q.y);
    }
    Point operator*(double s)
    {
        return Point(s * x, s * y);
    }
};
class Segment
{
public:
    Point s, t;
    Segment() { }
    Segment(Point s, Point t)
    {
        this->s = s, this->t = t;
    }
};

double dot(Point p, Point q)
{
    return p.x * q.x + p.y * q.y;
}
double cross(Point p, Point q)
{
    return p.x * q.y - p.y * q.x;
}
bool intersects(Segment S, Segment T)
{
    Point A = S.s, B = T.s, C = S.t, D = T.t;
    Point u = A - B, v = A - C, w = A - D;
    if(cross(v, u) * cross(v, w) > EPS) return false;
    u = B - A, v = B - D, w = B - C;
    if(cross(v, u) * cross(v, w) > EPS) return false;
    return true;
}

double length(Point v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

bool cmp(Point p, Point q)
{
    return p.x < q.x;
}

int N;
Point P[50050];

double upper_hull()
{
    sort(P, P + N, cmp);
    vector<int> S;
    for(int i = 0; i < N; i++)
    {
        while(S.size() >= 2)
        {
            Point A = P[S[S.size() - 2]], B = P[S[S.size() - 1]], C = P[i];
            if(cross(A - B, C - B) > -EPS) S.pop_back();
            else break;
        }
        S.push_back(i);
    }
    double total = 0;
    for(int i = 1; i < S.size(); i++) total += length(P[S[i]] - P[S[i - 1]]);
    return total;
}

Point rotate(Point p, double theta)
{
    return Point(cos(theta) * p.x + sin(theta) * p.y, -sin(theta) * p.x + cos(theta) * p.y);
}

int main()
{
    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> P[i].x >> P[i].y;
        P[i] = rotate(P[i], 123.456789);
    }
    double total = upper_hull();
    for(int i = 0; i < N; i++) P[i] = P[i] * -1;
    total += upper_hull();
    printf("%.9f\n", total);
    return 0;
}



MORE 2D GEO


double length(Point v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}
double angle(Point u, Point v)
{
    return acos(dot(u, v) / (length(u) * length(v)));
}
double dist(Point p, Segment S)
{
    Point a = S.s, b = S.t;
    if(angle(p - b, a - b) > PI/2) return length(p - b);
    if(angle(p - a, b - a) > PI/2) return length(p - a);
    return abs(cross(a - p, b - p) / length(a - b));
}

bool intersects(Segment S, Segment T)
{
    Point A = S.s, B = T.s, C = S.t, D = T.t;
    Point u = A - B, v = A - C, w = A - D;
    //cout << "cross = " << cross(v, u) * cross(v, w) << endl;
    if(cross(v, u) * cross(v, w) > -EPS) return false;
    u = B - A, v = B - D, w = B - C;
    if(cross(v, u) * cross(v, w) > -EPS) return false;
    return true;
}
bool on_seg(Point p, Segment S)
{
    Point A = S.s, B = S.t;
    Point u = A - p, v = B - p;
    return abs(dot(u, v) + length(u) * length(v)) < EPS;
}
