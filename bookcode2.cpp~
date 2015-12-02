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

vector<ll> conv(vector<ll> A, vector<ll> B) // multiply/convolute two polynomials
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

const int LGMAX = 19;
const int MAX = (1 << LGMAX);

struct SparseTable
{
	int table[LGMAX + 1][MAX];
	void init(int A[MAX])
	{
		for(int i = 0; i < MAX; i++)
			table[0][i] = A[i];
		for(int s = 1; s <= LGMAX; s++)
			for(int i = 0; i <= MAX - (1 << s); i++)
				table[s][i] = min(table[s - 1][i], table[s - 1][i + (1 << (s - 1))]);
	}
	int lookup(int l, int r) // [l, r]
	{
		r++;
		int s = 31 - __builtin_clz(r - l);
		return min(table[s][l], table[s][r - (1 << s)]);
	}
};
struct SuffixArray
{
	int N;
	string S;
	int sa[MAX];
	int rank[MAX];
	int height[MAX];
	SparseTable table;

	void build_sa(string S0)
	{
		S = S0;
		N = S.size();

		int freq[256];
		memset(freq, 0, sizeof(freq));
		for(int i = 0; i < N; i++)
			freq[S[i]]++;
		for(int i = 1; i < 256; i++)
			freq[i] += freq[i - 1];
		for(int i = N - 1; i >= 0; i--)
			sa[--freq[S[i]]] = i;

		rank[sa[0]] = 0;
		for(int i = 0; i < N - 1; i++)
		{
			if(S[sa[i]] == S[sa[i + 1]])
				rank[sa[i + 1]] = rank[sa[i]];
			else
				rank[sa[i + 1]] = i + 1;
		}

		int nxt[MAX];
		int temp[MAX];
		for(int len = 1; len < N; len *= 2)
		{
			for(int i = 0; i < N; i++)
				nxt[i] = i;
			for(int i = N - len; i < N; i++)
				temp[nxt[rank[i]]++] = i; // end have highest priority
			for(int i = 0; i < N; i++) // then, prioritize segments based on next seg
				if(sa[i] >= len)
					temp[nxt[rank[sa[i] - len]]++] = sa[i] - len;
			memcpy(sa, temp, sizeof(temp)); // copy new orderings of segments into sa
			temp[sa[0]] = 0;
			for(int i = 0; i < N - 1; i++)
			{
				if(sa[i] + len < N && sa[i + 1] + len < N && rank[sa[i]] == rank[sa[i + 1]] && rank[sa[i] + len] == rank[sa[i + 1] + len])
					temp[sa[i + 1]] = temp[sa[i]]; // can't separate yet, so leave the same
				else
					temp[sa[i + 1]] = i + 1;
			}
			memcpy(rank, temp, sizeof(temp)); // copy new orderings into rank
		}
	}

	int find_heights_lcp(int p1, int p2, int l)
	{
		while(p1 + l < N && p2 + l < N && S[p1 + l] == S[p2 + l])
			l++;
		return l;
	}
	void find_heights()
	{
		int pre = 0;
		for(int i = 0; i < N; i++)
		{
			if(rank[i] == 0)
				height[0] = 0;
			else
			{
				pre = find_heights_lcp(sa[rank[i] - 1], sa[rank[i]], max(pre - 1, 0));
				height[rank[i]] = pre;
			}
		}

		table.init(height);
	}

	void init(string S0)
	{
		build_sa(S0);
		find_heights();
	}

	int lcp(int i, int j)
	{
		if(i == j) return N - i;
		return table.lookup(min(rank[i], rank[j]) + 1, max(rank[i], rank[j]));
	}
};


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



/***** STRONGLY CONNECTED COMPONENTS *****/

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




/***** KMP *****/

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

bool match[MAX];
void kmp_search(string& S, string& W)
{
	memset(match, 0, sizeof(match));
	int m = 0, i = 0;
	while(m + i < S.size())
	{
		if(i == W.size() - 1) match[m] = true;
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



/***** FIND NEGATIVE CYCLE *****/

int neg_cycle()
{
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


/***** LAZY PROPAGATION SEGTREE *****/

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


/***** EULER TOUR *****/

set<pair<int, int> > G[100005]; // (other edge, any unique id)

vector<int> tour;
void dfs(int u)
{
	while(!G[u].empty())
	{
		int v = (G[u].begin())->first, i = (G[u].begin())->second;
		G[u].erase(make_pair(v, i));
		G[v].erase(G[v].lower_bound(make_pair(u, -1)));
		dfs(v);
	}
	tour.push_back(u);
}
vector<pair<int, int> > added;
vector<int> odd;
void add_edge(int u, int v)
{
	G[u].insert(make_pair(v, 1000000 + added.size() * 2 + 1)); // ids must be distinct
	G[v].insert(make_pair(u, 1000000 + added.size() * 2));
	added.push_back(make_pair(u, v));
}




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



/***** MATRIX MULTIPLY *****/

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


