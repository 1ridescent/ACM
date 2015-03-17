#include <iostream>
#include <set>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

int N, M;
ll K, P;
ll H[100005], A[100005];

ll cur[100005];
set<pair<ll, int> > Short; // shorter than P, indexed by # days left
set<pair<ll, int> > Tall; // taller than P, ordered by mod P
bool Try(ll goal)
{
	for(int i = 1; i <= N; i++)
	{
		cur[i] = H[i] - goal;
		if(cur[i] >= P)
			tall.push_back(i);
		else
			small.insert(make_pair())
	}
	for(int m = 0; m < M; m++)
	{

	}
}

int main()
{
	cin >> N >> M >> K >> P;

}
