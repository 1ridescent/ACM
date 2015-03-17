#include <iostream>
#include <cstring>

using namespace std;

const int MAX = (1 << 18);

struct RankSegTree
{
        int seg[2 * MAX];
        RankSegTree()
        {
                memset(seg, 0, sizeof(seg));
        }
        void insert(int v, int i)
        {
                for(i += MAX; i > 0; i /= 2) seg[i] += v;
        }
        int rank(int k)
        {
                int p;
                for(p = 1; p < MAX; )
                {
                        if(seg[2 * p] < k)
                        {
                                k -= seg[2 * p];
                                p = 2 * p + 1;
                        }
                        else
                        {
                                p = 2 * p;
                        }
                }
                return p - MAX;
        }
};
struct BIT
{
	int bit[MAX];
	BIT()
	{
		memset(bit, 0, sizeof(bit));
	}
	void insert(int i)
	{
		i += 100;
		for(; i < MAX; i += i & -i)
			bit[i]++;
	}
	int lookup(int i)
	{
		i += 100;
		int res = 0;
		for(; i > 0; i -= i & -i)
			res += bit[i];
		return res;
	}
};

int N;
int A[200005], B[200005];

BIT SA, SB;
int RC[200005];
RankSegTree SC;

int main()
{
	ios::sync_with_stdio(false);
	cin >> N;

	for(int i = 0; i < N; i++) cin >> A[i];
	for(int i = 0; i < N; i++) cin >> B[i];
	int carry = 0;
	for(int i = N - 1; i >= 0; i--)
	{
		int s = N - i;
		int a = A[i], b = B[i];
		int ra = SA.lookup(a), rb = SB.lookup(b);
		int rc = ra + rb + carry;
		carry = 0;
		if(rc >= s)
		{
			rc -= s;
			carry++;
		}
		RC[i] = rc;
		SA.insert(a);
		SB.insert(b);
	}
	//for(int i = 0; i < N; i++) cout << RC[i] << ' '; cout << endl;
	for(int i = 0; i < N; i++) SC.insert(1, i);
	for(int i = 0; i < N; i++)
	{
		int c = RC[i];
		int ci = SC.rank(c + 1);
		cout << ci << ' ';
		SC.insert(-1, ci);
	}
}
