/***** MIN-COST FLOW *****/

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

typedef long long ll;

struct Treap
{
	int size, key, val;
	ll pri;
	Treap *left, *right;

	Treap(int s, int k, int v, ll p, Treap* l, Treap* r)
	{
		size = s;
		key = k;
		val = v;
		pri = p;
		left = l;
		right = r;
	}
};
Treap* nil = new Treap(0, 0, 0, -1, NULL, NULL);

void get_size(Treap* &node)
{
	if(node == nil) return;
	node->size = node->left->size + node->right->size + 1;
}
void rotate_left(Treap* &node)
{
	Treap* aux = node->left;
	node->left = node->left->right;
	aux->right = node;
	node = aux;

	get_size(node->left);
	get_size(node->right);
	get_size(node);
}
void rotate_right(Treap* &node)
{
	Treap* aux = node->right;
	node->right = node->right->left;
	aux->left = node;
	node = aux;

	get_size(node->left);
	get_size(node->right);
	get_size(node);
}
void balance(Treap* &node)
{
	if(node->left->pri > node->pri) rotate_left(node);
	if(node->right->pri > node->pri) rotate_right(node);
	get_size(node);
}
void insert(Treap* &node, int key, int val)
{
	if(node == nil)
	{
		node = new Treap(1, key, val, ((ll)(rand()) << 15) + rand(), nil, nil);
		return;
	}

	if(node->key > key) insert(node->left, key, val);
	else insert(node->right, key, val);

	balance(node);
}
void erase(Treap* &node, int key)
{
	if(node->key > key)
	{
		erase(node->left, key);
		balance(node);
	}
	else if(node->key < key)
	{
		erase(node->right, key);
		balance(node);
	}
	else
	{
		if(node->left == nil && node->right == nil)
		{
			delete node;
			node = nil;
			return;
		}
		if(node->left->pri > node->right->pri)
		{
			rotate_left(node);
			erase(node->right, key);
			balance(node);
		}
		else
		{
			rotate_right(node);
			erase(node->left, key);
			balance(node);
		}
	}
}
Treap* find_rank(Treap* node, int rank)
{
	if(node->left->size == rank) return node;

	if(node->left->size > rank) return find_rank(node->left, rank);
	else return find_rank(node->right, rank - node->left->size - 1);
}
void dfs_order_print(Treap* node)
{
	if(node == nil) return;
	cout << "(";
	dfs_order_print(node->left);
	cout << ")";
	cout << node->key << "->" << node->val;
	cout << "(";
	dfs_order_print(node->right);
	cout << ")";
}


Treap* root = nil;

int main()
{
	srand(time(0));
	while(true)
	{
		char t;
		cin >> t;
		if(t == 'i')
		{
			int k, v;
			cin >> k >> v;
			insert(root, k, v);
		}
		else if(t == 'd')
		{
			int k;
			cin >> k;
			erase(root, k);
		}
		else
		{
			int r;
			cin >> r;
			Treap* node = find_rank(root, r);
			cout << node->key << "->" << node->val << endl;
		}
		dfs_order_print(root);
	}
}



/***** MAX-FLOW *****/

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
	//cout << "height array for string " << S << " is: ";	for(int i = 0; i < n1; i++) cout << height1[rank1[i]] << ' ';	cout << endl;
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


// SEG TREES

const int MAX = (1 << 17);
struct SumSegTree
{
	ll seg[2 * MAX];
	void init()
	{
		memset(seg, 0, sizeof(seg));
	}
	void insert(ll v, int i)
	{
		for(i += MAX; i > 0; i /= 2)
		{
			seg[i] += v;
		}
	}
	ll lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return lookup2(l, r, p * 2, a, m) + lookup2(l, r, p * 2 + 1, m, b);
	}
	ll lookup(int l, int r)
	{
		return lookup2(l, r, 1, 0, MAX);
	}
}

struct MaxSegTree
{
	int seg[2 * MAX];
	void init(int v)
	{
		for(int i = 0; i < 2 * MAX; i++) seg[i] = v;
	}
	void insert2(int v, int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return;
		if(l <= a && b <= r) seg[p] = max(seg[p], v);
		else
		{
			int m = (a + b) / 2;
			insert2(v, l, r, p * 2, a, m);
			insert2(v, l, r, p * 2 + 1, m, b);
		}
	}
	void insert(int v, int l, int r)
	{
		insert2(v, l, r + 1, 1, 0, MAX);
	}
	int lookup(int i)
	{
		int res = -INF;
		for(i += MAX; i > 0; i /= 2) res = max(res, seg[i]);
		return res;
	}
};

