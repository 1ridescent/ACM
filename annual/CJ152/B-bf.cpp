#include <bits/stdc++.h>

using namespace std;

typedef long double ld;

int N;
ld V, X;
ld rate[105], temp[105];

int main2()
{
	cin >> N >> V >> X;
	for(int i = 0; i < N; i++) cin >> rate[i] >> temp[i];
	if(N == 1 || temp[0] == temp[1])
	{
		if(temp[0] != X) { cout << "IMPOSSIBLE\n"; return 0; }
		double r = rate[0];
		if(N == 2) r += rate[1];
		printf("%.9f\n", (double)( V / r));
		return 0;
	}
	ld S = V * X;
	ld V1 = (S - V * temp[0]) / (temp[1] - temp[0]);
	ld V0 = V - V1;
	//cout << (V0*temp[0]+V1*temp[1])/V << endl;
	//printf("V0=%.9f V1=%.9f\n", (double)V0,(double)V1);
	if(V0 < -1e-10 || V1 < -1e-10) cout << "IMPOSSIBLE\n";
	else printf("%.9f\n", (double)max(V0 / rate[0], V1 / rate[1]));
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
