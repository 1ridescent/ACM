#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include <deque>

using namespace std;

string SS;
char S[1000005];
char T[1000005];
int N, M;

int next[1000005];
int prev[1000005];

bool vis[1000005];

deque<int> order;
deque<int> path;
deque<int> cycle;

int main()
{
	ios::sync_with_stdio(false);
	cin >> SS;
	N = SS.size();
	for(int i = 0; i < N; i++) S[i] = SS[i];
	cin >> M;
	while(M--)
	{
		int K, D;
		cin >> K >> D;

		//cout << "query " << K << ' ' << D << endl;

		order.clear();
		for(int b = 0; b < D; b++)
			for(int i = b; i < K; i += D)
				order.push_back(i);

		for(int i = 0; i < order.size(); i++)
		{
			next[order[i]] = i - 1;
			if(i > 0)
				prev[i - 1] = next[order[i]];
			//printf("%d -> %d\n", order[i], i - 1);
		}

		for(int i = 0; i < K; i++) vis[i] = false;

		// process path
		path.clear();
		for(int i = K - 1; i != -1; i = next[i])
		{
			vis[i] = true;
			path.push_front(i);
		}
		int P = path.size();

		for(int i = K; i < N; i++) path.push_back(i);

		//for(int i = 0; i < path.size(); i++) cout << path[i] << ' '; cout << endl;

		for(int i = 0; i < N - K; i++)
			T[i] = S[path[i]];

		for(int i = 0; i < P; i++)
		{
			//printf("T[%d] = S[%d]\n", N-K+path[i], N-P+i);
			T[N - K + path[i]] = S[path[path.size() - P + i]];
		}

		/*for(int i = 0; i < path.size(); i++)
			T[i] = S[path[i]];

		for(int i = K; i < N - path.size(); i++)
			T[i - K + path.size()] = S[i];

		for(int i = 0; i < path.size(); i++)
			T[N - K + path[i] + 1] = S[N - path.size() + i];*/

		// process cycles
		for(int i = 0; i < K; i++)
		{
			if(vis[i]) continue;
			cycle.clear();
			{
				int j = i;
				do
				{
					//printf("cycle %d\n", j);
					vis[j] = true;
					cycle.push_back(j);
					j = next[j];
				}
				while(j != i);
			}

			if(cycle.empty()) continue;

			int iters = N - K;
			for(int j = 0; j < cycle.size(); j++)
			{
				T[N - K + cycle[(j + iters) % cycle.size()]] = S[cycle[j]];
			}
		}

		for(int i = 0; i < N; i++) S[i] = T[i];
		// last move
		for(int i = 0; i < K; i++)
			T[N - K + next[i] + 1] = S[N - K + i];

		for(int i = 0; i < N; i++) cout << T[i]; cout << '\n';
		for(int i = 0; i < N; i++) S[i] = T[i];
	}
	return 0;
}
