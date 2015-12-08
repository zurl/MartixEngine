#ifndef FRAC_LIB_
#define FRAC_LIB_
#include<iostream>
#include<sstream>
#include<vector>
#include<algorithm>
using namespace std;
class Frac{
private:
	int x, y;
	int abs(int x){
		return x > 0 ? x : -x;
	}
	int gcd(int x, int y){
		return y == 0 ? x : gcd(y, x%y);
	}
public:
	Frac(){
		x = 0; y = 1;
	}
	~Frac() = default;
	Frac(const int &a){
		this->x = a;
		this->y = 1;
	}
	Frac(const int &a, const int &b){
		int flag = 1;
		int _gcd = gcd(abs(a), abs(b));
		if (b < 0)flag = -1;
		this->x = a * flag / _gcd;
		this->y = b * flag / _gcd;
	}
	Frac(const Frac &t){
		int flag = 1;
		int _gcd = gcd(abs(t.x), abs(t.y));
		if (t.y < 0)flag = -1;
		this->x = t.x * flag / _gcd;
		this->y = t.y * flag / _gcd;
	}
	Frac abs()const{
		if (this->x>0)return *this;
		else return Frac(-(this->x), this->y);
	}
	Frac &operator=(const Frac &t){
		int flag = 1;
		int _gcd = gcd(t.x, t.y);
		if (t.y < 0)flag = -1;
		this->x = t.x * flag / _gcd;
		this->y = t.y * flag / _gcd;
		return *this;
	}
	Frac operator+()const{
		return (*this);
	}
	Frac operator-()const{
		return Frac(-(this->x), this->y);
	}
	Frac operator+(const Frac &t)const{
		return Frac(y*t.x + x*t.y, y*t.y);
	}
	Frac operator-(const Frac &t)const{
		return Frac(x*t.y - y*t.x, y*t.y);
	}
	Frac operator*(const Frac &t)const{
		return Frac(x*t.x, y*t.y);
	}
	Frac operator/(const Frac &t)const{
		return Frac(x*t.y, y*t.x);
	}
	Frac &operator+=(const Frac &t){
		*this = *this + t;
		return *this;
	}
	Frac &operator-=(const Frac &t){
		*this = *this - t;
		return *this;
	}
	Frac &operator*=(const Frac &t){
		*this = *this * t;
		return *this;
	}
	Frac &operator/=(const Frac &t){
		*this = *this / t;
		return *this;
	}
	string out(){
		ostringstream os;
		if (this->y == 1){
			os << this->x;
		}
		else{
			os << this->x << "/" << this->y;
		}
		return os.str();
	}
	bool operator>(const Frac &t)const{
		return x*t.y > y*t.x;
	}
	bool operator<(const Frac &t)const{
		return x*t.y < y*t.x;
	}
	bool operator>=(const Frac &t)const{
		return x*t.y >= y*t.x;
	}
	bool operator<=(const Frac &t)const{
		return x*t.y <= y*t.x;
	}
	bool operator==(const Frac &t)const{
		return (x == t.x) && (y == t.y);
	}
	bool operator!=(const Frac &t)const{
		return (x != t.x) || (y != t.y);
	}
};
istream &operator>>(istream &is, Frac &f){
	int x, y = 1; char c;
	is >> x;
	is.get(c);
	if (c == '/')is >> y;
	f = { x, y };
	return is;
}
ostream &operator<<(ostream &os, Frac &f){
	os << f.out();
	return os;
}
Frac abs(const Frac &t){
	return t.abs();
}
template<typename T>
class Martix{
private:
	void throwError(unsigned code)const{
		switch (code){
		case 0:
			cout << "Error : Invaild calculate : Operand martix size mismatch ( Code : #0 ) " << endl;
			break;
		case 1:
			cout << "Error : Reserved Error ( Code : #1 ) " << endl;
			break;
		case 4:
			cout << "Error : Invaild arguments ( Code : #4 ) " << endl;
			break;
		}

	}
public:
	vector<vector<T>> v;
	Martix() = default;
	~Martix() = default;
	Martix(unsigned n){
		v = vector<vector<T>>(n, vector<T>(n));
	}
	Martix(unsigned n, unsigned m){
		v = vector<vector<T>>(n, vector<T>(m));
	}
	inline unsigned getColumnSize()const{
		return v.size();
	}
	inline unsigned getRowSize()const{
		if (getColumnSize() == 0)return 0;
		else return v[0].size();
	}
	inline Martix<T> _lineRender(const Martix<T> &t, T (f)(const T &a, const T &b))const{
		if (getColumnSize() == t.getColumnSize()){
			if (getRowSize() == t.getRowSize()){
				Martix<T> ret(getColumnSize(), getRowSize());
				for (unsigned i = 0; i <= getColumnSize() - 1; i++){
					for (unsigned j = 0; j <= getRowSize() - 1; j++){
						ret.v[i][j] = f(v[i][j], t.v[i][j]);
					}
				}
				return ret;
			}
			else{
				throwError(0);
				return *this;
			}
		}
		else{
			throwError(0);
			return *this;
		}
	}
	inline Martix<T> _mulRender(const Martix<T> &t,T (f)(const T &a, const T &b))const{
		if (getRowSize() == t.getColumnSize()){
			Martix<T> ret(getColumnSize(), t.getRowSize());
			for (unsigned i = 0; i <= getColumnSize() - 1; i++){
				for (unsigned j = 0; j <= t.getRowSize() - 1; j++){
					for (unsigned k = 0; k <= t.getRowSize() - 1; k++){
						ret.v[i][j] += f(v[i][k], t.v[k][j]);
					}
				}
			}
			return ret;
		}
		else{
			throwError(0);
			return *this;
		}
	}
	Martix<T> operator+(const Martix<T> &t)const{
		return _lineRender( t, [](const T &a, const T &b){
			return a + b;
		});
	}
	Martix<T> operator-(const Martix<T> &t)const{
		return this->_lineRender(t, [](const T &a, const T &b){
			return a - b;
		});
	}
	Martix<T> operator*(const Martix<T> &t)const{
		return this->_mulRender( t, [](const T &a, const T &b){
			return a * b;
		});
	}
	Martix<T> operator+=(const Martix<T> &t){
		*this = *this + t;
		return *this;
	}
	Martix<T> &operator-=(const Martix<T> &t){
		*this = *this - t;
		return *this;
	}
	Martix<T> &operator*=(const Martix<T> &t){
		*this = *this * t;
		return *this;
	}
	Martix<T> operator&(const Martix<T> &t)const{
		if (getRowSize() != t.getRowSize()){
			throwError(0);
			return 0;
		}
		else{
			Martix ret;
			for (unsigned i = 0; i <= getColumnSize() - 1; i++){
				ret.v.emplace_back(vector<T>());
				for (auto &x : v[i])ret.v[i].emplace_back(x);
				for (auto &x : t.v[i])ret.v[i].emplace_back(x);
			}
			return ret;
		}
	}
	Martix<T> operator|(const Martix<T> &t)const{
		if (getRowSize() != t.getRowSize()){
			throwError(0);
			return 0;
		}
		else{
			Martix ret = *this;
			for (auto &x : t.v){
				ret.v.emplace_back(x);
			}
			return ret;
		}
	}
	Martix<T> &operator&=(const Martix<T> t){
		return *this & t;
	}
	Martix<T> &operator|=(const Martix<T> t){
		return *this | t;
	}
	bool swapColumn(const unsigned &a, const unsigned &b){
		if (a == b)return 1;
		for (unsigned i = 0; i <= getRowSize() - 1; i++){
			swap(v[a][i], v[b][i]);
		}
		return 1;
	}
	bool swapRow(const unsigned &a, const unsigned &b){
		if (a == b)return 1;
		for (unsigned i = 0; i <= getColumnSize() - 1; i++){
			swap(v[i][a], v[i][b]);
		}
		return 1;
	}
	bool mulColumn(const unsigned &n, const T &t){
		if (t == 1)return 1;
		for (unsigned i = 0; i <= getRowSize() - 1; i++){
			v[n][i] *= t;
		}
		return 1;
	}
	bool mulRow(const unsigned &n, const T &t){
		if (t == 1)return 1;
		for (unsigned i = 0; i <= getColumnSize() - 1; i++){
			v[i][n] *= t;
		}
		return 1;
	}
	bool addColumn(const unsigned &a, const unsigned &b, const T &t){
		if (t == 0)return 1;
		for (unsigned i = 0; i <= getRowSize() - 1; i++){
			v[b][i] += v[a][i] * t;
		}
		return 1;
	}
	bool addRow(const unsigned &n, const T &t){
		if (t == 0)return 1;
		for (unsigned i = 0; i <= getColumnSize() - 1; i++){
			v[i][b] += v[i][a] * t;
		}
		return 1;
	}
	T simplify(){
		//preprocessor
		T ret = 1;
		for (unsigned i = 0; i <= getColumnSize() - 1; i++){
			T max = 0;
			unsigned maxn = 1;
			for (unsigned j = i; j <= getColumnSize() - 1; j++){
				if (abs(v[j][i]) > max){
					max = abs(v[j][i]);
					maxn = j;
				}
			}
			swapColumn(i, maxn);
			ret = -ret;
		}
		for (unsigned i = 0; i <= getColumnSize() - 1; i++){
			if (v[i][i] == 0)continue;
			ret = ret * v[i][i];
			mulColumn(i, T(1) / v[i][i]);
			
			for (unsigned j = 0; j <= getColumnSize() - 1; j++){
				if (j == i)continue;
				if (v[j][i] == 0)continue;
				T temp = (-v[j][i]) / v[i][i];
				addColumn(i, j, temp);
			}
		}
		return ret;
	}
	Martix<T> getDivide(const unsigned &ux, const unsigned &uy, const unsigned &dx, const unsigned &dy)const{
		if (ux < 0 || uy < 0 || dx < 0 || dy < 0 ||
			ux > dx || uy > dy ||
			dx >= getColumnSize() || dy >= getRowSize()){
			throwError(4);
			return *this;
		}
		else{
			Martix<T> ret;
			for (unsigned i = ux; i <= dx; i++){
				ret.v.emplace_back(vector<T>());
				for (unsigned j = uy; j <= dy; j++){
					ret.v[i - ux].emplace_back(v[i][j]);
				}
			}
			return ret;
		}
	}
	Martix<T> operator!()const{
		Martix ret;
		for (int i = 0; i <= getRowSize() - 1; i++){
			ret.v.emplace_back(vector<T>());
			for (int j = 0; j <= getColumn() - 1; j++){
				ret.v[i].emplace_back(v[j][i]);
			}
		}
		return ret;
	}
	Martix<T> operator~()const{
		if (getColumnSize() != getRowSize()){
			throwError(0);
			return *this;
		}
		Martix<T> ret((*this)&getUnitMartix<T>(this->getColumnSize()));
		ret.simplify();
		//return ret;
		return ret.getDivide(0, getRowSize(), getColumnSize() - 1, 2 * getRowSize() - 1);
	}
	T rank()const{
		Martix<T> ret = *this;
		T ans = 0;
		ret.simplify();
		for (auto &x : ret.v){
			bool flag = 0;
			for (auto &y : x){
				if (y != 0)flag = 1;
			}
			ans += flag;
		}
		return ans;
	}
	T det()const{
		if (getColumnSize() != getRowSize()){
			throwError(0);
			return 0;
		}
		Martix<T> ret = *this;
		T ans = ret.simplify();
		for (unsigned i = 0; i <= ret.getColumnSize()-1; i++){
			ans *= ret.v[i][i];
		}
		return ans;
	}
};
template<typename T>
istream &operator>>(istream &is, Martix<T> &t){
	for (auto &i : t.v){
		for (auto &j : i){
			is >> j;
		}
	}
	return is;
}
template<typename T>
ostream &operator<<(ostream &os, Martix<T> &t){
	for (auto &i : t.v){
		for (auto &j : i){
			os << j << " ";
		}
		os << endl;
	}
	return os;
}
template<typename T>
Martix<T> getUnitMartix(const unsigned &n){
	Martix<T> ret(n);
	for (unsigned i = 0; i <= n - 1; i++){
		ret.v[i][i] = 1;
	}
	return ret;
}
#endif
