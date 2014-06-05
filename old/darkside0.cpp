#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

typedef long long ll;

const int MAX = (1 << 19);
const int LGMAX = 20;

string S;
typedef pair<int, pair<int, int> > entry;
#define prev first
#define next second.first
#define id second.second
entry compare[2 * MAX];
entry compare2[2 * MAX];
vector<int> temp[MAX];
inline void radix_sort(int len)
{
	for(int i = 0; i < len; i++) temp[compare[i].next + 1].push_back(i); // + 1 because next could be -1?
	int index = 0;
	for(int i = 0; i < MAX; i++)
	{
		if(!temp[i].empty())
		{
			for(int j = 0; j < temp[i].size(); j++) compare2[index++] = compare[temp[i][j]];
			temp[i].clear();
		}
	}
	for(int i = 0; i < len; i++) temp[compare2[i].prev + 1].push_back(i);
	index = 0;
	for(int i = 0; i < MAX; i++)
	{
		if(!temp[i].empty())
		{
			for(int j = 0; j < temp[i].size(); j++) compare[index++] = compare2[temp[i][j]];
			temp[i].clear();
		}
	}
}
int suffix[LGMAX+1][2*MAX+1];
int get_suffix_array()
{
	//cout << "S = " << S << endl;
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
	//for(int i=0;i<S.size();i++) cout << suffix[LGMAX][i] << ' '; cout << endl;
}


int pals[2*MAX-1]; // length of pal centered at s[i] is at [2*i]
void find_pals(const string& S)
{
	pals[0] = 1, pals[1] = 0;
	for(int d, i = 1; i+2 < 2 * S.size(); i += d)
	{
		int& p = pals[i];
		int left = (i-p-1)/2, right = (i+p+1)/2;
		while(0 <= left && right < S.size() && S[left] == S[right])
		{
			left--;
			right++;
			p += 2;
		}
		for(d = 1; pals[i-d] < p-d; d++)
			pals[i+d] = pals[i-d];
		pals[i+d] = p-d;
	}
	pals[2*(S.size()-1)] = 1;
}

string A, B;
inline int lcp(int s, int t)
{
	//t += A.size()+1; // move t to index t in the B part of S
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

int suffix_index[MAX]; // index of k-th suffix in order
int B_lcp[MAX]; // [i]: LCP of suffix starting at i, over all suffixes in A

void process_lcp()
{
	for(int i = 0; i < S.size(); i++) suffix_index[suffix[LGMAX][i]] = i;
	for(int i = 0; i < B.size(); i++) B_lcp[i] = 0;
	int last = 0;
	for(int i = 1; i < S.size(); i++) // left sweep
	{
		if(suffix_index[i] < A.size()) // in A
		{
			int j = i-1;
			//int min_lcp = lcp(suffix_index[j], suffix_index[j+1]);
			//cout << "min_lcp of " << suffix_index[j] << " and " << suffix_index[j+1] << " is " << min_lcp << endl;
			while(true)
			{
				//cout << suffix_index[j] << ' ' << A.size() << endl;
				if(suffix_index[j] > A.size()) // in B
					B_lcp[suffix_index[j]-1-A.size()] = max(B_lcp[suffix_index[j]-1-A.size()], lcp(suffix_index[j], suffix_index[i]));
				j--;
				if(j < last) break;
				//min_lcp = min(min_lcp, lcp(suffix_index[j], suffix_index[j+1]));
			}
			last = i;
		}
	}
	last = S.size()-1;
	for(int i = S.size()-2; i >= 0; i--) // right sweep
	{
		if(suffix_index[i] < A.size())
		{
			int j = i+1;
			//int min_lcp = lcp(suffix_index[j-1], suffix_index[j]);
			while(true)
			{
				if(suffix_index[j] > A.size())
					B_lcp[suffix_index[j]-1-A.size()] = max(B_lcp[suffix_index[j]-1-A.size()], lcp(suffix_index[j], suffix_index[i]));
				j++;
				if(j > last) break;
				//min_lcp = min(min_lcp, lcp(suffix_index[j-1], suffix_index[j]));
			}
			last = i;
		}
	}
}

int bit[MAX];
inline void init()
{
	for(int i=0;i<MAX;i++) bit[i] = 0;
}
inline void insert(int p)
{
	p += 3;
	for(int i = p; i < MAX; i += i & -i)
		bit[i]++;
}
inline ll lookup2(int p)
{
	if(p < 0) return 0;
	p += 3;
	ll total = 0;
	for(int i = p; i > 0; i -= i & -i)
		total += bit[i];
	return total;
}
inline ll lookup(int l, int r) // [l,r]
{
	if(l > r) return 0;
	return lookup2(r) - lookup2(l-1);
}

ll solve()
{
	//cout << "B=" << B << endl;
	find_pals(B);
	init();
	//for(int i=0;i<2*B.size();i++) cout << pals[i];
	for(int i = 0; i < B.size(); i++) // find palindrome suffixes
	{
		if(i + (pals[2*i]+1)/2 == B.size()) insert(i);
	}
	S = A + '\0' + B;
	//cout << "S.size = " << S.size() << endl;
	get_suffix_array();
	process_lcp();
	//for(int i=0;i<B.size();i++) cout << B_lcp[i] << ' '; cout << endl;
	ll total = 0;
	for(int i = 0; i < B.size(); i++) // find palindrome prefixes now
	{
		if(i == pals[2*i]/2)
		{
			//cout << i << ' ' << B_lcp[i] << ' ';
			int best_lcp = B_lcp[i];
			int l = (pals[2*i] + B.size())/2, r = i + best_lcp - 1;
			//cout << "l=" << l << ", r=" << r << ", lookup=" << lookup(l,r) << endl;
			total += lookup(l,r);
		}
	}
	return total;
}
int main()
{
	cin >> A >> B;
	if(B.size() == 1)
	{
		bool found = false;
		for(int i=0;i<A.size();i++) found |= (A[i] == B[0]);
		cout << found << endl;
		return 0;
	}
	ll total = solve();
	string Br = B;
	for(int i=0;i<B.size();i++) Br[B.size()-1-i] = B[i];
	B = Br;
	total += solve();
	if(B.size() % 2 == 1 && pals[2*(B.size()/2)] == B.size())
	{
		if(B_lcp[0] >= (B.size()+1)/2) total++;
		if(B_lcp[B.size()/2] >= (B.size()+1)/2) total++;
	}
	cout << total;
	return 0;
}
