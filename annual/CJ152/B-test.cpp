#include <bits/stdc++.h>

using namespace std;

int N;
double V, X;
double rate, temp;

#define id 11

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cin >> N >> V >> X;
		if(t == id) cout << 1 << endl;
		if(t == id) cout << N << ' ' << V << ' ' << X << endl;
		while(N--)
		{
			cin >> rate>> temp;
			if(t == id) cout << rate << ' ' << temp << endl;
		}
	}
}
