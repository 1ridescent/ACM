#include <iostream>
#include <cstring>

using namespace std;

int val[10000010];

bool isprime[10000010];

void pre()
{
	memset(val, 0, sizeof(val));
	memset(isprime, -1, sizeof(isprime));
	for(int i = 2; i <= 10000005; i++)
	{
		if(isprime[i])
		{
			for(int j = i + i; j <= 10000005; j += i)
				isprime[j] = false;
			for(int j = i; j <= 10000005; j += i)
				val[j]++;
		}
	}
}

int main()
{
	pre();
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		int A, B, K;
		cin >> A >> B >> K;
		int res = 0;
		for(int i = A; i <= B; i++)
		{
			if(val[i] == K)
				res++;
		}
		cout << "Case #" << t << ": " << res << endl;
	}
}
