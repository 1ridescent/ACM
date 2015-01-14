#include <iostream>
#include <map>
#include <vector>
#include <cstring>

using namespace std;

int N;
map<string, int> id;
string inv[13];

int dep[13][13];
double wt[13];
int wt2[13];

int main()
{
	while(true)
	{
		cin >> N;
		if(!N) break;
		id.clear();
		for(int i = 1; i <= N; i++)
		{
			string s;
			cin >> s;
			id[s] = i;
			inv[i] = s;
		}

		memset(dep, 0, sizeof(dep));
		for(int i = 1; i < N; i++)
		{
			string a, b, c;
			int v;
			cin >> a >> b >> v >> c;
			dep[id[a]][id[c]] = v;
			//cout << id[a] << ' ' << id[c] << endl;
		}

		memset(wt, 0, sizeof(wt));
		wt[1] = 1.0;
		for(int t = 1; t < N  + 5; t++)
		{
			for(int i = 1; i <= N; i++)
				for(int j = 1; j <= N; j++)
				{
					if(!dep[i][j]) continue;
					if(wt[i] != 0 && wt[j] == 0)
						wt[j] = wt[i] / dep[i][j];
					else if(wt[i] == 0 && wt[j] != 0)
						wt[i] = wt[j] * dep[i][j];
				}
		}

		int mini = 1;
		double minv = wt[1];
		int maxi = 1;
		double maxv = wt[1];
		for(int i = 2; i <= N; i++)
		{
			if(wt[i] < minv)
			{
				minv = wt[i];
				mini = i;
			}
			if(wt[i] > maxv)
			{
				maxv = wt[i];
			}
		}

		memset(wt2, 0, sizeof(wt2));
		wt2[mini] = 1;
		for(int t = 1; t < N + 5; t++)
		{
			for(int i = 1; i <= N; i++)
				for(int j = 1;j <= N; j++)
				{
					if(!dep[i][j]) continue;
					if(wt2[i] != 0 && wt2[j] == 0)
						wt2[j] = wt2[i] / dep[i][j];
					else if(wt2[i] == 0 && wt2[j] != 0)
						wt2[i] = wt2[j] * dep[i][j];
				}
		}
		for(int i = 1; i <= N; i++) cout << wt2[i] << ' '; cout << endl;

		for(int i = 1; i <= N; i++)
		{
			if(maxv / wt2[i] > 1) cout << maxv / wt2[i];
			cout << inv[i];
			if(i != N) cout << " = ";
			else cout << endl;
		}
	}
}
