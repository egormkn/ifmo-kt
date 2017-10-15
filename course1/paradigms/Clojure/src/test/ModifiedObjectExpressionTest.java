package test;

import static expression.Util.list;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ModifiedObjectExpressionTest extends ObjectExpressionTest {
    public static final Ops OPS = ObjectExpressionTest.OPS
            .unary("sin", "Sin", "sin", StrictMath::sin)
            .unary("cos", "Cos", "cos", StrictMath::cos);

    protected ModifiedObjectExpressionTest(final boolean hard, final boolean bonus) {
        super(hard, bonus, new SinCosLanguage(OBJECT, ExpressionTest.POLISH, OPS));
        simplifications.addAll(list(
                new int[]{9, 14, 1},
                new int[]{16, 16, 1},
                new int[]{55, 55, 56}
        ));
    }

    public static void main(final String[] args) {
        final int mode = mode(args, ModifiedObjectExpressionTest.class, "easy", "hard", "bonus");
        new ModifiedObjectExpressionTest(mode >= 1, mode >= 2).test();
    }

    public static class SinCosLanguage extends ExpressionTest.ArithmeticLanguage {
        public SinCosLanguage(final Dialect parsed, final Dialect unparsed, final Ops ops) {
            super(parsed, unparsed, ops);

            tests.addAll(list(
                    u("sin", b("-", vx, vy)),
                    u("cos", b("+", vx, vy)),
                    u("cos", b("/", u("sin", vz), b("+", vx, vy)))
            ));
        }
    }
}
