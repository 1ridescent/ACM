#include <iostream>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const int INF = 1001001000;

struct cow
{
	int height, breed;
};
bool cmp(cow a, cow b)
{
	return a.height < b.height;
}

int N;
cow cows[50050];
set<int> breeds;
map<int, int> freq; // frequency of breeds
int cur_breeds;
int num_breeds;

void insert(int breed)
{
	if(freq[breed] == 0) cur_breeds++;
	freq[breed]++;
}
void remove(int breed)
{
	if(freq[breed] == 1) cur_breeds--;
	freq[breed]--;
}
void reset()
{
	freq.clear();
	cur_breeds = 0;
}
bool test(int range)
{
	reset();
	insert(cows[0].breed);
	int back = 0;
	if(cur_breeds == num_breeds) return true;
	for(int front = 1; front < N; front++)
	{
		while(cows[front].height - cows[back].height > range)
		{
			remove(cows[back].breed);
			back++;
		}
		insert(cows[front].breed);
		if(cur_breeds == num_breeds) return true;
	}
	return false;
}

int main()
{
	cin >> N;
	if(N == 1)
	{
		cout << 0 << endl;
		return 0;
	}
	num_breeds = 0;
	for(int i = 0; i < N; i++)
	{
		cin >> cows[i].height >> cows[i].breed;
		if(breeds.find(cows[i].breed) == breeds.end())
		{
			breeds.insert(cows[i].breed);
			num_breeds++;
		}
	}
	//cout << "nb="<<num_breeds<<endl;
	sort(cows, cows+N, cmp);
	int low = -1, high = INF;
	while(low + 1 < high)
	{
		int mid = (low+high+1)/2;
		if(test(mid)) high = mid;
		else low = mid;
	}
	cout << high << endl;
	return 0;
}
