#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

int last[1027];
int mask[1027];

int P[20];
int main2()
{
	int N, M;
	cin >> N >> M;
	P[0] = 1;
	for(int i = 1; i <= M; i++) cin >> P[i];
	M++;
	//sort(P, P + M);
	for(int i = 0; i < 1027; i++) last[i] = -1;
	mask[0] = 1023;
	last[mask[0]] = 0;
	for(int i = 1; i < 1027; i++)
	{
		mask[i] = (mask[i - 1] * 2) % 1024;
		for(int j = 0; j < M; j++) if(!(mask[i] & (1 << P[j]))) mask[i] |= 1;
		if(last[mask[i]] != -1)
		{
			int period = i - last[mask[i]];
			N %= period;
			if(mask[N] & 1) cout << "FIRST";
			else cout << "SECOND";
			cout << " PLAYER MUST WIN\n";
			return 0;
		}
		last[mask[i]] = i;
		//cout << i << ' ' << mask[i] << endl;
	}
	assert(false);
}

int main()
{
	int K;
	cin >> K;
	while(K--) main2();
}
