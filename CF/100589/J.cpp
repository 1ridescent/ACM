#include <bits/stdc++.h>

using namespace std;

int B[100005];
map<int, int> A, C;

int main()
{
	ios::sync_with_stdio(false);
	int T;
	cin >> T;
	while(T--)
	{
		int P, Q, R;
		A.clear();
		C.clear();
		cin >> P; for(int i = 1; i <= P; i++)
		{
			int x;
			cin >> x;
			A[x]++;
		}
		cin >> Q; for(int i = 1; i <= Q; i++) cin >> B[i];
		cin >> R; for(int i = 1; i <= R; i++)
		{
			int x;
			cin >> x;
			C[x]++;
		}
		int cnt = 0;
		for(map<int, int>::iterator it = A.begin(); it != A.end(); it++)
		{
			cnt += it->second;
			//cout << it->first << " : " << cnt << endl;
			it->second = cnt;
		}
		cnt = R;
		for(map<int, int>::iterator it = C.begin(); it != C.end(); it++)
		{
			int x = it->second;
			it->second = cnt;
			cnt -= x;
		}
		assert(cnt == 0);
		long long res = 0;
		for(int i = 1; i <= Q && i <= R; i++)
		{
			long long r = 1;
			map<int, int>::iterator it = A.upper_bound(B[i]);
			if(it == A.begin()) r *= 0;
			else r *= min(i, (--it)->second);
			it = C.lower_bound(B[i]);
			if(it == C.end()) r *= 0;
			else r *= min(R + 1 - i, it->second);
			//cout << i << " : " << r << endl;
			res += r;
		}
		cout << res << endl;
	}
}
