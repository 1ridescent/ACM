#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <cstdio>

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

vector<ll> conv(vector<ll>& A, vector<ll>& B)
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
void square(vector<ll>& A)
{
	int N = A.size() + A.size();
	int n = 1;
	while((1 << n) < N) n++;
	while(A.size() < (1 << n)) A.push_back(0);
	fft(A, n);
	for(int i = 0; i < (1 << n); i++) A[i] = (A[i] * A[i]) % P;
	fft(A, n, true);
}
/*priority_queue<pair<int, int> > vectors;
vector<ll> multi_conv(vector<vector<ll> >& V)
{
	while(!vectors.empty()) vectors.pop();
	for(int i = 0; i < V.size(); i++) vectors.push(make_pair(V[i].size(), i));
	while(vectors.size > 1)
	{
		int i = vectors.top();
		vectors.pop();
		int j = vectors.top();
		vectors.pop();
		V.push_back(conv(V[i], V[j]));
		vectors.push(make_pair(V.back().size(), V.size() - 1));
	}
	return V[vectors.top().second];
}*/

void print(vector<ll> V)
{
	for(int i = 0; i < V.size(); i++) cout << V[i] << ' ';
	cout << endl;
}

int N;
set<int> G[50050];

vector<int> depths;
void get_depths(int u, int p, int d)
{
	depths.push_back(d);
	for(set<int>::iterator it = G[u].begin(); it != G[u].end(); it++)
	{
		int v = *it;
		if(v == p) continue;
		get_depths(v, u, d + 1);
	}
}
int size[50050];
void get_sizes(int u, int p)
{
	size[u] = 1;
	for(set<int>::iterator it = G[u].begin(); it != G[u].end(); it++)
	{
		int v = *it;
		if(v == p) continue;
		get_sizes(v, u);
		size[u] += size[v];
	}
}
int get_balance(int r)
{
	int n = size[r];
	for(set<int>::iterator it = G[r].begin(); it != G[r].end(); it++)
	{
		int u = *it;
		if(size[u] > n / 2)
		{
			size[r] -= size[u];
			size[u] = n;
			return get_balance(u);
		}
	}
	return r;
}

int num[50050];
void compute(int r)
{
	get_sizes(r, -1);
	r = get_balance(r);
	int n = size[r];
	printf("balance: v=%d s=%d\n", r, n);
	for(int i = 1; i <= 5; i++) cout << size[i] << ' '; cout << endl;
	if(n == 1) return;
	vector<ll> res(n + 5, 0);
	vector<ll> sum(n + 5, 0);
	for(set<int>::iterator it = G[r].begin(); it != G[r].end(); it++)
	{
		int u = *it;
		G[u].erase(r);
		G[r].erase(u);

		vector<ll> single(n + 5, 0);
		depths.clear();
		get_depths(u, -1, 0);
		for(int i = 0; i < depths.size(); i++)
		{
			printf("%d->%d\n", u, depths[i]);
			num[depths[i] + 1]++; // to the root
			single[depths[i] + 1]++;
			sum[depths[i] + 1]++;
		}

		//cout << "single " << u << ": "; print(single);
		square(single);

		for(int i = 0; i < res.size() && i < single.size(); i++)
			res[i] = (res[i] + P - single[i]) % P;
	}
	printf("sum: "); print(sum);
	square(sum);
	for(int i = 0; i < res.size() && i < sum.size(); i++)
		res[i] += sum[i];
	const ll inv2 = (P + 1) / 2;
	for(int i = 0; i < res.size(); i++)
		res[i] = (res[i] * inv2) % P;
	for(int i = 0; i < res.size(); i++)
		num[i] += res[i];
	printf("res: "); print(res);
}

bool isprime(int p)
{
	if(p < 2) return false;
	for(int i = 2; i * i <= p; i++)
		if(p % i == 0) return false;
	return true;
}

int main()
{
	cin >> N;
	for(int i = 1; i < N; i++)
	{
		int a, b;
		cin >> a >> b;
		G[a].insert(b);
		G[b].insert(a);
	}
	compute(1);

	for(int i = 1; i <= N; i++) printf("%d: %d\n", i, num[i]);
	/*int res = 0;
	for(int i = 2; i < N; i++)
		if(isprime(i))
			res += num[i];
	cout << res << endl;*/
}
