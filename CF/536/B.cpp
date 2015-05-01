#include <bits/stdc++.h>

using namespace std;


// KMP

const int MAX = 1000005;

bool good[1000005];

int T[MAX];
void build_table(string& W)
{
	int pos = 2, cnd = 0;
	T[0] = -1, T[1] = 0;
	while(pos < W.size())
	{
		if(W[pos - 1] == W[cnd])
			cnd++, T[pos] = cnd, pos++;
		else if(cnd > 0)
			cnd = T[cnd];
		else
			T[pos] = 0, pos++;
	}
	//cout << "cnd = " << cnd << endl;
	good[0] = true;
	if(W[W.size() - 1] == W[0]) good[W.size() - 1] = true;
	for(; cnd != 0; cnd = T[cnd])
	{
		good[W.size() - 1 - cnd] = true;
	}
}

int N, M;
string P;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> M;
	cin >> P;
	build_table(P);
	int len = P.size();
	//cout << len << ": "; for(int i = 0; i < P.size(); i++) cout << good[i]; cout << endl;
	int last = -len + 1;
	int total = 0;
	while(M--)
	{
		int x;
		cin >> x;
		if(x >= last + len) { total += (x - (last + len)); last = x; }
		else if(good[x - last]) last = x;
		else
		{
			cout << "0\n";
			return 0;
		}
	}
	if(N + 1 >= last + len) total += (N + 1 - (last + len));
	long long res = 1;
	for(int i = 0; i < total; i++)
		res = ((res * 26) % 1000000007);
	cout << res;
}
