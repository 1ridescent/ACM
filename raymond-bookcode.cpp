/* splay tree with kth element, number of elements less than k, insert, erase */
struct splay_tree // cannot have duplicates {
 struct node {
 node *C[2];
 node *P;
 int v, ss;

        node(int v) : v(v), ss(1), P(NULL) {memset(C, NULL, sizeof(C));}

        int d() {
            return (this == P->C[1]);
        }
        void setc(node *x, int d) {
            C[d] = x;
            if (x) x->P = this;
        }
        void upd() {
            ss = 1 + (C[0] ? C[0]->ss : 0) + (C[1] ? C[1]->ss : 0);
        }
    } *root;

    void rotate(node *x) {
        node *y = x->P;
        int d = x->d();

        if (y->P) y->P->setc(x, y->d());
        else root = x, x->P = NULL;

        y->setc(x->C[!d], d);
        x->setc(y, !d);

        y->upd();
        x->upd();
    }

    void splay(node *x) {
        if (!x) return;

        node *y;
        while (x->P) {
            if ((y = x->P)->P) {
                if (y->d() == x->d()) rotate(y);
                else rotate(x);
            }
            rotate(x);
        }
    }

    node *find(int v) {
        node *p, *x = root;
        while (x) {
            p = x;
            if (x->v == v) {
                splay(x);
                return x;
            }
            x = x->C[x->v < v];
        }
        splay(p);
        return p;
    }

    node *max(node *x) {
        if (!x) return x;
        while (x->C[1]) x = x->C[1];
        splay(x);
        return x;
    }

    node *min(node *x) {
        if (!x) return x;
        while (x->C[0]) x = x->C[0];
        splay(x);
        return x;
    }

    node *lower_bound(int v) {
        node *ans = NULL, *x = root;
        while (x) {
            if (x->v >= v)
                ans = x;
            if (x->v == v) break;
            x = x->C[x->v < v];
        }
        splay(ans);
        return ans;
    }

    void insert(int v) {
        if (!root) {
            root = new node(v);
        }
        else {
            node *x = lower_bound(v);
            if (!x) {
                node *y = new node(v);
                y->setc(root, 0);
                root = y;

                root->upd();
            }
            else {
                if (x->v == v) return;
                node *y = new node(v);
                y->setc(x->C[0], 0);
                x->setc(y, 0);

                y->upd();
                x->upd();
            }
        }
    }

    void erase(int v) {
        node *x = lower_bound(v);
        if (!x || x->v != v) return;

        splay_tree *lside = new splay_tree(), *rside = new splay_tree();
        lside->root = x->C[0]; if (lside->root) lside->root->P = NULL;
        rside->root = x->C[1]; if (rside->root) rside->root->P = NULL;
        delete x;

        if (!lside->root) {
            root = rside->root;
        }
        else if (!rside->root) {
            root = lside->root;
        }
        else {
            lside->max(lside->root);
            lside->root->setc(rside->root, 1);
            root = lside->root;
        }
        if (root) root->upd();
    }

    node *kth(int k) // 0-indexed {
        if (!root) return NULL;
        if (k < 0 || k >= root->ss) return NULL;

        node *x = root;
        int at = (x->C[0] ? x->C[0]->ss : 0);
        while (at != k) {
            if (at < k) {
                x = x->C[1];
                at += (x->C[0] ? x->C[0]->ss : 0) + 1;
            }
            else {
                x = x->C[0];
                at -= (x->C[1] ? x->C[1]->ss : 0) + 1;
            }
        }
        splay(x);
        return x;
    }

    int count(int v) // number < v {
        if (!root) return 0;

        node *x = lower_bound(v);
        if (!x) return root->ss;

        return (x->C[0] ? x->C[0]->ss : 0);
    }

    void print_at(node *at) {
        if (!at) return;
        cout << "( ";
        print_at(at->C[0]);
        cout << " ) [" << at->v << "] ( ";
        print_at(at->C[1]);
        cout << " )";
    }

    void print() {
        print_at(root);
        cout << endl;
    }
};

/* link-cut tree */
struct node {
    node *P, *C[2];
    bool flip;
    node() : flip(0), P(0) {memset(C, 0, sizeof(C));}

