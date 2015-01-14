#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

const int MAX = (1 << 17);
const int LGMAX = 20;

string S;
struct entry
{
	int prev, next, id;
};
entry compare[2 * MAX];
int cmp(entry a, entry b)
{
	if(a.prev != b.prev) return (a.prev < b.prev);
	return a.next < b.next;
}
vector<entry> temp[2 * MAX];
void radix_sort(int len)
{
	for(int i = 0; i < len; i++) temp[compare[i].next + 1].push_back(compare[i]); // + 1 because next could be -1?
	int index = 0;
	for(int i = 0; i < 2 * MAX; i++)
	{
		if(!temp[i].empty())
		{
			for(int j = 0; j < temp[i].size(); j++) compare[index++] = temp[i][j];
			temp[i].clear();
		}
	}
	for(int i = 0; i < len; i++) temp[compare[i].prev + 1].push_back(compare[i]);
	index = 0;
	for(int i = 0; i < 2 * MAX; i++)
	{
		if(!temp[i].empty())
		{
			for(int j = 0; j < temp[i].size(); j++) compare[index++] = temp[i][j];
			temp[i].clear();
		}
	}
}

int suffix[LGMAX+2][2*MAX+1];


int lcp(int s, int t)
{
	if(s == t) return S.size() - s; // edge case
	int len = 0;
	for(int i = LGMAX; i >= 0 && s < S.size() && t < S.size(); i--)
		if(suffix[i][s] == suffix[i][t])
		{
			s += (1 << i);
			t += (1 << i);
			len += (1 << i);
		}
	return len;
}

int main()
{
	cin >> S;
	for(int i = 0; i < S.size(); i++) suffix[0][i] = S[i];
	for(int t = 1; t <= LGMAX; t++)
	{
		int len = (1 << (t-1));
		for(int i = 0; i < S.size(); i++)
		{
			compare[i].prev = suffix[t-1][i];
			compare[i].next = i + len < S.size() ? suffix[t-1][i + len] : -1; // -1 goes before any other char
			compare[i].id = i;
		}
		radix_sort(S.size());
		for(int i = 0; i < S.size(); i++)
			suffix[t][compare[i].id] = (i > 0 && compare[i].prev == compare[i-1].prev && compare[i].next == compare[i-1].next)
			                        ? suffix[t][compare[i-1].id] : i;
	}
	for(int i=0;i<S.size();i++) cout << suffix[LGMAX][i] << ' '; cout << endl;
	while(true)
	{
		int s, t;
		cin >> s;
		if(s < 0) break;
		cin >> t;
		cout << lcp(s, t);
	}
	return 0;
}
