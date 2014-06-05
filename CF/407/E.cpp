#include <iostream>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

typedef long long ll;

ll N, K, D;
ll A[200200];
ll diff[200200], mod[200200], uni[200200];

#define FIRST(S) ((S).begin())
#define LAST(S) (--(S).end())
#define MOD(x, y) ((((x) % (y)) + (y)) % (y))

int main()
{
	cin >> N >> K >> D;
	for(int i = 1; i <= N; i++) cin >> A[i];

	if(D == 0)
	{
		int cnt = 1;
		int best = -1, bestl;
		for(int i = N - 1; i >= 1; i--)
		{
			if(A[i] == A[i + 1]) cnt++;
			else cnt = 1;
			if(cnt > best)
			{
				best = cnt;
				bestl = i;
			}
		}
		cout << bestl << ' ' << bestl + best - 1 << endl;
		return 0;
	}

	{
		set< pair<ll, int> > cur;
		int r = 1;
		for(int l = 1; l <= N; l++)
		{
			while(r <= N)
			{
				cur.insert( make_pair(A[r], r) );
				if(!cur.empty() && LAST(cur)->first - FIRST(cur)->first > (r - l + K) * D)
				{
					cur.erase( make_pair(A[r], r) );
					break;
				}
				else r++;
			}
			diff[l] = r;

			cur.erase( make_pair(A[l], l) );
		}
	}

	{
		mod[N] = N + 1;
		for(int r = N - 1; r >= 1; r--)
		{
			if(MOD(A[r], D) == MOD(A[r + 1], D)) mod[r] = mod[r + 1];
			else mod[r] = r + 1;
		}
	}

	{
		set<ll> cur;
		int r = 1;
		for(int l = 1; l <= N; l++)
		{
			while(r <= N)
			{
				if(cur.count(A[r])) break;
				else
				{
					cur.insert(A[r]);
					r++;
				}
			}
			uni[l] = r;

			cur.erase(A[l]);
		}
	}

	int best = -1, bestl;
	for(int l = 1; l <= N; l++)
	{
		cout << l << ' ' << diff[l] << ' ' << mod[l] << ' ' << uni[l] << endl;
		int val = min( min(diff[l], mod[l]), uni[l] ) - l;
		if(val > best)
		{
			best = val;
			bestl = l;
		}
	}

	cout << bestl << ' ' << bestl + best - 1 << endl;
	return 0;
}
