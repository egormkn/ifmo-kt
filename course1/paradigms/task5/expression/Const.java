package expression;

public class Const implements CommonExpression {
    private final double dValue;
    private final int iValue;

    public Const(double value) {
        dValue = value;
        iValue = 0;
    }

    public Const(int value) {
        iValue = value;
        dValue = value;
    }

    @Override
    public double evaluate(double x) {
        return dValue;
    }

    @Override
    public int evaluate(int x) {
        return iValue;
    }
}
