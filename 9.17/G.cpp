#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

const int inf = 1e9;

int N;
string S;

int curt = 0;
int curx = 250005, cury = 250005;

vector< pair<int, int> > hor[500050];
vector< pair<int, int> > ver[500050];

void insert(int x, int y)
{
	hor[cury].push_back(make_pair(curx, curt));
	ver[curx].push_back(make_pair(cury, curt));
}

int main()
{
	ios::sync_with_stdio(false);
	cin >> N >> S;

	insert(curx, cury);
	for(int i = 0; i < N; i++)
	{
		curt++;
		char c = S[i];
		if(c == 'N') cury++;
		if(c == 'S') cury--;
		if(c == 'E') curx++;
		if(c == 'W') curx--;
		insert(curx, cury);
	}

	for(int i = 0; i < 500050; i++)
	{
		sort(hor[i].begin(), hor[i].end());
		sort(ver[i].begin(), ver[i].end());
	}

	pair<int, pair<int, pair<int, char> > > best = make_pair(inf, make_pair(0, make_pair(0, '.')));
	for(int x = 0; x < 500050; x++)
	{
		for(int i = 1; i < ver[x].size(); i++)
		{
			int y1 = ver[x][i - 1].first, y2 = ver[x][i].first;
			int len = y2 - y1;
			int t1 = ver[x][i - 1].second, t2 = ver[x][i].second;
			int mint = min(t1, t2);
			int maxt = max(t1, t2);
			char c = 'N';
			if(t1 > t2) c = 'S';
			if(abs(t1 - t2) <= 1) continue;
			pair<int, pair<int, pair<int, char> > > res = make_pair(len, make_pair(mint, make_pair(-maxt, c)));
			best = min(best, res);
		}
	}
	for(int y = 0; y < 500050; y++)
	{
		for(int i = 1; i < hor[y].size(); i++)
		{
			int x1 = hor[y][i - 1].first, x2 = hor[y][i].first;
			int len = x2 - x1;
			int t1 = hor[y][i - 1].second, t2 = hor[y][i].second;
			int mint = min(t1, t2);
			int maxt = max(t1, t2);
			char c = 'E';
			if(t1 > t2) c = 'W';
			if(abs(t1 - t2) <= 1) continue;
			pair<int, pair<int, pair<int, char> > > res = make_pair(len, make_pair(mint, make_pair(-maxt, c)));
			best = min(best, res);
		}
	}

	cout << best.first << ' ' << best.second.first << ' ' << -best.second.second.first << ' ' << best.second.second.second << endl;

}
