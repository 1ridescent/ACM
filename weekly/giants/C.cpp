#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

class vec
{
    public:
    ll x, y;
    int t;
    int i;
    vec() { }
    vec(ll x2, ll y2, int t2, int i2)
    {
        x = x2, y = y2;
        t = t2, i = i2;
    }
    vec normalize()
    {
        ll g = __gcd(abs(x), abs(y));
        return vec(x / g, y / g, t, i);
    }
    double tan()
    {
        return atan2(y, x);
    }

    vec operator+(vec v) { return vec(x + v.x, y + v.y, t, i); }
    vec operator-(vec v) { return vec(x - v.x, y - v.y, t, i); }
    vec operator*(ll s) { return vec(x * s, y * s, t, i); }
};
ll dot(vec u, vec v) { return u.x * v.x + u.y * v.y; }
ll cross(vec u, vec v) { return -u.y * v.x + u.x * v.y; }

vec rotate_cw(vec v)
{
    return vec(v.y, -v.x, v.t, v.i);
}
vec rotate_ccw(vec v)
{
    return vec(-v.y, v.x, v.t, v.i);
}

bool cmp(vec u, vec v)
{
    if(u.x == v.x && u.y == v.y)
    {
        return u.t < v.t;
    }
    return u.tan() < v.tan();
}

int N, Q;

vec P[1000005];

vector<vec> V;

map<pair<ll, ll>, int> freq;
map<pair<ll, ll>, int> freq2;

pair<ll, ll> query[1000005];
int ans[1000005];

int main()
{

    cin >> N;
    for(int i = 0; i < N; i++)
    {
        cin >> P[i].x >> P[i].y;
        P[i + N] = P[i];
    }

    int cur = 0;
    for(int i = 0; i < N; i++)
    {
        {
                vec u = P[i] - P[i + 1];
                vec v = P[i + 2] - P[i + 1];
                if(cross(u, v) > 0) swap(u, v);
            //printf("u=(%lld %lld) v=(%lld %lld)\n", u.x, u.y, v.x, v.y);
                u = rotate_cw(u);
                v = rotate_ccw(v);
            //printf("u=(%lld %lld) v=(%lld %lld)\n", u.x, u.y, v.x, v.y);
                assert(cross(u, v) > 0);
                u.t = 1;
                v.t = -1;
            //printf("u=(%lld %lld) v=(%lld %lld)\n", u.x, u.y, v.x, v.y);
                V.push_back(u.normalize());
                V.push_back(v.normalize());
            if(u.tan() > v.tan()) cur++;
        }

        {
            vec u = P[i + 1] - P[i], v = P[i + 2] - P[i + 1], w = P[i + 3] - P[i + 2];
            if((cross(u * -1, v) > 0) ^ (cross(w, v * -1) > 0))
            {
                v = rotate_ccw(v);
                v = v.normalize();
                //printf("inserting %d %d\n", v.x, v.y);
                freq[make_pair(v.x, v.y)]++;
            }
        }
    }

    cin >> Q;
    for(int i = 0; i < Q; i++)
    {
        vec d;
        cin >> d.x >> d.y;
        d = d.normalize();
        d.t = 0;
        d.i = i;
        V.push_back(d);
        V.push_back(d * -1);
        query[i] = make_pair(d.x, d.y);
    }

    sort(V.begin(), V.end(), cmp);
    for(int i = 0; i < V.size(); i++)
    {
        //printf("cur = %d\n", (int)cur);
        vec v = V[i];
        //printf("v.x v.y v.t = %d %d %d\n", (int)v.x, (int)v.y, (int)v.t);
        if(v.t != 0) cur += v.t;
        else freq2[make_pair(v.x, v.y)] = cur;
    }

    for(int i = 0; i < Q; i++)
    {
        int f = freq[query[i]] + freq2[query[i]];
        query[i] = make_pair(query[i].first * -1, query[i].second * -1);
        int f2 = freq[query[i]] + freq2[query[i]];
        //printf("query %d: %d %d\n", i, f, f2);
        if(f == 1 && f2 == 1) puts("YES");
        else puts("NO");
    }
}