struct MaxSegTree2
{
	int seg[2 * MAX];
	void init(int v)
	{
		for(int i = 0; i < 2 * MAX; i++) seg[i] = v;
	}
	void insert(int v, int i)
	{
		for(i += MAX; i > 0; i /= 2) seg[i] = max(seg[i], v);
	}
	int lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return -INF;
		if(l <= a && b <= r) return seg[p];
		int m = (a + b) / 2;
		return max(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r + 1, 1, 0, MAX);
	}
};



// 2D GEO

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
bool intersects(segment S, segment T)
{
	point A = S.s, B = T.s, C = S.t, D = T.t;
	point u = A - B, v = A - C, w = A - D;
	if(cross(v, u) == 0 || cross(v, w) == 0) return false;
	if(cross(v, u) >= 0 == cross(v, w) >= 0) return false;
	u = B - A, v = B - D, w = B - C;
	if(cross(v, u) == 0 || cross(v, w) == 0) return false;
	if(cross(v, u) >= 0 == cross(v, w) >= 0) return false;
	return true;
}


// STRONGLY CONNECTED COMPONENTS

const int MAX = 100100;

struct SCC
{
	int N, cnt, cmpt;
	int num[MAX], low[MAX], ans[MAX];
	vector<int> G[MAX];
	vector<int> S; // stack
	bool on_stack[MAX];
	
	void reset()
	{
		for(int i = 0; i < MAX; i++) G[i].clear();
	}
	void strong(int u)
	{
		if(num[u] != 0) return;
		num[u] = low[u] = ++cnt;
		S.push_back(u);
		on_stack[u] = true;
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			strong(v);
		}
		for(int i = 0; i < G[u].size(); i++)
		{
			int v = G[u][i];
			if(on_stack[v]) low[u] = min(low[u], low[v]);
		}
		if(num[u] == low[u])
		{
			while(!S.empty())
			{
				int x = S.back();
				S.pop_back();
				on_stack[x] = false;
				ans[x] = cmpt;
				if(x == u) break;
			}
			cmpt++;
		}
	}
	void scc()
	{
		memset(num, 0, sizeof(num));
		memset(low, 0, sizeof(low));
		memset(ans, 0, sizeof(ans));
		memset(on_stack, 0, sizeof(on_stack));
		S.clear();
		cnt = 0;
		cmpt = 0;
		for(int i = 1; i <= N; i++) strong(i);
	}
};




// KMP

const int MAX = 100005;

int T[MAX];
void build_table(string& W)
{
	int pos = 2, cnd = 0;
	T[0] = -1, T[1] = 0;
	while(pos < W.size())
	{
		if(W[pos - 1] == W[cnd])
			cnd++, T[pos] = cnd, pos++;
		else if(cnd > 0)
			cnd = T[cnd];
		else
			T[pos] = 0, pos++;
	}
}

bool full[MAX];
void kmp_search(string& S, string& W)
{
	memset(full, 0, sizeof(full));
	int m = 0, i = 0;
	while(m + i < S.size())
	{
		if(i == W.size() - 1) full[m] = true;
		if(W[i] == S[m + i])
			i++;
		else
		{
			if(T[i] > -1)
				m += i - T[i], i = T[i];
			else
				i = 0, m++;
		}
	}
}

string S, W;

int main()
{
	cin >> S >> W;
	S += "###";
	W += '$';
	build_table(W);
	kmp_search(S, W);
}



// find negative cycle

int neg_cycle()
{
	//for(int i = 0; i < N; i++) { for(int j = 0; j < N; j++) printf("%d/%d ", cost[i][j], cap[i][j]); printf("\n"); }
	int dist[122];
	int from[122];
	memset(from, -1, sizeof(from));
	for(int i = 0; i < N; i++) dist[i] = inf;
	dist[0] = 0;
	int neg_cycle_at = -1;
	for(int t = 0; t <= N; t++)
		for(int u = 0; u < N; u++)
			for(int v = 0; v < N; v++)
				if(cap[u][v] && dist[u] + cost[u][v] < dist[v])
				{
					if(t == N)
						neg_cycle_at = v;
					dist[v] = dist[u] + cost[u][v];
					from[v] = u;
				}
	if(neg_cycle_at == -1) return 0;

	bool vis[122];
	memset(vis, 0, sizeof(vis));
	int neg_cycle_start = -1;
	for(int v = neg_cycle_at; ; v = from[v])
	{
		vis[v] = true;
		int u = from[v];
		//printf("%d -> %d\n", u, v);
		if(vis[u])
		{
			neg_cycle_start = u;
			break;
		}
	}

	int v = neg_cycle_start;
	int len = 0;
	do
	{
		int u = from[v];
		//printf("cycle: %d -> %d\n", u, v);
		cap[u][v]--;
		cap[v][u]++;
		len += cost[u][v];
		v = from[v];
	}
	while(v != neg_cycle_start);
	assert(len < 0);
	//printf("len = %d\n", len);
	return len;
}


