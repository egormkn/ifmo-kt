int power(int a, int n) {
    int r = 1;
    
    // r' * a'^n' == a^n
    while (n != 0) {
        // I ∧ n' != 0
		if (n % 2 == 1) {
			// I ∧ n' % 2 == 1
			r *= a; n--;
			// I ∧ n' % 2 == 0
		} else {
			// I ∧ n' % 2 == 0
		}
		// I ∧ n' % 2 == 0
		n /= 2; a *= a;
		// I
    }
    // r' * a'^n' == a^n ∧ n' == 0
    // => r' == a^n
    return r;
}

