package expression.noexceptions;

public abstract class BinaryOperation implements CommonExpression {
    private final CommonExpression left;
    private final CommonExpression right;

    public BinaryOperation(CommonExpression left, CommonExpression right) {
        this.left = left;
        this.right = right;
    }

    protected abstract double count(double left, double right);

    protected abstract int count(int left, int right);

    @Override
    public double evaluate(double x) {
        return count(left.evaluate(x), right.evaluate(x));
    }

    @Override
    public int evaluate(int x) {
        return count(left.evaluate(x), right.evaluate(x));
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return count(left.evaluate(x, y, z), right.evaluate(x, y, z));
    }
}
