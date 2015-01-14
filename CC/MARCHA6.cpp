#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <deque>

using namespace std;

typedef long long ll;

const int MAX = 1e8;

int table[10050];
int best[17][1 << 17];

int bitcnt(int x)
{
	int res = 0;
	while(x > 0)
	{
		if(x & 1) res++;
		x /= 2;
	}
	return res;
}

void print(vector<ll>& V)
{
	for(int i = 0; i < V.size(); i++) cout << V[i] << ' ';
	cout << endl;
}

void pre()
{
	//cout << "pre..." << endl;
	for(int i = 0; i <= 10040; i++) table[i] = (bitcnt(i) % 2);
	memset(best, -1, sizeof(best));
	for(int i = 10000; i >= 0; i--)
	{
		//cout << i;
		int s = 0;
		for(int j = 0; j < 16; j++)
		{
			s *= 2;
			s += table[i + j];
			best[j][s] = i;
		}
	}
	//cout << "done" << endl;
}

int test(vector<ll>& V) // find 01101001 or 10010110, range [1, 8] to [8, 15]
{
	int cur = 0;
	for(int i = 1; i < 16; i++)
	{
		//cout << cur << endl;
		cur *= 10;
		while(cur >= MAX) cur -= MAX;
		cur += (V[i]);
		if(cur == 10010110) return i - 7;
		if(i >= 8 && cur == 1101001) return i - 7;
	}
	return -1;
}

vector<ll> solve(vector<ll> V)
{
	vector<ll> res(V.size(), -1);
	int s = 0;
	for(int i = 0; i < 16 && i < V.size(); i++)
	{
		s *= 2;
		s += V[i];
		//printf("%d %d -> %d\n", i, s, best[i][s]);
		res[i] = best[i][s];
	}
	if(V.size() > 16)
	{
		int k = test(V);
		//printf("k = %d\n", k);
		if(k == -1) return res; // rest are -1
		deque<int> a;
		a.push_back(V[k]);
		a.push_back(V[k + 4]);

		//cout << "V is : ";
		//print(V);
		for(int i = k - 1; i >= 0; i -= 4)
		{
			int b[2];
			b[0] = b[1] = 0;
			for(int j = i; j > i - 4 && j >= 0; j--)
			{
				//printf("%d:%d %d:%d\n", j, V[j], j + 4, V[j + 4]);
				b[(V[j]) ^ (V[j + 4])]++;
			}
			//cout << b[0] << ' ' << b[1] << endl;
			if(b[1] == 0) a.push_front(a.front());
			else if(b[0] == 0) a.push_front((a.front()) ^ 1);
			else return res;
		}

		vector<ll> next;
		for(int i = 0; i < a.size(); i++) next.push_back(a[i]);
		int next_i = next.size();
		//cout << "a is : ";
		//print(next);
		for(int i = k + 8; i < V.size(); i += 4)
		{
			int b[2];
			b[0] = b[1] = 0;
			for(int j = i; j < i + 4 && j < V.size(); j++)
			{
				b[(V[j]) ^ (V[j - 4])]++;
			}
			//cout << b[0] << ' ' << b[1] << endl;
			if(b[1] == 0) next.push_back(next.back());
			else if(b[0] == 0) next.push_back((next.back()) ^ 1);
			else break;
		}
		//cout << "next is : ";
		//print(next);

		next = solve(next);
		//cout << "solved next is : ";
		//print(next);
		for(int i = next_i; i < next.size(); i++)
		{
			if(next[i] == -1) break;
			for(int j = 0; j < 4; j++)
			{
				int index = k + 8 + 4 * (i - next_i) + j;
				if(index < res.size())
					res[index] = 4 * next[i] + ((44 - k) % 4);
			}
		}

	}
	return res;
}

int N;
vector<ll> A;

int main2()
{
	cin >> N;
	A = vector<ll>(N);
	for(int i = 0; i < N; i++) scanf("%lld", &(A[i]));
	vector<ll> res = solve(A);
	for(int i = 0; i < res.size(); i++) printf("%d ", (int)res[i]);
	printf("\n");
	return 0;
}

int main()
{
	pre();
	//printf("1\n100\n");for(int i = 0; i < 100; i++) cout << table[i] << ' ';return 0;
	int T;
	cin >> T;
	while(T--) main2();
}