// lazy propagation segtree

const int MAX = (1 << 23);
struct SegTree
{
	int seg[2 * MAX];
	int delta[2 * MAX];
	void init()
	{
		memset(seg, 0, sizeof(seg));
		memset(delta, 0, sizeof(delta));
	}
	void propagate_up(int p)
	{
		seg[p] = max(seg[p * 2], seg[p * 2 + 1]);
	}
	void propagate_down(int p)
	{
		if(p >= MAX) return;
		seg[p * 2] += delta[p];
		delta[p * 2] += delta[p];
		seg[p * 2 + 1] += delta[p];
		delta[p * 2 + 1] += delta[p];
		delta[p] = 0;
	}
	int lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return 0;
		if(l <= a && b <= r) return seg[p];
		propagate_down(p);
		int m = (a + b) / 2;
		return max(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r + 1, 1, 0, MAX);
	}
	void insert2(int v, int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return;
		if(l <= a && b <= r)
		{
			seg[p] += v;
			delta[p] += v;
		}
		else
		{
			propagate_down(p);
			int m = (a + b) / 2;
			insert2(v, l, r, p * 2, a, m);
			insert2(v, l, r, p * 2 + 1, m, b);
			propagate_up(p);
		}
	}
	void insert(int v, int l, int r)
	{
		//printf("insert %d in [%d, %d]\n", v, l, r);
		insert2(v, l, r + 1, 1, 0, MAX);
	}
};


const int MAX = (1 << 21);
const int INF = (1 << 27);
class Tree
{
public:
	pair<int, int> seg[2*MAX];
	void insert(pair<int, int> v, int i)
	{
		for(int p = i+MAX; p > 0; p /= 2) seg[p] = min(seg[p], v);
	}
	pair<int, int> lookup2(int l, int r, int p, int a, int b)
	{
		if(a >= r || b <= l) return make_pair(INF, INF);
		if(l <= a && b <= r) return seg[p];
		int m = (a+b)/2;
		return min(lookup2(l, r, p*2, a, m), lookup2(l, r, p*2+1, m, b));
	}
	int lookup(int l, int r)
	{
		return lookup2(l, r, 1, 0, MAX).second;
	}
	vector<int> G[MAX];
	int depth[MAX];
	int dfstime[MAX];
	int timestamp;
	void dfs(int v, int p, int d)
	{
		depth[v] = d;
		dfstime[v] = timestamp;
		insert(make_pair(d, v), timestamp);
		timestamp++;
		for(int i = 0; i < G[v].size(); i++)
		{
			int w = G[v][i];
			if(w == p) continue;
			dfs(w, v, d+1);
			insert(make_pair(d, v), timestamp);
			timestamp++;
		}
	}
	void get_dfstimes()
	{
		for(int i = 0; i < 2*MAX; i++) seg[i] = make_pair(INF, INF);
		timestamp = 1;
		dfs(1, -1, 1);
	}
	int lca(int u, int v)
	{
		//cout << dfstime[u] << ' ' << dfstime[v] << endl;
		if(u == v) return u;
		return lookup(min(dfstime[u], dfstime[v]), max(dfstime[u], dfstime[v]));
	}
};
// pairwise lca
int get_lca(int a, int b)
{
	//cout << " at " << a << ' ' << b << endl;
	if(lca[a][b] != 0) return lca[a][b];

	if(a == b) lca[a][b] = a;
	else if(par[a] == -1) lca[a][b] = a;
	else if(par[b] == -1) lca[a][b] = b;
	else
	{
		int l1 = get_lca(par[a], b);
		int l2 = get_lca(a, par[b]);
		if(l1 == l2) lca[a][b] = l1;
		else if(l1 == par[l2]) lca[a][b] = l2;
		else if(l2 == par[l1]) lca[a][b] = l1;
		else assert(false);
	}
	return lca[a][b];
}

// lca with tree jump pointers

