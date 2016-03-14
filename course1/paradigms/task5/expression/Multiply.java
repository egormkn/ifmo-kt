package expression;

public class Multiply extends BinaryOperation {

    public Multiply(CommonExpression left, CommonExpression right) {
        super(left, right);
    }

    @Override
    protected double count(double left, double right) {
        return left * right;
    }

    @Override
    protected int count(int left, int right) {
        return left * right;
    }
}
