#include <iostream>
#include <cstring>
#include <queue>

using namespace std;

int N;
int A[2][13][13];

int poss[13][1 << 13][13]; // [i][queue] -> [j] ?
int num[13][1 << 13];

queue<pair<int, int> > Q;
bool test(int len) // queue is len
{
	memset(poss, 0, sizeof(poss));
	memset(num, 0, sizeof(num));

	for(int i = 0; i < N; i++)
		for(int b = 0; b < (1 << len); b++)
		{
			int t = !!(b & (1 << (len - 1)));
			for(int j = 0; j < N; j++)
				if(A[t][i][j])
				{
					//cout << i << " -> " << t << " -> " << j << endl;
					//cout << "t = " << t << " b = " << b << endl;
					//cout << "len = " << len << ": + " << i << ' ' << b << ' ' << j << endl;
					poss[i][b][j] = true;
					num[i][b]++;
				}
		}

	for(int i = 0; i < N; i++)
		for(int b = 0; b < (1 << len); b++)
		{
			if(num[i][b] == 0) // dead
			{
				Q.push(make_pair(i, b));
			}
		}

	bool res = false;
	while(!Q.empty())
	{
		int j0 = Q.front().first, b0 = Q.front().second;
		//cout << j0 << ' ' << b0 << " dead" << endl;
		Q.pop();
		if(j0 == 0) res = true;
		for(int i = 0; i < N; i++)
		{
			for(int t = 0; t < 2; t++)
				if(A[t][i][j0])
				{
					int b = b0 / 2 + (t << (len - 1));
					if(poss[i][b][j0])
					{
						poss[i][b][j0] = false;
						num[i][b]--;
						if(num[i][b] == 0)
							Q.push(make_pair(i, b));
					}
				}
		}
	}
	return res;
}

int main2()
{
	cin >> N;
	for(int t = 0; t < 2; t++)
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				cin >> A[t][i][j];
	int best = 0;
	for(int l = N; l >= 1; l--)
	{
		if(!test(l)) best = l;
	}
	cout << best << endl;
	return 0;
}

int main()
{
	int T;
	cin >> T;
	while(T--) main2();
	return 0;
}
