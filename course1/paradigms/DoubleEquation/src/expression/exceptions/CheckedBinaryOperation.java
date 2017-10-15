package expression.exceptions;

public abstract class CheckedBinaryOperation implements TripleExpression {
    private final TripleExpression left;
    private final TripleExpression right;

    public CheckedBinaryOperation(TripleExpression left, TripleExpression right) {
        this.left = left;
        this.right = right;
    }

    protected abstract int count(int left, int right)
            throws OverflowException, DivisionByZeroException, CountException;

    @Override
    public int evaluate(int x, int y, int z)
            throws DivisionByZeroException, CountException, OverflowException {
        return count(left.evaluate(x, y, z), right.evaluate(x, y, z));
    }
}
