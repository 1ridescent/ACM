/*#include <iostream>
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
		//cout << "\nrotate left: initial = "; this->print(root); cout << endl;
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
		//cout << "end = "; this->print(root); cout << endl;
	}
	inline void rotate_right(node* n)
	{
		//cout << "\nrotate right: initial = "; this->print(root); cout << endl;
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
		//cout << "end = "; this->print(root); cout << endl;
	}
	inline void rotate_up(node* n)
	{
		//cout << "\nrotate up: initial = "; this->print(root); cout << endl;
		if(n == n->parent->left)
			rotate_right(n);
		else
			rotate_left(n);
		//cout << "end = "; this->print(root); cout << endl;
	}
	inline void splay(node* n)
	{
		//cout << "\n\ninitial = "; this->print(root); cout << endl;
		while(n != root)
		{
			if(n->parent != root)
			{
				if((n == n->parent->left) ^ (n->parent == n->parent->parent->left))
				{
					cout << "\n1\n";
					rotate_up(n);
				}
				else
				{
					cout << "\n2\n";
					rotate_up(n->parent);
				}
				this->print(root); cout << endl;
			}
			rotate_up(n);
			this->print(root); cout << endl;
		}
	}
	inline node* find(ll key) // finds key, or where the key would be placed
	{
		if(root == NULL)
			return NULL;

		node* place = root;
		while(true)
		{
			//cout << '-' << place->key << '-';
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
		cout << "next lowest key is " << place->key << endl;
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
	inline void print(node* n)
	{
		return;
		if(n == NULL) return;
		cout << n->key << '(';
		print(n->left);
		cout << ',';
		print(n->right);
		cout << ')';
	}
};*/

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
	/*inline void fix_up(node* n)
	{
		while(n != NULL)
		{
			n->join();
			n = n->parent;
		}
	}*/
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


int main()
{
	SplayTree T;
	while(1)
	{
		char c;
		cin >> c;
		if(c == 'i')
		{
			int i;
			cin >> i;
			T.insert(1,i);
			//T.print(T.root);
		}
		else
		{
			int r;
			cin >> r;
			cout << T.segment_left(r) << endl;
		}
	}
	return 0;
}
