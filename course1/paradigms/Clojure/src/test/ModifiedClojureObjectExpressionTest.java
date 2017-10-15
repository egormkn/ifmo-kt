package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ModifiedClojureObjectExpressionTest extends ClojureObjectExpressionTest {
    protected ModifiedClojureObjectExpressionTest(final boolean testMultiarg) {
        super(new ModifiedObjectExpressionTest.SinCosLanguage(UNPARSED, PARSED, ModifiedObjectExpressionTest.OPS), testMultiarg);
    }

    public static void main(final String... args) {
        new ModifiedClojureObjectExpressionTest(mode(args, ModifiedClojureObjectExpressionTest.class, "easy", "hard") == 1).test();
    }
}

