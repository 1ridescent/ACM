#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct rect
{
	int x0, x1, y0, y1;
};
vector<rect> V;

rect P;
void calc()
{
	P = V[0];
	for(int i = 0; i < V.size(); i++)
	{
		P.x0 = min(P.x0, V[i].x0);
		P.x1 = max(P.x1, V[i].x1);
		P.y0 = min(P.y0, V[i].y0);
		P.y1 = max(P.y1, V[i].y1);
	}
	for(int i = 0; i < V.size(); i++)
	{
		//printf("%d: x0=%d x1=%d y0=%d y1=%d\n", i, V[i].x0, V[i].x1, V[i].y0, V[i].y1);
	}
}

int main()
{
	while(true)
	{
		V.clear();
		int W, H, N;
		cin >> W >> H >> N;
		if(!W && !H && !N) break;
		rect r0;
		r0.x0 = 0, r0.x1 = W;
		r0.y0 = 0, r0.y1 = H;
		V.push_back(r0);
		calc();
		for(int t = 0; t < N; t++)
		{
			char D;
			int K;
			cin >> D >> K;
			int size = V.size();
			for(int i = 0; i < size; i++)
			{
				rect p = V[i];
				if(D == 'T')
				{
					int yf = P.y1 - K;
					if(p.y1 >= yf)
					{
						if(p.y0 < yf)
						{
							rect r = p;
							r.y1 = yf;
							V.push_back(r);
							p.y0 = yf;
						}
						p.y0 = yf * 2 - p.y0;
						p.y1 = yf * 2 - p.y1;
						swap(p.y0, p.y1);
					}
				}
				else if(D == 'B')
				{
					int yf = P.y0 + K;
					//printf("yf = %d\n", yf);
					if(p.y0 <= yf)
					{
						if(p.y1 > yf)
						{
							rect r = p;
							r.y0 = yf;
							V.push_back(r);
							p.y1 = yf;
						}
						p.y0 = yf * 2 - p.y0;
						p.y1 = yf * 2 - p.y1;
						swap(p.y0, p.y1);
					}
				}
				else if(D == 'L')
				{
					int xf = P.x0 + K;
					if(p.x0 <= xf)
					{
						if(p.x1 > xf)
						{
							rect r = p;
							r.x0 = xf;
							V.push_back(r);
							p.x1 = xf;
						}
						p.x0 = xf * 2 - p.x0;
						p.x1 = xf * 2 - p.x1;
						swap(p.x0, p.x1);
					}
				}
				else
				{
					int xf = P.x1 - K;
					if(p.x1 >= xf)
					{
						if(p.x0 < xf)
						{
							rect r = p;
							r.x1 = xf;
							V.push_back(r);
							p.x0 = xf;
						}
						p.x0 = xf * 2 - p.x0;
						p.x1 = xf * 2 - p.x1;
						swap(p.x0, p.x1);
					}
				}
				V[i] = p;
			}
			calc();
		}
		int X, Y;
		cin >> X >> Y;
		X += P.x0;
		Y += P.y0;
		//printf("X=%d Y=%d\n", X, Y);
		int cnt = 0;
		for(int i = 0; i < V.size(); i++)
		{
			rect& p = V[i];
			if(p.x0 < X && X < p.x1 && p.y0 < Y && Y < p.y1)
				cnt++;
		}
		cout << cnt << '\n';
	}
}
