#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int MAX = (1 << 19);

struct
{
    int m; // min
    int d; // delta
    int n; // num min
} seg[2*MAX];

void init2(int p, int a, int b)
{
    if(p >= 2*MAX) return;
    seg[p].m = 0;
    seg[p].d = 0;
    seg[p].n = b-a;
    int m = (a+b)/2;
    init2(p*2, a, m);
    init2(p*2+1, m, b);
}
void init()
{
    init2(1, 0, MAX);
}
void insert2(int v, int l, int r, int p, int a, int b)
{
    if(a >= r || b <= l) return;
    else if(l <= a && b <= r)
    {
        seg[p].m += v;
        seg[p].d += v;
    }
    else
    {
        int m = (a+b)/2;
        seg[p*2].m += seg[p].d; // propagate delta
        seg[p*2].d += seg[p].d;
        seg[p*2+1].m += seg[p].d;
        seg[p*2+1].d += seg[p].d;
        seg[p].d = 0;
        insert2(v, l, r, p*2, a, m);
        insert2(v, l, r, p*2+1, m, b);
        if(p < MAX) // fix
        {
            if(seg[p*2].m < seg[p*2+1].m)
            {
                seg[p].m = seg[p*2].m;
                seg[p].n = seg[p*2].n;
            }
            else if(seg[p*2].m == seg[p*2+1].m)
            {
                seg[p].m = seg[p*2].m;
                seg[p].n = seg[p*2].n + seg[p*2+1].n;
            }
            else
            {
                seg[p].m = seg[p*2+1].m;
                seg[p].n = seg[p*2+1].n;
            }
        }
    }
}
void insert(int v, int l, int r)
{
	//printf("%d %d %d\n",v,l,r);
    insert2(v, l, r, 1, 0, MAX);
}
int lookup2(int l, int r, int p, int a, int b)
{
    if(a >= r || b <= l) return 0;
    else if(l <= a && b <= r)
    {
        return (seg[p].m == 0 ? seg[p].n : 0);
    }
    else
    {
        int m = (a+b)/2;
        seg[p*2].m += seg[p].d; // propagate delta
        seg[p*2].d += seg[p].d;
        seg[p*2+1].m += seg[p].d;
        seg[p*2+1].d += seg[p].d;
        seg[p].d = 0;
        return lookup2(l, r, p*2, a, m) + lookup2(l, r, p*2+1, m, b);
    }
}
int lookup(int l, int r)
{
    return lookup2(l, r, 1, 0, MAX);
}




int N;
int A[MAX];
deque<pair<int, int> > Max, Min;

int main()
{
	//ios::sync_with_stdio(false);
	init();
	cin >> N;
	for(int i = 1; i <= N; i++)
	{
		int x, y;
		cin >> x >> y;
		A[x] = y;
	}
	Max.push_back(make_pair(N + 1, MAX));
	Min.push_back(make_pair(N + 1, 0));
	ll res = 0;
	for(int i = N; i >= 1; i--)
	{
		//cout << i << ":\n";
		//cout << A[i] << ' ' << Max[0].second << endl;
		while(A[i] > Max[0].second)
		{
			//printf("hi1\n");
			int d = A[i] - Max[0].second;
			insert(d, Max[0].first, Max[1].first);
			Max.pop_front();
		}
		Max.push_front(make_pair(i, A[i]));
		while(A[i] < Min[0].second)
		{
			//puts("hi2");
			int d = Min[0].second - A[i];
			insert(d, Min[0].first, Min[1].first);
			Min.pop_front();
		}
		Min.push_front(make_pair(i, A[i]));
		insert(-1, i + 1, N + 1);
		res += lookup(i, N + 1);
	}
	cout << res;
}
