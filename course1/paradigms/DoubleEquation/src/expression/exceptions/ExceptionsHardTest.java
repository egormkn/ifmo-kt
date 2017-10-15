package expression.exceptions;

import static expression.Util.*;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ExceptionsHardTest extends ExceptionsEasyTest {
    protected ExceptionsHardTest() {
        levels.add(list(op("**", this::power)));
        levels.add(list(op("//", this::log)));

        tests.addAll(list(
                op("2 ** 3", (x, y, z) -> 8L),
                op("2 ** 3 * 3", (x, y, z) -> 24L),
                op("x ** (y * z)", (x, y, z) -> power(x, y * z)),
                op("2 ** x + 1", (x, y, z) -> power(2, x) + 1),
                op("-1 ** (3 ** x)", (x, y, z) -> -1L),
                op("8 // 2", (x, y, z) -> 3L),
                op("x // y", (x, y, z) -> log(x, y))
        ));
    }

    private Long log(final long a, final long b) {
        try {
            final double result = Math.log(a) / Math.log(b);
            return a > 0 && b > 0 && result == result ? (long) result : null;
        } catch (final  ArithmeticException e) {
            return null;
        }
    }

    private Long power(final long a, long b) {
        if (b < 0 || a == 0 && b == 0) {
            return null;
        }
        if (Math.abs(a) <= 1 && b > 2) {
            b = (b - 1) % 2 + 1;
        }

        long result = 1;
        for (int i = 0; i < b; i++) {
            result *= a;
            if (result < Integer.MIN_VALUE || Integer.MAX_VALUE < result) {
                return null;
            }
        }
        return result;
    }

    public static void main(final String[] args) {
        checkAssert(ExceptionsHardTest.class);
        new ExceptionsHardTest().test();
    }
}
