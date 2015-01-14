#include <iostream>

using namespace std;

typedef long long ll;

ll eval(string s, int b)
{
	ll ans = 0;
	for(int i = 0; i < s.size(); i++)
	{
		ans *= b;
		ans += (s[i] - '0');
	}
	return ans;
}

int main()
{
	string s2, s3;
	cin >> s2 >> s3;
	for(int i2 = 0; i2 < s2.size(); i2++)
	{
		for(int i3 = 0; i3 < s3.size(); i3++)
		{
			for(int d = 1; d <= 2; d++)
			{
				int d2 = s2[i2]-'0', d3 = s3[i3]-'0';
				d2 = (d2+1)%2, d3 = (d3+d)%3;
				string t2 = s2, t3 = s3;
				t2[i2] = d2+'0', t3[i3] = d3+'0';
				if(eval(t2, 2) == eval(t3, 3))
				{
					cout << eval(t2, 2) << endl;
					return 0;
				}
			}
		}
	}
	return -1;
}
