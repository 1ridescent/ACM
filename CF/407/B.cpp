#include <iostream>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define MOD(x) ((x) % mod)

int N;
int P[1010];
ll cycle[1010];

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++) cin >> P[i];
	for(int i = 1; i <= N; i++)
	{
		cycle[i] = 2;
		for(int j = P[i]; j < i; j++)
		{
			cycle[i] = MOD(cycle[i] + cycle[j]);
		}
	}
	ll total = 0;
	for(int i = 1; i <= N; i++) total = MOD(total + cycle[i]);
	cout << total << endl;
	return 0;
}
