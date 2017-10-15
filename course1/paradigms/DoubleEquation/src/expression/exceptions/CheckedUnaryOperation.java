package expression.exceptions;

public abstract class CheckedUnaryOperation implements TripleExpression {
    protected final TripleExpression expr;

    public CheckedUnaryOperation(TripleExpression expr) {
        this.expr = expr;
    }

    protected abstract int count(int r) throws OverflowException, CountException;

    @Override
    public int evaluate(int x, int y, int z) throws CountException, OverflowException, DivisionByZeroException {
        return count(expr.evaluate(x, y, z));
    }
}