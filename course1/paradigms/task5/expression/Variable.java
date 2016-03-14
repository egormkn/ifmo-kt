package expression;

public class Variable implements CommonExpression {

    private final String name;

    public Variable(String name) {
        this.name = name;
    }

    public double evaluate(double x) {
        return x;
    }

    @Override
    public int evaluate(int x) {
        return x;
    }
}
