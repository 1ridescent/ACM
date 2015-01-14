#include <iostream>
#include <cmath>
#include <cstdio>

using namespace std;

int sx, sy, sz;

int tx, ty, tz;
int tx2, ty2, tz2;

void update()
{
	tx = tx2;
	ty = ty2;
	tz = tz2;
}

void Up()
{
	tx2 = tz;
	ty2 = ty;
	tz2 = -tx;
	update();
}
void Down()
{
	tx2 = -tz;
	ty2 = ty;
	tz2 = tx;
	update();
}
void Left()
{
	tx2 = ty;
	ty2 = -tx;
	tz2 = tz;
	update();
}
void Right()
{
	tx2 = -ty;
	ty2 = tx;
	tz2 = tz;
	update();
}

void Forward()
{
	tx--;
}

double dist()
{
	return sqrt(tx * tx + ty * ty + tz * tz);
}

int main()
{
	cin >> sx >> sy >> sz;
	cin >> tx >> ty >> tz;
	tx -= sx;
	ty -= sy;
	tz -= sz;
	sx = sy = sz = 0;
	double best = dist();
	while(true)
	{
		int d;
		cin >> d;
		for(int i = 0; i < d; i++)
		{
			Forward();
			best = min(best, dist());
		}
		char c;
		cin >> c;
		if(c == 'L') Left();
		else if(c == 'R') Right();
		else if(c == 'U') Up();
		else if(c == 'D') Down();
		else if(c == 'E') break;
	}
	printf("%.2f\n", best);
}

