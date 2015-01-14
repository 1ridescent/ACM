#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAX = 1024;
struct BIT
{
	int A[MAX];
	void init()
	{
		memset(A, 0, sizeof(A));
	}
	void insert(int v, int i)
	{
		for(; i < MAX; i += i & -i) A[i] += v;
	}
	int lookup(int i)
	{
		int res = 0;
		for(; i > 0; i -= i & -i) res += A[i];
		return res;
	}
};
BIT A;

void print(vector<int>& V)
{
	for(int i = 0; i < V.size(); i++) cout << V[i] << ' ';
	cout << endl;
}

int num_invs(vector<int>& V)
{
	map<int, int> id;
	for(int i = 0; i < V.size(); i++) id[V[i]] = -1;
	int nextid = 1;
	for(map<int, int>::iterator it = id.begin(); it != id.end(); it++)
	{
		it->second = nextid++;
	}
	for(int i = 0; i < V.size(); i++) V[i] = id[V[i]];

	int res = 0;
	A.init();
	for(int i = V.size() - 1; i >= 0; i--)
	{
		res += A.lookup(V[i]);
		A.insert(1, V[i]);
	}
	//cout << " num invs of "; print(V); cout << " is " << res << endl;
	return res;
}

int main2()
{
	int N;
	cin >> N;
	vector<int> V(N);
	for(int i = 0; i < N; i++) cin >> V[i];
	if(N == 1)
	{
		cout << 0 << endl;
		return 0;
	}
	int best = -1, besti;
	for(int i = 0; i < N; i++)
		if(V[i] > best)
			best = V[i], besti = i;
	int res = 123123123;
	for(int m = 0; m < N; m++)
	{
		int ini = abs(besti - m);
		vector<int> V2 = V;
		if(besti < m) for(int i = besti; i < m; i++) swap(V2[i], V2[i + 1]);
		if(besti > m) for(int i = besti; i > m; i--) swap(V2[i], V2[i - 1]);
		//cout << m << ": ";
		//print(V2);
		vector<int> Left, Right;
		for(int i = 0; i < m; i++) Left.push_back(V2[i]);
		for(int i = m + 1; i < N; i++) Right.push_back(-V2[i]);
		int after = num_invs(Left) + num_invs(Right);
		//cout << ini << ' ' << after << endl;
		res = min(res, ini + after);
	}
	/*for(int l = 0; l < N - 1; l++)
	{
		vector<int> Left, Right;
		for(int i = 0; i < N; i++)
		{
			if(i <= l) Left.push_back(V[i]);
			else Right.push_back(-V[i]);
		}
		int total = num_invs(Left) + num_invs(Right);
		//cout << l << ": " << total << endl;
		best = min(best, total);
	}*/
	cout << res << endl;
}

int main()
{
	int T;
	cin >> T;
	for(int t = 1; t <= T; t++)
	{
		cout << "Case #" << t << ": ";
		main2();
		//vector<int> V;int N;cin >> N;for(int i=0;i<N;i++){int x;cin >> x;V.push_back(x);}cout<<num_invs(V);
	}
}
