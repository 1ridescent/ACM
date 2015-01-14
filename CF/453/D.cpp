#include <iostream>

using namespace std;

typedef long long ll;
ll P;
#define MOD(x) ((((x) % P) + P) % P)

class Matrix
{
	int size;
	Matrix* inner; // NULL if 1x1 matrix
	ll add;

	Matrix()
	{
		size = 1;
		inner = NULL;
		add = 0;
	}
	ll rowsum()
	{
		if(size == 1) return add;
		ll res = inner->rowsum();
		return MOD(res * 2 + add * (size / 2));
	}
	void add_const(ll c)
	{
		if(size == 1) add = MOD(add + c);
		else inner->add_const(c);
	}
	void mult_const(ll c)
	{
		add = MOD(add * c);
		if(size > 1) inner->mult_const(c);
	}
	void print()
	{
		cout << " + " << add << " [";
		if(size > 1) inner->print();
		cout << "]";
	}
};

void add(Matrix A, Matrix B, Matrix& C)
{
	C.size = A.size;
	C.add = MOD(A.add + B.add);
	if(A.size == 1) return;
	
	C.inner = new Matrix();
	add(*(A.inner), *(B.inner), *(C.inner));
}

void mult(Matrix A, Matrix B, Matrix& C)
{
	C.size = A.size;
	if(A.size == 1)
	{
		C.add = A.add * B.add;
		return;
	}

	ll c = MOD(A.add * B.add) * A.size / 2;

	C.inner = new Matrix();
	mult(*(A.inner), *(B.inner), *(C.inner));
	C.inner->mult_const(2);
	C.inner->add_const(MOD(A.inner->rowsum() * B.add + B.inner->rowsum() * A.add + c));
	C.add = MOD(-c);
}

void base_matrix(int size, Matrix& C)
{
	C.size = size;
	C.add = 1;
	if(size == 1)
	{
		C.add = 0;
		return;
	}

	C.inner = new Matrix();
	base_matrix(size / 2, *(C.inner));
}

void matrix_power(Matrix A, ll e, Matrix& C)
{
	if(e == 1)
	{
		C.size = A.size;
		C.add = A.add;
		C.inner = A.inner;
		return;
	}
	Matrix B;
	if(e % 2)
	{
		matrix_power(A, e - 1, B);
		mult(B, A, C);
	}
	else
	{
		matrix_power(A, e / 2, B);
		mult(B, B, C);
	}
}

int main()
{
	Matrix A;
	base_matrix(4, A);
	Matrix C;
	mult(A, A, C);
	C.print();
}
