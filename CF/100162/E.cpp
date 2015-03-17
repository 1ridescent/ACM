#include <bits/stdc++.h>

using namespace std;

#define a first
#define b second
#define SQ(x) ((x) * (x))
#define ODD(x) (((x) % 2) != 0)
#define EVEN(x) (((x) % 2) == 0)

vector<int> ans;
void add(int n1, int m1, int n2, int m2)
{
	ans.push_back(n1);
	ans.push_back(m1);
	ans.push_back(n2);
	ans.push_back(m2);
}
void solve(int N, int M, int P)
{
	ans.clear();
	if(P == 1)
		for(int m = 0; m < M; m += 2)
			for(int n = 0; n < N; n++)
				add(n, m, n, m + 1);
	else if(P == 2)
	{
		if(ODD(N * M))
		{
			add(0, 0, 1, 1);
			for(int m = 0; m < M; m++)
				add(0, m, 1, m);
			for(int m = 1; m < M - 1; m += 2)
				add(0, m, 0, m + 1);
			for(int m = 2; m < M - 1; m += 2)
				add(1, m, 1, m + 1);
			add(1, 0, 2, 0);
			add(1, M - 1, 2, M - 1);
			for(int n = 3; n < N - 1; n += 2)
			{
				add(n, 0, n + 1, 0);
				add(n, M - 1, n + 1, M - 1);
			}
			for(int n = 2; n < N; n++)
				for(int m = 1; m < M; m++)
					add(n, m - 1, n, m);
		}
		else
		{
			for(int m = 0; m < M; m += 2)
			{
				add(0, m, 0, m + 1);
				add(N - 1, m, N - 1, m + 1);
			}
			for(int m = 0; m < M; m++)
				for(int n = 1; n < N; n++)
					add(n - 1, m, n, m);
		}
	}
	else if(P == 3)
	{
		for(int n = 1; n < N; n++)
		{
			add(n - 1, 0, n, 0);
			add(n - 1, M - 1, n, M - 1);
		}
		for(int m = 1; m < M; m++)
		{
			add(0, m - 1, 0, m);
			add(N - 1, m - 1, N - 1, m);
		}
		if(N == 3)
		{
			if(M == 6)
			{
				for(int m = 1; m <= 2; m++)
				{
					add(0, m - 1, 1, m);
					add(2, m - 1, 1, m);
				}
				for(int m = 3; m < M - 1; m++)
				{
					add(0, m + 1, 1, m);
					add(2, m + 1, 1, m);
				}
				add(1, 2, 2, 2);
				add(1, 3, 0, 3);
				add(0, 2, 2, 3);
				for(int m = 0; m < M - 1; m += 2)
					if(m != 2)
						add(1, m, 1, m + 1);
			}
			else
			{
				for(int m = 1; m < M - 1; m++)
				{
					if(m <= 2) add(1, m, 0, m - 1);
					if(m <= 3) add(1, m, 2, m - 1);
					if(m >= M - 3) add(1, m, 0, m + 1);
					if(m >= M - 4) add(1, m, 2, m + 1);
					if(2 <= m && m <= M - 3)
						add(0, m, 1, m);
					if(3 <= m && m <= M - 4)
						add(1, m, 2, m);
				}
				add(1, 0, 1, 1);
				add(1, M - 2, 1, M - 1);
				for(int m = 4; m < M - 4; m += 2)
					add(1, m, 1, m + 1);
			}
		}
		else if(N == 4)
		{
			assert(M == 4);
			int a[4] = {0, 0, 3, 3};
			for(int n = 1; n <= 2; n++)
				for(int m = 1; m <= 2; m++)
				{
					add(n, m, a[n], m);
					add(n, m, n, a[m]);
					add(n, m, a[n], a[m]);
				}
		}
		else if(N == 5)
		{
			for(int n = 1; n <= 3; n++)
			{
				add(n, 0, n, 1);
				add(n, M - 2, n, M - 1);
			}
			add(0, 0, 1, 1);
			add(1, 1, 2, 1);
			add(2, 1, 2, 2);
			add(0, 1, 1, 2);
			add(N - 1, 0, N - 2, 1);
			add(N - 2, 1, N - 1, 1);
			add(0, M - 1, 1, M - 2);
			add(1, M - 2, 2, M - 2);
			add(2, M - 2, 2, M - 3);
			add(0, M - 2, 1, M - 3);
			add(N - 1, M - 1, N - 2, M - 2);
			add(N - 2, M - 2, N - 1, M - 2);
			for(int m = 2; m < M - 2; m++)
				for(int n = 1; n < N; n++)
					add(n - 1, m, n, m);
			for(int m = 2; m <= M - 4; m++)
			{
				if(EVEN(m))
					add(3, m, 3, m + 1);
				else
				{
					add(1, m, 1, m + 1);
					add(2, m, 2, m + 1);
				}
			}
		}
		else
		{
			add(0, 0, 1, 1);
			add(N - 1, 0, N - 2, 1);
			add(0, M - 1, 1, M - 2);
			add(N - 1, M - 1, N - 2, M - 2);
			for(int m = 0; m < M; m += 2)
				for(int n = 1; n <= N - 2; n++)
					if(!((m != 0 && m != M - 2) && (n == 2 || n == N - 3)))
						add(n, m, n, m + 1);
			for(int m = 1; m < M - 1; m += 2)
			{
				add(2, m, 2, m + 1);
				add(N - 3, m, N - 3, m + 1);
			}
			for(int m = 1; m < M - 1; m++)
				for(int n = 0; n < N - 1; n++)
					if(!((m == 1 || m == M - 2) && (n == 1 || n == N - 3)))
						add(n, m, n + 1, m);
		}
	}
	else assert(false);
}

int main()
{
	int N, M, P, test = 0;
	while(cin >> N >> M >> P)
	{
		printf("Case %d: ", ++test);
		if(P > 3 || (P != 2 && ODD(N * M)) || (P == 2 && min(N, M) == 1) || (P == 3 && (min(N, M) <= 2 || N * M == 12)))
		{
			printf("-1\n");
			continue;
		}
		bool swapped = false;
		if(EVEN(N * M) && (ODD(M) || (EVEN(N) && N < M)))
		{
			swap(N, M);
			swapped = true;
		}
		solve(N, M, P);
		double total = 0;
		for(int i = 0; i < ans.size(); i += 4)
			total += sqrt(SQ(ans[i] - ans[i + 2]) + SQ(ans[i + 1] - ans[i + 3]));
		printf("%.9f\n", total);
		cout << ans.size() / 4 << '\n';
		for(int i = 0; i < ans.size(); i += 4)
		{
			if(!swapped) printf("%d %d %d %d\n", ans[i], ans[i + 1], ans[i + 2], ans[i + 3]);
			else printf("%d %d %d %d\n", ans[i + 1], ans[i], ans[i + 3], ans[i + 2]);
		}
	}
}
