#include <cstdio>
#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
#include <cmath>

using namespace std;

struct problem
{
	int I, A, L, O;
};
struct team
{
	int T, Z, V, C;
};
struct score
{
	int tid, num, pen;
};

int numprobs, numteams, numselect, length;

bool cmprank(score a, score b)
{
	if(a.num > b.num) return true;
	if(a.num < b.num) return false;
	if(a.pen < b.pen) return true;
	if(a.pen > b.pen) return false;
	return a.tid < b.tid;
}
vector<score> ranking;

inline int divi(int p, int q)
{
	return (p + q - 1) / q;
}
int Tj, Zj, Vj, Cj;
int actual(problem& a)
{
	return max(a.I - Tj, 0) + divi(a.A, Zj + Cj) + divi(a.L, Vj);
}
bool cmpprob(problem a, problem b)
{
	int expa = divi(a.I, a.O) + max(divi(a.A, Cj), 5);
	int expb = divi(b.I, b.O) + max(divi(b.A, Cj), 5);
	if(expa < expb) return true;
	if(expa > expb) return false;
	int acta = max(a.I - Tj, 0) + divi(a.A, Zj + Cj) + divi(a.L, Vj);
	int actb = max(b.I - Tj, 0) + divi(b.A, Zj + Cj) + divi(b.L, Vj);
	if(acta < actb) return true;
	return false;
}
void get_score(team& T, vector<problem>& P, score& S)
{
	Tj = T.T, Zj = T.Z, Vj = T.V, Cj = T.C;
	sort(P.begin(), P.end(), cmpprob);

	int totaltime = 0;
	int totalprobs = 0;
	int totalpen = 0;
	for(int i = 0; i < P.size(); i++)
	{
		if(Tj + Cj <= P[i].I - P[i].O) continue;
		totaltime += actual(P[i]);
		if(totaltime > length) break;
		totalprobs++;
		totalpen += totaltime;
	}
	S.num = totalprobs;
	S.pen = totalpen;
}
int team1rank(vector<problem>& problems, vector<team>& teams)
{
	ranking.clear();
	for(int ti = 0; ti < teams.size(); ti++)
	{
		score s;
		s.tid = ti;
		get_score(teams[ti], problems, s);
		ranking.push_back(s);
	}
	sort(ranking.begin(), ranking.end(), cmprank);
	for(int i = 0; i < ranking.size(); i++)
	{
		if(ranking[i].tid == 0) return i;
	}
}

int bestrank = 134134134, bestmask = 1343543;
int main()
{
	freopen("unfair.in", "r", stdin); freopen("unfair.out", "w", stdout);

	cin >> numprobs >> numselect >> numteams >> length;

	vector<problem> P(numprobs);
	vector<team> T(numteams);
	for(int i = 0; i < numprobs; i++)
	{
		cin >> P[i].I >> P[i].A >> P[i].L >> P[i].O;
	}
	for(int i = 0; i < numteams; i++)
	{
		cin >> T[i].T >> T[i].Z >> T[i].V >> T[i].C;
	}
	for(int mask = 0; mask < (1 << numprobs); mask++)
	{
		int bitcnt = 0;
		for(int i = 0; i < numprobs; i++)
		{
			if(mask & (1 << i)) bitcnt++;
		}
		//cout << "bitcnt = " << bitcnt << endl;
		if(bitcnt == numselect)
		{
			vector<problem> P2;
			for(int i = 0; i < numprobs; i++)
			{
				if(mask & (1 << i))
				{
					P2.push_back(P[i]);
				}
			}
			int rank = team1rank(P2, T);
			//cout << "rank = " << rank << endl;
			if(rank < bestrank)
			{
				bestrank = rank;
				bestmask = mask;
			}
		}
	}
	bool space = false;
	for(int i = 0; i < numprobs; i++)
	{
		if(bestmask & (1 << i))
		{
			if(space) cout << ' ';
			cout << i + 1;
			space = true;
		}
	}
	cout << endl;
}
