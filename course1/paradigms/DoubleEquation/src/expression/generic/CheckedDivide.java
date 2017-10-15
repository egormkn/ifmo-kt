package expression.generic;

import expression.exceptions.DivisionByZeroException;
import expression.exceptions.OverflowException;
import expression.exceptions.TripleExpression;

public class CheckedDivide extends CheckedBinaryOperation {

    public CheckedDivide(expression.exceptions.TripleExpression left, TripleExpression right) {
        super(left, right);
    }

    @Override
    protected int count(int left, int right) throws OverflowException, DivisionByZeroException {
        if (left == Integer.MIN_VALUE && right == -1) {
            throw new OverflowException(left + " / " + right);
        }
        if (right == 0) {
            throw new DivisionByZeroException(left + " / " + right);
        }
        return left / right;
    }

    public int checkedCount(int left, int right) throws OverflowException, DivisionByZeroException {
        return count(left, right);
    }
}
