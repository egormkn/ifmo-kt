package test;

import static expression.Util.list;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ModifiedPrefixParserTest extends PrefixParserTest {
    public static final Ops OPS = ModifiedObjectExpressionTest.OPS
            .unary("atan", "ArcTan", "atan", StrictMath::atan)
            .unary("exp", "Exp", "exp", StrictMath::exp);

    protected ModifiedPrefixParserTest(final boolean hard) {
        super(hard, new AdvancedLanguage(OBJECT, PREFIX, OPS));
    }

    @Override
    protected void test() {
        super.test();

        printParsingError("Empty input", "");
        printParsingError("Unknown variable", "a");
        printParsingError("Invalid number", "-a");
        printParsingError("Missing )", "(* z (+ x y)");
        printParsingError("Unknown operation", "(@@  x y)");
        printParsingError("Excessive info", "(+ x y) x");
        printParsingError("Invalid unary (0 args)", "(negate)");
        printParsingError("Invalid unary (2 args)", "(negate x y)");
        printParsingError("Invalid binary (0 args)", "(+)");
        printParsingError("Invalid binary (1 args)", "(+ x)");
        printParsingError("Invalid binary (3 args)", "(+ x y z)");
    }

    private void printParsingError(final String description, final String input) {
        final String message = assertParsingError(input, "", "");
        final int index = message.lastIndexOf("in <eval>");
        System.out.format("%-25s: %s\n", description, message.substring(0, index > 0 ? index : message.length()));
    }

    public static void main(final String[] args) {
        final int mode = mode(args, ModifiedPrefixParserTest.class, "easy", "hard");
        new ModifiedPrefixParserTest(mode >= 1).test();
    }

    /**
     * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
     */
    public static class AdvancedLanguage extends ModifiedObjectExpressionTest.SinCosLanguage {
        public AdvancedLanguage(final Dialect parsed, final Dialect unparsed, final Ops ops) {
            super(parsed, unparsed, ops);

            tests.addAll(list(
                    u("exp", b("+", vx, vy)),
                    u("exp", b("/", u("exp", vz), b("+", vx, vy))),
                    u("atan", b("-", vx, vy)),
                    u("exp", b("+", vx, vy)),
                    u("atan", b("/", u("atan", vz), b("+", vx, vy)))
            ));
        }
    }
}
