#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;

const ll inf = 1e17;

vector<ll> A0, B0;

ll calc(vector<ll>& A, vector<ll>& B)
{
	ll totalB = 0;
	for(int i = 0; i < B.size(); i++) totalB += B[i];
	ll best = inf;
	ll cum = 0;
	for(int i = 0; i < A.size(); i++)
	{
		ll rem = A.size() - i;
		ll total = rem * totalB + cum;
		//cout << i << ' ' << rem << ' ' << cum << endl;
		if(total < best) best = total;
		cum += A[i];
	}
	return best;
}

int main()
{
	ios::sync_with_stdio(0);
	int sA, sB;
	cin >> sA >> sB;
	for(int i = 0; i < sA; i++)
	{
		ll x;
		cin >> x;
		A0.push_back(x);
	}
	for(int i = 0; i < sB; i++)
	{
		ll x;
		cin >> x;
		B0.push_back(x);
	}
	sort(A0.begin(), A0.end());
	sort(B0.begin(), B0.end());
	cout << min(calc(A0, B0), calc(B0, A0));
}
