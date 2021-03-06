#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
#define MOD(x) (((x) + 1000000007000LL) % 1000000007)
const ll INV2 = 500000004;
const int MAX = 1000005;

ll sum_squares[MAX + 10];
ll gcd_weight[MAX + 10];
ll gcd_sum[MAX + 10];
ll total_num[MAX + 10];
ll total_sum[MAX + 10];
ll total_sum_i[MAX + 10];
ll total_sum_i2[MAX + 10];
void pre()
{
	sum_squares[0] = 0, sum_squares[1] = 1;
	for(ll n = 2; n <= MAX; n++) sum_squares[n] = MOD(sum_squares[n - 2] + n * n);
	
	for(int n = 1; n <= MAX; n++) gcd_weight[n] = n;
	for(int f = 1; f <= MAX; f++)
		for(int n = 2 * f; n <= MAX; n += f)
			gcd_weight[n] -= gcd_weight[f];
	
	memset(gcd_sum, 0, sizeof(gcd_sum));
	for(int f = 1; f <= MAX; f++)
		for(int n = f; n <= MAX; n += f)
			gcd_sum[n] += (n / f) * gcd_weight[f];

	memset(total_num, 0, sizeof(total_num));
	total_num[1] = 1;
	for(ll n = 2; n <= MAX; n++)
	{
		total_num[n] += n * n;
		total_num[n] += MOD(INV2 * MOD((n - 1) * MOD(n * n) + 2 * sum_squares[n - 2]));
		total_num[n] += -2 * MOD((n - 1) * n);
		total_num[n] += 2 * (gcd_sum[n] - n);
		total_num[n] = MOD(total_num[n]);
	}

	total_sum[1] = total_num[1];
	for(int n = 2; n <= MAX; n++) total_sum[n] = MOD(total_sum[n - 1] + total_num[n]);
	total_sum_i[1] = total_num[1];
	for(int n = 2; n <= MAX; n++) total_sum_i[n] = MOD(total_sum_i[n - 1] + n * total_num[n]);
	total_sum_i2[1] = total_num[1];
	for(ll n = 2; n <= MAX; n++) total_sum_i2[n] = MOD(total_sum_i2[n - 1] + MOD(n * n) * total_num[n]);
}


int main()
{
	pre();
	ios::sync_with_stdio(0);
	int T;
	cin >> T;
	for(int t = 0; t < T; t++)
	{
		ll n, m;
		cin >> n >> m;
		if(n > m) swap(n, m);
		ll res = 0;
		res += MOD((n + 1) * (m + 1)) * total_sum[n];
		res -= MOD((n + 1 + m + 1) * total_sum_i[n]);
		res += total_sum_i2[n];
		cout << MOD(res) << '\n';
	}
}
