#include <iostream>

using namespace std;

bool pref(string a, string b)
{
	if(a.size() < b.size()) return pref(b, a);
	bool res = (a.substr(0, b.size()) == b);
	//cout << a << ' ' << b << ' ' << res << endl;
	return res;
}

bool suff(string a, string b)
{
	if(a.size() < b.size()) return suff(b, a);
	bool res = (a.substr(a.size() - b.size()) == b);
	//cout << a << ' ' << b << ' ' << res << endl;
	return res;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		string S[3];
		cin >> S[0] >> S[1] >> S[2];
		bool ans = true;
		for(int i = 0; i < 3; i++)
			for(int j = i + 1; j < 3; j++)
				if(pref(S[i], S[j]) || suff(S[i], S[j]))
					ans = false;
		cout << (ans ? "Yes\n" : "No\n");
	}
}
