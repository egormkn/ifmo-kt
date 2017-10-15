package expression.generic;

public abstract class CheckedUnaryOperation<T extends Numeric> implements TripleExpression<T> {
    protected final TripleExpression<T> expr;

    public CheckedUnaryOperation(TripleExpression<T> expr) {
        this.expr = expr;
    }

    protected abstract T count(T r) throws OverflowException, CountException;

    @Override
    public T evaluate(int x, int y, int z) throws CountException, OverflowException, DivisionByZeroException {
        return count(expr.evaluate(x, y, z));
    }
}