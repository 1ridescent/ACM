#include <bits/stdc++.h>

using namespace std;
const int inf = 1e7;

int N;
int V[100005];
int L[100005], R[100005];
int reach_left[100005], reach_right[100005], size[100005];

void expand(int u, int l, int r)
{
	if(L[reach_left[u]] && V[L[reach_left[u]]] < V[reach_left[u]] && l < V[L[reach_left[u]]])
	{
		expand(L[reach_left[u]], l, V[reach_left[u]]);
		size[u] += size[L[reach_left[u]]];
		reach_left[u] = reach_left[L[reach_left[u]]];
	}
	if(R[reach_right[u]] && V[reach_right[u]] < V[R[reach_right[u]]] && V[R[reach_right[u]]] < r)
	{
		expand(R[reach_right[u]], V[reach_right[u]], r);
		size[u] += size[R[reach_right[u]]];
		reach_right[u] = reach_right[R[reach_right[u]]];
	}
}
int dfs(int u)
{
	if(u == 0) return 0;
	expand(u, -inf, inf);
	//printf("size[%d] = %d\n", u, size[u]);
	return max(size[u], max(dfs(L[u]), dfs(R[u])));
}

int main()
{
	ios::sync_with_stdio(false);
	int tests;
	cin >> tests;
	while(tests--)
	{
		cin >> N;
		for(int i = 1; i <= N; i++)
		{
			cin >> L[i] >> R[i] >> V[i];
			reach_left[i] = reach_right[i] = i;
			size[i] = 1;
		}
		cout << dfs(1) << endl;
	}
}
