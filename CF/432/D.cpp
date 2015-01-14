#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define MOD(x) (((x) + mod) % mod)

const int inv2 = 500000004;
const int MAX = 100100;
ll pow2[MAX + 10];
ll powinv2[MAX + 10];

ll val[256];

string S;
ll hash[MAX + 10];
void setup()
{
	srand(time(0));
	for(int i = 0; i < 256; i++) val[i] = MOD(rand());
	pow2[0] = powinv2[0] = 1;
	for(int i = 1; i < MAX; i++)
	{
		pow2[i] = MOD(2 * pow2[i - 1]);
		powinv2[i] = MOD(inv2 * powinv2[i - 1]);
	}
	for(int i = 0; i < S.size(); i++)
	{
		hash[i] = MOD(val[S[i]] * pow2[i]);
	}
	for(int i = 1; i < S.size(); i++) hash[i] = MOD(hash[i] + hash[i - 1]);
}

ll get_hash(int i, int j) // [i, j)
{
	return MOD(powinv2[i] * MOD(hash[j - 1] - (i > 0 ? hash[i - 1] : 0)));
}

int lcp(int i, int j)
{
	if(S[i] != S[j]) return 0;
	int low = 1, high = S.size() - max(i, j) + 1;
	while(low + 1 < high)
	{
		int mid = (low + high) / 2;
		if(get_hash(i, i + mid) == get_hash(j, j + mid)) low = mid;
		else high = mid;
	}
	return low;
}

int lcp_freq[MAX + 10];

vector< pair<int, int> > res;

int main()
{
	cin >> S;
	setup();
	/*while(true)
	{
		int a, b;
		cin >> a >> b;
		cout << lcp(a, b) << endl;
	}*/
	memset(lcp_freq, 0, sizeof(lcp_freq));
	for(int j = 0; j < S.size(); j++)
	{
		lcp_freq[lcp(0, j)]++;
	}
	for(int i = S.size() - 1; i >= 0; i--) lcp_freq[i] += lcp_freq[i + 1];

	for(int len = 1; len <= S.size(); len++)
	{
		if(lcp(0, S.size() - len) == len)
		{
			res.push_back( make_pair(len, lcp_freq[len]) );
		}
	}

	cout << res.size() << '\n';
	for(int i = 0; i < res.size(); i++) cout << res[i].first << ' ' << res[i].second << '\n';
}
