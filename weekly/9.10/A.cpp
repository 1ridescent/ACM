#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int mod = 21092013;

vector<char> dfs;
int num[256];

int main()
{
	ios::sync_with_stdio(false);
	int tests;
	cin >> tests;
	for(int test = 1; test <= tests; test++)
	{
		string S, T;
		cin >> S >> T;
		for(int i = 0; i < S.size(); i++)
		{
			if(S[i] == 'U')
			{
				if(!dfs.empty()) dfs.pop_back();
			}
			else dfs.push_back(S[i]);
		}

		memset(num, 0, sizeof(num));
		num['T'] = num['L'] = num['R'] = 1;
		for(int i = 0; i < T.size(); i++)
		{
			if(T[i] == 'U')
			{
				if(!dfs.empty())
				{
					if(dfs.back() == 'L') num['R']++;
					else num['L']++;
					num['T']++;
					dfs.pop_back();
				}
			}
			else if(T[i] == 'L')
			{
				num['R'] += num[T[i]];
				num['T'] += num[T[i]];
			}
			else
			{
				num['L'] += num[T[i]];
				num['T'] += num[T[i]];
			}
			num['T'] %= mod;
			num['L'] %= mod;
			num['R'] %= mod;
			//cout << "T=" << num['T'] << " L=" << num['L'] << " R=" << num['R'] << endl;
		}
		cout << "Case " << test << ": " << num['T'] << '\n';

		dfs.clear();
	}
}
