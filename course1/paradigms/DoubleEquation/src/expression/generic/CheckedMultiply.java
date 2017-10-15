package expression.generic;

import expression.exceptions.OverflowException;
import expression.exceptions.TripleExpression;

public class CheckedMultiply extends CheckedBinaryOperation {

    public CheckedMultiply(expression.exceptions.TripleExpression left, TripleExpression right) {
        super(left, right);
    }

    @Override
    protected int count(int left, int right) throws OverflowException {
        if ((right > 0 && (left > Integer.MAX_VALUE / right || left < Integer.MIN_VALUE / right))
                || (right < 0 && ((right != -1 && left > Integer.MIN_VALUE / right) || left < Integer.MAX_VALUE / right))) {
            throw new OverflowException(left + " * " + right);
        }
        return left * right;
    }
}
