package expression.exceptions;

import expression.Either;
import expression.TripleExpression;
import expression.Variable;

import java.util.ArrayList;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.BinaryOperator;
import java.util.function.LongBinaryOperator;
import java.util.function.UnaryOperator;

import static expression.Util.*;

/**
 * @author Niyaz Nigmatullin
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ExceptionsTest {
    private static long total;

    protected final List<Op<UnaryOperator<Long>>> unary = new ArrayList<>();
    protected final List<List<Op<BinaryOperator<Long>>>> levels = new ArrayList<>();
    protected List<Op<TExpression>> tests;

    private final static int D = 5;
    private final static List<Integer> VALUES = new ArrayList<>();
    private final char[] CHARS = "AZ-+*%()[]".toCharArray();

    static {
        addRange(VALUES, D, Integer.MIN_VALUE + D);
        addRange(VALUES, D, Integer.MIN_VALUE / 2);
        addRange(VALUES, D, (int) -Math.sqrt(Integer.MAX_VALUE));
        addRange(VALUES, D, 0);
        addRange(VALUES, D, (int) Math.sqrt(Integer.MAX_VALUE));
        addRange(VALUES, D, Integer.MAX_VALUE / 2);
        addRange(VALUES, D, Integer.MAX_VALUE - D);
    }

    private int subtests = 0;

    private final List<Op<String>> parsingTest = list(
            op("No first argument", "* y * z"),
            op("No middle argument", "x *  * z"),
            op("No last argument", "x * y * "),
            op("No opening parenthesis", "x * y)"),
            op("No closing parenthesis", "(x * y"),
            op("Start symbol", "@x * y"),
            op("Middle symbol", "x @ * y"),
            op("End symbol", "x * y@"),
            op("Constant overflow", "1000000000000000000000")
    );

    protected ExceptionsTest() {
        unary.add(op("-", a -> -a));

        levels.add(list(
                op("+", (a, b) -> a + b),
                op("-", (a, b) -> a - b)
        ));
        levels.add(list(
                op("*", (a, b) -> a * b),
                op("/", (a, b) -> b == 0 ? null : a / b)
        ));

        tests = list(
                op("10", (x, y, z) -> 10L),
                op("x", (x, y, z) -> x),
                op("y", (x, y, z) -> y),
                op("z", (x, y, z) -> z),
                op("x+2", (x, y, z) -> x + 2),
                op("2-y", (x, y, z) -> 2 - y),
                op("  3*  z  ", (x, y, z) -> 3 * z),
                op("x/  -  2", (x, y, z) -> -x / 2),
                op("x*y+(z-1   )/10", (x, y, z) -> x * y + (z - 1) / 10),
                op("-(-(-\t\t-5 + 16   *x*y) + 1 * z) -(((-11)))", (x, y, z) -> -(-(5 + 16 * x * y) + z) + 11),
                op("" + Integer.MAX_VALUE, (x, y, z) -> (long) Integer.MAX_VALUE),
                op("" + Integer.MIN_VALUE, (x, y, z) -> (long) Integer.MIN_VALUE),
                op("x--y--z", (x, y, z) -> x + y + z),
                op("((2+2))-0/(--2)*555", (x, y, z) -> 4L),
                op("x-x+y-y+z-(z)", (x, y, z) -> 0L),
                op(repeat("(", 500) + "x + y + (-10*-z)" + repeat(")", 500), (x, y, z) -> x + y + 10 * z)
        );
    }

    public static void main(final String[] args) {
        checkAssert(ExceptionsTest.class);
        new ExceptionsTest().test();
    }

    private void testParsing() {
        for (final Op<String> op : parsingTest) {
            try {
                new ExpressionParser().parse(op.f);
                assert false : "Successfully parsed " + op.f;
            } catch (final Exception e) {
                System.out.format("%-30s %s", op.name, e.getClass().getSimpleName() + ": " + e.getMessage());
                System.out.println();
            }
        }
    }

    private void testOverflow() {
        final Variable vx = new Variable("x");
        final Variable vy = new Variable("y");

        check((a, b) -> a + b, "+", new CheckedAdd(vx, vy));
        check((a, b) -> a - b, "-", new CheckedSubtract(vx, vy));
        check((a, b) -> a * b, "*", new CheckedMultiply(vx, vy));
        check((a, b) -> b == 0 ? Long.MAX_VALUE : a / b, "/", new CheckedDivide(vx, vy));
        check((a, b) -> -b, "<- ignore first argument, unary -", new CheckedNegate(vy));

        System.out.println("OK, " + subtests + " subtests");
    }

    private void check(final LongBinaryOperator f, final String op, final TripleExpression expression) {
        for (final int a : VALUES) {
            for (final int b : VALUES) {
                final long expected = f.applyAsLong(a, b);
                try {
                    final int actual = expression.evaluate(a, b, 0);
                    assert actual == expected : a + " " + op + " " + b + " == " + actual;
                } catch (final Exception e) {
                    if (Integer.MIN_VALUE <= expected && expected <= Integer.MAX_VALUE) {
                        throw new AssertionError("Unexpected error in " + a + " " + op + " " + b, e);
                    }
                }
                assert ++subtests > 0;
            }
        }
    }

    protected Either<Reason, Integer> lift(final Long value) {
        return value == null ? Either.left(Reason.DBZ)
                : value < Integer.MIN_VALUE || Integer.MAX_VALUE < value ? Either.left(Reason.OVERFLOW)
                : Either.right(value.intValue());
    }


    private TripleExpression parse(final String expression) {
        final Parser parser = new ExpressionParser();
        if (expression.length() > 10) {
            loop: for (final char ch : CHARS) {
                for (int i = 0; i < 10; i++) {
                    final int index = 1 + randomInt(expression.length() - 2);
                    final char c = expression.charAt(index);
                    if ("-( *".indexOf(c) < 0 && !Character.isLetterOrDigit(c)) {
                        final String input = expression.substring(0, index) + ch + expression.substring(index);
                        try {
                            parser.parse(input);
                            throw new AssertionError("Parsing error expected for " + expression.substring(0, index) + "<ERROR_INSERTED -->" + ch + expression.substring(index));
                        } catch (final Exception e) {
                            // Ok
                        }
                        continue loop;
                    }
                }
            }
        }
        try {
            return parser.parse(expression);
        } catch (final Exception e) {
            throw new AssertionError("Parser failed", e);
        }
    }


    private enum Reason {
        DBZ, OVERFLOW
    }

    protected interface TExpression {
        Long evaluate(long x, long y, long z);
    }

    protected void test() {
        testOverflow();

        for (final Op<TExpression> test : tests) {
            System.out.println("Testing: " + test.name);
            final TripleExpression expression = parse(test.name);
            for (int i = 0; i < 10; i++) {
                for (int j = 0; j < 10; j++) {
                    for (int k = 0; k < 10; k++) {
                        check(new int[]{i, j, k}, expression, lift(test.f.evaluate(i, j, k)));
                    }
                }
            }
        }

        testRandom(1, 2000, (v, i) -> generate(v, i / 5 + 2));
        testRandom(2, 777, (v, i) -> genExpression(1, i / 25 / levels.size() + 1, v, 0));
        testParsing();

        System.out.println(total);
        System.out.println("OK");
    }

    private void testRandom(final int seq, final int n, final BiFunction<int[], Integer, Test> f) {
        System.out.println("Testing random tests #" + seq);
        for (int i = 0; i < n; i++) {
            if (i % 100 == 0) {
                System.out.println("Completed " + i + " out of " + n);
            }
            final int[] vars = new int[]{RNG.nextInt(), RNG.nextInt(), RNG.nextInt()};

            final Test test = f.apply(vars, i);
            try {
                total += test.expr.length();
                check(vars, parse(test.expr), test.answer);
            } catch (final Throwable e) {
                System.out.println("Failed test: " + test.expr);
                throw e;
            }
        }
    }

    private void check(final int[] vars, final TripleExpression expression, final Either<Reason, Integer> answer) {
        try {
            final int actual = expression.evaluate(vars[0], vars[1], vars[2]);
            assertTrue(String.format("Error expected x = %d, y=%d, z=%d", vars[0], vars[1], vars[2]), !answer.isLeft());
            assertEquals(String.format("f(%d, %d, %d)\n%s", vars[0], vars[1], vars[2], expression), actual, (int) answer.getRight());
        } catch (final Exception e) {
            if (!answer.isLeft()) {
                throw new AssertionError(String.format("No error expected for x = %d, y=%d, z=%d", vars[0], vars[1], vars[2]), e);
            }
        }
    }

    private Test generate(final int[] vars, final int depth) {
        if (depth == 0) {
            return constOrVariable(vars);
        }
        final int operator = randomInt(6);
        if (operator <= 0) {
            return genP(vars, depth);
        } else if (operator <= 1) {
            return unary(genP(vars, depth));
        } else {
            return binary(random(levels), genP(vars, depth), genP(vars, depth));
        }
    }

    private Test genP(final int[] vars, final int depth) {
        return p(generate(vars, randomInt(depth)));
    }

    private static Test constOrVariable(final int[] vars) {
        if (RNG.nextBoolean()) {
            final int id = randomInt(3);
            return new Test("xyz".charAt(id) + "", Either.right(vars[id]));
        } else {
            final int value = RNG.nextInt();
            return new Test(value + "", Either.right(value));
        }
    }

    private Test genExpression(final int depth, final int coefficient, final int[] vars, final int level) {
        if (level == levels.size()) {
            return genFactor(depth, coefficient, vars);
        } else if (makeNewBranch(depth, coefficient)) {
            return binary(levels.get(level), genExpression(depth + 1, coefficient, vars, level), genExpression(depth, coefficient, vars, level + 1));
        } else {
            return genExpression(depth, coefficient, vars, level + 1);
        }
    }

    private Test genFactor(final int depth, final int coefficient, final int[] vars) {
        if (makeNewBranch(depth, coefficient)) {
            return unary(genFactor(depth + 1, coefficient, vars));
        } else {
            return genValue(depth, coefficient, vars);
        }
    }

    private static Test p(final Test t) {
        return new Test("("  + t.expr + ")", t.answer);
    }

    private Test binary(final List<Op<BinaryOperator<Long>>> ops, final Test t1, final Test t2) {
        final Op<BinaryOperator<Long>> op = random(ops);
        return new Test(
                t1.expr + op.name + t2.expr,
                t1.answer.flatMapRight(a -> t2.answer.mapRight(b -> op.f.apply((long) a, (long) b)).flatMapRight(this::lift))
        );
    }

    private Test unary(final Test arg) {
        final Op<UnaryOperator<Long>> op = random(unary);
        return new Test(op.name + " " + arg.expr, arg.answer.mapRight(a -> op.f.apply((long) a)).flatMapRight(this::lift));
    }

    private Test genValue(final int depth, final int coefficient, final int[] vars) {
        if (makeNewBranch(depth, coefficient)) {
            return p(genExpression(depth + 1, coefficient, vars, 0));
        } else {
            return constOrVariable(vars);
        }
    }

    private static boolean makeNewBranch(final int depth, final int coefficient) {
        return randomInt(depth + coefficient) < coefficient;
    }

    private static class Test {
        final String expr;
        final Either<Reason, Integer> answer;

        Test(final String expr, final Either<Reason, Integer> answer) {
            this.expr = expr;
            this.answer = answer;
        }
    }
}
