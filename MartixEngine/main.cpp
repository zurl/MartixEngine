#include<iostream>
#include<sstream>
#include<map>
#include "Frac.h"
using namespace std;
int main(){
	map<string, Martix<Frac>> var;
	string t,a;
	
	int n, m;
	cin >> n >> m;
	Martix<Frac> tm(n,m);
	cin >> tm;
	//cout << tm.rank() << endl;
	tm.simplify();
	cout << tm << endl;
	while (cin >> t){
		if (t == "end")break;
		else if (t == "def"){
			cin >> a;
		}
	}
	return 0;
}