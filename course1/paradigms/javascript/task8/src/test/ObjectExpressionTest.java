package test;

import java.util.List;

import static expression.Util.*;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ObjectExpressionTest extends BaseTest<JSEngine> {
    public static final Dialect OBJECT = dialect("new Variable('%s')", "new Const(%s)", "new %s(%s)", "new %s(%s, %s)");
    public static final Ops OPS = ops()
            .binary("+", "Add", "+", (a, b) -> a + b)
            .binary("-", "Subtract", "-", (a, b) -> a - b)
            .binary("*", "Multiply", "*", (a, b) -> a * b)
            .binary("/", "Divide", "/", (a, b) -> a / b)
            .unary("negate", "Negate", "negate", a -> -a);
    public final double D = 1e-4;

    final List<int[]> simplifications = list(
            new int[]{1, 1, 1},
            new int[]{1, 1, 1},
            new int[]{1, 1, 1},
            new int[]{1, 1, 1},
            new int[]{1, 1, 1},
            new int[]{1, 2, 1},
            new int[]{1, 1, 1},
            new int[]{1, 1, 10},
            new int[]{4, 1, 1},
            new int[]{21, 28, 28},
            new int[]{5, 5, 5},
            new int[]{5, 2, 21}
    );

    protected final boolean testSimplify;

    protected ObjectExpressionTest(final boolean hard, final boolean testSimplify, final Dialect unparsed) {
        this(hard, testSimplify, new ExpressionTest.ArithmeticLanguage(OBJECT, unparsed, OPS));
    }

    protected ObjectExpressionTest(final boolean testParsing, final boolean testSimplify, final Language language) {
        super(new JSEngine("objectExpression.js", ".evaluate"), language, testParsing);
        this.testSimplify = testSimplify;
    }

    @Override
    protected void test() {
        super.test();

        if (testParse) {
            for (final Expr<TExpr> test : language.tests) {
                testDiff(test, test.parsed, null);
                testDiff(test, parse(test.unparsed), null);
            }
            if (testSimplify) {
                for (int i = 0; i < simplifications.size(); i++) {
                    final Expr<TExpr> test = language.tests.get(i);
                    testDiff(test, parse(test.unparsed), simplifications.get(i));
                }
            }
        }
    }

    private void testDiff(final Expr<TExpr> test, final String expression, final int[] simplifications) {
        for (int variable = 0; variable < 3; variable++) {
            final String s = expression + ".diff('" + "xyz".charAt(variable) + "')";
            final String value = s + (simplifications != null ? ".simplify()" : "");
            System.out.println("Testing: " + value);
            engine.parse(value);
            if (simplifications != null) {
                final Engine.Result<String> result = engine.parsedToString();
                final int length = result.value.length();
                final int expected = simplifications[variable];
                assertTrue("Simplified length too long: " + length + " instead of " + expected + result.context, length <= expected);
            }
            for (int i = 1; i <= N; i += 1) {
                final double di = variable == 0 ? D : 0;
                for (int j = 1; j <= N; j += 1) {
                    final double dj = variable == 1 ? D : 0;
                    for (int k = 1; k <= N; k += 1) {
                        final double dk = variable == 2 ? D : 0;
                        final double expected = (test.answer.evaluate(i + di, j + dj, k + dk) - test.answer.evaluate(i - di, j - dj, k - dk)) / D / 2;
                        evaluate(new double[]{i, j, k}, expected, 1e-5);
                    }
                }
            }
        }
    }

    @Override
    protected String parse(final String expression) {
        return "parse('" + expression + "')";
    }

    @Override
    protected void test(final String parsed, final String unparsed) {
        testToString(parsed, unparsed);

        testToString(language.addSpaces(parsed), unparsed);
    }

    private void testToString(final String expression, final String expected) {
        engine.parse(expression);
        final Engine.Result<String> result = engine.parsedToString();
        assertEquals(result.context, result.value, expected);
    }

    public static void main(final String... args) {
        final int mode = mode(args, ObjectExpressionTest.class, "easy", "hard", "bonus");
        new ObjectExpressionTest(mode >= 1, mode >= 2, ExpressionTest.POLISH).test();
    }
}
