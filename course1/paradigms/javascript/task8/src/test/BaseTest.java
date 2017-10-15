package test;

import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.function.BiFunction;
import java.util.function.BinaryOperator;
import java.util.function.UnaryOperator;

import static expression.Util.*;

/**
 * @author Niyaz Nigmatullin
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public abstract class BaseTest<E extends Engine> {
    public static final int N = 5;
    public static final double EPS = 1e-6;

    protected final E engine;
    protected final Language language;

    final boolean testParse;

    protected BaseTest(final E engine, final Language language, final boolean testParsing) {
        this.engine = engine;
        this.language = language;
        this.testParse = testParsing;
    }

    protected void test() {
        for (final Expr<TExpr> test : language.tests) {
            test(test.parsed, test.answer, test.unparsed);
            if (testParse) {
                test(parse(test.unparsed), test.answer, test.unparsed);
                test(parse(language.addSpaces(test.unparsed)), test.answer, test.unparsed);
            }
        }

        testRandom(500, (v, i) -> generate(v, i / 5 + 2));
        System.out.println("OK");
    }

    protected abstract String parse(final String expression);

    protected void test(final String expression, final TExpr f, final String polish) {
        System.out.println("Testing: " + expression);
        test(expression, polish);

        engine.parse(expression);
        for (double i = 1; i <= N; i += 1) {
            for (double j = 1; j <= N; j += 1) {
                for (double k = 1; k <= N; k += 1) {
                    evaluate(new double[]{i, j, k}, f.evaluate(i, j, k), EPS);
                }
            }
        }
    }

    protected void test(final String parsed, final String unparsed) {
    }

    public void testRandom(final int n, final BiFunction<double[], Integer, Expr<Double>> f) {
        System.out.println("Testing random tests");
        for (int i = 0; i < n; i++) {
            if (i % 100 == 0) {
                System.out.println("    Completed " + i + " out of " + n);
            }
            final double[] vars = new double[]{RNG.nextDouble(), RNG.nextDouble(), RNG.nextDouble()};

            final Expr<Double> test = f.apply(vars, i);

            engine.parse(test.parsed);
            evaluate(vars, test.answer, EPS);
            test(test.parsed, test.unparsed);
            test(language.addSpaces(test.parsed), test.unparsed);
            if (testParse) {
                final String expr = parse(test.unparsed);
                test(expr, test.unparsed);

                engine.parse(expr);
                evaluate(vars, test.answer, EPS);
            }
        }
    }

    protected void evaluate(final double[] vars, final double expected, final double precision) {
        final Engine.Result<Number> result = engine.evaluate(vars);
        assertEquals(result.context, precision, result.value.doubleValue(), expected);
    }

    protected Expr<Double> generate(final double[] vars, final int depth) {
        if (depth == 0) {
            if (RNG.nextBoolean()) {
                final int id = randomInt(3);
                final String name = "xyz".charAt(id) + "";
                return language.variable(name, vars[id]);
            } else {
                final int value = RNG.nextInt();
                return language.constant(value, (double) value);
            }
        }
        final int operator = randomInt(6);
        if (operator <= 0) {
            return generateP(vars, depth);
        } else if (operator <= 1) {
            return language.unary(random(language.unary), generateP(vars, depth));
        } else {
            return language.binary(random(language.binary), generateP(vars, depth), generateP(vars, depth));
        }
    }

    protected Expr<Double> generateP(final double[] vars, final int depth) {
        return generate(vars, randomInt(depth));
    }

    public static Dialect dialect(final String variable, final String constant, final String unary, final String binary) {
        return new Dialect(variable, constant, unary, binary);
    }

    public static Ops ops() {
        return new Ops();
    }

    protected static int mode(final String[] args, final Class<?> type, final String... modes) {
        checkAssert(type);

        if (args.length == 0) {
            System.err.println("No arguments found");
        } else if (args.length > 1) {
            System.err.println("Only one argument expected, " + args.length + " found");
        } else if (Arrays.asList(modes).indexOf(args[0]) < 0) {
            System.err.println("First argument should be one of: \"" + String.join("\", \"", modes) + "\", found: \"" + args[0] + "\"");
        } else {
            return Arrays.asList(modes).indexOf(args[0]);
        }
        System.err.println("Usage: java -ea " + type.getName() + " (" + String.join("|", modes) + ")");
        System.exit(0);
        return -1;
    }

    public interface TExpr {
        double evaluate(double x, double y, double z);
    }

    public static class Dialect {
        private final String variable;
        private final String constant;
        private final String unary;
        private final String binary;

        public Dialect(final String variable, final String constant, final String unary, final String binary) {
            this.variable = variable;
            this.constant = constant;
            this.unary = unary;
            this.binary = binary;
        }

        public String variable(final String name) {
            return String.format(variable, name);
        }

        public String constant(final int value) {
            return String.format(constant, value);
        }

        public String unary(final String op, final String a) {
            return String.format(unary, op, a);
        }

        String binary(final String op, final String a, final String b) {
            return String.format(binary, op, a, b);
        }
    }

    public static class Ops {
        final Map<String, Expr<UnaryOperator<Double>>> unary = new HashMap<>();
        final Map<String, Expr<BinaryOperator<Double>>> binary = new HashMap<>();

        public Ops unary(final String name, final String parsed, final String unparsed, final UnaryOperator<Double> answer) {
            unary.put(name, new Expr<>(parsed, unparsed, answer));
            return this;
        }

        public Ops binary(final String name, final String parsed, final String unparsed, final BinaryOperator<Double> answer) {
            binary.put(name, new Expr<>(parsed, unparsed, answer));
            return this;
        }
    }

    public static class Expr<T> {
        public final String parsed;
        public final String unparsed;
        public final T answer;

        protected Expr(final String parsed, final String unparsed, final T answer) {
            this.parsed = parsed;
            this.unparsed = unparsed;
            this.answer = answer;
        }
    }
}
