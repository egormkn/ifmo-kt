package common;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Asserts {
    public Asserts() {
        checkAssert();
    }

    protected static void checkAssert() {
        try {
            assert false;
            System.err.println("Assertions should be enabled");
            System.exit(1);
        } catch (final AssertionError e) {
            // ok
        }
    }

    protected static void assertEquals(final String message, final Object expected, final Object found) {
        assert expected.equals(found) : String.format("%s: expected %s, found %s", message, expected, found);
    }

    protected static void assertTrue(final String message, final boolean value) {
        if (!value) {
            throw new AssertionError(message);
        }
    }
}
