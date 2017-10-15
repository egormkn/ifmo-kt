package expression.generic;

import expression.exceptions.CountException;
import expression.exceptions.OverflowException;
import expression.exceptions.TripleExpression;

public class CheckedNegate extends CheckedUnaryOperation<T> {

    public CheckedNegate(TripleExpression expr) {
        super(expr);
    }

    @Override
    protected int count(int r) throws OverflowException, CountException {
        if (r == Integer.MIN_VALUE) {
            throw new OverflowException("-(" + r + ")");
        }
        return -r;
    }
}
