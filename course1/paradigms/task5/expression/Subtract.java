package expression;

public class Subtract extends BinaryOperation {

    public Subtract(CommonExpression left, CommonExpression right) {
        super(left, right);
    }

    @Override
    protected double count(double left, double right) {
        return left - right;
    }

    @Override
    protected int count(int left, int right) {
        return left - right;
    }
}
