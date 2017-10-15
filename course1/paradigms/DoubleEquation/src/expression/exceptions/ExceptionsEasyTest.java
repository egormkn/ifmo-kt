package expression.exceptions;

import java.util.function.LongUnaryOperator;

import static expression.Util.*;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ExceptionsEasyTest extends ExceptionsTest {
    protected ExceptionsEasyTest() {
        unary.add(op("abs", this::abs));
        unary.add(op("sqrt", a -> sqrt(a, LongUnaryOperator.identity())));

        tests.addAll(list(
                op("abs -4", (x, y, z) -> 4L),
                op("abs " + Integer.MIN_VALUE, (x, y, z) -> null),
                op("sqrt 4", (x, y, z) -> 2L),
                op("sqrt 8", (x, y, z) -> 2L),
                op("sqrt x * y * z", (x, y, z) -> sqrt(x, sx -> sx * y * z)),
                op("sqrt(x * y * z)", (x, y, z) -> sqrt(x * y * z, LongUnaryOperator.identity()))
        ));
    }

    private Long sqrt(final long a, final LongUnaryOperator f) {
        return a >= 0 ? (long) f.applyAsLong((int) Math.sqrt(a)) : null;
    }

    private long abs(final long a) {
        return lift(Math.abs(a)).getRight();
    }

    public static void main(final String[] args) {
        checkAssert(ExceptionsEasyTest.class);
        new ExceptionsEasyTest().test();
    }
}