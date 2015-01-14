#include <iostream>
#include <cstring>

using namespace std;

int N;
char dir[1005][14][4100];
short prev_p[1005][14][4100];
short prev_l[1005][14][4100];

int log2(int x)
{
	for(int i = 0; i < 17; i++)
		if((1 << i) == x)
			return i;
	return -1;
}

inline void assign(int i, int p, int l, char c, int p2, int l2)
{
	//cout << i << ' ' << p << ' ' << l << " : " << c << endl;
	dir[i][p][l] = c;
	prev_p[i][p][l] = p2;
	prev_l[i][p][l] = l2;
}

int main2()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
		for(int p = 0; p <= 13; p++)
			for(int l = 0; l <= (1 << p) && l < 4100; l++)
				dir[i][p][l] = 0;

	int x;
	cin >> x;
	dir[1][log2(x)][0] = 'l';

	int sum = x;
	for(int i = 2; i <= N; i++)
	{
		cin >> x;
		for(int p = log2(x); (1 << p) <= 4096; p++)
		{
			int b = (1 << p);
			for(int l = 0; l <= b && l + b <= sum; l++)
			{
				if(!dir[i - 1][p][l]) continue;
				int r = sum - l - b;
				if(r > b) continue;

				// left ?
				if((l & (x - 1)) == 0)
				{
					int l2 = l + x;
					if(l2 == b)
					{
						assign(i, p + 1, 0, 'l', p, l);
						//dir[i][p + 1][0] = 'l';
						//prev_p[i][p + 1][0] = b;
						//prev_l[i][p + 1][0] = l;
						//cout << i << ' ' << b << ' ' << l << endl;
					}
					else
					{
						assign(i, p, l2, 'l', p, l);
						//dir[i][p][l2] = 'l';
						//prev_p[i][p][l2] = b;
						//prev_l[i][p][l2] = l;
						//cout << i << ' ' << b << ' ' << l << endl;
					}
				}

				// right ?
				if((r & (x - 1)) == 0)
				{
					int r2 = r + x;
					if(r2 == b)
					{
						assign(i, p + 1, l, 'r', p, l);
						//dir[i][p + 1][l] = 'r';
						//prev_p[i][p + 1][l] = b;
						//prev_l[i][p + 1][l] = l;
						//cout << i << ' ' << b << ' ' << l << endl;
					}
					else
					{
						assign(i, p, l, 'r', p, l);
						//dir[i][p][l] = 'r';
						//prev_p[i][p][l] = b;
						//prev_l[i][p][l] = l;
						//cout << i << ' ' << b << ' ' << l << endl;
					}
				}
			}
		}
		for(int p = 0; (1 << p) < x; p++)
		{
			int b = (1 << p);
			int lr = sum - b;
			if(lr < 0) continue;
			if(lr > b) continue;
			if(dir[i - 1][p][0])
			{
				assign(i, log2(x), 0, 'l', p, 0);
				//dir[i][log2(x)][0] = 'l';
				//prev_p[i][log2(x)][0] = b;
				//prev_l[i][log2(x)][0] = 0;
				//cout << i << ' ' << b << ' ' << 0 << endl;
			}
			if(dir[i - 1][p][lr])
			{
				assign(i, log2(x), lr + b, 'r', p, lr);
				//dir[i][log2(x)][lr + b] = 'r';
				//prev_p[i][log2(x)][lr + b] = b;
				//prev_l[i][log2(x)][lr + b] = lr;
				//cout << i << ' ' << b << ' ' << lr << endl;
			}
		}

		sum += x;
	}

	for(int p = 0; p <= 13; p++)
	{
		if((1 << p) == sum)
		{
			if(dir[N][p][0])
			{
				string s;
				int l = 0;
				for(int i = N; i >= 1; i--)
				{
					s = dir[i][p][l] + s;
					int p2 = prev_p[i][p][l];
					l = prev_l[i][p][l];
					p = p2;
				}
				cout << s << '\n';
				return 0;
			}
		}
	}
	cout << "no\n";
	return 0;
}

int main()
{
	int T;
	cin >> T;
	while(T--) main2();
}
