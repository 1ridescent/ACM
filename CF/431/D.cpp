#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

typedef unsigned long long ll;

vector<int> binary(ll k)
{
	vector<int> V;
	while(k > 0)
	{
		V.push_back(k % 2);
		k /= 2;
	}
	return V;
}
void print(vector<int> V)
{
	for(int i = 0; i < V.size(); i++) cout << V[i] << ' ';
	cout << endl;
}

ll choose[66][66];
void pre()
{
	memset(choose, 0, sizeof(choose));
	choose[0][0] = 1;
	for(int n = 1; n <= 65; n++)
	{
		choose[n][0] = choose[n][n] = 1;
		for(int k = 1; k < n; k++) choose[n][k] = choose[n - 1][k - 1] + choose[n - 1][k];
	}
}

ll num(ll n, int k)
{
	vector<int> B = binary(n);
	vector<int> ones;
	for(int i = 0; i < B.size(); i++) if(B[i] == 1) ones.push_back(i);
	ll total = (ones.size() == k);
	for(int i = 0; i < ones.size(); i++)
	{
		int add = ones.size() - i - 1;
		int need = k - add;
		if(need < 0) continue;
		//cout << ones[i] << ' ' << need << endl;
		total += choose[ones[i]][need];
	}
	return total;
}

ll compute(ll n, int k)
{
	return num(2 * n, k) - num(n, k);
}

int main()
{
	pre();
	/*while(true)
	{
		ll n;
		int k;
		cin >> n >> k;
		cout << compute(n, k);
	}*/
	ll M;
	int K;
	cin >> M >> K;
	ll low = 0, high = (ll)(1e18) + 1;
	while(low + 1 < high)
	{
		ll mid = (low + high) / 2;
		ll val = compute(mid, K);
		//cout << mid << " -> " << val << endl;
		if(val == M)
		{
			cout << mid << endl;
			return 0;
		}
		else if(val < M)
		{
			low = mid;
		}
		else if(val > M)
		{
			high = mid;
		}
	}
	return -1;
}
