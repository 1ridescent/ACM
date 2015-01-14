#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int inf = 1e9;

int R, C;
bool B[22][22];
bool B2[22][22];

inline void flip(int r, int c)
{
	B2[r][c] ^= 1;
	B2[r + 1][c] ^= 1;
	B2[r - 1][c] ^= 1;
	B2[r][c + 1] ^= 1;
	B2[r][c - 1] ^= 1;
}

bool check()
{
	for(int r = 1; r <= R; r++)
		for(int c = 1; c <= C; c++)
			if(B2[r][c])
				return false;
	return true;
}

int Try(int cnt)
{
	for(int r = 1; r < R; r++)
	{
		// check residues
		for(int c = 1; c <= C; c++)
			if(B2[r][c])
			{
				flip(r + 1, c);
				cnt++;
			}
	}
	if(check()) return cnt;
	return inf;
}

int main2()
{
	int best = inf;
	for(int b = 0; b < (1 << C); b++)
	{
		memcpy(B2, B, sizeof(B));
		int cnt = 0;
		for(int i = 0; i < C; i++)
		{
			if(b & (1 << i))
			{
				flip(1, i + 1);
				cnt++;
			}
		}
		best = min(best, Try(cnt));
	}
	if(best == inf) cout << "Damaged billboard.\n";
	else cout<< best << "\n";
}

int main()
{
	int tests;cin>>tests;while(tests--)
	{
		R=C=3;
		if(R == 0 && C == 0) break;
		for(int r = 1; r <= R; r++)
			for(int c = 1; c <= C; c++)
			{
				char k;
				cin >> k;
				B[r][c] = (k == '*');
			}

		main2();
	}
}
