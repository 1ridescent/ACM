#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

vector<int> factors[100100];
int sumfact[100100];
void preprocess()
{
	for(int i = 1; i <= 100010; i++)
		for(int j = 2 * i; j <= 100010; j += i)
			factors[j].push_back(i);

	for(int i = 1; i <= 100010; i++)
	{
		sumfact[i] = 0;
		for(int j = 0; j < factors[i].size(); j++)
			sumfact[i] += factors[i][j];
	}
}

int main()
{
	preprocess();
	while(true)
	{
		int x;
		scanf("%d", &x);
		if(x == -1) break;
		//cout << sumfact[x] << endl;
		if(sumfact[x] == x)
		{
			printf("%d = %d", x, factors[x][0]);
			for(int i = 1; i < factors[x].size(); i++)
				printf(" + %d", factors[x][i]);
			printf("\n");
		}
		else printf("%d is NOT perfect.\n", x);
	}
}
