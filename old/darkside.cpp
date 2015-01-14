#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

typedef long long ll;

const int MAX = (1 << 19);

int n1;
string S;
int sa1[MAX];
int rank1[MAX];
int height1[MAX];

int next[MAX];
int temp[MAX];
bool comp1(int a, int b)
{
  return S[a] < S[b];
}

void buildSA1()
{
  for(int i = 0; i < n1; i++)
    sa1[i] = i;
  sort(sa1, sa1 + n1, comp1);
  
  rank1[sa1[0]] = 0;
  for(int i = 0; i < n1-1; i++)
  {
    if(S[sa1[i]] == S[sa1[i+1]])
      rank1[sa1[i+1]] = rank1[sa1[i]];
    else
      rank1[sa1[i+1]] = i+1;
  }
  for(int len = 1; len < n1; len *= 2)
  {
    for(int i = 0; i < n1; i++)
      next[i] = i;
    for(int i = n1-len; i < n1; i++) // end have highest priority
      temp[next[rank1[i]]++] = i; 
    for(int i = 0; i < n1; i++) // then, prioritize segments based on next seg
      if(sa1[i] >= len)
        temp[next[rank1[sa1[i]-len]]++] = sa1[i]-len;
    memcpy(sa1, temp, sizeof(temp)); // copy new orderings of segments into sa1
    temp[sa1[0]] = 0;
    for(int i = 0; i < n1-1; i++)
    {
      if(sa1[i] + len < n1 && sa1[i+1] + len < n1 && rank1[sa1[i]] == rank1[sa1[i+1]] && rank1[sa1[i]+len] == rank1[sa1[i+1]+len])
        temp[sa1[i+1]] = temp[sa1[i]]; // can't separate yet, so leave the same
      else
        temp[sa1[i+1]] = i+1;
    }
    memcpy(rank1, temp, sizeof(temp)); // copy new ranks into rank1
  }
}

int lcp1(int p1, int p2, int l)
{
  while(p1+l < n1 && p2+l < n1 && S[p1+l] == S[p2+l])
    l++;
  return l;
}

void calcHeight1()
{
  int pre = 0;
  for(int i = 0; i < n1; i++)
  {
    if(rank1[i] == 0)
      height1[0] = 0;
    else
    {
      pre = lcp1(sa1[rank1[i]-1], sa1[rank1[i]], max(pre-1, 0));
      height1[rank1[i]] = pre;
    }
  }
}


int seg[MAX * 2]; // segtree for height array

void seg_init()
{
  for(int i = 0; i < 2*MAX; i++)
    seg[i] = MAX;
  for(int i = 0; i < n1; i++)
    seg[MAX+i] = height1[i];
  for(int i = MAX-1; i >= 0; i--)
    seg[i] = min(seg[i*2], seg[i*2+1]);
}
int seg_lookup2(int l, int r, int p, int a, int b) // min in [l, r)
{
    //cout << l << ' ' << r << ' ' << p << ' ' << a << ' ' << b << endl;
    if(a >= r || b <= l)
        return MAX;
    if(l <= a && b <= r)
        return seg[p];
    int m = (a + b) / 2;
    return min(seg_lookup2(l, r, p * 2, a, m), seg_lookup2(l, r, p * 2 + 1, m, b));
}
int seg_lookup(int l, int r)
{
    return seg_lookup2(l, r, 1, 0, MAX);
}
int lcp(int i, int j)
{
  return seg_lookup(min(rank1[i], rank1[j])+1, max(rank1[i], rank1[j])+1);
}

// * end of library * //

string A, B;
void get_suffix_array()
{
  n1 = S.size();
  buildSA1();
  calcHeight1();
  //cout << "height array for string " << S << " is: ";  for(int i = 0; i < n1; i++) cout << height1[rank1[i]] << ' ';  cout << endl;
  seg_init();
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

int suffix_index[MAX]; // index of k-th suffix in order
int B_lcp[MAX]; // [i]: LCP of suffix starting at i, over all suffixes in A

void process_lcp()
{
	for(int i = 0; i < S.size(); i++) suffix_index[rank1[i]] = i;
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
	S = A + '#' + B;
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
