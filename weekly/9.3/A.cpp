#include <iostream>
#include <cstdio>

using namespace std;

int main()
{
	for(int t = 1; ; t++)
	{
		int r, w, l;
		cin >> r;
		if(r == 0) return 0;
		cin >> w >> l;
		if(l * l + w * w <= 4 * r * r) printf("Pizza %d fits on the table.\n", t);
		else printf("Pizza %d does not fit on the table.\n", t);
	}
}
