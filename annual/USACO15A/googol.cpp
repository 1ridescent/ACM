#include <bits/stdc++.h>

using namespace std;

vector<int> add(vector<int> a, vector<int> b)
{
	while(a.size() < b.size()) a.push_back(0);
	while(b.size() < a.size()) b.push_back(0);
	int n = a.size();
	vector<int> c(n);
	int carry = 0;
	for(int i = 0; i < n; i++)
	{
		c[i] = a[i] + b[i] + carry;
		if(c[i] >= 10)
		{
			c[i] -= 10;
			carry = 1;
		}
		else carry = 0;
	}
	if(carry) c.push_back(1);
	return c;
}

struct bignum
{
	deque<int> bits;
	void add1()
	{
		int i = 0;
		if(i == bits.size()) bits.push_back(0);
		while(bits[i] == 1)
		{
			i++;
			if(i == bits.size()) bits.push_back(0);
		}
		bits[i] = 1;
		for(int j = 0; j < i; j++) bits[j] = 0;
	}
	void sub1()
	{
		int i = 0;
		while(bits[i] == 0) i++;
		bits[i] = 0;
		if(i == bits.size() - 1) bits.pop_back();
		for(int j = 0; j < i; j++) bits[j] = 1;
	}
	void mul2()
	{
		bits.push_front(0);
	}
	int mod2()
	{
		if(bits.empty()) return 0;
		return bits[0];
	}
	void div2()
	{
		if(!bits.empty()) bits.pop_front();
	}
	bool is0()
	{
		return bits.empty();
	}
	string to_string()
	{
		vector<int> one(1, 1);
		vector<int> n = one;
		for(int i = bits.size() - 2; i >= 0; i--)
		{
			n = add(n, n);
			if(bits[i]) n = add(n, one);
		}
		string s;
		for(int i = 0; i < n.size(); i++)
			s = char('0' + n[i]) + s;
		return s;
	}
	void input()
	{
		int n;
		cin >> n;
		for(int i = 0; i < n; i++)
		{
			int b;
			cin >> b;
			bits.push_back(b);
		}
	}
	void output()
	{
		for(int i = 0; i < bits.size(); i++)
			cout << bits[i] << ' ';
		cout << endl;
	}
};

void test()
{
	bignum b;
	b.input();
	b.add1();
	b.sub1();
	b.output();
	cout << b.to_string();
}

int main()
{
	//freopen("googol.in","r",stdin);freopen("googol.out","w",stdout);
	vector<string> dfs;
	string cur = "1";
	dfs.push_back("1");
	while(true)
	{
		cout << cur << endl;
		string l, r;
		cin >> l >> r;
		if(l == "0") break;
		cur = l;
		dfs.push_back(r);
	}
	bignum num;
	num.add1();
	//cout << "num = " << num.to_string() << endl;
	while(dfs.size() > 1)
	{
		bignum temp;
		temp.bits = num.bits;
		temp.sub1();
		// temp or temp+1 ?
		string cur = dfs.back();
		while(!temp.is0())
		{
			cout << cur << endl;
			string l, r;
			cin >> l >> r;
			temp.sub1();
			if(temp.mod2())
				cur = r;
			else
				cur = l;
			temp.div2();
		}
		num.mul2();
		if(cur != "0")
			num.add1();
		dfs.pop_back();
	}
	cout << "Answer " << num.to_string() << endl;
}
