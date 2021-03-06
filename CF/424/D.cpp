#include <iostream>
#include <map>

using namespace std;

const int INF = 1300000000;

struct Table
{
    map<int, int> T; // total, row
    int offset = 0;
    void clear()
    {
        T.clear();
        offset = 0;
    }
    void add(int v)
    {
        offset -= v;
    }
    void insert(int v, int i)
    {
        v += offset;
    }
    pair<int, int> find(int v, int t)
    {
        v += offset;
        int best = INF, besti = -1;
        map<int, int>::iterator higher = T.lower_bound(v);
        map<int, int>::iterator lower = T.lower_bound(v);
        if(higher != T.end())
        {
            if(abs(t - higher->first) < best)
            {
                best = abs(t - higher->first);
                besti = higher->second;
            }
        }
        if(lower != T.begin())
        {
            lower--;
            if(abs(t - lower->first) < best)
            {
                best = abs(t - lower->first);
                besti = lower->second;
            }
        }
        return make_pair(best, besti);
    }
};

int N, M, t;
Table T;

int main()
{
    
}
