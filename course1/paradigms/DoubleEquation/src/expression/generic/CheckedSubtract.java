package expression.generic;

public class CheckedSubtract<T> extends CheckedBinaryOperation<T> {

    public CheckedSubtract(TripleExpression left, TripleExpression right) {
        super(left, right);
    }

    @Override
    protected int count(int left, int right) throws OverflowException {
        if ((left < 0 && right > left - Integer.MIN_VALUE)
                || (left >= 0 && right < left - Integer.MAX_VALUE)) {
            throw new OverflowException(left + " - " + right);
        }
        return left - right;
    }
}
