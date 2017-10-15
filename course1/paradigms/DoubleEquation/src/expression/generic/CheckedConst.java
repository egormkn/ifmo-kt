package expression.generic;

import expression.exceptions.TripleExpression;

public class CheckedConst implements TripleExpression {
    private final int value;

    public CheckedConst(int value) {
        this.value = value;
    }

    @Override
    public int evaluate(int x, int y, int z) {
        return value;
    }
}
