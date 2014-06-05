#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
int G[105];
int total = 0;

int max_elt(int k)
{
	int best = 0, besti = -1;
	for(int i = 1; i <= N; i++)
	{
		if(i == k) continue;
		if(G[i] > best) best = G[i], besti = i;
	}
	return besti;
}
int min_elt(int k)
{
	int best = 123123123, besti = -1;
	for(int i = 1; i <= N; i++)
	{
		if(i == k) continue;
		if(G[i] == 0) continue;
		if(G[i] < best) best = G[i], besti = i;
	}
	return besti;
}

int main()
{
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		cin >> G[i];
		total += G[i];
	}
	cout << total / 2 << endl;
	int cur = max_elt(-1);
	while(total)
	{
		int m = max_elt(cur);
		if(m != -1 && 2 * G[m] == total) // end
		{
			cout << m << ' ' << cur << '\n';
			G[m]--, G[cur]--;
			for(int i = 1; i <= N; i++)
			{
				if(i == m) continue;
				while(G[i]--) cout << m << ' ' << i << '\n';
			}
			return 0;
		}
		if(G[cur] == 1)
		{
			int next = max_elt(cur);
			cout << next << ' ' << cur << '\n';
			G[cur]--, G[next]--;
			total -= 2;
			cur = next;
		}
		else
		{
			int next = min_elt(cur);
			cout << cur << ' ' << next << '\n';
			G[cur]--, G[next]--;
			total -= 2;
		}
	}/*

	while(true)
	{
		int m = max_elt();
		if(m == -1) return 0;
		if(G[m] > G[winner])
		{
			cout << m << ' ' << winner << '\n';
			G[m]--, G[winner]--;
			winner = m;
		}
		else
		{
			int temp = G[winner];
			G[winner] = 123123123;
			m = min_elt();
			G[winner] = temp;
			cout << winner << ' ' << m << '\n';
			G[m]--, G[winner]--;
		}
		for(int i = 1; i <= N; i++) cout << G[i] << ' '; cout << endl;
	}*/
}
