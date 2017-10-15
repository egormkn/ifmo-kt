package expression.generic;

import expression.exceptions.CountException;
import expression.exceptions.DivisionByZeroException;
import expression.exceptions.OverflowException;
import expression.exceptions.TripleExpression;

public abstract class CheckedBinaryOperation<T extends Numeric> implements TripleExpression<T> {
    private final TripleExpression<T> left;
    private final TripleExpression<T> right;

    public CheckedBinaryOperation(TripleExpression<T> left, TripleExpression<T> right) {
        this.left = left;
        this.right = right;
    }

    protected abstract T count(T left, T right)
            throws OverflowException, DivisionByZeroException, CountException;

    @Override
    public T evaluate(int x, int y, int z)
            throws DivisionByZeroException, CountException, OverflowException {
        return count(left.evaluate(x, y, z), right.evaluate(x, y, z));
    }
}
