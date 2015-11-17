#include<iostream>
#include<sstream>
#include "Frac.h"
using namespace std;
int main(){
	unsigned n, m;
	cin >> n >> m;
	Martix<Frac> t(n, m);
	cin >> t;
	t.simplify();
	cout << t;
	return 0;
}