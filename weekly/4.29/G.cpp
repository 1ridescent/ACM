#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <set>
#include <map>
#include <queue>
#include <cstdlib>
#include <cassert>
#include <ctime>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
const ll INV2 = 500000004;

ll key[256];
ll pow2[100005];
ll inv2[100005];

void setup()
{
	srand(time(0));
	for(int i = 0; i < 256; i++)
		key[i] = rand() % mod;
	pow2[0] = inv2[0] = 1;
	for(int i = 1; i < 100005; i++)
	{
		pow2[i] = (pow2[i - 1] * 2) % mod;
		inv2[i] = (inv2[i - 1] * INV2) % mod;
	}
}

ll Hash[100005];
char ans[100005];
int Next;
ll get(int l, int r) // [l, r]
{
	//for(int i = l; i <= r; i++) cout << ans[i]; cout << " : ";
	//cout << l << ' ' << r << ' ' << ((Hash[r] - (l == 0 ? 0 : Hash[l - 1]) + mod) * inv2[l]) % mod << endl;
	return ((Hash[r] - (l == 0 ? 0 : Hash[l - 1]) + mod) * inv2[l]) % mod;
}
/*void process(string s)
{
	Hash[0] = key[s[0]];
	for(int i = 1; i < s.size(); i++)
		Hash[i] = (Hash[i - 1] + key[s[i]] * pow2[i]) % mod;
}*/

map<ll, bool> dict[100005]; // [len]

string S;
int N;

int main()
{
	setup();
	cin >> S >> N;
	for(int i = 0; i < N; i++)
	{
		string w;
		cin >> w; // abcdef
		ll h = 0;
		for(int l = 1; l <= w.size(); l++)
		{
			h = (h * 2 + key[w[w.size() - l]]) % mod;
			//cout << l << ' ' << h << endl;
			dict[l][h] = (l == w.size());
		}
	}
	Hash[0] = key[0];
	Next = 1;
	for(int h = 0; h < S.size(); h++)
	{
		char c = S[h];
		ans[Next] = c;
		Hash[Next] = (Hash[Next - 1] + key[c] * pow2[Next]) % mod;
		Next++;
		int low = -1, high = Next;
		while(low + 1 < high)
		{
			int mid = (low + high) / 2;
			int len = Next - mid;
			if(dict[len].count(get(mid, Next - 1))) high = mid;
			else low = mid;
		}
		//cout << Next << ' ' << high << '\n';
		if(Next == high) continue;
		int len = Next - high;
		assert(dict[len].count(get(high, Next - 1)));
		//cout << dict[len][get(high, Next - 1)] << endl;
		if(dict[len][get(high, Next - 1)])
			Next = high;
	}
	for(int i = 1; i < Next; i++) cout << ans[i];
	cout << endl;
}
