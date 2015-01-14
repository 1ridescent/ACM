#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <cstdio>

using namespace std;

void yes()
{
	cout << "YES\n";
	exit(0);
}
void no()
{
	cout << "NO\n";
	exit(0);
}

int N;
int S[25];

int poss[24][1 << 11]; // totalsize, mask

bool possible(int total, int mask)
{
	if(poss[total][mask]) return (poss[total][mask] == 1);

	if(!mask)
	{
		poss[total][mask] = 1;
		return true;
	}
	if(!total)
	{
		poss[total][mask] = -1;
		return false;
	}

	// multi
	for(int b = 0; b < (1 << N); b++)
	{
		if((b & mask) == b)
		{
			for(int t = 1; t < total; t++)
			{
				if(possible(t, b) && possible(total - t, mask ^ b))
				{
					poss[total][mask] = 1;
					return true;
				}
			}
		}
	}

	// single
	int root = 0;
	while(!(mask & (1 << root))) root++;
	printf("root=%d m=%d t=%d ->", root, mask, total);
	mask ^= (1 << root);
	total--;
	printf("m=%d t=%d\n", mask, total);
	if(possible(total, mask))
	{
		poss[total][mask] = 1;
		return true;
	}

	poss[total][mask] = -1;
	return false;
}

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++) cin >> S[i];
	sort(S, S + N, greater<int>());
	if(S[0] != N) no();
	if(N == 1) yes();
	if(S[N - 1] != 1) no();
	int L = 0;
	while(S[N - 1] == 1)
	{
		L++;
		N--;
	}
	if(N > 11) no();
	memset(poss, 0, sizeof(poss));
	for(int t = 0; t <= S[0]; t++) for(int i = 0; i < (1 << N); i++) printf("[t=%d][i=%d] = %d\n", t, i, (int)(possible(t, i)));
	if(possible(S[0], (1 << N) - 1)) yes();
	else no();
}
