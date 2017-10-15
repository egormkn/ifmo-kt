package expression.generic;

import expression.exceptions.CountException;
import expression.exceptions.TripleExpression;

public class CheckedVariable implements TripleExpression {

    private final String name;

    public CheckedVariable(String name) {
        this.name = name;
    }

    @Override
    public int evaluate(int x, int y, int z) throws CountException {
        switch (name) {
            case "x":
                return x;
            case "y":
                return y;
            case "z":
                return z;
            default:
                throw new CountException("unknown variable '" + name + "'");
        }
    }
}
