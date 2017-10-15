package expression.generic;

import expression.exceptions.CountException;
import expression.exceptions.TripleExpression;

public class CheckedSqrt extends CheckedUnaryOperation<T> {

    private static final int MAX = 46341;

    public CheckedSqrt(TripleExpression expr) {
        super(expr);
    }

    @Override
    protected int count(int r) throws CountException {

        if (r < 0) {
            throw new CountException("sqrt " + r);
        }
        if(r < 2){
            return r;
        }
        int min = 0, max = (r < MAX ? r : MAX), mid;
        while (max - min > 1) {
            mid = (max + min) >>> 1;
            if (mid * mid > r) {
                max = mid;
            } else {
                min = mid;
            }
        }
        return min;
    }
}
