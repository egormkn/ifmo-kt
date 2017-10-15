package test;

import static expression.Util.list;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ExpressionTest extends BaseTest<Engine> {
    public static final Dialect FUNCTIONS = dialect("variable('%s')", "cnst(%s)", "%s(%s)", "%s(%s, %s)");
    public static final Dialect POLISH = dialect("%s", "%s", "%2$s %1$s", "%2$s %3$s %1$s");

    public static final Ops OPS = ops()
            .binary("+", "add", "+", (a, b) -> a + b)
            .binary("-", "subtract", "-", (a, b) -> a - b)
            .binary("*", "multiply", "*", (a, b) -> a * b)
            .binary("/", "divide", "/", (a, b) -> a / b)
            .unary("negate", "negate", "negate", a -> -a);

    public ExpressionTest(final Engine engine, final Dialect parsed, final Dialect unparsed, final boolean testParsing) {
        super(engine, new ArithmeticLanguage(parsed, unparsed, OPS), testParsing);
    }

    protected ExpressionTest(final boolean testParsing) {
        this(new JSEngine("expression.js", ""), FUNCTIONS, POLISH, testParsing);
    }

    @Override
    protected String parse(final String expression) {
        return "parse('" + expression + "')";
    }

    public static void main(final String... args) {
        new ExpressionTest(mode(args, ExpressionTest.class, "easy", "hard") == 1).test();
    }

    public static class ArithmeticLanguage extends Language {
        public ArithmeticLanguage(final Dialect parsed, final Dialect unparsed, final Ops ops) {
            super(parsed, unparsed, ops);
            tests.addAll(list(
                    constant(10),
                    vx,
                    vy,
                    vz,
                    b("+", vx, constant(2)),
                    b("-", constant(3), vy),
                    b("*", constant(4), vz),
                    b("/", constant(5), vz),
                    b("/", u("negate", vx), constant(2)),
                    b("/", vx, b("*", vy, vz)),
                    b("+", b("+", b("*", vx, vx), b("*", vy, vy)), b("*", vz, vz)),
                    b("-", b("+", b("*", vx, vx), b("*", constant(5), b("*", vz, b("*", vz, vz)))), b("*", vy, constant(8)))
            ));
        }
    }
}
