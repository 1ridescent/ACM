#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct parcel
{
	int in, out, wt, str, val;
};

parcel P[505];

bool cmp_parcel(int i, int j)
{
	return    make_pair( -P[i].str , i )
			< make_pair( -P[j].str , j );
}

int locate(pair<int, char> a)
{
	int i = a.first;
	if(a.first == '(') return P[i].in;
	return P[i].out;
}
bool cmp_data(pair<int, char> a, pair<int, char> b)
{
	if(locate(a) != locate(b))
		return locate(a) < locate(b);
	if(a.second == ')' && b.first == '(') return true;
	if(a.second == '(' && b.second == ')') return false;
	int i = P[a.first], j = P[b.first];
	if(a.second == '(' && b.second == '(')
	{
		if(P[i].out < P[j].out) return false;
		if(P[i].out > P[j].out) return true;
		return cmp_parcel(i, j);
	}
	else
	{
		if(P[i].out < P[j].out) return true;
		if(P[i].out > P[j].out) return false;
		return !cmp_parcel(i, j);
	}
}

int left[505], right[505];

vector<pair<int, char> > data;

int val[505][1005]; // [id][weight]

vector<int> inner[1005];

int main()
{
	cin >> N;
	for(int i = 0; i < N; i++)
	{
		cin >> P[i].in >> P[i].out >> P[i].wt > P[i].str >> P[i].val;
		data.push_back(make_pair(i, '('));
		data.push_back(make_pair(i, ')'));
	}

	sort(data.begin(), data.end(), cmp_data);

	for(int i = 0; i < data.size(); i++)
	{
		if(data[i].second == '(') left[data[i].first] = i;
		if(data[i].second == ')') right[data[i].first] = i;
	}

	for(int len = 1; len < 1005; len++)
	{
		for(int id = 0; id < N; id++)
		{
			int start = left[id], end = right[id];
			if(end - start == len)
			{
				for(int i = start; i < end; i++) inner[i].clear();
				for(int i = 0; i < N; i++)
					if(start < left[i] && right[i] < end)
						inner[right[i]].push_back(i);
			}
			memset(val[id], 0, sizeof(val[id]));
			for(int t = start; t < end; t++)
			{
				for(int i = 0; i < inner[t].size(); i++)
				{
					for(int w = 0; w <= P[id].str; w++)
					{

					}
				}
			}
		}
	}
}
