package expression;

import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Util {
    public static final Random RNG = new Random(58L);

    // Utility class
    private Util() {}

    public static void assertTrue(final String message, final boolean condition) {
        assert condition : message;
    }

    public static void assertEquals(final String message, final int actual, final int expected) {
        assertTrue(String.format("%s: Expected %d, found %d", message, expected, actual), actual == expected);
    }

    public static void assertEquals(final String message, final Object actual, final Object expected) {
        assertTrue(String.format("%s: Expected \"%s\", found \"%s\"", message, expected, actual), actual != null && actual.equals(expected) || expected == null);
    }

    public static void assertEquals(final String message, final double precision, final double actual, final double expected) {
        assertTrue(
                String.format("%s: Expected %.12f, found %.12f", message, expected, actual),
                Math.abs(actual - expected) < precision ||
                        Math.abs(actual - expected) < precision * Math.abs(actual) ||
                        (Double.isNaN(actual) || Double.isInfinite(actual)) &&
                        (Double.isNaN(expected) || Double.isInfinite(expected))
        );
    }

    public static void checkAssert(final Class<?> c) {
        Locale.setDefault(Locale.US);

        boolean assertsEnabled = false;
        assert assertsEnabled = true;
        if (!assertsEnabled) {
            throw new AssertionError("You should enable assertions by running 'java -ea " + c.getName() + "'");
        }
    }

    public static String repeat(final String s, final int n) {
        return Stream.generate(() -> s).limit(n).collect(Collectors.joining());
    }

    public static <T> T random(final List<T> variants) {
        return variants.get(RNG.nextInt(variants.size()));
    }

    @SafeVarargs
    public static <T> T random(final T... variants) {
        return random(Arrays.asList(variants));
    }

    public static int randomInt(final int n) {
        return RNG.nextInt(n);
    }

    @SafeVarargs
    public static <T> List<T> list(final T... items) {
        return new ArrayList<>(Arrays.asList(items));
    }

    public static void addRange(final List<Integer> values, final int d, final int c) {
        for (int i = -d; i <= d; i++) {
            values.add(c + i);
        }
    }

    public static final class Op<T> {
        public final String name;
        public final T f;

        private Op(final String name, final T f) {
            this.name = name;
            this.f = f;
        }
    }

    public static <T> Op<T> op(final String name, final T f) {
        return new Op<>(name, f);
    }
}
