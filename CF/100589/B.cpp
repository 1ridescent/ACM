#include <iostream>

using namespace std;

int pref[1000005];

bool is_valid(int x)
{
	int h = x / 10000;
	int m = (x % 10000) / 100;
	int d = x % 100;
	return (m <= 59 && d <= 59);
}
void pre()
{
	for(int a = 0; a < 10; a++)
		for(int b = 0; b < 10; b++)
			for(int c = 0; c < 10; c++)
			{
				int x = a * 100000 + b * 10000 + c * 1000 + c * 100 + b * 10 + a;
				if(is_valid(x)) pref[x]++;
			}
	for(int i = 1; i < 1000000; i++) pref[i] += pref[i - 1];
}
int input()
{
	int a, b, c;
	char j, k;
	cin >> a >> j >>  b >> k >> c;
	return a * 10000 + b * 100 + c;
}

int main()
{
	ios::sync_with_stdio(false);
	pre();
	int Q;
	cin >> Q;
	while(Q--)
	{
		int s = input();
		int t = input();
		cout << pref[t] - (s == 0 ? 0 : pref[s - 1]) << '\n';
	}
}
