#include <iostream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

map<int, int> breeds;
map<int, set<int> > sizes;

void insert(int i)
{
	sizes[breeds[i]].erase(i);
	if(sizes[breeds[i]].empty())
		sizes.erase(breeds[i]);
	breeds[i]++;
	sizes[breeds[i]].insert(i);
}
void remove(int i)
{
	//cout << "size = " << breeds.size() << endl;
	sizes[breeds[i]].erase(i);
	if(sizes[breeds[i]].empty())
		sizes.erase(breeds[i]);
	breeds[i]--;
	sizes[breeds[i]].insert(i);
	if(breeds[i] == 0)
		breeds.erase(i);
}

int N, K;
int A[100005];

int main()
{
	cin >> N >> K;
	for(int i = 1; i <= N; i++) cin >> A[i];
	int l = 0;
	int best = 0;
	for(int r = 1; r <= N; r++)
	{
		insert(A[r]);
		//cout << "l = " << l << endl;
		while(l <= N && breeds.size() > K + 1)
			remove(A[++l]);
		best = max(best, (sizes.empty() ? 0 : (--sizes.end())->first));
	}
	cout << best << '\n';
}
