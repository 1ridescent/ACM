#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll P = 2013265921; // 15*2^27+1
const ll ORDER = (1 << 27);
const ll ROOT = 440564289; // ORDER'th root of unity
const int MAX = (1 << 19);
#define PIVOT 202020

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
	//cout << "convolving "; for(int i = 0; i < A.size(); i++) cout << A[i]; cout << " and "; for(int i = 0; i < B.size(); i++) cout << B[i]; cout << endl;
	int N = A.size() + B.size();
	int n = 1;
	while((1 << n) < N) n++;
	while(A.size() < (1 << n)) A.push_back(0);
	while(B.size() < (1 << n)) B.push_back(0);
	fft(A, n);
	fft(B, n);
	for(int i = 0; i < (1 << n); i++) A[i] = (A[i] * B[i]) % P;
	fft(A, n, true);
	//cout << "result: "; for(int i = 0; i < A.size(); i++) cout << A[i]; cout << endl;
	return A;
}

// end of library



int to_int(char c)
{
	if(c == 'A') return 0;
	if(c == 'T') return 1;
	if(c == 'G') return 2;
	return 3;
}

int N, M, K;
int S[MAX], T[MAX];
int pref[4][MAX];
bool good[4][MAX];
bool bad[MAX];

int main()
{
	cin >> N >> M >> K;
	for(int i = 1; i <= N; i++)
	{
		char c;
		cin >> c;
		S[i] = to_int(c);
		pref[S[i]][i]++;
	}
	for(int i = 1; i < MAX; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			pref[j][i] += pref[j][i - 1];
		}
		//if(i <= N) printf("%d %d\n", i, pref[0][i]);
	}
	for(int i = 1; i <= M; i++)
	{
		char c;
		cin >> c;
		T[i] = to_int(c);
	}
	for(int i = 1; i <= N; i++)
	{
		for(int c = 0; c < 4; c++)
		{
			good[c][i] = (pref[c][i + K] > pref[c][max(0, i - K - 1)]);
			//printf("%d: %d %d\n", i, c, good[c][i]);
		}
	}
	for(int c = 0; c < 4; c++)
	{
		vector<ll> A(MAX / 2, 0), B(MAX / 2, 0);
		int wanted = 0;
		for(int i = 1; i <= N; i++)
		{
			//cout << good[c][i];
			A[i - 1] = good[c][i];
		}
		//cout << endl;
		for(int i = 1; i <= M; i++)
		{
			//cout << (T[i] == c);
			if(T[i] == c)
			{
				B[PIVOT - (i - 1)] = 1;
				wanted++;
			}
		}
		//cout << endl;
		vector<ll> C = conv(A, B);
		for(int i = 0; i < N; i++)
		{
			//cout << C[PIVOT + i];
			if(C[PIVOT + i] != wanted)
				bad[i] = true;
		}
		//cout << endl << endl;
	}
	int res = 0;
	for(int i = 0; i < N; i++)
		if(!bad[i]) res++;
	cout << res;
}
