#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int N;
char A[55][55];

bool vis[55][55][55];
queue<int> Q;
int bfs(int s1, int s2, int s3)
{
	while(!Q.empty()) Q.pop();
	memset(vis, 0, sizeof(vis));
	vis[s1][s2][s3] = true;
	Q.push(s1); Q.push(s2); Q.push(s3); Q.push(0);
	while(!Q.empty())
	{
		int S[4];
		S[1] = Q.front(); Q.pop(); S[2] = Q.front(); Q.pop(); S[3] = Q.front(); Q.pop();
		int d = Q.front(); Q.pop();
		if(S[1] == S[2] && S[2] == S[3]) return d;

		for(int i = 1; i <= 3; i++)
		{
			int j = i + 1;
			if(j > 3) j -= 3;
			int k = j + 1;
			if(k > 3) k -= 3;
			for(int t = 1; t <= N; t++)
			{
				if(A[S[i]][t] != A[S[j]][S[k]]) continue;
				int T[4];
				T[1] = S[1], T[2] = S[2], T[3] = S[3];
				T[i] = t;
				if(vis[T[1]][T[2]][T[3]]) continue;
				vis[T[1]][T[2]][T[3]] = true;
				Q.push(T[1]); Q.push(T[2]); Q.push(T[3]); Q.push(d + 1);
			}
		}
	}
	return -1;
}

int main()
{
	while(true)
	{
		cin >> N;
		if(!N) break;
		int s1, s2, s3;
		cin >> s1 >> s2 >> s3;
		for(int i = 1; i <= N; i++)
			for(int j = 1; j <= N; j++)
				cin >> A[i][j];
		int ans = bfs(s1, s2, s3);
		if(ans == -1) cout << "impossible\n";
		else cout << ans << '\n';
	}
}
