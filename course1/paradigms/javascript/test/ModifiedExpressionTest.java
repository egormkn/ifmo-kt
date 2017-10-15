package test;

import static expression.Util.list;
import static test.Language.expr;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ModifiedExpressionTest extends ExpressionTest {
    protected ModifiedExpressionTest(final boolean hard) {
        super(hard);
        language.binary.addAll(list(
                expr("mod", "%", (a, b) -> a % (double) b),
                expr("power", "**", StrictMath::pow)
        ));
        language.unary.addAll(list(
                expr("abs", "abs", StrictMath::abs),
                expr("log", "log", StrictMath::log)
        ));
        language.tests.addAll(list(
                expr("abs(subtract(variable('x'), variable('y')))", "x y - abs", (x, y, z) -> StrictMath.abs(x - y)),
                expr("log(add(variable('x'), variable('y')))", "x y + log", (x, y, z) -> StrictMath.log(x + y)),
                expr("mod(variable('x'), variable('y'))", "x y %", (x, y, z) -> x % y),
                expr("power(variable('x'), variable('y'))", "x y **", (x, y, z) -> StrictMath.pow(x, y))
        ));
    }

    public static void main(final String[] args) {
        new ModifiedExpressionTest(mode(args, ModifiedExpressionTest.class, "easy", "hard") == 1).test();
    }
}
