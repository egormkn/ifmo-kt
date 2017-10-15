package expression.generic;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface Parser<T extends Numeric> {
    TripleExpression<T> parse(String expression) throws ParserException;
}
