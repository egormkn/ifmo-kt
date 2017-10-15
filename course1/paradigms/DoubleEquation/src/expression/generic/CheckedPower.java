package expression.generic;

import expression.exceptions.CountException;
import expression.exceptions.DivisionByZeroException;
import expression.exceptions.OverflowException;
import expression.exceptions.TripleExpression;

public class CheckedPower extends CheckedBinaryOperation {

    public CheckedPower(expression.exceptions.TripleExpression left, TripleExpression right) {
        super(left, right);
    }

    @Override
    protected int count(int left, int right) throws OverflowException, DivisionByZeroException, CountException {
        if ((left == 0 && right == 0) || right < 0) {
            throw new CountException(left + " ** " + right);
        }
        try {
            int r = 1, a = left, n = right;
            while (n != 0) {
                if (n % 2 == 1) {
                    r = new CheckedMultiply(new CheckedConst(r), new CheckedConst(a)).evaluate(0, 0, 0);
                }
                n /= 2;
                if (n == 0) {
                    break;
                }
                if ((a > 0 && a > Integer.MAX_VALUE / a) || (a < 0 && a < Integer.MAX_VALUE / a)) {
                    throw new OverflowException(left + " ** " + right);
                }
                a = new CheckedMultiply(new CheckedConst(a), new CheckedConst(a)).evaluate(0, 0, 0);
            }
            return r;
        } catch (OverflowException e) {
            throw new OverflowException(left + " ** " + right);
        }
    }
}
