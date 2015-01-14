#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

int N;
vector<int> primes;
bool isprime[100100];

void get_primes()
{
    for(int p = 2; p <= N; p++)
    {
        int good = true;
        for(int d = 2; d * d <= p; d++)
        {
            if(p % d == 0) good = false;
        }
        if(good) primes.push_back(p);
    }
}

pair<int, int> even[100100];

void setup()
{
    memset(isprime, 0, sizeof(isprime));
    for(int i = 0; i < primes.size(); i++) isprime[primes[i]] = true;
    int cnt = 0;
    for(int n = 2; n <= N; n += 2)
    {
        for(int i = 0; i < primes.size(); i++)
        {
            cnt++;
            if(isprime[n - primes[i]])
            {
                even[n] = make_pair(primes[i], n - primes[i]);
                break;
            }
        }
    }
    //cout << cnt;
}

vector<pair<int, int> > res;

void prime_swap(int i, int j)
{
    if(i == j) return;
    if(i > j) swap(i, j);
    if(isprime[j - i + 1])
    {
        res.push_back(make_pair(i, j));
        return;
    }
    vector<int> locs;
    if((j - i + 1) % 2 == 0)
    {
        locs.push_back(i);
        i++;
    }
    int d = j - i;
    //cout << "d = " << d << endl;
    int p1 = even[d + 2].first, p2 = even[d + 2].second;
    int d1 = p1 - 1, d2 = p2 - 1;
    locs.push_back(i);
    locs.push_back(i + d1);
    locs.push_back(i + d1 + d2);
    //for(int i = 0; i < locs.size(); i++) cout << locs[i] << ' '; cout << endl;
    
    int a = locs[0], b = locs[1], c = locs[2];
    if(locs.size() == 3)
    {
        res.push_back(make_pair(a, b));
        res.push_back(make_pair(b, c));
        res.push_back(make_pair(a, c));
    }
    else
    {
        int d = locs[3];
        res.push_back(make_pair(a, b));
        res.push_back(make_pair(b, c));
        res.push_back(make_pair(c, d));
        res.push_back(make_pair(b, c));
        res.push_back(make_pair(a, b));
    }
}

vector< pair<int, int> > P;
int val[100100];
int loc[100100];

int main()
{
    cin >> N;
    get_primes();
    setup();
    
    /*while(true)
    {
        int a, b;
        cin >> a >> b;
        prime_swap(a, b);
        for(int i = 0; i < res.size(); i++) cout << res[i].first << ' ' << res[i].second << endl;
        res.clear();
    }*/
    
    for(int i = 1; i <= N; i++)
    {
        pair<int, int> x;
        cin >> x.first;
        x.second = i;
        P.push_back(x);
        loc[x.first] = i;
        val[i] = x.first;
    }
    
    for(int l = 1; l <= N; l++)
    {
        int r = loc[l];
        swap(loc[val[l]], loc[val[r]]);
        swap(val[l], val[r]);
        
        //cout << "swapping " << l << ' ' << r << endl;
        prime_swap(l, r);
    }
    
    cout << res.size() << '\n';
    for(int i = 0; i < res.size(); i++)
    {
        cout << res[i].first << ' ' << res[i].second << '\n';
    }
}