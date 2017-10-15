package expression.noexceptions;

public class Negate implements CommonExpression {
    private final CommonExpression expr;

    public Negate(CommonExpression expr) {
        this.expr = expr;
    }

    @Override
    public double evaluate(double x) {
        return -expr.evaluate(x);
    }

    @Override
    public int evaluate(int x) {
        return -expr.evaluate(x);
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return -expr.evaluate(x, y, z);
    }
}
