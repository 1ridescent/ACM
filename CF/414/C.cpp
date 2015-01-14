#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include <set>

using namespace std;

typedef long long ll;

int N, P;
map<int, map<int, int> > pairs;
vector<int> doubles[300100];
ll num[300100]; // [i]: number satisfied with i
vector<int> freq[300100];
ll cumul[300100];

int main()
{
	memset(num, 0, sizeof(num));
	memset(cumul, 0, sizeof(cumul));
	ios::sync_with_stdio(false);
	cin >> N >> P;
	for(int i = 1; i <= N; i++)
	{
		int a, b;
		cin >> a >> b;
		num[a]++, num[b]++;
		if(pairs[a][b] == 0)
		{
			doubles[a].push_back(b);
			doubles[b].push_back(a);
		}
		pairs[a][b]++;
		pairs[b][a]++;
	}
	for(int i = 1; i <= N; i++)
	{
		freq[num[i]].push_back(i);
	}
	for(int i = 0; i <= N; i++) cumul[i] = freq[i].size();
	for(int i = N - 1; i >= 0; i--) cumul[i] += cumul[i + 1];
	ll total = 0;
	for(int a = 1; a <= N; a++)
	{
		ll numposs = (num[a] >= P ? N : cumul[P - num[a]]);
		if(num[a] + num[a] >= P) numposs--;
		for(int i = 0; i < doubles[a].size(); i++)
		{
			int b = doubles[a][i];
			if(num[a] + num[b] >= P)
			{
				numposs--;
				if(num[a] + num[b] - pairs[a][b] >= P) numposs++;
			}
		}
		total += numposs;
	}
	cout << total / 2 << endl;
	return 0;
}
