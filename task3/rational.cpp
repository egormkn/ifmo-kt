#include "rational.h"

rational::rational(int num) {
	rational::n = num;
	rational::d = 1;
}

rational::rational(int num, int denom) {
	rational::n = num;
	rational::d = denom;
	simplify(rational::n, rational::d);
}

int rational::getNum() const {
	return rational::n;
}
	
int rational::getDenom() const {
	return rational::d;
}
	
rational rational::operator +(rational const &a) const {
	int nok = rational::d * a.d / gcd(rational::d, a.d);
	int num = rational::n * (nok / rational::d) + a.n * (nok / a.d), denom = nok;
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
	
~rational() {
    // Bye bye
}


static int rational::gcd (int a, int b) {
	return b ? gcd (b, a % b) : a;
}

static void rational::simplify(int &n, int &d){
	int g = gcd(n, d);
	while(g != 1) {
		n = n / g;
		d = d / g;
		g = rational::gcd(n, d);
	}
}
