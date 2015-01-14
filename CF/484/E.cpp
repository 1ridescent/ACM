#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

const int INF = 1231231231;

const int SEGSIZE = 334;
const int NUMSEGS = 300;

int N;
int A[SEGSIZE * NUMSEGS];

int minseg[NUMSEGS + 5];
int minsegs[NUMSEGS + 5][NUMSEGS + 5];
int minreach[NUMSEGS + 5][NUMSEGS + 5][2 * SEGSIZE + 5];

int minleft[NUMSEGS + 5][SEGSIZE + 5];
int minright[NUMSEGS + 5][SEGSIZE + 5];

void preprocess()
{
	for(int i = 0; i < NUMSEGS; i++)
	{
		minseg[i] = INF;
		for(int j = 0; j < SEGSIZE; j++)
			minseg[i] = min(minseg[i], A[i * SEGSIZE + j]);
	}

	memset(minsegs, 127, sizeof(minsegs));
	for(int i = 0; i < NUMSEGS; i++)
	{
		minsegs[i][i] = minseg[i];
		for(int j = i + 1; j < NUMSEGS; j++)
			minsegs[i][j] = min(minsegs[i][j - 1], minseg[j]);
	}

	memset(minreach, 127, sizeof(minreach));
	for(int s = 0; s < NUMSEGS; s++)
	{
		for(int i = 0; i < SEGSIZE; i++)
		{
			int cur_min = INF;
			for(int l = 0; l < SEGSIZE - i; l++)
			{
				cur_min = min(cur_min, A[s * SEGSIZE + (i + l)]);
				minreach[s][s][l + 1] = min(minreach[s][s][l + 1], cur_min);
			}
		}
	}

	for(int l = 0; l < NUMSEGS; l++)
		for(int r = l + 1; r < NUMSEGS; r++)
		{
			int nextl = SEGSIZE - 1, nextr = 0;
			int cur_min = INF;
			for(int s = 1; s <= 2 * SEGSIZE; s++)
			{
				char use;
				if(nextl < 0) use = 'r';
				else if(nextr >= SEGSIZE) use = 'l';
				else if(A[l * SEGSIZE + nextl] > A[r * SEGSIZE + nextr]) use = 'l';
				else use = 'r';

				if(use == 'l')
				{
					cur_min = min(cur_min, A[l * SEGSIZE + nextl]);
					nextl--;
				}
				else
				{
					cur_min = min(cur_min, A[r * SEGSIZE + nextr]);
					nextr++;
				}
			}
		}

	memset(minleft, 127, sizeof(minleft));
	for(int s = 0; s < NUMSEGS; s++)
	{
		for(int i = 0; i < SEGSIZE; i++)
			minleft[s][i + 1] = min(minleft[s][i], A[s * SEGSIZE + i]);
	}
	memset(minright, 127, sizeof(minright));
	for(int s = 0; s < NUMSEGS; s++)
	{
		for(int i = 0; i < SEGSIZE; i++)
			minright[s][i + 1] = min(minleft[s][i], A[s * SEGSIZE + (SEGSIZE - 1 - i)]);
	}
}


int Q;
struct
{
	int l, r, w, a;
} queries[100005];
vector<int> smalls[SEGSIZE + 5];


const int MAX = (1 << 17);
int seg[2 * MAX];
int lookup2(int l, int r, int p, int a, int b)
{
	if(r <= a || l >= b) return INF;
	if(l <= a && b <= r) return seg[p];
	int m = (a + b) / 2;
	return min(lookup2(l, r, p * 2, a, m), lookup2(l, r, p * 2 + 1, m, b));
}
int lookup(int l, int r)
{
	return lookup2(l, r + 1, 1, 0, MAX);
}

const int SMALL = SEGSIZE + 2;
void process_smalls()
{
	memset(seg, 127, sizeof(seg));
	for(int s = 0; s <= SMALL; s++)
	{
		for(int i = 0; i < N; i++) seg[i + MAX] = min(seg[i + MAX], A[i + s]);
		for(int p = MAX - 1; p > 0; p--) seg[p] = min(seg[p * 2], seg[p * 2 + 1]);
		for(int i = 0; i < smalls[s].size(); i++)
		{
			int id = smalls[s][i];
			queries[id].a = lookup(queries[id].l, queries[id].r - s + 1);
		}
	}
}

void process_larges()
{
	memset(seg, 127, sizeof(seg));
	for(int i = 0; i < N; i++) seg[i + MAX] = A[i];
	for(int p = MAX - 1; p > 0; p--) seg[p] = min(seg[p * 2], seg[p * 2 + 1]);

	for(int i = 0; i < Q; i++)
	{
		if(queries[i].w <= SMALL) continue;

		int l = queries[i].l, r = queries[i].r, w = queries[i].w;

		// check left
		int leftseg = l / SEGSIZE;
		int leftextra = SEGSIZE - l % SEGSIZE;
		int cur = lookup(leftseg + SEGSIZE, l + w - 1);
		for(int e = leftextra; e >= 0; e--)

	}
}

int main()
{
	memset(A, 0, sizeof(A));

	ios::sync_with_stdio(false);

	cin >> N;
	for(int i = 0; i < N; i++) cin >> A[i];

	preprocess();

	int Q;
	cin >> Q;
	for(int i = 0; i < Q; i++)
	{
		cin >> queries[i].l >> queries[i].r >> queries[i].w;
		queries[i].l--, queries[i].r--;
		if(queries[i].w <= SMALL)
			smalls[queries[i].w].push_back(i);
	}

	process_smalls();
}
