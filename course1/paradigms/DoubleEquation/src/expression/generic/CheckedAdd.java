package expression.generic;

public class CheckedAdd<T extends Numeric> extends CheckedBinaryOperation<T> {
    public CheckedAdd(TripleExpression left, TripleExpression right) {
        super(left, right);
    }

    @Override
    protected T count(T left, T right) throws OverflowException {
        return left.add(right);
    }
}