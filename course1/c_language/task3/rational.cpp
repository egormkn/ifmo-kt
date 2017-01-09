#include "rational.h"

rational::rational(int num) {
	n = num;
	d = 1;
}

rational::rational(int num, int denom) {
	n = num;
	d = denom;
	simplify(n, d);
}

int rational::getNum() const {
	return n;
}
	
int rational::getDenom() const {
	return d;
}
	
rational rational::operator +(rational const &a) const {
	int nok = d * a.d / gcd(d, a.d);
	int num = n * (nok / d) + a.n * (nok / a.d), denom = nok;
	simplify(num, denom);
	return rational(num, denom);
}
	
rational rational::operator -(rational const &a) const {
	int nok = d * a.d / gcd(d, a.d);
	int num = n * (nok / d) - a.n * (nok / a.d), denom = nok;
	simplify(num, denom);
	return rational(num, denom);
}
	
rational rational::operator *(rational const &a) const {
	int num = n * a.n, denom = d * a.d;
	simplify(num, denom);
	return rational(num, denom);
}
	
rational rational::operator /(rational const &a) const {
	int num = n * a.d, denom = d * a.n;
	simplify(num, denom);
	return rational(num, denom);
}

int rational::gcd (int a, int b) {
	return b ? gcd (b, a % b) : a;
}

void rational::simplify(int &n, int &d) {
	int g = gcd(n, d);
	while(g != 1) {
		n = n / g;
		d = d / g;
		g = gcd(n, d);
	}
}
