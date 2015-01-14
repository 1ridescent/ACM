#include <iostream>
#include <algorithm>

using namespace std;

typedef long long ll;

int stk[20];
ll test(int ini_len, int cur_len, ll cur_val)
{
	//cout << "ini_len = " << ini_len << ", cur_len = " << cur_len << ", cur_val = " << cur_val << endl;
	if(2 * cur_len >= ini_len)
	{
		if(ini_len == 1)
		{
			if(stk[cur_len] % 2 == 0 && cur_val == 0)
				return 1;
			else return 0;
		}
		//cout << "testing " << cur_val << ", stack = ";
		//for(int i = 1; i <= cur_len; i++) cout << stk[i] << ' ';
		//cout << endl;
		for(int i = ini_len - cur_len; i > 0; i--)
		{
			//cout << "i: " << i << ", cur_val = " << cur_val << endl;
			if(cur_val <= 0) return 0;
			if(cur_val % 10 != stk[i] % 10) return 0;
			cur_val -= stk[i];
			if(i == 1)
			{
				if(cur_val == 0)
				{
					if(ini_len % 2 == 1 && stk[cur_len] % 2 == 1) return 0;

					ll res = 1;
					for(int i = ini_len - cur_len; i > 0; i--)
					{
						ll num;
						if(i > 1) num = 10 - abs(9 - stk[i]);
						else num = min(stk[i], 19 - stk[i]);
						num = max(0LL, num);
						res *= num;
					}
					//cout << "res = " << res << endl;
					return res;
				}
				return 0;
			}
			if(cur_val <= 0) return 0;
			cur_val /= 10;
		}
	}

	if(cur_val <= 0) return 0;

	ll total = 0;
	// don't carry
	stk[cur_len + 1] = cur_val % 10;
	total += test(ini_len, cur_len + 1, cur_val / 10);
	// carry
	stk[cur_len + 1] = cur_val % 10 + 10;
	total += test(ini_len, cur_len + 1, cur_val / 10 - 1);
	return total;
}

int main()
{
	int T;
	cin >> T;
	while(T--)
	{
		ll x;
		cin >> x;
		int len = 0, head = 0;
		for(ll y = x; y > 0; y /= 10)
		{
			len++;
			if(y < 10) head = y;
		}
		cout << test(len, 0, x) + test(len - 1, 0, x) << '\n';
	}
}