    int d() {
        return (this == P->C[1]);
    }
    void setc(node *x, int c) {
        C[c] = x;
        if (x) x->P = this;
        update();
    }
    bool isroot() {
        return (P == NULL || P->C[d()] != this);
    }
    void update() {
        if (flip) {
            flip = false;
            swap(C[0], C[1]);
            if (C[0]) C[0]->flip = !C[0]->flip;
            if (C[1]) C[1]->flip = !C[1]->flip;
        }
    }
};
void rotate(node *x) {
    node *y = x->P;
    y->update();
    x->update();
    int d = x->d();

    if (y->isroot()) x->P = y->P;
    else y->P->setc(x, y->d());

    y->setc(x->C[!d], d);
    x->setc(y, !d);

    x->update();
    y->update();
}
void splay(node *x) {
    while (!x->isroot()) {
        x->P->update();
        if (!x->P->isroot()) {
            x->P->P->update();
            if (x->P->d() == x->d()) rotate(x->P);
            else rotate(x);
        }
        x->P->update();
        rotate(x);
    }
    x->update();
}
void expose(node *x) {
    node *from = NULL;
    for (node *p=x; p; p=p->P) {
        splay(p);
        p->setc(from, 0);
        p->update();
        from = p;
    }
    splay(x);
}
void make_root(node *x) {
    expose(x);
    x->flip = !x->flip;
    x->update();
}
node *getroot(node *x) {
    expose(x);
    while (x->C[1]) {
        x = x->C[1];
        x->update();
    }
    expose(x);
    return x;
}
bool same(node *x, node *y) {
    return getroot(x) == getroot(y);
}
bool link(node *x, node *y) {
    if (getroot(x) == getroot(y))
        return false;
    make_root(x);
    x->P = y;
    return true;
}
bool cut(node *x, node *y) {
    make_root(x);
    expose(y);
    if (y->C[1] == x) {
        x->P = NULL;
        y->C[1] = NULL;
        return true;
    }
    return false;
}


// BBST
#include <bits/stdc++.h>
using namespace std;
struct Node {
  Node *left, *right;
  int val, depth;
  Node(int a) : val(a), depth(1), left(NULL), right(NULL) {}
};
int height(Node *x) {
  return x == NULL ? 0 : x->depth;
}
void updateHeight(Node *x) {
  x->depth = max(height(x->left), height(x->right)) + 1;
}
Node *leftRotate(Node *x) {
  Node *a = x->right, *b = x->right->left;
  x->right = b;
  a->left = x;
  updateHeight(a);
  updateHeight(x);
  return a;
}
Node *rightRotate(Node *x) {
  Node *a = x->left, *b = x->left->right;
  x->left = b;
  a->right = x;
  updateHeight(a);
  updateHeight(x);
  return a;
}
void insert(Node *&x, int a) {
  if (x == NULL) {
    x = new Node(a);
    return;
  }
  if (a == x->val) return; // Already in tree
  if (a < x->val) insert(x->left, a);
  else insert(x->right, a);
  int lefth = height(x->left), righth = height(x->right);
  if (lefth - righth >= 2) {
    if (height(x->left->left) < height(x->left->right))
      x->left = leftRotate(x->left);
    x = rightRotate(x);
  } else if (righth - lefth >= 2) {
    if (height(x->right->left) > height(x->right->right))
      x->right = rightRotate(x->right);
    x = leftRotate(x);
  } else {
    updateHeight(x);
  }
}
void printTree(Node *x) {
  if (x == NULL) return;
  printTree(x->left);
  printf("%d ", x->val);
  printTree(x->right);
}
int A[1000005];
int main() {
  int N = 1000000;
  for (int i = 0; i < N; ++i) A[i] = i;
  srand(time(NULL));
  random_shuffle(A, A + N);
  Node *root = NULL;
  for (int i = 0; i < N; ++i) insert(root, A[i]);
  printf("%d\n", root->depth);
}
// Convex Hull
#include <bits/stdc++.h>
using namespace std;
struct Point {
  int x, y;
} P[2005];
bool cmp(Point a, Point b) {
  if (a.x != b.x) return a.x < b.x;
  return a.y < b.y;
}
int area2(Point &a, Point &b, Point &c) {
  return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}
