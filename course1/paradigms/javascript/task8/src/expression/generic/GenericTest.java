package expression.generic;

import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Objects;

import static expression.Util.*;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class GenericTest {
    private static final int SIZE = 20;

    protected final List<Op<F<?>>> tests = new ArrayList<>();
    private final Tabulator tabulator = new GenericTabulator();

    public GenericTest() {
        all(
                "10",
                (x, y, z) -> 10,
                (x, y, z) -> 10.0,
                (x, y, z) -> BigInteger.TEN
        );
        all(
                "x",
                (x, y, z) -> x,
                (x, y, z) -> (double) x,
                (x, y, z) -> bi(x)
        );
        all(
                "y + 2",
                (x, y, z) -> y + 2,
                (x, y, z) -> y + 2.0,
                (x, y, z) -> bi(y + 2)
        );
        all(
                "z / 2",
                (x, y, z) -> z / 2,
                (x, y, z) -> z / 2.0,
                (x, y, z) -> bi(z / 2)
        );
        all(
                "y / z",
                (x, y, z) -> y / z,
                (x, y, z) -> y / (double) z,
                (x, y, z) -> bi(y / z)
        );
        all(
                "10000000 * x * y * 10000000 + z",
                (x, y, z) -> i(10000000 * x * y * 10000000L + z),
                (x, y, z) -> 10000000 * x * y * 10000000.0 + z,
                (x, y, z) -> bi(10000000).multiply(bi(x)).multiply(bi(y)).multiply(bi(10000000)).add(bi(z))
        );
        all(
                "x * y + (z - 1) / 10",
                (x, y, z) -> x * y + (z - 1) / 10,
                (x, y, z) -> x * y + (z - 1) / 10.0,
                (x, y, z) -> bi(x * y + (z - 1) / 10)
        );
    }

    protected BigInteger bi(final int x) {
        return BigInteger.valueOf(x);
    }

    protected Integer i(final long x) {
        return Integer.MIN_VALUE <= x && x <= Integer.MAX_VALUE ? (int) x : null;
    }

    protected void all(final String expression, final F<Integer> fi, final F<Double> fd, final F<BigInteger> fb) {
        tests.addAll(Arrays.asList(
                        op("i:" + expression, fi),
                        op("d:" + expression, fd),
                        op("bi:" + expression, fb))
        );
    }

    public void test() {
        for (final Op<F<?>> test : tests) {
            final String[] parts = test.name.split(":");
            test(
                    parts[0], parts[1], test.f,
                    -randomInt(SIZE), randomInt(SIZE),
                    -randomInt(SIZE), randomInt(SIZE),
                    -randomInt(SIZE), randomInt(SIZE)
            );
        }
    }

    private void test(final String mode, final String expression, final F<?> f, final int x1, final int x2, final int y1, final int y2, final int z1, final int z2) {
        System.out.format("mode=%s, x=[%d, %d] y=[%d, %d] z=[%d, %d], expression=%s\n", mode, x1, x2, y1, y2, z1, z2, expression);
        final Object[][][] result;
        try {
            result = tabulator.tabulate(mode, expression, x1, x2, y1, y2, z1, z2);
        } catch (final Exception e) {
            throw new AssertionError(e);
        }
        for (int x = x1; x <= x2; x++) {
            for (int y = y1; y <= y2; y++) {
                for (int z = z1; z <= z2; z++) {
                    Object expected;
                    try {
                        expected = f.apply(x, y, z);
                    } catch (final RuntimeException e) {
                        expected = null;
                    }
                    final Object actual = result[x - x1][y - y1][z - z1];
                    assert Objects.equals(expected, actual) : String.format("table[%d][%d][%d] = %s", x - x1, y - y1, z - z1, actual);
                }
            }
        }
    }

    public static void main(final String[] args) {
        checkAssert(GenericTest.class);
        new GenericTest().test();
    }

    protected interface F<T> {
        T apply(int x, int y, int z);
    }
}
