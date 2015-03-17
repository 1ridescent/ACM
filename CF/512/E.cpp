#include <bits/stdc++.h>

using namespace std;

typedef set<int>::iterator iter;
typedef map<int, set<int> >::iterator map_iter;

struct board
{
	map<int, set<int> > edges;
	void init(int n)
	{
		for(int i = 1; i <= n; i++)
		{
			edges[i].insert(i % n + 1);
			edges[i % n + 1].insert(i);
		}
		//print();
	}
	void insert(int a, int b)
	{
		edges[a].insert(b);
		edges[b].insert(a);
	}
	pair<int, int> flip(int a, int b)
	{
		//print();
		iter it = edges[a].find(b);
		iter it2 = it;
		it2++;
		if(it2 == edges[a].end()) it2 = edges[a].begin();
		int c = *it2;
		it2 = it;
		if(it2 == edges[a].begin()) it2 = edges[a].end();
		it2--;
		int d = *it2;
		edges[a].erase(b);
		edges[b].erase(a);
		edges[c].insert(d);
		edges[d].insert(c);
		//printf("flipped %d %d to %d %d\n", a, b, c, d);
		//print();
		return make_pair(c, d);
	}
	void erase(int a)
	{
		for(map_iter it = edges.begin(); it != edges.end(); it++)
			it->second.erase(a);
		edges.erase(a);
	}
	void print()
	{
		for(map_iter it = edges.begin(); it != edges.end(); it++)
		{
			cout << it->first << " : ";
			for(iter it2 = it->second.begin(); it2 != it->second.end(); it2++) cout << *it2 << ' ';
			cout << endl;
		}
	}
};

int N;
board start, finish;
vector<pair<int, int> > front, back;

int main()
{
	cin >> N;
	start.init(N);
	finish.init(N);
	for(int i = 1; i <= N - 3; i++)
	{
		int a, b;
		cin >> a >> b;
		start.insert(a, b);
	}
	for(int i = 1; i <= N - 3; i++)
	{
		int a, b;
		cin >> a >> b;
		finish.insert(a, b);
	}
	while(N != 3)
	{
		int min_deg = 1000000000, min_i = -1;
		for(map_iter it = start.edges.begin(); it != start.edges.end(); it++)
		{
			int i = it->first;
			int s = start.edges[i].size() + finish.edges[i].size();
			if(s < min_deg)
				min_deg = s, min_i = i;
		}
		int v = min_i;
		while(start.edges[v].size() > 2)
		{
			iter it = start.edges[v].upper_bound(v);
			if(it == start.edges[v].end()) it = start.edges[v].begin();
			it++;
			if(it == start.edges[v].end()) it = start.edges[v].begin();
			front.push_back(make_pair(v, *it));
			start.flip(v, *it);
		}
		//cout << "--\n";
		while(finish.edges[v].size() > 2)
		{
			iter it = finish.edges[v].upper_bound(v);
			if(it == finish.edges[v].end()) it = finish.edges[v].begin();
			it++;
			if(it == finish.edges[v].end()) it = finish.edges[v].begin();
			back.push_back(finish.flip(v, *it));
		}
		start.erase(v);
		finish.erase(v);
		//cout << "deleted " << v << endl; start.print();
		N--;
	}
	cout << front.size() + back.size() << endl;
	for(int i = 0; i < front.size(); i++) cout << front[i].first << ' ' << front[i].second << endl;
	for(int i = back.size() - 1; i >= 0; i--) cout << back[i].first << ' ' << back[i].second << endl;
}
