#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

typedef long long ll;

struct Treap
{
	int size, key, val;
	ll pri;
	Treap *left, *right;

	Treap(int s, int k, int v, ll p, Treap* l, Treap* r)
	{
		size = s;
		key = k;
		val = v;
		pri = p;
		left = l;
		right = r;
	}
};
Treap* nil = new Treap(0, 0, 0, -1, NULL, NULL);

void get_size(Treap* &node)
{
	if(node == nil) return;
	node->size = node->left->size + node->right->size + 1;
}
void rotate_left(Treap* &node)
{
	Treap* aux = node->left;
	node->left = node->left->right;
	aux->right = node;
	node = aux;

	get_size(node->left);
	get_size(node->right);
	get_size(node);
}
void rotate_right(Treap* &node)
{
	Treap* aux = node->right;
	node->right = node->right->left;
	aux->left = node;
	node = aux;

	get_size(node->left);
	get_size(node->right);
	get_size(node);
}
void balance(Treap* &node)
{
	if(node->left->pri > node->pri) rotate_left(node);
	if(node->right->pri > node->pri) rotate_right(node);
	get_size(node);
}
void insert(Treap* &node, int key, int val)
{
	if(node == nil)
	{
		node = new Treap(1, key, val, ((ll)(rand()) << 15) + rand(), nil, nil);
		return;
	}

	if(node->key > key) insert(node->left, key, val);
	else insert(node->right, key, val);

	balance(node);
}
void erase(Treap* &node, int key)
{
	if(node->key > key)
	{
		erase(node->left, key);
		balance(node);
	}
	else if(node->key < key)
	{
		erase(node->right, key);
		balance(node);
	}
	else
	{
		if(node->left == nil && node->right == nil)
		{
			delete node;
			node = nil;
			return;
		}
		if(node->left->pri > node->right->pri)
		{
			rotate_left(node);
			erase(node->right, key);
			balance(node);
		}
		else
		{
			rotate_right(node);
			erase(node->left, key);
			balance(node);
		}
	}
}
Treap* find_rank(Treap* node, int rank)
{
	if(node->left->size == rank) return node;

	if(node->left->size > rank) return find_rank(node->left, rank);
	else return find_rank(node->right, rank - node->left->size - 1);
}
void dfs_order_print(Treap* node)
{
	if(node == nil) return;
	cout << "(";
	dfs_order_print(node->left);
	cout << ")";
	cout << node->key << "->" << node->val;
	cout << "(";
	dfs_order_print(node->right);
	cout << ")";
}


Treap* root = nil;

int main()
{
	srand(time(0));
	while(true)
	{
		char t;
		cin >> t;
		if(t == 'i')
		{
			int k, v;
			cin >> k >> v;
			insert(root, k, v);
		}
		else if(t == 'd')
		{
			int k;
			cin >> k;
			erase(root, k);
		}
		else
		{
			int r;
			cin >> r;
			Treap* node = find_rank(root, r);
			cout << node->key << "->" << node->val << endl;
		}
		dfs_order_print(root);
	}
}
