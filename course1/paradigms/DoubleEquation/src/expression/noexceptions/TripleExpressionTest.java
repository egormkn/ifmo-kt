package expression.noexceptions;

import static expression.Util.*;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class TripleExpressionTest {
    public static void main(final String[] args) {
        checkAssert(TripleExpressionTest.class);
        testExpression("10", new Const(10), (x, y, z) -> 10);
        testExpression("x", new Variable("x"), (x, y, z) -> x);
        testExpression("y", new Variable("y"), (x, y, z) -> y);
        testExpression("z", new Variable("z"), (x, y, z) -> z);
        testExpression("x+2", new Add(new Variable("x"), new Const(2)), (x, y, z) -> x + 2);
        testExpression("2-y", new Subtract(new Const(2), new Variable("y")), (x, y, z) -> 2 - y);
        testExpression("3*z", new Multiply(new Const(3), new Variable("z")), (x, y, z) -> 3 * z);
        testExpression("x/-2", new Divide(new Variable("x"), new Const(-2)), (x, y, z) -> -x / 2);
        testExpression(
                "x*y+(z-1)/10",
                new Add(
                        new Multiply(new Variable("x"), new Variable("y")),
                        new Divide(new Subtract(new Variable("z"), new Const(1)), new Const(10))
                ),
                (x, y, z) -> x * y + (z - 1) / 10
        );
        System.out.println("OK");
    }

    private static void testExpression(final String description, final TripleExpression actual, final TripleExpression expected) {
        System.out.println("Testing " + description);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                for (int k = 0; k < 10; k++) {
                    assertEquals(String.format("f(%d, %d, %d)", i, j, k), actual.evaluate(i, j, k), expected.evaluate(i, j, k));
                }
            }
        }
    }
}
