package test;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStreamReader;
import java.io.UnsupportedEncodingException;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class JSEngine implements Engine {
    private final ScriptEngine engine;
    private final String evaluate;
    private String expression;

    protected String toStringMethod = "toString";

    public JSEngine(final String script, final String evaluate) {
        this.evaluate = evaluate;

        try {
            final ScriptEngineManager factory = new ScriptEngineManager();
            engine = factory.getEngineByName("JavaScript");
            engine.put("io", new IO(engine));
            engine.eval("var println = function() { io.println(Array.prototype.map.call(arguments, String).join(' ')); };");
            engine.eval("var print   = function() { io.print  (Array.prototype.map.call(arguments, String).join(' ')); };");
            engine.eval("var include = function(file) { io.include(file); }");
            engine.eval("var expr;");
        } catch (final ScriptException e) {
            throw new EngineException("Invalid initialization", e);
        }

        try {
            engine.eval(new InputStreamReader(new FileInputStream(script), "UTF-8"));
        } catch (final ScriptException e) {
            throw new EngineException("Script error", e);
        } catch (final UnsupportedEncodingException e) {
            throw new EngineException("Fail", e);
        } catch (final FileNotFoundException e) {
            throw new EngineException("Script not found", e);
        }
    }

    @Override
    public void parse(final String expression) {
        try {
            engine.eval("expr = " + expression);
            this.expression = expression;
        } catch (final ScriptException e) {
            throw new EngineException("Script error", e);
        }
    }

    private <T> Result<T> evaluate(final String code, final Class<T> token) {
        final String context = String.format("\n    in %s\n    where expr = %s\n", code, expression);
        try {
            final Object result = engine.eval(code);
            if (token.isAssignableFrom(result.getClass())) {
                return new Result<T>(context, token.cast(result));
            }
            throw new EngineException(String.format(
                    "Expected %s, found \"%s\" (%s)%s",
                    token.getClass().getSimpleName(),
                    result,
                    result.getClass().getSimpleName(),
                    context
            ), null);
        } catch (final ScriptException e) {
            throw new EngineException("No error expected" + context, e);
        }
    }

    @Override
    public Result<Number> evaluate(final double[] vars) {
        final String code = String.format("expr%s(%.20f, %.20f, %.20f);", this.evaluate, vars[0], vars[1], vars[2]);
        return evaluate(code, Number.class);
    }

    @Override
    public Result<String> parsedToString() {
        return evaluate("expr." + toStringMethod + "()", String.class);
    }

    public static class IO {
        private final ScriptEngine engine;
        public IO(final ScriptEngine engine) {
            this.engine = engine;
        }

        public void print(final String message) {
            System.out.print(message);
        }

        public void println(final String message) {
            System.out.println(message);
        }

        public void include(final String file) throws Exception {
            engine.eval(new InputStreamReader(new FileInputStream(file), "UTF-8"));
        }
    }
}
