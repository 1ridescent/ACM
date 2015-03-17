#include <bits/stdc++.h>

using namespace std;

bool vis[106][66][22][22];
string dp[106][66][22][22];

int table[11][4];

bool cmp(string s, string t) // s > t ?
{
	if(s.size() > t.size()) return true;
	if(s.size() < t.size()) return false;
	return (s > t);
}

string compute(int a, int b, int c, int d) // 2 3 5 7
{
	if(vis[a][b][c][d]) return dp[a][b][c][d];
	string s;
	bool found = false;
	for(int f = 2; f <= 9; f++)
	{
		int a2 = a - table[f][0], b2 = b - table[f][1], c2 = c - table[f][2], d2 = d - table[f][3];
		if(a2 < 0 || b2 < 0 || c2 < 0 || d2 < 0) continue;
		string t = compute(a2, b2, c2, d2);
		if(t == "bad") continue;
		t = ((char)(f + '0')) + t;
		if(cmp(t, s)) s = t;
		found = true;
	}
	vis[a][b][c][d] = true;
	dp[a][b][c][d] = s;
	if(!found) dp[a][b][c][d] = "bad";
	//cout << a << ' ' << b << ' ' << c << ' ' << d << ' '<< dp[a][b][c][d] << endl;
	return dp[a][b][c][d];
}

int main()
{
	for(int d = 0; d <= 9; d++)
	{
		for(int f = 1; f <= d; f++)
		{
			int f2 = f;
			while(f2 % 2 == 0) f2 /= 2, table[d][0]++;
			while(f2 % 3 == 0) f2 /= 3, table[d][1]++;
			while(f2 % 5 == 0) f2 /= 5, table[d][2]++;
			while(f2 % 7 == 0) f2 /= 7, table[d][3]++;
		}
	}
	//for(int d = 0; d <= 9; d++) { for(int i = 0; i < 4; i++) cout << table[d][i] << ' '; cout << endl;}
	int N;
	cin >> N;
	string S;
	cin >> S;
	int a = 0, b = 0, c = 0, d = 0;
	for(int i = 0; i < N; i++)
	{
		char v = S[i];
		int f = (int)(v - '0');
		//cout << f << endl;
		a += table[f][0];
		b += table[f][1];
		c += table[f][2];
		d += table[f][3];
	}
	//cout << a << ' ' << b << ' ' << c << ' ' << d << endl;return 0;
	vis[0][0][0][0] = true;
	dp[0][0][0][0] = "";
	S = compute(a, b, c, d);
	for(int i = 0; i < S.size(); i++) if(S[i] != 'x') cout << S[i];
}
