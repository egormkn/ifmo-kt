package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public interface Engine {
    void parse(String expression);

    Result<Number> evaluate(double[] vars);

    Result<String> parsedToString();

    class Result<T> {
        final String context;
        final T value;

        public Result(final String context, final T value) {
            this.context = context;
            this.value = value;
        }
    }
}
