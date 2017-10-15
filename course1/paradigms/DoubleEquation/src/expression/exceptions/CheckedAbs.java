package expression.exceptions;

public class CheckedAbs extends CheckedUnaryOperation {
    public CheckedAbs(TripleExpression expr) {
        super(expr);
    }

    @Override
    protected int count(int r) throws OverflowException {
        if (r == Integer.MIN_VALUE) {
            throw new OverflowException("abs " + r);
        }
        return r < 0 ? -r : r;
    }
}
