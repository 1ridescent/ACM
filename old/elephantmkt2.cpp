#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

struct node
{
	node *left, *right, *parent;
	ll key, val, total; // total values of subtree rooted at this node
	int size;
	//bool rev;

	node(ll k, ll v)
	{
		left = NULL, right = NULL, parent = NULL;
		key = k, val = v, total = v;
		size = 1;
		//rev = false;
	}
	inline void set_left(node* n)
	{
		left = n;
		if(left != NULL) left->parent = this;
	}
	inline void set_right(node* n)
	{
		right = n;
		if(right != NULL) right->parent = this;
	}
	inline void push()
	{
		/*if(rev)
		{
			swap(left, right);
			if(left != NULL) left->rev ^= 1;
			if(right != NULL) right->rev ^= 1;
			rev = false;
		}*/
	}
	inline void join()
	{
		size = 1;
		total = val;
		if(left != NULL)
		{
			size += left->size;
			total += left->total;
		}
		if(right != NULL)
		{
			size += right->size;
			total += right->total;
		}
	}
};

class SplayTree
{
public:
	node* root;
	SplayTree()
	{
		root = NULL;
	}
	inline void rotate_left(node* n)
	{
		node *p = n->parent;
		node *pp = p->parent;

		p->set_right(n->left);
		n->set_left(p);

		if(pp == NULL)
		{
			root = n;
			root->parent = NULL;
		}
		else if(p == pp->left)
			pp->set_left(n);
		else
			pp->set_right(n);

		p->join();
		n->join();
	}
	inline void rotate_right(node* n)
	{
		node *p = n->parent;
		node *pp = p->parent;

		p->set_left(n->right);
		n->set_right(p);

		if(pp == NULL)
		{
			root = n;
			root->parent = NULL;
		}
		else if(p == pp->left)
			pp->set_left(n);
		else
			pp->set_right(n);

		p->join();
		n->join();
	}
	inline void rotate_up(node* n)
	{
		if(n == n->parent->left)
			rotate_right(n);
		else
			rotate_left(n);
	}
	inline void splay(node* n)
	{
		while(n != root)
		{
			if(n->parent != root)
			{
				if((n == n->parent->left) ^ (n->parent == n->parent->parent->left))
					rotate_up(n);
				else
					rotate_up(n->parent);
			}
			rotate_up(n);
		}
	}
	inline node* find(ll key) // finds key, or where the key would be placed
	{
		if(root == NULL)
			return NULL;

		node* place = root;
		while(true)
		{
			if(key == place->key)
				return place;
			else if(key < place->key) // rev??
			{
				if(place->left == NULL) return place;
				place = place->left;
			}
			else
			{
				if(place->right == NULL) return place;
				place = place->right;
			}
		}
	}
	inline void insert(ll val, ll key)
	{
		node* next = new node(key, val);

		if(root == NULL)
		{
			root = next;
			return;
		}

		node* place = find(key);
		if(key == place->key) // rev?
		{
			place->val += val;
			place->total += val;
			splay(place);
			// NOTE: if this fails, try splaying place first before updating values
		}
		else if(key < place->key) // rev?
		{
			place->set_left(next);
			splay(next);
		}
		else
		{
			place->set_right(next);
			splay(next);
		}
	}
	inline node* next_lowest(ll key) // returns largest key <= given key, or NULL
	{
		if(root == NULL) return NULL;

		node* place = root;
		node* next = NULL;
		while(true)
		{
			if(key == place->key)
				return place;
			else if(key < place->key)
			{
				if(place->left == NULL) return next;
				place = place->left;
			}
			else
			{
				next = place;
				if(place->right == NULL) return next;
				place = place->right;
			}
		}
	}
	inline node* next_highest(ll key)
	{
		if(root == NULL) return NULL;

		node* place = root;
		node* next = NULL;
		while(true)
		{
			if(key == place->key)
				return place;
			else if(key < place->key)
			{
				next = place;
				if(place->left == NULL) return next;
				place = place->left;
			}
			else
			{
				if(place->right == NULL) return next;
				place = place->right;
			}
		}
	}

	// custom functions
	ll get_total(node* n)
	{
		return (n == NULL) ? 0 : n->total;
	}
	inline ll segment_left(ll key) // inclusive
	{
		node* place = next_lowest(key);
		if(place == NULL) return 0;

		splay(place);
		return get_total(place->left) + root->val;
	}
	inline ll segment_right(ll key)
	{
		node* place = next_highest(key);
		if(place == NULL) return 0;

		splay(place);
		return get_total(place->right) + root->val;
	}
};

const int MAX = (1<<30);
SplayTree B; // number
SplayTree S;
SplayTree Bt; // total price
SplayTree St;

int main()
{
	string s;
	while(1)
	{
		cin >> s;
		if(s[0] == 'e') break;
		ll d, p;
		cin >> d >> p;
		if(s[0] == 'b')
		{
			//cout << "S[" << p << "] += " << d << endl;
			S.insert(d, p);//insert(S, d, p);
			St.insert(d*p, p);//insert(St, d*p, p);
		}
		else if(s[0] == 's')
		{
			//cout << "B[" << p << "] += " << d << endl;
			B.insert(d, p);//insert(B, d, p);
			Bt.insert(d*p, p);//insert(Bt, d*p, p);
		}
		ll low = 0, high = MAX;
		while(low + 1 < high)
		{
			ll mid = (low+high)/2;
			//cout << "numB[" << mid-1 << "] = " << B.segment_left(mid-1) << endl;
			//cout << "numS[" << mid << "] = " << S.segment_right(mid) << endl;
			ll numB = B.segment_left(mid-1);//lookup(B, 0, mid);
			ll numS = S.segment_right(mid);//lookup(S, mid, MAX);
			if(numS < numB) high = mid; // i'm buying too many
			else low = mid;
		}
		//cout << low << endl; continue;
		ll numB = B.segment_left(low-1);//lookup(B, 0, low);
		ll numS = S.segment_right(low);//lookup(S, low, MAX);
		ll numBt = Bt.segment_left(low-1);//lookup(Bt, 0, low);
		ll numSt = St.segment_right(low) - (numS-numB)*low;//lookup(St, low, MAX) - (numS-numB)*low;
		//cout << numB << ' ' << numS << ' ' << numBt << ' ' << numSt << endl;
		cout << numSt-numBt << endl;
	}
	return 0;
}
