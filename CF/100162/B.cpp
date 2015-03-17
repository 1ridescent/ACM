#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
ll pow2[2000005];
ll inv2[2000005];

ll key[256];
void precompute()
{
	pow2[0] = inv2[0] = 1;
	for(int i = 1; i < 2000005; i++)
	{
		pow2[i] = (2 * pow2[i - 1]) % mod;
		inv2[i] = (500000004 * inv2[i - 1]) % mod;
	}
	srand(time(0));
	for(int i = 0; i < 256; i++)
		key[i] = rand() % mod;
}

bool output[2000005];
ll hash[2000005];
void process(ll* input, int len)
{
	//cout << "len = " << len << endl;
	hash[0] = 0;
	for(int i = 0; i < len; i++)
		hash[i + 1] = (hash[i] + input[i] * pow2[i]) % mod;
	for(int k = 1; k < len; k++) output[k] = false;
	for(int k = 1; k < len; k++)
		output[k] = (hash[len - k] != (((hash[len] - hash[k] + mod) * inv2[k]) % mod));
	//for(int i = 1; i <= len; i++) cout << output[i]; cout << endl;
}

int N;
string str;
ll input[2000005];
bool ans[2000005];
int main()
{
	precompute();
	int test = 0;
	while(cin >> str)
	{
		test++;
		printf("Case %d: ", test);
		N = str.size();
		for(int i = 0; i < N; i++)
			input[i] = input[i + N] = key[str[i]];
		for(int i = 0; i < N; i++) ans[i] = false;
		ans[N - 1] = true;
		int l = 0;
		for(int r = 0; r < 2 * N; r++)
		{
			if(r == 2 * N - 1 || input[r] == input[r + 1])
			{
				//printf("l = %d, r = %d\n", l, r);
				process(input + l, r - l + 1);
				for(int k = 1; k < r - l + 1; k++)
					if(N - k - 1 >= 0)
						ans[N - k - 1] |= output[k];
				l = r + 1;
			}
		}
		for(int i = 0; i < N; i++) printf("%c", ans[i] ? '1' : '0');
		printf("\n");
	}
}
