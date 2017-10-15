package expression.noexceptions;

public class Divide extends BinaryOperation {

    public Divide(CommonExpression left, CommonExpression right) {
        super(left, right);
    }

    @Override
    protected double count(double left, double right) {
        return left / right;
    }

    @Override
    protected int count(int left, int right) {
        return left / right;
    }
}
