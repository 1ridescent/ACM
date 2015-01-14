#include <iostream>

using namespace std;

bool check(string& S)
{
	int cnt = 0;
	for(int i = 0; i < S.size(); i++)
	{
		if(S[i] == '(') cnt++;
		else cnt--;
		if(cnt < 0) return false;
	}
	return true;
}

int main()
{
	string S;
	cin >> S;
	int cnt = 0;
	int last = 0;
	int num = 0;
	for(int i = 0; i < S.size(); i++)
	{
		if(S[i] == '(') cnt++;
		else if(S[i] == '#')
		{
			S[i] = ')';
			last = i;
			cnt--;
			num++;
		}
		else cnt--;
	}
	if(cnt < 0)
	{
		cout << -1;
		return 0;
	}
	string T = S.substr(0, last) + string(cnt + 1, ')') + S.substr(last + 1);
	//cout << T << endl;
	if(!check(T))
	{
		cout << -1;
		return 0;
	}
	for(int i = 1; i < num; i++) cout << "1\n";
	cout << cnt + 1;
}
