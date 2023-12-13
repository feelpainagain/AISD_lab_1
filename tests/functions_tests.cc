#include <iostream>
#include "functions/functions.h"
#include <complex>

using namespace polynom;
using namespace std;

int main() {
	int e = 10;
	Polynomial <int> a = (5);
	cout << a << endl;
	int* c = new int [3] {4, 6, 8};
	Polynomial <int> b(c, 3);
	for (int i = 0; i < b.size(); i++) {
		cout << i << ':' << b[i] << endl;
	}
	cout << b << endl;

	cout << b[1] << endl;

	cout << b * e << endl;

	b.set(12, 1);
	cout << b << endl;
	
	Polynomial <int> d(c, 3);
	cout << b + d << endl;

	int* f = new int [4] {2, 4, 6, 8};
	Polynomial <int> h(f, 4);
	int* f1 = new int[4] {2, 2, 2, 2};
	Polynomial <int> h1(f1,4);
	h1 =h * 5;
	cout << 1345678 << endl;
	cout << h << endl;
	cout << h1 << endl;


	cout << b + h << endl;

	cout << d.calculation_Polynomial_x(2) << endl;

	cout << differentiate(d) << endl;

	return 0;
}