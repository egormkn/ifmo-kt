package expression.exceptions;

public class CheckedNegate extends CheckedUnaryOperation {

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
