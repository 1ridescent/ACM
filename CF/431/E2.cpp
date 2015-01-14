#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <cassert>

using namespace std;

typedef  ll;

struct node
{
	node *left, *right, *parent;
	ll key, val, total; // total values of subtree rooted at this node
	int label, assign;
	int size;

	node(ll k, ll v)
	{
		left = NULL, right = NULL, parent = NULL;
		key = k, val = v, total = v;
		size = 1;
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
	void print(node* n)
	{
		if(n->left != NULL)
		{
			cout << '(';
			print(n->left);
			cout << ')';
		}
		else cout << '.';
		cout << n->key;
		if(n->right != NULL)
		{
			cout << '(';
			print(n->right);
			cout << ')';
		}
		else cout << '.';
	}
	void print()
	{
		cout << '(';
		if(root != NULL) print(root);
		cout << ')' << endl;
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
	inline node* find(ll key) // finds key, or where the key would be placed.
	//MUST SPLAY AFTERWARDS!
	{
		if(root == NULL)
			return NULL;

		node* place = root;
		while(true)
		{
			if(key == place->key)
				return place;
			else if(key < place->key)
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
	inline node* insert(ll val, ll key)
	{
		node* next = new node(key, val);

		if(root == NULL)
		{
			root = next;
			return next;
		}

		node* place = find(key);
		if(key == place->key)
		{
			place->val += val;
			place->total += val;
			splay(place);
		}
		else if(key < place->key)
		{
			place->set_left(next);
			splay(next);
		}
		else
		{
			place->set_right(next);
			splay(next);
		}
		return next;
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
	inline void remove(node* n)
	{
		if(n->size == 1)
		{
			root = NULL;
			delete n;
			return;
		}
		splay(n);
		if(n->right == NULL)
		{
			root = n->left;
			root->parent = NULL;
			delete n;
		}
		else
		{
			node* next = next_highest(n->key + 1);
			splay(next);
			assert(n->right == NULL);
			next->set_left(n->left);
			delete n;
		}
	}
	inline void remove(ll key)
	{
		node* place = find(key);
		if(place->key == key) remove(place);
	}
	inline node* rank(ll rk)
	{
		node* cur = root;
		while(true)
		{
			int leftsize = (cur->left == NULL ? 0 : cur->left->size);
			if(leftsize >= rk) cur = cur->left;
			else if(leftsize + cur->val == rk) break;
			else if(cur->right == NULL) break;
			else
			{
				cur = cur->right;
				rk -= (leftsize + cur->val);
			}
		}
		splay(cur);
		return cur;
	}
};

SplayTree tree;

int main()
{
	int N, Q;
}
