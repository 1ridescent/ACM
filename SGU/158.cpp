#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int L;
int M, P[305];
int N, D[305];

const int inf = 100000000;

int main()
{
	cin >> L;
	L *= 2;
	cin >> M;
	for(int i = 0; i < M; i++)
	{
		cin >> P[i];
		P[i] *= 2;
	}
	cin >> N;
	D[0] = 0;
	for(int i = 1; i < N; i++)
	{
		cin >> D[i];
		D[i] *= 2;
	}
	sort(P, P + M);
	int best = -1, besto;
	for(int o = 0; o <= L - D[N - 1]; o++)
	{
		//set<int> s;
		//for(int i = 0; i < N; i++) s.insert(D[i] + o);
		int total = 0;
		int p = 0;
		for(int i = 0; i < M; i++)
		{
			while(p < N - 1 && (D[p] + o) < P[i]) p++;
			total += min(p > 0 ? abs(P[i] - (D[p - 1] + o)) : inf, abs(P[i] - (D[p] + o)));
		}
		/*for(int i = 0; i < M; i++)
		{
			set<int>::iterator it = s.lower_bound(P[i]);
			int add;
			if(it == s.end())
			{
				it--;
				add = abs(P[i] - *it);
			}
			else
			{
				add = abs(P[i] - *it);
				if(it != s.begin())
				{
					it--;
					add = min(add, abs(P[i] - *it));
				}
			}
			total += add;
		}*/
		//cout << o << ": " << total << endl;
		if(total > best)
		{
			best = total, besto = o;
		}
	}
	cout << besto / 2.0 << ' ' << best / 2.0;
}