int depth[500500]; // root has depth 0
int path[500500][20]; // [v][d] means jump from v up 2^d nodes
int largest[500500][20]; // largest node in jump from v up 2^d nodes, excluding final node
void setup_dfs(int v, int p, int d)
{
    depth[v] = d;
    int last = p;
    int maxval = val[v];
    for(int i = 0; (1<<i) <= d; i++)
    {
        path[v][i] = last;
        largest[v][i] = maxval;
        maxval = max(maxval, largest[last][i]);
        last = path[last][i];
    }
    for(int i = 0; i < G[v].size(); i++)
    {
        int w = G[v][i];
        setup_dfs(w, v, d+1);
    }
}
void setup_lca() // 1 is the root
{
    for(int i = 0; i < 500500; i++) if(is_root[i]) setup_dfs(i, -1, 0);
}
int jump(int v, int d) // jump from v up d nodes
{
    for(int i = 0; i < 20; i++)
    {
        if(d & (1<<i)) v = path[v][i];
    }
    return v;
}
int maxjump(int v, int d) // max in jump from v up d nodes
{
    int maxval = val[v];
    for(int i = 0; i < 20; i++)
    {
        if(d & (1<<i))
        {
            maxval = max(maxval, largest[v][i]);
            v = path[v][i];
        }
    }
    return maxval;
}
int maxjumpto(int s, int f)
{
    int d = depth[s] - depth[f];
    return maxjump(s, d);
}
int lca(int v, int w)
{
    if(depth[v] < depth[w]) return lca(w, v);
    v = jump(v, depth[v] - depth[w]);
    int d = depth[v];
    for(int i = 19; i >= 0; i--)
    {
        if((1<<i) > d) continue;
        if(jump(v, 1<<i) != jump(w, 1<<i))
        {
            v = jump(v, 1<<i), w = jump(w, 1<<i);
        }
    }
    if(v == 1) return 1;
    return jump(v, 1);
}



typedef long long ll;
const int MAX = 1000100;
const ll base = 2, invbase = 500000004, mod = 1000000007;

int N;
char S[MAX];

struct Hash
{
	ll key[256];
	ll power[MAX];
	ll inv[MAX];
	ll hash[MAX];
	void init()
	{
		for(int i = 0; i < 256; i++)
			key[i] = rand() % mod;
		power[0] = inv[0] = 1;
		for(int i = 1; i < N; i++)
		{
			power[i] = (power[i - 1] * base) % mod;
			inv[i] = (inv[i - 1] * invbase) % mod;
		}
		hash[0] = (power[0] * key[S[0]]) % mod;
		for(int i = 1; i < N; i++)
			hash[i] = (hash[i - 1] + power[i] * key[S[i]]) % mod;
	}
	ll get(ll start, ll len)
	{
		return (inv[start] * (hash[start + len - 1] - (start == 0 ? 0LL : hash[start - 1]) + mod)) % mod;
	}
};



struct edge
{
	int v, id;
	edge(int v2, int id2)
	{
		v = v2, id = id2;
	}
};

const int MAX = 300300;
struct EulerTour
{
	vector<edge> G[MAX];
	bool used[MAX];
	vector<int> tour;
	void euler_tour(int v)
	{
		for(int i = 0; i < G[v].size(); i++)
		{
			//cout << v << " -> " << G[v][i].v << endl;
			if(used[G[v][i].id]) continue;
			used[G[v][i].id] = true;
			euler_tour(G[v][i].v);
		}
		tour.push_back(v);
	}
};




struct Trie
{
	Trie* trie[26];
	int cnt[26];
	int last;
	Trie()
	{
		memset(trie, 0, sizeof(trie));
		memset(cnt, 0, sizeof(cnt));
		last = false;
	}
};

int N;
Trie* root;
string S[30030];
vector<string> res;

void insert(string S)
{
	Trie* T = root;
	for(int i = 0; i < S.size(); i++)
	{
		char c = S[i];
		T->cnt[c - 'a']++;
		if(T->cnt[c - 'a'] == 1)
		{
			T->trie[c - 'a'] = new Trie();
		}
		T = T->trie[c - 'a'];
	}
	T->last = true;
}




#define SIZE 105

ll mult(ll A[SIZE][SIZE], ll B[SIZE][SIZE], ll C[SIZE][SIZE])
{
	memset(C, 0, sizeof(C));
	for(int i = 0; i < SIZE; i++)
		for(int j = 0; j < SIZE; j++)
			for(int k = 0; k < SIZE; k++)
				C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
}
void identity(ll I[SIZE][SIZE])
{
	memset(I, 0, sizeof(I));
	for(int i = 0; i < SIZE;i ++) I[i][i] = 1;
}
ll power(ll A[SIZE][SIZE], ll C[SIZE][SIZE], int e)
{
	if(e == 0) identity(C);
	else
	{
		ll temp[SIZE][SIZE];
		memset(temp, 0, sizeof(temp));
		power(A, temp, e / 2);
		if(e % 2)
		{
			ll temp2[SIZE][SIZE];
			memset(temp2, 0, sizeof(temp2));
			mult(temp, temp, temp2);
			mult(temp2, A, C);
		}
		else mult(temp, temp, C);
	}
}


