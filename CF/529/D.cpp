#include <bits/stdc++.h>

using namespace std;

int N, M, T;

int parse(string S)
{
	int a[8];
	for(int i = 0; i < 8; i++) a[i] = S[i] - '0';
	int h = a[0] * 10 + a[1];
	int m = a[3] * 10 + a[4];
	int s = a[6] * 10 + a[7];
	return h * 3600 + m * 60 + s;
}

int cnt = 0;
int freq[88888];
deque<pair<int, int> > D;
vector<int> ans;
void add(int t, int id)
{
	if(freq[id] == 0) cnt++;
	freq[id]++;
	D.push_back(make_pair(t, id));
	ans.push_back(id);
}
void remove()
{
	int id = D.front().second;
	freq[id]--;
	if(freq[id] == 0) cnt--;
	D.pop_front();
}

bool attained = false;
int total = 0;

int main()
{
	//string S;cin>>S;cout<<parse(S);
	ios::sync_with_stdio(false);
	cin >> N >> M >> T;
	for(int i = 0; i < N; i++)
	{
		string S;
		cin >> S;
		int t = parse(S);
		while(!D.empty() && t - D.front().first >= T)
			remove();
		if(cnt == M) add(t, D.back().second);
		else add(t, ++total);
		if(cnt == M) attained = true;
	}
	if(!attained)
	{
		cout << "No solution";
		return 0;
	}
	cout << total << '\n';
	for(int i = 0; i < ans.size(); i++)
		cout << ans[i] << '\n';
}
