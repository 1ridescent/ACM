#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define x first
#define y second

int order[2][2] = { {1, 2}, {4, 3} };

bool cmp1(pair<ll, ll> a, pair<ll, ll> b, ll S)
{
	ll m = S / 2;
	if(order[a.x > m][a.y > m] != order[b.x > m][b.y > m])
		return order[a.x > m][a.y > m] < order[b.x > m][b.y > m];
	if(a.x < m && a.y < m)
	{
		swap(a.x, a.y);
		swap(b.x, b.y);
	}
	else if(a.x < m && a.y > m)
	{
		a.y -= m;
		b.y -= m;
	}
	else if(a.x > m && a.y > m)
	{
		a.x -= m;
		a.y -= m;
		b.x -= m;
		b.y -= m;
	}
	else if(a.x > m && a.y < m)
	{
		a.x -= m;
		b.x -= m;
		a.x = m - a.x;
		b.x = m - b.x;
		a.y = m - a.y;
		b.y = m - b.y;
		swap(a.x, a.y);
				swap(b.x, b.y);

	}
	return cmp1(a, b, m);
}

int N;
ll S;
pair<pair<ll, ll>, string> A[200005];
bool cmp(pair<pair<ll, ll>, string> a, pair<pair<ll, ll>, string> b)
{
	return cmp1(a.first, b.first, S);
}


int main()
{
	cin >> N >> S;
	S <<= 31;
	for(int i = 0; i < N; i++)
	{
		cin >> A[i].first.x >> A[i].first.y >> A[i].second;
		A[i].first.x <<= 31;
		A[i].first.y <<= 31;
		if(A[i].first.x == 0) A[i].first.x++;
		if(A[i].first.y == 0) A[i].first.y++;
		if(A[i].first.x == S) A[i].first.x--;
		if(A[i].first.y == S) A[i].first.y--;
	}
	sort(A, A + N, cmp);
	for(int i = 0; i < N; i++) cout << A[i].second << '\n';
}
