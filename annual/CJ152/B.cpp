#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

ld Min(vector<pair<ld, ld> > A, ld V)
{
	sort(A.begin(), A.end());
	ld res = 0;
	for(int i = 0; i < A.size(); i++)
	{
		if(A[i].second >= V)
		{
			res += A[i].first * V;
			return res;
		}
		res += A[i].first * A[i].second;
		V -= A[i].second;
	}
	return res;
}

int N;
ld V, S;
ld rate[105], temp[105];

bool test(ld t)
{
	vector<pair<ld, ld> > A; // (temp, max_vol)
	ld max_vol = 0;
	for(int i = 0; i < N; i++)
	{
		ld v = rate[i] * t;
		//cout << rate[i] << ' ' << t << ' ' << v << endl;
		max_vol += v;
		A.push_back(make_pair(temp[i], v));
	}
//	cout << "time " << t << ": max vol = " << max_vol << endl;
	if(max_vol < V) return false;
	ld min_sum = Min(A, V);
	for(int i = 0; i < N; i++) A[i].first *= -1;
	ld max_sum = -Min(A, V);
	return (min_sum <= S && S <= max_sum);
}

int main2()
{
	ld X;
	cin >> N >> V >> X;
	S = V * X;
	for(int i = 0; i < N; i++) cin >> rate[i] >> temp[i];
	ld low = 0, high = 1e10;
	ld good = false;
	while(low * (1 + 1e-8) < high)
	{
		ld mid = (low + high) / 2;
		if(test(mid))
		{
			good = true;
			high = mid;
		}
		else low = mid;
	}
	if(!good) printf("IMPOSSIBLE\n");
	else printf("%.9f\n", (double)high);
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		printf("Case #%d: ", t);
		main2();
	}
}
