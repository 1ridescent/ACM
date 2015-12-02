#include <bits/stdc++.h>

using namespace std;

int main()
{
	int t;cin>>t;while(t--){
	int N;
	cin >> N;
	int n[2];
	int a = 0;
	n[0] = n[1] = 0;
	for(int i = 0; i < N; i++)
	{
		int x;
		cin >> x;
		a ^= x;
		n[x]++;
	}
	cout << (a ? n[1] : n[0]) << endl;
}}
