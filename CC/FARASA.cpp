#include <iostream>
#include <vector>
#include <set>
#include <cstring>

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

ll A[100100];
set<ll> S;
bool F[1001000];
ll pt[100100];

int main()
{
	int N;
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> A[i];
	pt[0] = 0;
	for(int i = 1; i <= N; i++) pt[i] = pt[i - 1] + A[i];

	if(N <= 1000)
	{
		for(int l = 0; l < N; l++)
			for(int r = l + 1; r <= N; r++)
				S.insert(pt[r] - pt[l]);
		cout << S.size() - 1 << endl;
	}
	else if(N <= 10000)
	{
		memset(F, 0, sizeof(F));
		for(int l = 0; l < N; l++)
			for(int r = l + 1; r <= N; r++)
				F[pt[r] - pt[l]] = true;
		int cnt = 0;
		for(int i = 0; i < 1001000; i++) cnt += F[i];
		cout << cnt - 1 << endl;
	}
	else
	{
		const int MID = (1 << 17);
		vector<ll> L(2 * MID, 0), R(2 * MID, 0);
		for(int i = 1; i <= N; i++)
			L[MID - pt[i]] = 1;
		for(int i = 1; i <= N; i++)
			R[pt[i]] = 1;
		vector<ll> LR = conv(L, R);
		int cnt = 0;
		for(int i = MID + 1; i < 2 * MID; i++)
			if(LR[i]) cnt++;
		cout << cnt - 1 << endl;
	}
}
