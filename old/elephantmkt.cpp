#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long ll;

struct node
{
	ll v;
	int li, ri; // index of left, right
};
const int MAX = (1<<30);
void insert2(vector<node>& A, ll v, int i, int p, int a, int b) // [a, b)
{
	if(a > i || b <= i) return;
	A[p].v += v;
	if(a+1 == b) return;
	if(A[p].li == -1) // create new
	{
		node n;
		n.v = 0;
		n.li = n.ri = -1;
		A[p].li = A.size();
		A.push_back(n);
		A[p].ri = A.size();
		A.push_back(n);
	}
	//cout << "a = " << a << ", b = " << b << ", p = " << p << ", l = " << A[p].li << ", r = " << A[p].ri << endl;
	int m = (a+b)/2;
	insert2(A,v,i,A[p].li,a,m);
	insert2(A,v,i,A[p].ri,m,b);
}
void insert(vector<node>& A, ll v, int i)
{
	if(A.empty())
	{
		node n;
		n.v = 0;
		n.li = n.ri = -1;
		A.push_back(n);
	}
	insert2(A,v,i,0,0,MAX);
}
ll lookup2(vector<node>& A, int l, int r, int p, int a, int b)
{
	if(a >= r || b <= l) return 0;
	if(l <= a && b <= r) return A[p].v;
	//cout << "a = " << a << ", b = " << b << ", p = " << p << ", l = " << A[p].li << ", r = " << A[p].ri << endl;
	if(A[p].li == -1) return 0;
	if(A[p].li == -1) // create new
	{
		node n;
		n.v = 0;
		n.li = n.ri = -1;
		A[p].li = A.size();
		A.push_back(n);
		A[p].ri = A.size();
		A.push_back(n);
	}
	int m = (a+b)/2;
	return lookup2(A,l,r,A[p].li,a,m) + lookup2(A,l,r,A[p].ri,m,b);
}
ll lookup(vector<node>& A, ll l, ll r)
{
	if(A.empty()) return 0;
	return lookup2(A,l,r,0,0,MAX);
}

vector<node> B; // number
vector<node> S;
vector<node> Bt; // total price
vector<node> St;

int main()
{
	string s;
	while(1)
	{
		cin >> s;
		if(s[0] == 'e') break;
		ll d, p;
		cin >> d >> p;
		if(s[0] == 'b')
		{
			insert(S, d, p);
			insert(St, d*p, p);
		}
		else if(s[0] == 's')
		{
			insert(B, d, p);
			insert(Bt, d*p, p);
		}
		ll low = 0, high = MAX;
		while(low + 1 < high)
		{
			ll mid = (low+high)/2;
			ll numB = lookup(B, 0, mid);
			ll numS = lookup(S, mid, MAX);
			if(numS < numB) high = mid; // i'm buying too many
			else low = mid;
		}
		//cout << low << endl; continue;
		ll numB = lookup(B, 0, low);
		ll numS = lookup(S, low, MAX);
		ll numBt = lookup(Bt, 0, low);
		ll numSt = lookup(St, low, MAX) - (numS-numB)*low;
		//cout << numB << ' ' << numS << ' ' << numBt << ' ' << numSt << endl;
		cout << numSt-numBt << endl;
	}
	return 0;
}
