package expression;

import static expression.Util.*;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class DoubleExpressionTest {
    public static void main(final String[] args) {
        checkAssert(DoubleExpressionTest.class);
        testExpression("10", new Const(10), x -> 10);
        testExpression("x", new Variable("x"), x -> x);
        testExpression("x+2", new Add(new Variable("x"), new Const(2)), x -> x + 2);
        testExpression("2-x", new Subtract(new Const(2), new Variable("x")), x -> 2 - x);
        testExpression("3*x", new Multiply(new Const(3), new Variable("x")), x -> 3 * x);
        testExpression("x/-2", new Divide(new Variable("x"), new Const(-2)), x -> -x / 2);
        testExpression(
                "x*x+(x-1)/10",
                new Add(
                        new Multiply(new Variable("x"), new Variable("x")),
                        new Divide(new Subtract(new Variable("x"), new Const(1)), new Const(10))
                ),
                x -> x * x + (x - 1) / 10
        );
        System.out.println("OK");
    }

    private static void testExpression(final String description, final DoubleExpression actual, final DoubleExpression expected) {
        System.out.println("Testing " + description);
        for (int i = 0; i < 10; i++) {
            assertEquals(String.format("f(%d)", i), actual.evaluate(i), expected.evaluate(i));
        }
    }
}
