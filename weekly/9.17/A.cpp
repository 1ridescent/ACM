#include <iostream>
#include <map>
#include <set>
#include <cstdio>

using namespace std;

int N;
map<string, int> teams[256];
double total_time[256];
double total_tries[256];
int total_num[256];

int main()
{
	cin >> N;
	while(N--)
	{
		int time1;
		string team;
		char prob;
		char res;
		cin >> time1 >> team >> prob >> res;
		if(teams[prob][team] == -1) continue;

		if(res == 'A')
		{
			int tries = teams[prob][team] + 1;
			total_time[prob] += time1;
			total_tries[prob] += tries;
			total_num[prob]++;
			teams[prob][team] = -1;
		}
		else
		{
			teams[prob][team]++;
		}
	}
	for(char p = 'A'; p <= 'I'; p++)
	{
		if(total_num[p] == 0) cout << p << " 0\n";
	else printf("%c %d %.2f %.2f\n", p, total_num[p], total_tries[p] / total_num[p], total_time[p] / total_num[p]);
	}
}
