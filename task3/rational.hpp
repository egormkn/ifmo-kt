class rational {
    public:
        rational(int num) {
			n = num;
			d = 1;
        }

        rational(int num, int denom) {
			n = num;
			d = denom;
			simplify(n, d);
		}

		int getNum() const {
			return n;
		}
		
		int getDenom() const {
			return d;
		}
		
		rational operator +(rational const &a) const {
			int nok = d * a.d / gcd(d, a.d);
			int num = n * (nok / d) + a.n * (nok / a.d), denom = nok;
			simplify(num, denom);
			return rational(num, denom);
		}
		
		rational operator -(rational const &a) const {
			int nok = d * a.d / gcd(d, a.d);
			int num = n * (nok / d) - a.n * (nok / a.d), denom = nok;
			simplify(num, denom);
			return rational(num, denom);
		}
		
		rational operator *(rational const &a) const {
			int num = n * a.n, denom = d * a.d;
			simplify(num, denom);
			return rational(num, denom);
		}
		
		rational operator /(rational const &a) const {
			int num = n * a.d, denom = d * a.n;
			simplify(num, denom);
			return rational(num, denom);
		}
		
		~rational() {
            // Bye bye
        }


    private:
        int n, d;

		static int gcd (int a, int b) {
			return b ? gcd (b, a % b) : a;
		}

        static void simplify(int &n, int &d){
			int g = gcd(n, d);
			while(g != 1) {
				n = n / g;
				d = d / g;
				g = gcd(n, d);
			}
		}
};
