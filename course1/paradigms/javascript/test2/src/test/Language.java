package test;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.function.BinaryOperator;
import java.util.function.UnaryOperator;

import static expression.Util.randomInt;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Language {
    private final BaseTest.Dialect parsed;
    private final BaseTest.Dialect unparsed;

    protected final List<BaseTest.Expr<UnaryOperator<Double>>> unary = new ArrayList<>();
    protected final List<BaseTest.Expr<BinaryOperator<Double>>> binary = new ArrayList<>();
    private final Map<String, BaseTest.Expr<UnaryOperator<Double>>> us;
    final Map<String, BaseTest.Expr<BinaryOperator<Double>>> bs;

    protected List<BaseTest.Expr<BaseTest.TExpr>> tests = new ArrayList<>();

    protected final BaseTest.Expr<BaseTest.TExpr> vx;
    protected final BaseTest.Expr<BaseTest.TExpr> vy;
    protected final BaseTest.Expr<BaseTest.TExpr> vz;

    public Language(final BaseTest.Dialect parsed, final BaseTest.Dialect unparsed, final BaseTest.Ops ops) {
        this.parsed = parsed;
        this.unparsed = unparsed;

        us = ops.unary;
        bs = ops.binary;
        unary.addAll(us.values());
        binary.addAll(bs.values());

        vx = variable("x", (x, y, z) -> x);
        vy = variable("y", (x, y, z) -> y);
        vz = variable("z", (x, y, z) -> z);
    }

    private boolean safe(final char ch) {
        return !Character.isLetterOrDigit(ch) && "+-*/.".indexOf(ch) == -1;
    }

    protected String addSpaces(final String expression) {
        String spaced = expression;
        for (int n = StrictMath.min(10, 200 / expression.length()); n > 0;) {
            final int index = randomInt(spaced.length() + 1);
            final char c = index == 0 ? 0 : spaced.charAt(index - 1);
            final char nc = index == spaced.length() ? 0 : spaced.charAt(index);
            if ((safe(c) || safe(nc)) && c != '\'' && nc != '\'' && c != '"' && nc != '"') {
                spaced = spaced.substring(0, index) + " " + spaced.substring(index);
                n--;
            }
        }
        return spaced;
    }

    protected <T> BaseTest.Expr<T> variable(final String name, final T answer) {
        return expr(parsed.variable(name), unparsed.variable(name), answer);
    }

    protected <T> BaseTest.Expr<T> constant(final int value, final T answer) {
        return expr(parsed.constant(value), unparsed.constant(value), answer);
    }

    protected <T> BaseTest.Expr<T> unary(final BaseTest.Expr<UnaryOperator<T>> op, final BaseTest.Expr<T> arg) {
        return expr(
                parsed.unary(op.parsed, arg.parsed),
                unparsed.unary(op.unparsed, arg.unparsed),
                op.answer.apply(arg.answer)
        );
    }

    protected <T> BaseTest.Expr<T> binary(final BaseTest.Expr<BinaryOperator<T>> op, final BaseTest.Expr<T> t1, final BaseTest.Expr<T> t2) {
        return expr(
                parsed.binary(op.parsed, t1.parsed, t2.parsed),
                unparsed.binary(op.unparsed, t1.unparsed, t2.unparsed),
                op.answer.apply(t1.answer, t2.answer)
        );
    }

    protected BaseTest.Expr<BaseTest.TExpr> constant(final int value) {
        return constant(value, (x, y, z) -> value);
    }

//    private List<Expr<TExpr>> next(final List<Expr<TExpr>> prev) {
//        final List<Expr<TExpr>> next = new ArrayList<>(prev);
//        for (final Expr<BinaryOperator<Double>> op : binary) {
//            for (final Expr<TExpr> a : prev) {
//                for (final Expr<TExpr> b : prev) {
//                    next.add(liftBinary(op, a, b));
//                }
//            }
//        }
//        for (final Expr<UnaryOperator<Double>> op : unary) {
//            for (final Expr<TExpr> a : prev) {
//                next.add(liftUnary(op, a));
//            }
//        }
//        return next;
//    }

    protected BaseTest.Expr<BaseTest.TExpr> u(final String name, final BaseTest.Expr<BaseTest.TExpr> a) {
        final BaseTest.Expr<UnaryOperator<Double>> op = us.get(name);
        final UnaryOperator<BaseTest.TExpr> t = q -> (x, y, z) -> op.answer.apply(q.evaluate(x, y, z));
        return unary(expr(op.parsed, op.unparsed, t), a);
    }

    protected BaseTest.Expr<BaseTest.TExpr> b(final String name, final BaseTest.Expr<BaseTest.TExpr> a, final BaseTest.Expr<BaseTest.TExpr> b) {
        final BaseTest.Expr<BinaryOperator<Double>> op = bs.get(name);
        final BinaryOperator<BaseTest.TExpr> t = (q, r) -> (x, y, z) -> op.answer.apply(q.evaluate(x, y, z), r.evaluate(x, y, z));
        return binary(expr(op.parsed, op.unparsed, t), a, b);
    }

    public static <T> BaseTest.Expr<T> expr(final String parsed, final String unparsed, final T answer) {
        return new BaseTest.Expr<>(parsed, unparsed, answer);
    }
}
