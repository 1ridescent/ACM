// Author: Lech Duraj
// O(k! log n + n log n)

#include <cstdio>
#include <algorithm>
#include <vector>
#include <cassert>

using namespace std;

typedef pair<int,int> PI;

int n;
vector<PI> A;

const int infty = 1000*1000*1000;

#define dprintf(...)
//#define dprintf(...) fprintf(stderr,__VA_ARGS__)

struct tree
{

    vector<int> check, value;
    vector<int> T;
    int M;
    
    int setval(int k, int v)
    {
        value[k] = v;
        int x = (M+k)/2;
        while(x>=1)
        {
            if (value[T[2*x]]>=value[T[2*x+1]])
                T[x] = T[2*x];
            else
                T[x] = T[2*x+1];
            x /= 2;
        }
    }
    
    void init(int n)
    {
        M = 1;
        while(M<=n+1)
            M *= 2;
        check.clear();
        check.resize(M,infty+1);
        value.clear();
        value.resize(M,-infty);
        T.clear();
        T.resize(2*M);
        for(int i=0; i<M; i++)
            T[M+i] = i;
        for(int i=0; i<M; i++)
            setval(i,-infty);
            
    }

    int query(int c)            // index i of element with max value[i] with check[i] <= c
    {
        int x = M + upper_bound(check.begin(),check.end(),c) - check.begin();
        int best = 0;
        while(x>1)
        {
            if (x%2!=0 && value[T[x-1]]>value[best])
                best = T[x-1];
            x /= 2;
        }
        return best;
    } 

};

tree tree1, tree2;

void start()
{
    tree1.init(n);
    tree2.init(n);
    for(int i=0; i<n; i++)
    {
        tree1.check[i] = A[i].first;
        tree2.check[i] = -A[n-1-i].first;
    }
}

void add(int i)
{
    tree1.setval(i,A[i].first-A[i].second);
    tree2.setval(n-1-i,-A[i].second);
}

void remove(int i)
{
    tree1.setval(i,-infty);
    tree2.setval(n-1-i,-infty);
}

int go(int k, vector<int> &sol)
{
    sol.clear();
    if (k==0)
    {
        int best_diff = tree1.query(infty-1);
        sol.push_back(best_diff);
        return A[best_diff].first - A[best_diff].second;
    }
    vector<int> sol_part;
    int c = go(k-1,sol_part);
    int current = -infty+1;
    for(int r : sol_part)
    {
        vector<int> sol_o;
        remove(r);
        int other = go(k-1, sol_o);
        if (A[r].first<=other)
            other = A[r].first - A[r].second;
        else
            other = other - A[r].second;
        sol_o.push_back(r);
        if (other>current)
        {
            sol = sol_o;
            current = other;
        }
        add(r);
    } 
    for (int r : sol_part)
        remove(r);
    int best1 = tree1.query(c);
    int best2 = tree2.query(-c);
    int val1 =  tree1.value[best1];    
    int val2 =  tree2.value[best2];
    if (val2 != -infty)
        val2 += c;
    best2 = n-1-best2;
    if (val1>=val2 && val1>current)
    {
        sol = sol_part;
        current = val1;
        sol.push_back(best1);
    }
    if (val1<val2 && val2>current)
    {
        sol = sol_part;
        current = val2;
        sol.push_back(best2);
    }
    for(int r : sol_part)
        add(r);
    return current;
}

int main()
{
    int TT;
    scanf("%d",&TT);
    while(TT--)
    {
        int k;
        scanf("%d %d",&n,&k);
        A.resize(n);
        for(int i=0; i<n; i++)
            scanf("%d %d",&A[i].first,&A[i].second);
        n+=2;
        A.push_back(PI(-infty,infty));
        A.push_back(PI(infty,infty));
        sort(A.begin(),A.end());
        start();
        for(int i=0; i<n; i++)
            add(i);
//        tree1.print();
        vector<int> sol;
        printf("%d\n",max(go(k,sol),0));
    }
}
