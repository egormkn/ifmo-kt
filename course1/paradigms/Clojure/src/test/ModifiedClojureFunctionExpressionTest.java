package test;

import java.util.Optional;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ModifiedClojureFunctionExpressionTest extends ClojureFunctionExpressionTest {
    public static final Ops OPS = ExpressionTest.OPS
            .unary("sin", "sin", "sin", StrictMath::sin)
            .unary("cos", "cos", "cos", StrictMath::cos);

    protected ModifiedClojureFunctionExpressionTest(final boolean testMultiarg) {
        super(
                new ModifiedObjectExpressionTest.SinCosLanguage(UNPARSED, PARSED, OPS),
                testMultiarg,
                Optional.<String>empty()
        );
    }

    public static void main(final String... args) {
        new ModifiedClojureFunctionExpressionTest(mode(args, ModifiedClojureFunctionExpressionTest.class, "easy", "hard") == 1).test();
    }
}