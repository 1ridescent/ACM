#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class StringCompare
{
public:
	bool operator()(pair<string, int> s, pair<string, int> t)
	{
		if(s.first.size() != t.first.size()) return (s.first.size() > t.first.size());
		return s.first > t.first;
	}
};
priority_queue<pair<string, int>, vector< pair<string, int> >, StringCompare> Q;

string best[555];
string compute(int N)
{
	for(int i = 0; i < N-1; i++) best[i] = "";
	Q.push(make_pair("9", 9%N));
	while(!Q.empty())
	{
		pair<string, int> s = Q.top();
		Q.pop();
		if(best[s.second] == "")
		{
			best[s.second] = s.first;
			Q.push(make_pair(s.first+"0", (s.second*10)%N));
			Q.push(make_pair(s.first+"9", (s.second*10+9)%N));
		}
	}
	return best[0];
}

int main()
{
	string ans[555];
	for(int i = 1; i <= 500; i++) ans[i] = compute(i);
	int T;
	cin >> T;
	for(int t = 0; t < T; t++)
	{
		int N;
		cin >> N;
		cout << ans[N] << endl;
	}
	return 0;
}
