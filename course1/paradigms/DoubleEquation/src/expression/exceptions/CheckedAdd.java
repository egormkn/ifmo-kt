package expression.exceptions;

public class CheckedAdd extends CheckedBinaryOperation {
    public CheckedAdd(TripleExpression left, TripleExpression right) {
        super(left, right);
    }

    @Override
    protected int count(int left, int right) throws OverflowException {
        if ((left < 0 && right < Integer.MIN_VALUE - left)
                || (left > 0 && right > Integer.MAX_VALUE - left)) {
            throw new OverflowException(left + " + " + right);
        }
        return left + right;
    }
}