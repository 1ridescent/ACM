#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;
const ll mod = 1000000007;
#define MOD(x) ((x) % mod)

const int MAX = 100010;

vector<int> factors[MAX];
ll val_added[MAX];
void pre()
{
	for(int i = 1; i <= MAX; i++)
	{
		for(int j = 2*i; j <= MAX; j += i) factors[j].push_back(i); // exclude self
	}
	for(int i = 1; i <= MAX; i++)
	{
		val_added[i] = i;
		for(int j = 0; j < factors[i].size(); j++) val_added[i] = MOD(val_added[i] - val_added[factors[i][j]]);
	}
}

int dim[505];

int main()
{
	pre();
	int T;
	cin >> T;
	for(int t = 0; t < T; t++)
	{
		int K;
		cin >> K;
		for(int i = 0; i < K; i++) cin >> dim[i];
		ll total = 0;
		for(int g = 1; g <= 100000; g++)
		{
			ll cur = 1;
			for(int i = 0; i < K; i++) cur = MOD(cur * (dim[i]/g));
			total = MOD(total + val_added[g] * cur);
		}
		cout << total << endl;
	}
	return 0;
}
