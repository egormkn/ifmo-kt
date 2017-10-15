#include "rational.h"

rational::rational(int num) {
	rational::n = num;
	rational::d = 1;
}

rational::rational(int num, int denom) {
	rational::n = num;
	rational::d = denom;
	rational::simplify(rational::n, rational::d);
}

int rational::getNum() const {
	return rational::n;
}
	
int rational::getDenom() const {
	return rational::d;
}
	
rational rational::operator +(rational const &a) const {
	int nok = rational::d * a.d / rational::gcd(rational::d, a.d);
	int num = rational::n * (nok / rational::d) + a.n * (nok / a.d), denom = nok;
	simplify(num, denom);
	return rational(num, denom);
}
	
rational rational::operator -(rational const &a) const {
	int nok = d * a.d / rational::gcd(d, a.d);
	int num = n * (nok / d) - a.n * (nok / a.d), denom = nok;
	simplify(num, denom);
	return rational(num, denom);
}
	
rational rational::operator *(rational const &a) const {
	int num = n * a.n, denom = d * a.d;
	rational::simplify(num, denom);
	return rational(num, denom);
}
	
rational rational::operator /(rational const &a) const {
	int num = n * a.d, denom = d * a.n;
	rational::simplify(num, denom);
	return rational(num, denom);
}

int rational::gcd (int a, int b) {
	return b ? rational::gcd (b, a % b) : a;
}

void rational::simplify(int &n, int &d) {
	int g = rational::gcd(n, d);
	while(g != 1) {
		n = n / g;
		d = d / g;
		g = rational::gcd(n, d);
	}
}
