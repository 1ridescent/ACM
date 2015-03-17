#include <bits/stdc++.h>

using namespace std;

int N, K, M;
int C[22], P[22];
int T[1 << 16];
double S[22][1 << 16]; // [num good][used]

int main()
{
	int tests;
	cin >> tests;
	while(tests--)
	{
		cin >> N >> K >> M;
		for(int i = 0; i < N; i++) cin >> C[i] >> P[i];
		for(int b = 0; b < (1 << N); b++)
		{
			T[b] = 0;
			for(int i = 0; i < N; i++)
				if(b & (1 << i))
					T[b] += C[i];
		}
		for(int b = 0; b < (1 << N); b++)
			S[K][b] = 1.0;
		for(int c = K - 1; c >= 0; c--)
			for(int b = (1 << N) - 1; b >= 0; b--)
			{
				S[c][b] = 0.0;
				for(int i = 0; i < N; i++)
					if(!(b & (1 << i)))
					{
						int b2 = (b | (1 << i));
						if(T[b2] <= M)
							S[c][b] = max(S[c][b], (S[c + 1][b2] * P[i] + S[c][b2] * (100 - P[i])) / 100.0);
					}
			}
		printf("%.9f\n", S[0][0]);
	}
}