int main() {
  // Get counter-clockwise convex hull, starting at leftmost bottommost point
  for (int i = 0; i < N; ++i) scanf("%d%d", &P[i].x, &P[i].y);
  sort(P, P + N, cmp);
  vector<Point> up, dn, hull;
  for (int i = 0; i < N; ++i) {
    while (up.size() > 1 && area2(up[up.size() - 2], up.back(), P[i]) >= 0) up.pop_back();
    while (dn.size() > 1 && area2(dn[dn.size() - 2], dn.back(), P[i]) <= 0) dn.pop_back();
    up.push_back(P[i]);
    dn.push_back(P[i]);
  }
  hull = up;
  for (int i = (int)dn.size() - 2; i > 0; --i)
    hull.push_back(dn[i]);
  reverse(hull.begin(), hull.end());
}

// Min Cost Flow
#include <bits/stdc++.h>
using namespace std;
const int INF = 1000000000;
int C[105][105], cap[105][105], N, SRC, SINK, dist[105], pi[105], cost[105][105], dad[105];
int match[105];
bool done[105];
bool path() {
  memset(done, 0, sizeof(done));
  for (int i = 0; i <= SINK; ++i) dist[i] = INF;
  dist[SRC] = 0;
  for (;;) {
    int x = -1;
    for (int i = 0; i <= SINK; ++i)
      if (!done[i] && (x == -1 || dist[i] < dist[x]))
        x = i;
    if (x == -1) break;
    done[x] = true;
    for (int i = 0; i <= SINK; ++i)
      if (!done[i] && cap[x][i] > 0) {
        int nd = dist[x] + cost[x][i];
        if (nd < dist[i]) {
          dist[i] = nd;
          dad[i] = x;
        }
      }
  }
  if (dist[SINK] == INF) return false;
  int x = SINK;
  while (x != SRC) {
    ++cap[x][dad[x]];
    --cap[dad[x]][x];
    x = dad[x];
  }
  for (int i = 0; i <= SINK; ++i)
    pi[i] = min(pi[i] + dist[i], INF);
  return true;
}
void minCostFlow(int G[105][105]) {
  memset(pi, 0, sizeof(pi));
  for (;;) {
    for (int i = 0; i <= SINK; ++i)
      for (int j = 0; j <= SINK; ++j)
        cost[i][j] = G[i][j] + pi[i] - pi[j];
    if (!path()) break;
  }
  for (int i = 0; i < N; ++i)
    for (int j = N; j < 2 * N; ++j)
      if (!cap[i][j]) {
        match[i] = j;
      }
}
int main() {
  int cn = 1;
  while (scanf("%d", &N) == 1) {
    if (!N) break;
    SRC = 2 * N;
    SINK = 2 * N + 1;
    memset(cap, 0, sizeof(cap));
    memset(C, 0, sizeof(C));
    for (int i = 0; i < N; ++i) {
      cap[SRC][i] = cap[N + i][SINK] = 1;
      for (int j = N; j < SRC; ++j) {
        scanf("%d", &C[i][j]);
        C[j][i] = -C[i][j];
        cap[i][j] = 1;
      }
    }
    minCostFlow(C);
  }
}
// Aho Corasick
#include <bits/stdc++.h>
using namespace std;
char S[100005], word[100005];
struct Node {
  int matchlen;
  Node *fail;
  Node *nex[26];
  Node() {
    matchlen = 0;
    memset(nex, 0, sizeof(nex));
    fail = NULL;
  }
} *root;
char chst[100005];
Node mems[100005];
Node *nodest[100005];
int n, memi;
int main() {
  int N;
  scanf("%s%d", S, &N);
  root = &mems[memi++];
  for (int i = 0; i < N; ++i) {
    scanf("%s", word);
    int len = strlen(word);
    Node *p = root;
    for (int j = 0; j < len; ++j) {
      int c = word[j] - 'a';
      if (p->nex[c] == NULL) {
        p->nex[c] = &mems[memi++];
      }
      p = p->nex[c];
    }
    p->matchlen = len;
  }
  queue<Node*> Q;
  for (int i = 0; i < 26; ++i)
    if (root->nex[i] == NULL) {
      root->nex[i] = root;
    } else {
      root->nex[i]->fail = root;
      Q.push(root->nex[i]);
    }
  while (!Q.empty()) {
    Node *p = Q.front();
    Q.pop();
    for (int i = 0; i < 26; ++i) {
      Node *v = p->fail;
      while (v->nex[i] == NULL) v = v->fail;
      v = v->nex[i];
      if (p->nex[i] != NULL) {
        p->nex[i]->fail = v;
        Q.push(p->nex[i]);
      } else {
        p->nex[i] = v;
      }
    }
  }
  int M = strlen(S);
  Node *p = root;
  nodest[n++] = p;
  for (int i = 0; i < M; ++i) {
    int c = S[i] - 'a';
    p = p->nex[c];
    if (p->matchlen) {
      n -= p->matchlen - 1;
      p = nodest[n - 1];
    } else {
      chst[n] = S[i];
      nodest[n++] = p;
    }
  }
  chst[n] = '\0';
  printf("%s\n", chst + 1);
}
// Suffix Array
#include <bits/stdc++.h>
using namespace std;
const int MAXP = 17;
char S[100005];
int N;
pair<pair<int, int>, int> T[100005];
void getSuffixArray(int rank[MAXP + 1][100005]) {
  for (int i = 0; i < N; ++i) rank[0][i] = S[i];
  for (int l = 1; l <= MAXP; ++l) {
    int len = 1 << (l - 1);
    for (int i = 0; i < N; ++i) {
      int nex = i + len < N ? rank[l - 1][i + len] : -1;
      T[i] = make_pair(make_pair(rank[l - 1][i], nex), i);
    }
    sort(T, T + N);
    for (int i = 0; i < N; ++i) {
      if (i && T[i].first == T[i - 1].first) rank[l][T[i].second] = rank[l][T[i - 1].second];
      else rank[l][T[i].second] = i;
    }
  }
}
int getLcp(int a, int b, int rank[MAXP + 1][100005]) {
  int len = 0;
  for (int l = MAXP; l >= 0; --l) {
    if (a + len >= N || b + len >= N) break;
    if (rank[l][a + len] == rank[l][b + len])
      len += 1 << l;
  }
  return len;
}
int main() {
  while (scanf("%s", S) == 1) {
    if (S[0] == '0') break;
    N = strlen(S);
    getSuffixArray(sufrank);
  }
}


