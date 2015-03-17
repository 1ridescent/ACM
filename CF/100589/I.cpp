#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
ll A[2][100005];

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--)
	{
		string S;
		cin >> S;
		memset(A, 0, sizeof(A));
		for(int i = 0; i < S.size(); i++)
			if(S[i] == 'L')
				A[0][i]++, A[1][i]++;
		for(int i = 0; i < S.size(); i++)
			A[0][i] += (i == 0 ? 0 : A[0][i - 1]);
		for(int i = S.size() - 1; i >= 0; i--)
			A[1][i] += A[1][i + 1];
		ll res=  0;
		for(int i = 0; i < S.size(); i++)
			if(S[i] == 'O')
				res += A[0][i] * A[1][i];
		cout << res << endl;
	}
}
