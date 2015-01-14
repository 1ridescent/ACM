#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef unsigned long long ll;

const ll P = 24LL * (1LL << 27) + 1;
const ll ORDER = (1 << 27);
const ll ROOT = 229807484; // ORDER'th root of unity
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
				ll temp2 = A[s] + P - A[t];
				if(temp2 >= P) temp2 -= P;
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

void conv(vector<ll>& A, vector<ll>& B)
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
}

#define VALID(x) (0 <= (x) && (x) <= 30010)
ll freq[30030];
ll slow(vector<int> V)
{
	memset(freq, 0, sizeof(freq));
	ll res = 0;
	for(int m = 0; m < V.size(); m++)
	{
		for(int r = m + 1; r < V.size(); r++)
		{
			int target = 2 * V[m] - V[r];
			if(VALID(target)) res += freq[target];
		}
		freq[V[m]]++;
	}
	return res;
}

#define SEG 2500
ll solve(vector<int> V)
{
	ll res = 0;
	vector<vector<int> > S;

	/* 3 */
	for(int i = 0; i < V.size(); i += SEG)
	{
		S.push_back(vector<int>());
		for(int j = i; j < V.size() && j < i + SEG; j++) S.back().push_back(V[j]);
		res += slow(S.back());
	}

	/* 2 + 1 */
	memset(freq, 0, sizeof(freq));
	for(int s = 0; s < S.size(); s++)
	{
		for(int m = 0; m < S[s].size(); m++)
			for(int r = m + 1; r < S[s].size(); r++)
			{
				int target = 2 * S[s][m] - S[s][r];
				if(VALID(target)) res += freq[target];
			}
		for(int i = 0; i < S[s].size(); i++) freq[S[s][i]]++;
	}
	memset(freq, 0, sizeof(freq));
	for(int s = S.size() - 1; s >= 0; s--)
	{
		for(int l = 0; l < S[s].size(); l++)
			for(int m = l + 1; m < S[s].size(); m++)
			{
				int target = 2 * S[s][m] - S[s][l];
				if(VALID(target)) res += freq[target];
			}
		for(int i = 0; i < S[s].size(); i++) freq[S[s][i]]++;
	}

	/* 1 + 1 + 1 */
	for(int m = 1; m < S.size() - 1; m++)
	{
		vector<ll> L(32768, 0);
		for(int l = 0; l < m; l++)
			for(int i = 0; i < S[l].size(); i++)
				L[S[l][i]]++;
		vector<ll> R(32768, 0);
		for(int r = m + 1; r < S.size(); r++)
			for(int i = 0; i < S[r].size(); i++)
				R[S[r][i]]++;
		conv(L, R);
		for(int i = 0; i < S[m].size(); i++)
			res += L[2 * S[m][i]];
	}

	return res;
}

int main()
{
	int N;
	cin >> N;
	vector<int> A(N);
	for(int i = 0; i < N; i++) cin >> A[i];
	cout << solve(A) << '\n';
}
