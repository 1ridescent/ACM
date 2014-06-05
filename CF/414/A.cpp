#include <iostream>
#include <cstring>

using namespace std;

bool good[256];

int main()
{
	memset(good, 0, sizeof(good));
	good['A'] = good['H'] = good['I'] = good['M'] = good['O'] = good['T']
	          = good['U'] = good['V'] = good['W'] = good['X'] = good['Y'] = true;
	ios::sync_with_stdio(false);
	string S;
	cin >> S;
	for(int i = 0; i < S.size(); i++)
	{
		if(!good[S[i]] || S[i] != S[S.size() - 1 - i])
		{
			cout << "NO\n";
			return 0;
		}
	}
	cout << "YES\n";
	return 0;
}
