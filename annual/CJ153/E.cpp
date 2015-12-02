#include <bits/stdc++.h>

using namespace std;

int N, D;
int A[100000];

inline int sum(int s, int n)
{
	int res = 0;
	for(int i = s; i < s + n; i++) res += A[i];
	return res;
}
inline void add(int s, int v, int d)
{
	//cout << s << ' ' << v << ' ' << d << endl;
	for(; s < N; s += 2 * d)
		for(int i = s; i < s + d; i++)
			A[i] += v;
}

int mane()
{
	cin >> N >> D;
	for(int i = 0; i < N; i++) cin >> A[i];
	for(int i = N; i < N + 2 * D; i++) A[i] = A[i - 2 * D];
	N += 2 * D;
	int res = 0;
	for(int d = D; d > 0; d /= 2)
	{
		//for(int i = 0; i < N; i++) cout << A[i] << ' '; cout << endl;
		for(int s = 0; s < 2 * d; s++)
			for(int i = s + 2 * d; i < N; i++)
				if(A[i - 2 * d] != A[i])
					return -1;
		vector<int> V;
		for(int s = 0; s < 2 * d; s++) V.push_back(sum(s, d));
		//for(int i = 0; i < V.size(); i++) cout << V[i] << ' '; cout << endl;
		vector<int> F;
		for(int s = 0; s < d; s++)
		{
			int v = 2 * V[s] - V[(s + V.size() - 1) % V.size()] - V[(s + 1) % V.size()];
			if(v % 2 != 0) return -1;
			v /= 2;
			res += abs(v);
			F.push_back(-v);
		}
		for(int s = 0; s < d; s++) add(s, F[s], d);
	}
	for(int i = 1; i < N; i++) if(A[i - 1] != A[i]) return -1;
	return res;
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cout << "Case #" << t << ": ";
		int res = mane();
		if(res == -1) cout << "CHEATERS!\n";
		else cout << res << '\n';
	}
}
