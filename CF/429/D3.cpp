#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<cstdio>
using namespace std;


typedef long long ll;
const int maxn = 200005;

struct node{
 ll x,y;
}point[maxn];

int n;
ll inf;

bool cmp(node p1, node p2){
    if(p1.x != p2.x) return p1.x < p2.x;
    else return p1.y < p2.y;
}
bool cmp2(node p1, node p2){
     if (p1.y != p2.y) return p1.y < p2.y;
     else return p1.x < p2.x;
}
ll dist(node a, node b){
    return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}
ll getmin(ll a, ll b){ 
    return a < b ? a : b;
}
ll solve(int l,int r)
{
    if(l == r) return (ll)2e18;
    if(l == r - 1) return dist(point[l],point[r]);
    if(l == r - 2) return getmin(getmin(dist(point[l],point[l+1]),dist(point[l+1],point[l+2])),dist(point[l],point[l+2]));
    int i, j, mid = (l+r) >> 1;
    ll curmin = getmin(solve(l,mid),solve(mid+1,r));
    sort(point + l, point + r + 1, cmp2);
    for(int i = l;i <= r;i ++)
    for(int j = i+1;j <= i+8 && j <= r;j ++){
        curmin = getmin(curmin,dist(point[i],point[j]));
     }
    return curmin;
}

int main(){
    //freopen("d.in","r",stdin);
    //freopen("d.out","w",stdout);
    scanf("%d",&n);

   for (int i = 0; i < n; i ++){
    scanf("%lld %lld",&point[i].x,&point[i].y);
    }

    
   sort(point, point + n, cmp);
   ll ans = solve(0, n-1);
   printf("%lld\n",(long long)ans);

return 0;
}
