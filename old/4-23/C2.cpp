#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N, M;
int otherN = 0;
int G[105];
int cur = -1, freq = 0;

int G2[105];

vector<int> res;

int check()
{
	for(int i = 1; i <= M; i++) G2[i] = G[i];
	int cur2 = cur, freq2 = freq;
	while(true)
	{
		int maxother = 0, maxid = -1;
		for(int i = 2; i <= M; i++)
		{
			//if(freq2 > 0 && i == cur2) continue;
			if(G2[i] > maxother)
			{
				maxother = G2[i];
				maxid = i;
			}
		}
		//cout << maxid << maxother << ' ';
		if(maxid == -1)
		{
			if(freq2 == 0) return G2[1];
			G2[1]--;
			freq2--;
			if(G2[1] == 0) return -1;
		}
		else
		{
			if(freq2 > 0)
			{
				if(cur2 == maxid) freq2++;
				else freq2--;
				G2[maxid]--;
			}
			else
			{
				cur2 = maxid;
				freq2 = 1;
				G2[maxid]--;
			}
		}
	}
}

int main()
{
	cin >> N >> M;
	for(int i = 1; i <= M; i++) cin >> G[i];
	for(int i = 0; i < 123; i++)
	{
		int c = check();
		//cout << endl; for(int i = 1; i <= M; i++) cout << G[i] << ' '; cout << endl;
		//cout << "cur = " << cur << ", freq = " << freq << endl;
		//cout << "check " << c << endl;
		if(c == -1)
		{
			cout << "NO\n";
			return 0;
		}
		for(int i = 1; i <= M; i++)
		{
			if(G[i] > 0)
			{
				int cur0 = cur, freq0 = freq;
				if(freq == 0) cur = i, freq = 1;
				else
				{
					if(cur == i) freq++;
					else freq--;
				}
				G[i]--;
				if(check() == c)
				{
					//cout << "got " << i << endl;
					res.push_back(i);
					break;
				}
				cur = cur0;
				freq = freq0;
				G[i]++;
			}
		}
	}
	cout << "YES\n";
	cout << check() << '\n';
	for(int i = 0; i < res.size(); i++) cout << res[i] << '\n';
	for(int i = 0; i < G[1]; i++) cout << 1 << '\n';
}
