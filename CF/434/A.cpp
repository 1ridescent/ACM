#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;
const ll INF = (1LL << 60);

ll get_min(vector<int> V)
{
	if(V.empty()) return 0;
	sort(V.begin(), V.end());
	int m = V.size() / 2;
	ll total = 0;
	for(int i = 0; i < V.size(); i++) total += abs(V[i] - V[m]);
	return total;
}

int N;
vector<ll> A;
ll original[100005];
vector<int> neighbors[100005];

int main()
{
	cin >> N >> N;
	for(int i = 0; i < N; i++)
	{
		ll x;
		cin >> x;
		if(A.empty() || x != A.back()) A.push_back(x);
	}
	N = A.size();
	memset(original, 0, sizeof(original));
	ll total = 0;
	for(int i = 0; i < N; i++)
	{
		if(i > 0)
		{
			original[A[i]] += abs(A[i] - A[i - 1]);
			neighbors[A[i]].push_back(A[i - 1]);
		}
		if(i < N - 1)
		{
			original[A[i]] += abs(A[i] - A[i + 1]);
			neighbors[A[i]].push_back(A[i + 1]);
		}
		if(i > 0) total += abs(A[i] - A[i - 1]);
	}
	//cout << total << endl;

	ll best = INF;
	for(int x = 1; x <= 100000; x++)
	{
		best = min(best, total - original[x] + get_min(neighbors[x]));
	}
	cout << best;
}
