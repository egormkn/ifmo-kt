package expression.generic;

public interface TripleExpression<T extends Numeric> {
    T evaluate(int x, int y, int z) throws CountException, DivisionByZeroException, OverflowException;
}