package expression.generic;

public class CheckedAbs<T extends Numeric> extends CheckedUnaryOperation<T> {
    public CheckedAbs(TripleExpression expr) {
        super(expr);
    }

    @Override
    protected T count(T r) throws OverflowException {
        if (r. == Integer.MIN_VALUE) {
            throw new OverflowException("abs " + r);
        }
        return r < 0 ? -r : r;
    }
}