// DINIC
const int MAXV = 3000000;
const int MAXE = 2 * 30000000;
const int INF = 1000000005, CAPINF = 1000000005;

template <typename T> struct Dinic {
 int V, source, sink;
 int eind, eadj [MAXE], eprev [MAXE], elast [MAXV], start [MAXV];
 int front, back, q [MAXV], dist [MAXV];
 T ecap [MAXE];

 inline void init (int v) {
 V = v; eind = 0;
 memset (elast, -1, V * sizeof (int));
 }

 inline void addedge (int a, int b, T cap1, T cap2) {
 eadj [eind] = b; ecap [eind] = cap1;
 eprev [eind] = elast [a]; elast [a] = eind++;
 eadj [eind] = a; ecap [eind] = cap2;
 eprev [eind] = elast [b]; elast [b] = eind++;
 }

 bool bfs () {
 memset (dist, 63, V * sizeof (int));
 front = back = 0;
 q [back++] = source; dist [source] = 0;

 while (front < back) {
 int top = q [front++];

 for (int i = elast [top]; i != -1; i = eprev [i])
 if (ecap [i] > 0 && dist [top] + 1 < dist [eadj [i]]) {
 dist [eadj [i]] = dist [top] + 1;
 q [back++] = eadj [i];
 }
 }

 return dist [sink] < INF;
 }

    T dfs (int num, T pcap) {
        if (num == sink) return pcap;
        T total = 0;

        for (int &i = start [num]; i != -1; i = eprev [i])
            if (ecap [i] > 0 && dist [num] + 1 == dist [eadj [i]]) {
                T p = dfs (eadj [i], min (pcap, ecap [i]));
                ecap [i] -= p; ecap [i ^ 1] += p;
                pcap -= p; total += p;
                if (pcap == 0) break;
            }

        return total;
    }

    T flow (int _source, int _sink) {
        if (V == 0) return -1;

        source = _source; sink = _sink;
        T total = 0;
        while (bfs ()) {
            memcpy (start, elast, V * sizeof (int));
            total += dfs (source, CAPINF);
        }

        return total;
    }
};
