#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

bool occ[123][3];

ll dp[123][77];

int M, K;

int main()
{
	cin >>M >> K;
	while(K--)
	{
		double x, y;
		cin >> x >> y;
		occ[1 + int(x)][int(y)] = true;
	}
	dp[0][0] = 1;
	for(int m = 1; m <= M; m++)
	{
		for(int b1 = 0; b1 < 8; b1++) // stick twos
		{
			for(int b2 = 0; b2 < 8; b2++)
			{
				bool bad = false;
				bool pool[3]; // to be filled
				for(int i = 0; i < 3; i++)
					pool[i] = !(b2 & (1 << i));
				for(int i = 0; i < 3; i++)
					if(occ[m][i])
					{
						if(!pool[i]) bad =true;
						pool[i] = false;
					}
				ll add = 0;
				for(int i = 0; i < 3; i++)
				{
					if(b1 & (1 << i)) // must stick
					{
						if(!pool[i]) bad = true;
						pool[i] = false;
					}
				}
				if(bad) continue;
				int s = 1;
				if(pool[0] && pool[1]) s++;
				if(pool[1] && pool[2]) s++;
				//cout << b1 << ' ' << b2 << ' ' << s * dp[m - 1][b1] << endl;
				dp[m][b2] += s * dp[m - 1][b1];
			}
		}
	}
	cout << dp[M][0] << endl;
}
