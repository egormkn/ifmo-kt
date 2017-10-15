package test;

import clojure.java.api.Clojure;
import clojure.lang.IFn;

import java.util.Optional;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ClojureEngine implements Engine {
    public static final IFn HASH_MAP = Clojure.var("clojure.core", "hash-map");
    public static final IFn EVAL = Clojure.var("clojure.core", "eval");

    private final Optional<IFn> evaluate;
    private final IFn toString;
    private final String evaluateString;
    private IFn parsed;
    private String expression;

    public ClojureEngine(final String script, final Optional<String> evaluate) {
        Clojure.var("clojure.core", "load-file").invoke(script);

        this.evaluate = evaluate.map(n -> Clojure.var("clojure.core", n));
        this.evaluateString = evaluate.map(s -> s + " ").orElse("");
        this.toString = Clojure.var("clojure.core", "toString");
    }

    private <T> Result<T> invoke(final IFn f, final Object[] args, final Class<T> token, final String context) {
        final Object result;
        try {
            result = args.length == 1 ? f.invoke(args[0]) : f.invoke(args[0], args[1]);
        } catch (final Throwable e) {
            throw new EngineException("No error expected in " + context, e);
        }
        if (result == null) {
            throw new EngineException(String.format("Expected %s, found null\n%s", token.getSimpleName(), context), null);
        }
        if (!token.isAssignableFrom(result.getClass())) {
            throw new EngineException(String.format("Expected %s, found %s (%s)\n%s", token.getSimpleName(), result, result.getClass().getSimpleName(), context), null);
        }
        return new Result<>(context, token.cast(result));
    }

    @Override
    public void parse(final String expression) {
        parsed = invoke(EVAL, new Object[]{Clojure.read(expression)}, IFn.class, expression).value;
        this.expression = expression;
    }

    @Override
    public Result<Number> evaluate(final double[] vars) {
        final Object map = HASH_MAP.invoke("x", vars[0], "y", vars[1], "z", vars[2]);
        final String context = String.format("(%sexpr %s)\nwhere expr = %s", evaluateString, map, expression);
        if (evaluate.isPresent()) {
            return invoke( evaluate.get(), new Object[]{parsed, map}, Number.class, context );
        } else {
            return invoke(parsed, new Object[]{map}, Number.class, context);
        }
    }

    @Override
    public Result<String> parsedToString() {
        return invoke(toString, new Object[]{parsed}, String.class, String.format("(toString expr)\nwhere expr = %s", expression));
    }
}
