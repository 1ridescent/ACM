#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

typedef long long ll;
const ll mod[2] = {1000000007, 1000000009};

int N, M;
string S, T;

ll powers[200005][2];

ll val[2][26][2];
bool good[26];
bool check()
{
	//for(int i = 0; i < 26; i++) cout << val[0][i][0] << ' '; cout << endl;
	//for(int i = 0; i < 26; i++) cout << val[1][i][0] << ' '; cout << endl;
	memset(good, 0, sizeof(good));
	for(int i = 0; i < 26; i++)
	{
		if(good[i]) continue;
		for(int j = 0; j < 27; j++)
		{
			if(j == 26) return false;
			if(!good[j] && val[0][i][0] == val[1][j][0] && val[0][i][1] == val[1][j][1]
			            && val[0][j][0] == val[1][i][0] && val[0][j][1] == val[1][i][1])
			{
				good[j] = true;
				break;
			}
		}
	}
	return true;
}

void modadd(ll& v, ll d, ll m)
{
	v = (v + d) % m;
	if(v < 0) v += m;
}
void modmul(ll& v, ll s, ll m)
{
	v = (v * s) % m;
	if(v < 0) v += m;
}

int main()
{
	cin >> N >> M;
	srand(time(0));
	ll power = rand() % mod[0];
	for(int t = 0; t < 2; t++)
	{
		powers[0][t] = 1;
		for(int i = 1; i < 200005; i++)
			powers[i][t] = (powers[i - 1][t] * power) % mod[t];
	}
	cin >> S >> T;
	for(int i = 0; i < T.size(); i++)
		for(int t = 0; t < 2; t++)
		{
			modadd(val[0][S[i] - 'a'][t], powers[i][t], mod[t]);
			modadd(val[1][T[i] - 'a'][t], powers[i][t], mod[t]);
		}
	vector<int> res;
	if(check()) res.push_back(0);
	for(int i = T.size(); i < S.size(); i++)
	{
		for(int t = 0; t < 2; t++)
		{
			modadd(val[0][S[i] - 'a'][t], powers[i][t], mod[t]);
			modadd(val[0][S[i - T.size()] - 'a'][t], -powers[i - T.size()][t], mod[t]);
			for(int c = 0; c < 26; c++)
				modmul(val[1][c][t], power, mod[t]);
		}
		if(check()) res.push_back(i - T.size() + 1);
	}
	cout << res.size() << endl;
	for(int i = 0; i < res.size(); i++) cout << res[i] + 1 << ' ';
}
